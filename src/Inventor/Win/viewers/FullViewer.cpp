/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

// ************************************************************************

// Class is documented in common/viewers/SoGuiFullViewer.cpp.in.

// *************************************************************************

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/threads/SbStorage.h>

#include <sowindefs.h>
#include <Inventor/Win/Win32API.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/widgets/SoWinBitmapButton.h>
#include <Inventor/Win/widgets/WinNativePopupMenu.h>
#include <Inventor/Win/viewers/SoWinFullViewer.h>
#include <Inventor/Win/viewers/SoWinFullViewerP.h>

#include <float.h> // FLT_MAX

// Button icons.
#include <Inventor/Win/common/pixmaps/pick.xpm>
#include <Inventor/Win/common/pixmaps/view.xpm>
#include <Inventor/Win/common/pixmaps/home.xpm>
#include <Inventor/Win/common/pixmaps/set_home.xpm>
#include <Inventor/Win/common/pixmaps/view_all.xpm>
#include <Inventor/Win/common/pixmaps/seek.xpm>

static const int DECORATION_SIZE = 30;
static const int DECORATION_BUFFER = 5;

#define PRIVATE(o) (o->pimpl)
#define PUBLIC(o) (o->pub)

// *************************************************************************

SOWIN_OBJECT_ABSTRACT_SOURCE(SoWinFullViewer);

// *************************************************************************

static void hookhandle_constructor(void * closure)
{
  HHOOK * hookhandle = (HHOOK *) closure;
  *hookhandle = NULL;
}

static void hookhandle_destructor(void *)
{
  
}

ATOM SoWinFullViewerP::decorationsWndClassAtom = NULL;

SoWinFullViewer::SoWinFullViewer(HWND parent,
                                 const char * name,
                                 SbBool embedded,
                                 BuildFlag flag,
                                 SoWinViewer::Type type,
                                 SbBool build) :
  inherited(parent, name, embedded, type, FALSE)
{
  SoWinFullViewerP::nrinstances++;
  this->pimpl = new SoWinFullViewerP(this);


  if (SoWinFullViewerP::hookhandle == NULL) {
    SoWinFullViewerP::hookhandle = new SbStorage(sizeof(HHOOK),
                                                 hookhandle_constructor,
                                                 hookhandle_destructor);
  }

  HHOOK * hookhandle = (HHOOK *) SoWinFullViewerP::hookhandle->get();
  if (!(*hookhandle)) {
    *hookhandle = Win32::SetWindowsHookEx(WH_CALLWNDPROC,
                                          (HOOKPROC)SoWinFullViewerP::systemEventHook,
                                          NULL, GetCurrentThreadId());
  }

  if (SoWinFullViewerP::parentHWNDmappings == NULL) {
    SoWinFullViewerP::parentHWNDmappings = new SbDict;
  }

  PRIVATE(this)->viewerwidget = NULL;
  PRIVATE(this)->renderareawidget = NULL;

  PRIVATE(this)->menuenabled = (flag & SoWinFullViewer::BUILD_POPUP) ? TRUE : FALSE;
  PRIVATE(this)->decorations = (flag & SoWinFullViewer::BUILD_DECORATION) ? TRUE : FALSE;

  this->prefmenu = NULL;

  PRIVATE(this)->leftthumbwheel = NULL;
  PRIVATE(this)->bottomthumbwheel = NULL;
  PRIVATE(this)->rightthumbwheel = NULL;
  this->leftWheel = NULL;
  this->bottomWheel = NULL;
  this->rightWheel = NULL;
  this->rightWheelStr = NULL;

  // Let these be bogus until we actually set up the wheels.
  this->leftWheelVal = FLT_MAX;
  this->bottomWheelVal = FLT_MAX;
  this->rightWheelVal = FLT_MAX;

  if (build) {
    this->setClassName("SoWinFullViewer");
    this->setBaseWidget(this->buildWidget(this->getParentWidget()));
  }

  /* FIXME: We should use the actual size of the parent window instead
     of hardcoding the size here, at least if the size of the parent
     window is reasonable. See also
     SoWinExaminerViewerP::constructor(). 2004-01-08 thammer.  
  */
  RECT rect = {0, 0, 500, 420};
  if (this->getParentWidget())
    Win32::GetWindowRect(this->getParentWidget(), & rect);

  this->setSize(SbVec2s((short)(rect.right-rect.left), (short)(rect.bottom-rect.top)));

  if (! this->isViewing())
    this->setViewing(TRUE);
}

SoWinFullViewer::~SoWinFullViewer()
{
  (void)SoWinFullViewerP::parentHWNDmappings->remove((SbDict::Key)this->getParentWidget());

  SoWinFullViewerP::nrinstances--;
  if (SoWinFullViewerP::nrinstances == 0) {
    // Parent HWND -> SoWinFullViewer dict.
    delete SoWinFullViewerP::parentHWNDmappings;
    SoWinFullViewerP::parentHWNDmappings = NULL;

    HHOOK * hookhandle = (HHOOK *) SoWinFullViewerP::hookhandle->get();
    if (*hookhandle) {
      Win32::UnhookWindowsHookEx(*hookhandle);
    }

    delete SoWinFullViewerP::hookhandle;
    SoWinFullViewerP::hookhandle = NULL;

  }
  
  delete this->prefmenu;

  delete PRIVATE(this);

  if (IsWindow(this->leftWheelLabel))
    Win32::DestroyWindow(this->leftWheelLabel);
  if (IsWindow(this->bottomWheelLabel))
    Win32::DestroyWindow(this->bottomWheelLabel);
  if (IsWindow(this->rightWheelLabel))
    Win32::DestroyWindow(this->rightWheelLabel);
  if (IsWindow(this->leftDecoration))
    Win32::DestroyWindow(this->leftDecoration);
  if (IsWindow(this->bottomDecoration))
    Win32::DestroyWindow(this->bottomDecoration);
  if (IsWindow(this->rightDecoration))
    Win32::DestroyWindow(this->rightDecoration);

  delete [] this->rightWheelStr;
  this->rightWheelStr = NULL;

  if (SoWinFullViewerP::nrinstances == 0) {
    if (SoWinFullViewerP::decorationsWndClassAtom)
      Win32::UnregisterClass("Decorations Widget", NULL);
    SoWinFullViewerP::decorationsWndClassAtom = NULL;
  }
}

void
SoWinFullViewer::setDecoration(SbBool enable)
{
#if SOWIN_DEBUG
  if ((enable && this->isDecoration()) ||
       (! enable && ! this->isDecoration())) {
    SoDebugError::postWarning("SoWinFullViewer::setDecoration",
                               "decorations already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOWIN_DEBUG

  PRIVATE(this)->decorations = enable;
  PRIVATE(this)->showDecorationWidgets(enable);

  // reposition all widgets
  RECT rect;
  Win32::GetClientRect(this->getParentWidget(), & rect);

  this->sizeChanged(SbVec2s((short)rect.right, (short)rect.bottom));
}

SbBool
SoWinFullViewer::isDecoration(void) const
{
  return PRIVATE(this)->decorations;
}

void
SoWinFullViewer::setPopupMenuEnabled(SbBool enable)
{
#if SOWIN_DEBUG
  if ((enable && this->isPopupMenuEnabled()) ||
       (! enable && ! this->isPopupMenuEnabled())) {
    SoDebugError::postWarning("SoWinFullViewer::setPopupMenuEnabled",
                               "popup menu already turned %s",
                               enable ? "on" : "off");
    return;
  }
#endif // SOWIN_DEBUG
  PRIVATE(this)->menuenabled = enable;
}

SbBool
SoWinFullViewer::isPopupMenuEnabled(void) const
{
  return PRIVATE(this)->menuenabled;
}

HWND
SoWinFullViewer::getAppPushButtonParent(void) const
{
  return PRIVATE(this)->viewerwidget;
}

void
SoWinFullViewer::addAppPushButton(HWND newButton)
{
  PRIVATE(this)->lefttrimbuttons.append(newButton);
}

void
SoWinFullViewer::insertAppPushButton(HWND newButton, int index)
{
  PRIVATE(this)->lefttrimbuttons.insert(newButton, index);
}

void
SoWinFullViewer::removeAppPushButton(HWND oldButton)
{
  int index = PRIVATE(this)->lefttrimbuttons.find(oldButton);
  PRIVATE(this)->lefttrimbuttons.remove(index);
}

int
SoWinFullViewer::findAppPushButton(HWND oldButton) const
{
  return PRIVATE(this)->lefttrimbuttons.find(oldButton);
}

int
SoWinFullViewer::lengthAppPushButton(void) const
{
  return PRIVATE(this)->lefttrimbuttons.getLength();
}

HWND
SoWinFullViewer::getRenderAreaWidget(void) const
{
  return PRIVATE(this)->renderareawidget;
}

// Doc in superclass.
void
SoWinFullViewer::setComponentCursor(const SoWinCursor & cursor)
{
  // Overridden to apply the new cursor only for the rendering canvas
  // widget. Otherwise, the default SoWinComponent setComponentCursor()
  // method will set the cursor for the top-most parent widget, which
  // makes it affect all sub-widgets, like the decorations stuff.

  PRIVATE(this)->cursor = cursor;
  SoWinComponent::setWidgetCursor(this->getRenderAreaWidget(), cursor);
}

// Documented in superclass.
void
SoWinFullViewer::setViewing(SbBool enable)
{
  if ((enable && this->isViewing()) || (! enable && ! this->isViewing())) {
#if SOWIN_DEBUG
    SoDebugError::postWarning("SoWinFullViewer::setViewing", "view mode already %s",
                               enable ? "on" : "off");
#endif // SOWIN_DEBUG
    return;
  }

  inherited::setViewing(enable);

  if (PRIVATE(this)->viewerButton(SoWinFullViewerP::VIEWERBUTTON_VIEW) != NULL) {
    PRIVATE(this)->viewerButton(SoWinFullViewerP::VIEWERBUTTON_VIEW)->setPressedState(enable);
    PRIVATE(this)->viewerButton(SoWinFullViewerP::VIEWERBUTTON_PICK)->setPressedState(enable ? FALSE : TRUE);
    PRIVATE(this)->viewerButton(SoWinFullViewerP::VIEWERBUTTON_SEEK)->setEnabled(enable);
  }
}

///////////////////////////////////////////////////////////////////
//
//  (protected)
//
//

// Documented in superclass.
HWND
SoWinFullViewer::buildWidget(HWND parent)
{
  // This method will always be called with a parent.

  assert(IsWindow(parent));
  
  SoWinFullViewerP::parentHWNDmappings->enter((SbDict::Key)parent, this);

  PRIVATE(this)->viewerwidget = parent;
  PRIVATE(this)->renderareawidget = inherited::buildWidget(parent);
  assert(IsWindow(PRIVATE(this)->renderareawidget));

  // Change default cursor from pointer arrow, to *no* default
  // cursor. This must be done for the SetCursor()-call in
  // SoWinFullViewerP::systemEventHook() to work even when the canvas
  // has not grabbed the mouse.
  //
  (void)Win32::SetClassLongPtr(this->getGLWidget(), GCLP_HCURSOR, 0);
  
  if (PRIVATE(this)->menuenabled) { this->buildPopupMenu(); }
  if (PRIVATE(this)->decorations) { this->buildDecoration(parent); }

  return PRIVATE(this)->renderareawidget;
}

// doc in super
void
SoWinFullViewer::sizeChanged(const SbVec2s & size)
{
  if (! IsWindow(this->getBaseWidget())) return;
  
  if (PRIVATE(this)->decorations) {
    SoWinRenderArea::sizeChanged(SbVec2s(size[0] - (2 * DECORATION_SIZE),
                                         size[1] - DECORATION_SIZE));
  }
  else {
    SoWinRenderArea::sizeChanged(size);
  }
  PRIVATE(this)->layoutWidgets(size[0], size[1]);
  Win32::InvalidateRect(this->getParentWidget(), NULL, TRUE);
}

void
SoWinFullViewer::buildDecoration(HWND parent)
{
  if (! SoWinFullViewerP::decorationsWndClassAtom) {
    WNDCLASS windowclass;

    windowclass.lpszClassName = "Decorations Widget";
    windowclass.hInstance = GetModuleHandle(NULL);
    windowclass.lpfnWndProc = DefWindowProc;
    windowclass.style = CS_HREDRAW | CS_VREDRAW;
    windowclass.lpszMenuName = NULL;
    windowclass.hIcon = NULL;
    windowclass.hCursor = Win32::LoadCursor(NULL, IDC_ARROW);
    windowclass.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    windowclass.cbClsExtra = 0;
    windowclass.cbWndExtra = 0;

    SoWinFullViewerP::decorationsWndClassAtom = Win32::RegisterClass(& windowclass);
  }

  // comment the following two lines to remove the "sunken" style of the render area
  LONG_PTR dwExStyle = ::GetWindowLongPtr(this->getRenderAreaWidget(), GWL_EXSTYLE);
  ::SetWindowLongPtr(this->getRenderAreaWidget(), GWL_EXSTYLE, dwExStyle | WS_EX_CLIENTEDGE);
  this->leftDecoration = this->buildLeftTrim(parent);
  this->bottomDecoration = this->buildBottomTrim(parent);
  this->rightDecoration = this->buildRightTrim(parent);
}

HWND
SoWinFullViewer::buildViewerButtons(HWND parent)
{
  this->createViewerButtons(parent, & PRIVATE(this)->righttrimbuttons);

  // Now position the buttons.

  RECT rect;
  Win32::GetClientRect(parent, &rect);
  const int x = rect.right - DECORATION_SIZE;

  for (int i=0; i < PRIVATE(this)->righttrimbuttons.getLength(); i++) {
    SoWinBitmapButton * b = (SoWinBitmapButton *)
      PRIVATE(this)->righttrimbuttons[i];
    b->move(x, i * DECORATION_SIZE, DECORATION_SIZE, DECORATION_SIZE);
  }

  return parent;
}

void
SoWinFullViewer::buildPopupMenu(void)
{
  this->prefmenu = PRIVATE(this)->setupStandardPopupMenu();
}

void
SoWinFullViewer::openPopupMenu(const SbVec2s position)
{
  assert(this->prefmenu != NULL);
  PRIVATE(this)->prepareMenu(this->prefmenu);

  RECT clientrect;
  Win32::GetClientRect(PRIVATE(this)->renderareawidget, &clientrect);

  this->prefmenu->popUp(PRIVATE(this)->renderareawidget,
                        position[0], clientrect.bottom - position[1]);
}

void
SoWinFullViewer::setLeftWheelString(const char * const name)
{
  if (PRIVATE(this)->leftthumbwheel)
    PRIVATE(this)->leftthumbwheel->setLabelText(name);
  if (this->leftWheelLabel)
    PRIVATE(this)->setLabelText(this->leftWheelLabel, name);
}

void
SoWinFullViewer::setBottomWheelString(const char * const name)
{
  if (PRIVATE(this)->bottomthumbwheel)
    PRIVATE(this)->bottomthumbwheel->setLabelText(name);
  if (this->bottomWheelLabel)
    PRIVATE(this)->setLabelText(this->bottomWheelLabel, name);
}

const char *
SoWinFullViewer::getRightWheelString() const
{
  return this->rightWheelStr;
}

void
SoWinFullViewer::setRightWheelString(const char * const string)
{
  delete [] this->rightWheelStr;
  this->rightWheelStr = NULL;

  if (string)
    this->rightWheelStr = strcpy(new char [strlen(string)+1], string);

  if (PRIVATE(this)->rightthumbwheel) {
    PRIVATE(this)->rightthumbwheel->setLabelText(string);
  }
  if (this->rightWheelLabel)
    PRIVATE(this)->setLabelText(this->rightWheelLabel, string);
}

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

int SoWinFullViewerP::nrinstances = 0;
SbStorage * SoWinFullViewerP::hookhandle = NULL;
SbDict * SoWinFullViewerP::parentHWNDmappings = NULL;

HWND
SoWinFullViewerP::buildLeftWheel(HWND parent)
{
  // Create coords are not needed - the widget is moved into place
  // by layoutWidgets
  this->leftthumbwheel =
    new SoWinThumbWheel(SoWinThumbWheel::Vertical,
                        parent,
                        0,
                        0,
                        0,
                        "RotX");
  PUBLIC(this)->leftWheelVal = this->leftthumbwheel->value();
  this->leftthumbwheel->setCallback(this->leftWheelCB, this);
  this->leftthumbwheel->setRangeBoundaryHandling(SoWinThumbWheel::ACCUMULATE);
  this->leftthumbwheel->setLabelOffset(0,
                                          ((DECORATION_SIZE - this->leftthumbwheel->sizeHint().cx) / 2)
                                          + DECORATION_BUFFER + 1);

  return this->leftthumbwheel->getWidget();
}

HWND
SoWinFullViewerP::buildBottomWheel(HWND parent)
{
  // Create coords are not needed - the widget is moved into place
  // by layoutWidgets
  this->bottomthumbwheel =
    new SoWinThumbWheel(SoWinThumbWheel::Horizontal,
                        parent,
                        1,
                        0,
                        0,
                        "RotY");
  PUBLIC(this)->bottomWheelVal = this->bottomthumbwheel->value();
  this->bottomthumbwheel->setCallback(this->bottomWheelCB, this);
  this->bottomthumbwheel->setRangeBoundaryHandling(SoWinThumbWheel::ACCUMULATE);
  this->bottomthumbwheel->setLabelOffset(-4, 0);

  return this->bottomthumbwheel->getWidget();
}

HWND
SoWinFullViewerP::buildRightWheel(HWND parent)
{
  // Create coords are not needed - the widget is moved into place
  // by layoutWidgets
  this->rightthumbwheel =
    new SoWinThumbWheel(SoWinThumbWheel::Vertical,
                        parent,
                        2,
                        0,
                        0,
                        "Dolly");
  PUBLIC(this)->setRightWheelString("Dolly");
  PUBLIC(this)->rightWheelVal = this->rightthumbwheel->value();
  this->rightthumbwheel->setCallback(this->rightWheelCB, this);
  this->rightthumbwheel->setRangeBoundaryHandling(SoWinThumbWheel::ACCUMULATE);
  this->rightthumbwheel->setLabelOffset(- (this->bottomthumbwheel->getLabelSize().cx - this->rightthumbwheel->sizeHint().cx),
                                           ((DECORATION_SIZE - this->leftthumbwheel->sizeHint().cx) / 2)
                                           + DECORATION_BUFFER + 1);

  return this->rightthumbwheel->getWidget();
}

void
SoWinFullViewerP::seekbuttonProc(SoWinBitmapButton * b, void * userdata)
{
  SoWinFullViewerP * that = (SoWinFullViewerP *)userdata;
  that->seekbuttonClicked();
}

void
SoWinFullViewerP::seekbuttonClicked(void)
{
  PUBLIC(this)->setSeekMode(PUBLIC(this)->isSeekMode() ? FALSE : TRUE);
}

void
SoWinFullViewerP::leftWheelCB(SoWinThumbWheel::Interaction type, float val,
                              void * userdata)
{
  SoWinFullViewerP * that = (SoWinFullViewerP *)userdata;
  if (type == SoWinThumbWheel::START) { PUBLIC(that)->leftWheelStart(); }
  else if (type == SoWinThumbWheel::END) { PUBLIC(that)->leftWheelFinish(); }
  else { PUBLIC(that)->leftWheelMotion(val); }
}

void
SoWinFullViewerP::bottomWheelCB(SoWinThumbWheel::Interaction type, float val,
                                void * userdata)
{
  SoWinFullViewerP * that = (SoWinFullViewerP *)userdata;
  if (type == SoWinThumbWheel::START) { PUBLIC(that)->bottomWheelStart(); }
  else if (type == SoWinThumbWheel::END) { PUBLIC(that)->bottomWheelFinish(); }
  else { PUBLIC(that)->bottomWheelMotion(val); }
}

void
SoWinFullViewerP::rightWheelCB(SoWinThumbWheel::Interaction type, float val,
                               void * userdata)
{
  SoWinFullViewerP * that = (SoWinFullViewerP *)userdata;
  if (type == SoWinThumbWheel::START) { PUBLIC(that)->rightWheelStart(); }
  else if (type == SoWinThumbWheel::END) { PUBLIC(that)->rightWheelFinish(); }
  else { PUBLIC(that)->rightWheelMotion(val); }
}

void
SoWinFullViewerP::interactbuttonProc(SoWinBitmapButton * b, void * userdata)
{
  SoWinFullViewerP * that = (SoWinFullViewerP *)userdata;
  that->viewerButton(SoWinFullViewerP::VIEWERBUTTON_PICK)->setPressedState(TRUE);
  that->viewerButton(SoWinFullViewerP::VIEWERBUTTON_VIEW)->setPressedState(FALSE);
  if (PUBLIC(that)->isViewing()) { PUBLIC(that)->setViewing(FALSE); }
}

void
SoWinFullViewerP::examinebuttonProc(SoWinBitmapButton * b, void * userdata)
{
  SoWinFullViewerP * that = (SoWinFullViewerP *)userdata;
  that->viewerButton(SoWinFullViewerP::VIEWERBUTTON_VIEW)->setPressedState(TRUE);
  that->viewerButton(SoWinFullViewerP::VIEWERBUTTON_PICK)->setPressedState(FALSE);
  if (!PUBLIC(that)->isViewing()) { PUBLIC(that)->setViewing(TRUE); }
}

void
SoWinFullViewerP::homebuttonProc(SoWinBitmapButton * b, void * userdata)
{
  SoWinFullViewerP * that = (SoWinFullViewerP *)userdata;
  PUBLIC(that)->resetToHomePosition();
}

void
SoWinFullViewerP::sethomebuttonProc(SoWinBitmapButton * b, void * userdata)
{
  SoWinFullViewerP * that = (SoWinFullViewerP *)userdata;
  PUBLIC(that)->saveHomePosition();
}

void
SoWinFullViewerP::viewallbuttonProc(SoWinBitmapButton * b, void * userdata)
{
  SoWinFullViewerP * that = (SoWinFullViewerP *)userdata;
  PUBLIC(that)->viewAll();
}

int
SoWinFullViewerP::layoutWidgets(int cx, int cy)
{
  int x = 0, y, width, height, bottom, right, top;
  const int numViewerButtons = this->righttrimbuttons.getLength();
  const int numAppButtons = this->lefttrimbuttons.getLength();
  HWND renderArea = PUBLIC(this)->getBaseWidget();
  UINT flags = /*SWP_NOSIZE |*/ SWP_NOZORDER | SWP_NOREDRAW;
  
  // RenderArea
  assert(IsWindow(renderArea));

  if (this->decorations) {
    Win32::SetWindowPos(renderArea, NULL, DECORATION_SIZE, 0, cx - 2*DECORATION_SIZE, cy - DECORATION_SIZE, flags);

    if (PUBLIC(this)->leftDecoration) {
      Win32::MoveWindow(PUBLIC(this)->leftDecoration,
                        0, 0,
                        DECORATION_SIZE, cy - DECORATION_SIZE, TRUE);
    }
    if (PUBLIC(this)->bottomDecoration) {
      Win32::MoveWindow(PUBLIC(this)->bottomDecoration,
                        0, cy - DECORATION_SIZE,
                        cx, DECORATION_SIZE, TRUE);
    }
    if (PUBLIC(this)->rightDecoration) {
      Win32::MoveWindow(PUBLIC(this)->rightDecoration,
                        cx - DECORATION_SIZE, 0,
                        DECORATION_SIZE, cy - DECORATION_SIZE, TRUE);
    }
  }
  else {
    Win32::SetWindowPos(renderArea, NULL, 0, 0, cx, cy, flags);
    return 0;
  }
  
  // Viewer buttons
  int i;
  for(i = 0; i < numViewerButtons; i++)
    this->viewerButton(i)->move(0, DECORATION_SIZE * i);

  // App buttons
  for(i = 0; i < numAppButtons; i++) {
    Win32::MoveWindow(this->appButton(i),
                      0, DECORATION_SIZE * i,
                      DECORATION_SIZE, DECORATION_SIZE, TRUE);
  }

  // Wheels

  bottom = (cy - (DECORATION_SIZE + DECORATION_BUFFER));
  right = (cx - ((PUBLIC(this)->rightWheelLabel ? this->getLabelSize(PUBLIC(this)->rightWheelLabel).cx : 0) + 8));

  // Left wheel
  if (this->leftthumbwheel) {

    width = this->leftthumbwheel->sizeHint().cx;
    height = this->leftthumbwheel->sizeHint().cy;

    x = (DECORATION_SIZE / 2) - (width / 2) - 1;

    top = numAppButtons * DECORATION_SIZE + DECORATION_BUFFER;

    // if area is large enough for full height
    if ((bottom - top) > height) {

      y = bottom - height;

    } // else we must use all available space
    else {

      y = top;

      height = bottom - top;

    }

    this->leftthumbwheel->move(x, y, width, height);
  }

  // Bottom wheel
  if (this->bottomthumbwheel) {

    x += (PUBLIC(this)->leftWheelLabel ? this->getLabelSize(PUBLIC(this)->leftWheelLabel).cx : 0) +
         (PUBLIC(this)->bottomWheelLabel ? this->getLabelSize(PUBLIC(this)->bottomWheelLabel).cx : 0) + 8;

    width =  this->bottomthumbwheel->sizeHint().cx;
    height = this->bottomthumbwheel->sizeHint().cy;

    y = (DECORATION_SIZE / 2) - (height / 2) + 1;

    if (right < (x + width)) {

      width = right - x;

    }

    this->bottomthumbwheel->move(x, y, width, height);

  }

  // Right wheel
  if (this->rightthumbwheel) {

    width = this->rightthumbwheel->sizeHint().cx;
    height = this->rightthumbwheel->sizeHint().cy;

    x = (DECORATION_SIZE / 2) - (width / 2) + 1;

    top = numViewerButtons * DECORATION_SIZE + DECORATION_BUFFER;

    // if area is large enough for original height
    if ((bottom - top) > height) {

      y = bottom - height;

    } // else we must use all available space
    else {

      y = top;

      height = bottom - top;

    }

    this->rightthumbwheel->move(x, y, width, height);
  }

  // All labels
  width = this->leftthumbwheel ? this->leftthumbwheel->sizeHint().cx : 0;
  height = PUBLIC(this)->bottomWheelLabel ? this->getLabelSize(PUBLIC(this)->bottomWheelLabel).cy : 0;

  x = (DECORATION_SIZE / 2) - (width / 2) - 1;
  y = (DECORATION_SIZE / 2) - (height / 2) + 1;

  if (PUBLIC(this)->leftWheelLabel ) {
    Win32::MoveWindow(PUBLIC(this)->leftWheelLabel,
                      x,
                      y,
                      this->getLabelSize(PUBLIC(this)->leftWheelLabel).cx,
                      this->getLabelSize(PUBLIC(this)->leftWheelLabel).cy,
                      TRUE);
  }
  if (PUBLIC(this)->bottomWheelLabel ) {
    Win32::MoveWindow(PUBLIC(this)->bottomWheelLabel,
                      x + (PUBLIC(this)->leftWheelLabel ? this->getLabelSize(PUBLIC(this)->leftWheelLabel).cx : 0) + 4,
                      y,
                      this->getLabelSize(PUBLIC(this)->bottomWheelLabel).cx,
                      this->getLabelSize(PUBLIC(this)->bottomWheelLabel).cy,
                      TRUE);
  }
  if (PUBLIC(this)->rightWheelLabel ) {
    Win32::MoveWindow(PUBLIC(this)->rightWheelLabel,
                      right + 4,
                      y,
                      this->getLabelSize(PUBLIC(this)->rightWheelLabel).cx,
                      this->getLabelSize(PUBLIC(this)->rightWheelLabel).cy,
                      TRUE);
  }

  return 0;
}

void
SoWinFullViewerP::showDecorationWidgets(SbBool enable)
{
  // All decoration: viewer buttons, app buttons, thumb wheels, labels
  if (enable) {
    if (!PUBLIC(this)->leftDecoration) {
      PUBLIC(this)->buildDecoration(PUBLIC(this)->getParentWidget());
    }

	// comment the following two lines to remove the "sunken" style of the render area
	LONG_PTR dwExStyle = ::GetWindowLongPtr(this->renderareawidget, GWL_EXSTYLE);
    ::SetWindowLongPtr(this->renderareawidget, GWL_EXSTYLE, dwExStyle | WS_EX_CLIENTEDGE);

    (void)ShowWindow(PUBLIC(this)->leftDecoration, SW_SHOW);
    (void)ShowWindow(PUBLIC(this)->bottomDecoration, SW_SHOW);
    (void)ShowWindow(PUBLIC(this)->rightDecoration, SW_SHOW);
  }
  else {
    if (PUBLIC(this)->leftDecoration) {
		// comment the following two lines to remove the "sunken" style of the render area
		LONG_PTR dwExStyle = ::GetWindowLongPtr(this->renderareawidget, GWL_EXSTYLE);
      ::SetWindowLongPtr(this->renderareawidget, GWL_EXSTYLE, dwExStyle & (~WS_EX_CLIENTEDGE));

      (void)ShowWindow(PUBLIC(this)->leftDecoration, SW_HIDE);
      (void)ShowWindow(PUBLIC(this)->bottomDecoration, SW_HIDE);
      (void)ShowWindow(PUBLIC(this)->rightDecoration, SW_HIDE);
    }
  }
}

LRESULT CALLBACK
SoWinFullViewerP::systemEventHook(int code, WPARAM wparam, LPARAM lparam)
{
  // FIXME: if I'm not mistaken, this message hook catches ~ all
  // messages in our process, for _all_ windows / widgets. This is
  // superbly inefficient, and should be cleaned up. 20030424 mortene.

  CWPSTRUCT * msg = (CWPSTRUCT *)lparam;

  void * comp;
  SbBool found =
    SoWinFullViewerP::parentHWNDmappings->find((SbDict::Key)msg->hwnd, comp);

  if (found) {
    SoWinFullViewer * object = (SoWinFullViewer *)comp;

    // According to MSVC++ Win32 API doc on CallWndProc(), if code<0
    // we should not do any processing -- just pass message along to
    // next hook.
    if (code >= 0) {
      // FIXME: if code==HC_ACTION the Win32 API doc says we _must_
      // process the message. Weird. Try to find out what that really
      // means. 20011126 mortene.

      switch (msg->message) {
      case WM_SETCURSOR:
        SoWinComponent::setWidgetCursor(object->getRenderAreaWidget(),
                                        PRIVATE(object)->cursor);
        break;

      case WM_LBUTTONDOWN:
      case WM_SETFOCUS:
	if ( object->isStealFocus() )
	  (void)Win32::SetFocus(object->getGLWidget());
        break;
      }
    }
  }

  HHOOK * hookhandle = (HHOOK *) SoWinFullViewerP::hookhandle->get();
  return CallNextHookEx(*hookhandle, code, wparam, lparam);
}

// *************************************************************************

void
SoWinFullViewer::createViewerButtons(HWND parent, SbPList * buttonlist)
{
  SoWinBitmapButton * button = new SoWinBitmapButton(parent, 24, "pick", NULL);
  button->addBitmap(pick_xpm);
  button->setBitmap(0); // use first (and only) bitmap
  button->registerClickedProc(SoWinFullViewerP::interactbuttonProc, PRIVATE(this));
  buttonlist->append(button);
  button->setPressedState(this->isViewing() ? FALSE : TRUE);

  button = new SoWinBitmapButton(parent, 24, "view", NULL);
  button->addBitmap(view_xpm);
  button->setBitmap(0); // use first (and only) bitmap
  button->registerClickedProc(SoWinFullViewerP::examinebuttonProc, PRIVATE(this));
  buttonlist->append(button);
  button->setPressedState(this->isViewing());

  button = new SoWinBitmapButton(parent, 24, "home", NULL);
  button->addBitmap(home_xpm);
  button->setBitmap(0); // use first (and only) bitmap
  button->registerClickedProc(SoWinFullViewerP::homebuttonProc, PRIVATE(this));
  buttonlist->append(button);

  button = new SoWinBitmapButton(parent, 24, "set_home", NULL);
  button->addBitmap(set_home_xpm);
  button->setBitmap(0);
  button->registerClickedProc(SoWinFullViewerP::sethomebuttonProc, PRIVATE(this));
  buttonlist->append(button);

  button = new SoWinBitmapButton(parent, 24, "view_all", NULL);
  button->addBitmap(view_all_xpm);
  button->setBitmap(0); // use first (and only) bitmap
  button->registerClickedProc(SoWinFullViewerP::viewallbuttonProc, PRIVATE(this));
  buttonlist->append(button);

  button = new SoWinBitmapButton(parent, 24, "seek", NULL);
  button->addBitmap(seek_xpm);
  button->setBitmap(0); // use first (and only) bitmap
  button->registerClickedProc(SoWinFullViewerP::seekbuttonProc, PRIVATE(this));
  buttonlist->append(button);
}

// FIXME: the build*Trim() functions are present and working in the
// other So* toolkits, but are unimplemented missing in SoWin. Why?
// 20020111 mortene.

HWND
SoWinFullViewer::buildLeftTrim(HWND parent)
{
  assert(IsWindow(parent));

  RECT rect;
  Win32::GetClientRect(parent, & rect);

  HWND hWnd = Win32::CreateWindow_("Decorations Widget",
                                    "Left Decoration",
                                    WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CHILD,
                                    rect.left, rect.top,
                                    rect.left+DECORATION_SIZE, rect.bottom,
                                    parent,
                                    NULL,
                                    NULL,
                                    NULL);

  this->leftWheel = PRIVATE(this)->buildLeftWheel(hWnd);
  //(void)this->buildAppButtons(hWnd);

  return hWnd;
}

HWND
SoWinFullViewer::buildBottomTrim(HWND parent)
{
  assert(IsWindow(parent));

  RECT rect;
  Win32::GetClientRect(parent, & rect);

  HWND hWnd = Win32::CreateWindow_("Decorations Widget",
                                    "Bottom Decoration",
                                    WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CHILD,
                                    rect.left, rect.bottom-DECORATION_SIZE,
                                    rect.right, rect.bottom,
                                    parent,
                                    NULL,
                                    NULL,
                                    NULL);

  this->bottomWheel = PRIVATE(this)->buildBottomWheel(hWnd);

  this->leftWheelLabel = PRIVATE(this)->createLabelWindow(hWnd, 0, 0, "RotX");
  this->bottomWheelLabel = PRIVATE(this)->createLabelWindow(hWnd, 0, 0, "RotY");
  this->rightWheelLabel = PRIVATE(this)->createLabelWindow(hWnd, 0, 0, "Dolly");

  return hWnd;
}

HWND
SoWinFullViewer::buildRightTrim(HWND parent)
{
  assert(IsWindow(parent));

  RECT rect;
  Win32::GetClientRect(parent, & rect);

  HWND hWnd = Win32::CreateWindow_("Decorations Widget",
                                    "Right Decoration",
                                    WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CHILD,
                                    rect.right-DECORATION_SIZE, rect.top,
                                    rect.right, rect.bottom,
                                    parent,
                                    NULL,
                                    NULL,
                                    NULL);

  this->rightWheel = PRIVATE(this)->buildRightWheel(hWnd);

  (void)this->buildViewerButtons(hWnd);

  return hWnd;
}

// *************************************************************************

SoWinFullViewerP::SoWinFullViewerP(SoWinFullViewer * publ)
  : SoGuiFullViewerP(publ)
{
}

SoWinFullViewerP::~SoWinFullViewerP()
{
  const int len = this->righttrimbuttons.getLength();
  for (int i = 0; i < len; i++) {
    delete (SoWinBitmapButton *)this->righttrimbuttons[i];
  }
  if (this->leftthumbwheel) 
    delete this->leftthumbwheel;
  if (this->rightthumbwheel) 
    delete this->rightthumbwheel;
  if (this->bottomthumbwheel) 
    delete this->bottomthumbwheel;
}

SoWinBitmapButton *
SoWinFullViewerP::viewerButton(int idx)
{
  if (this->righttrimbuttons.getLength() <= idx) { return NULL; }

  return (SoWinBitmapButton *)this->righttrimbuttons[idx];
}

HWND
SoWinFullViewerP::appButton(int idx)
{
  if (this->lefttrimbuttons.getLength() <= idx) { return NULL; }

  return (HWND)this->lefttrimbuttons[idx];
}

void
SoWinFullViewerP::setThumbWheelValue(void * wheel, float val)
{
  SoWinThumbWheel * twheel = SoWinThumbWheel::getWheelFromHWND((HWND)wheel);
  assert(twheel != NULL);
  twheel->setValue(val);
}

HWND
SoWinFullViewerP::createLabelWindow(HWND parent, int x, int y, const char * text)
{
  assert(IsWindow(parent));
  // FIXME: assumes the same font as parent

  const char * label = (text ? text : " ");

  int len = (int)strlen(label);
  HDC hdc = Win32::GetDC(parent);

  SIZE textSize;
  Win32::GetTextExtentPoint(hdc, label, len, & textSize);

  HWND labelWindow = Win32::CreateWindow_("STATIC",
                                          label,
                                          WS_VISIBLE | WS_CHILD | SS_CENTER,
                                          x, y,
                                          textSize.cx + 2, textSize.cy, // SIZE
                                          parent,
                                          NULL,
                                          NULL,
                                          NULL);
  return labelWindow;
}

void
SoWinFullViewerP::setLabelText(HWND labelWindow, const char * text)
{
  assert(IsWindow(labelWindow));

  const char * label = (text ? text : " ");

  Win32::SetWindowText(labelWindow, label);

  int len = (int)strlen(label);
  HDC hdc = Win32::GetDC(labelWindow);

  SIZE textSize;
  Win32::GetTextExtentPoint(hdc, label, len, & textSize);

  UINT flags = SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW;
  Win32::SetWindowPos(labelWindow, NULL, 0, 0,
                      textSize.cx + 2, textSize.cy, flags);
}

SIZE
SoWinFullViewerP::getLabelSize(HWND labelWindow)
{
  RECT rect;
  Win32::GetWindowRect(labelWindow, & rect);
  SIZE size = { rect.right - rect.left, rect.bottom - rect.top };
  return size;
}

#endif // !DOXYGEN_SKIP_THIS

// *************************************************************************
