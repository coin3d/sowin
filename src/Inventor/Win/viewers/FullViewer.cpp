/**************************************************************************
 *
 *  This file is part of the Coin SoWin GUI binding library.
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of the distribution for
 *  more details.
 *
 *  If you want to use Coin SoWin for applications not compatible with the
 *  LGPL, please contact SIM to aquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/errors/SoDebugError.h>

#include <sowindefs.h>
#include <Inventor/Win/Win32API.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoWinCursor.h>
#include <Inventor/Win/widgets/SoWinViewerPrefSheet.h>
#include <Inventor/Win/widgets/SoWinThumbWheel.h>
#include <Inventor/Win/widgets/SoWinBitmapButton.h>
#include <Inventor/Win/widgets/WinNativePopupMenu.h>
#include <Inventor/Win/viewers/SoWinFullViewer.h>

// Button icons.
#include <Inventor/Win/common/pixmaps/pick.xpm>
#include <Inventor/Win/common/pixmaps/view.xpm>
#include <Inventor/Win/common/pixmaps/help.xpm>
#include <Inventor/Win/common/pixmaps/home.xpm>
#include <Inventor/Win/common/pixmaps/set_home.xpm>
#include <Inventor/Win/common/pixmaps/view_all.xpm>
#include <Inventor/Win/common/pixmaps/seek.xpm>

#define VIEWERBUTTON(index) ((SoWinBitmapButton *) (* viewerButtonList) [index])
#define APPBUTTON(index) ((HWND) (* appButtonList)[index])
#define VIEWERBUTTON_O(index) ((SoWinBitmapButton *) (* (owner->viewerButtonList)) [index])
#define APPBUTTON_O(index) ((HWND) (* (owner->appButtonList))[index])

static const int DECORATION_SIZE = 30;
static const int DECORATION_BUFFER = 5;

SOWIN_OBJECT_ABSTRACT_SOURCE(SoWinFullViewer);

// The private data for the SoWinFullViewer.

class SoWinFullViewerP {
public:
  SoWinFullViewerP(SoWinFullViewer * o) {
    this->owner = o;
  }

  static void rightWheelCB(SoWinFullViewer * viewer, void ** data);
  static void bottomWheelCB(SoWinFullViewer * viewer, void ** data);
  static void leftWheelCB(SoWinFullViewer * viewer, void ** data);

  void interactbuttonClicked(void);
  void viewbuttonClicked(void);
  void helpbuttonClicked(void);
  void homebuttonClicked(void);
  void sethomebuttonClicked(void);
  void viewallbuttonClicked(void);
  
  int layoutWidgets(int cx, int cy);
  static LRESULT CALLBACK callWndProc(int code, WPARAM wparam, LPARAM lparam);

  static HHOOK hookhandle;
  static int nrinstances;
  
  // App button callbacks
  AppPushButtonCB * appPushButtonCB;
  void * appPushButtonData;
  RedrawAppPushButtonCB * redrawAppPushButtonCB;
  void * redrawAppPushButtonData;
  CreateAppPushButtonCB * createAppPushButtonCB;
  void * createAppPushButtonData;

  //WNDPROC parentEventHandler;

  SbBool menuenabled;
  SbBool decorations;

  static SbBool doneButtonBar;
  static SbBool doButtonBar;

  SoWinCursor cursor;

private:
  SoWinFullViewer * owner;
};

SbBool SoWinFullViewerP::doButtonBar = TRUE;
SbBool SoWinFullViewerP::doneButtonBar = FALSE;
HHOOK SoWinFullViewerP::hookhandle = NULL;
int SoWinFullViewerP::nrinstances = 0;

#define PRIVATE(o) (o->pimpl)

///////////////////////////////////////////////////////////////////
//
//  Constructor / Destructor
//  (protected)
//

SoWinFullViewer::SoWinFullViewer(HWND parent,
                                  const char * name,
                                  SbBool embedded,
                                  BuildFlag flag,
                                  SoWinViewer::Type type,
                                  SbBool build) :
  inherited(parent, name, embedded, type, FALSE)
{
  this->pimpl = new SoWinFullViewerP(this);
  SoWinFullViewerP::nrinstances++;

  if (SoWinFullViewerP::nrinstances == 1) {
    SoWinFullViewerP::hookhandle =
      Win32::SetWindowsHookEx(WH_CALLWNDPROC,
                              (HOOKPROC)SoWinFullViewerP::callWndProc,
                              NULL, GetCurrentThreadId());
  }

  this->viewerWidget = NULL;
  this->renderAreaWidget = NULL;

  PRIVATE(this)->menuenabled = (flag & SoWinFullViewer::BUILD_POPUP) ? TRUE : FALSE;
  PRIVATE(this)->decorations = (flag & SoWinFullViewer::BUILD_DECORATION) ? TRUE : FALSE;

  this->viewerButtonList = new SbPList;
  this->appButtonList = new SbPList;

  this->prefmenu = NULL;
  this->prefsheet = new SoWinViewerPrefSheet();
  this->prefsheet->setTitle("Viewer Preference Sheet");

  this->leftWheel = NULL;
  this->bottomWheel = NULL;
  this->rightWheel = NULL;

  PRIVATE(this)->appPushButtonCB = NULL;
  PRIVATE(this)->appPushButtonData = NULL;
  PRIVATE(this)->redrawAppPushButtonCB = NULL;
  PRIVATE(this)->redrawAppPushButtonData = NULL;
  PRIVATE(this)->createAppPushButtonCB = NULL;
  PRIVATE(this)->createAppPushButtonData = NULL;

  this->zoomrange = SbVec2f(1.0f, 140.0f);
	
  if (build) {

    this->setClassName("SoWinFullViewer");
    this->setBaseWidget(this->buildWidget(this->getParentWidget()));
      
  }

  this->setSize(SbVec2s(500, 420));

  if (! this->isViewing())
    this->setViewing(TRUE);
}

SoWinFullViewer::~SoWinFullViewer(void)
{
  SoWinFullViewerP::nrinstances--;

  if (SoWinFullViewerP::nrinstances == 0) {
    assert(SoWinFullViewerP::hookhandle != NULL);
    Win32::UnhookWindowsHookEx(SoWinFullViewerP::hookhandle);
  }
  
  int i;

  for (i = this->viewerButtonList->getLength(); i >= 0; i--) {
    delete this->viewerButtonList->get(i);
    this->viewerButtonList->remove(i);
  }

  for (i =  this->appButtonList->getLength(); i >= 0; i--) {
    this->appButtonList->remove(i);
  }

  delete this->viewerButtonList;
  delete this->appButtonList;
  delete this->pimpl;

}

///////////////////////////////////////////////////////////////////
//
//  (public)
//

void
SoWinFullViewer::setDecoration(SbBool enable)
{
#if SOWIN_DEBUG & 1
  if ((enable && this->isDecoration()) ||
       (! enable && ! this->isDecoration())) {
    SoDebugError::postWarning("SoWinFullViewer::setDecoration",
                               "decorations already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOWIN_DEBUG

  PRIVATE(this)->decorations = enable;
  this->showDecorationWidgets(enable);

  // reposition all widgets
  RECT rect;
  Win32::GetClientRect(this->getParentWidget(), & rect);
  PRIVATE(this)->layoutWidgets(rect.right, rect.bottom);
  if (enable) {
    rect.right -= DECORATION_SIZE * 2;
    rect.bottom -= DECORATION_SIZE;
  }
  SoWinRenderArea::sizeChanged(SbVec2s(rect.right, rect.bottom));
  Win32::InvalidateRect(this->getParentWidget(), NULL, TRUE);
}

SbBool
SoWinFullViewer::isDecoration(void) const
{
  return PRIVATE(this)->decorations;
}

void
SoWinFullViewer::showDecorationWidgets(SbBool enable)
{
  int i;
  int numViewerButtons = this->viewerButtonList->getLength();
  int numAppButtons = this->appButtonList->getLength();

  // Viewer buttons
  for(i = 0; i < numViewerButtons; i++) {
    (void)ShowWindow(VIEWERBUTTON(i)->getWidget(),
                      (enable ? SW_SHOW : SW_HIDE));
  }

  // App buttons
  for(i = 0; i < numAppButtons; i++) {
    (void)ShowWindow(APPBUTTON(i), (enable ? SW_SHOW : SW_HIDE));
  }

  // Thumbwheels
  if (enable) {
    this->leftWheel->show();
    this->bottomWheel->show();
    this->rightWheel->show();
  }
  else {
    this->leftWheel->hide();
    this->bottomWheel->hide();
    this->rightWheel->hide();
  }
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

void
SoWinFullViewer::setDoButtonBar(SbBool enable)
{
#if SOWIN_DEBUG
  if (SoWinFullViewerP::doneButtonBar) { // buttons already built
    SoDebugError::postWarning("SoWinFullViewer::setDoButtonBar():",
                               "unhandled case");
    return;
  }
#endif // SOWIN_DEBUG

  SoWinFullViewerP::doButtonBar = enable;
}

SbBool
SoWinFullViewer::isDoButtonBar(void)
{
  return SoWinFullViewerP::doButtonBar;
}

HWND
SoWinFullViewer::getAppPushButtonParent(void) const
{
  return this->viewerWidget;
}

void
SoWinFullViewer::addAppPushButton(HWND newButton)
{
  this->appButtonList->append(newButton);
}

void
SoWinFullViewer::insertAppPushButton(HWND newButton, int index)
{
  this->appButtonList->insert(newButton, index);
}

void
SoWinFullViewer::removeAppPushButton(HWND oldButton)
{
  int index = this->appButtonList->find(oldButton);
  this->appButtonList->remove(index);
}

int
SoWinFullViewer::findAppPushButton(HWND oldButton) const
{
  return this->appButtonList->find(oldButton);
}

int
SoWinFullViewer::lengthAppPushButton(void) const
{
  return this->appButtonList->getLength();
}

void
SoWinFullViewer::addAppPushButtonCallback(AppPushButtonCB * callback, void * data)
{
  PRIVATE(this)->appPushButtonCB = callback;
  PRIVATE(this)->appPushButtonData = data ;
}

void
SoWinFullViewer::addRedrawAppPushButtonCallback(RedrawAppPushButtonCB * callback, void * data)
{
  PRIVATE(this)->redrawAppPushButtonCB = callback;
  PRIVATE(this)->redrawAppPushButtonData = data;
}

void
SoWinFullViewer::addCreateAppPushButtonCallback(CreateAppPushButtonCB * callback, void * data)
{
  PRIVATE(this)->createAppPushButtonCB = callback;
  PRIVATE(this)->createAppPushButtonData = data;
}

HWND
SoWinFullViewer::getRenderAreaWidget(void) const
{
  return this->renderAreaWidget;
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

  if (SoWinFullViewerP::doButtonBar) {
    VIEWERBUTTON(VIEWERBUTTON_VIEW)->setState(enable);
    VIEWERBUTTON(VIEWERBUTTON_PICK)->setState(enable ? FALSE : TRUE);
    VIEWERBUTTON(VIEWERBUTTON_SEEK)->setEnabled(enable);
  }
}

void
SoWinFullViewer::setCamera(SoCamera * newCamera)
{
  if (newCamera) {
    SoType camtype = newCamera->getTypeId();
    SbBool orthotype =
      camtype.isDerivedFrom(SoOrthographicCamera::getClassTypeId());

    this->setRightWheelString(orthotype ? "Zoom" : "Dolly");
  }

  inherited::setCamera(newCamera);
}

void
SoWinFullViewer::hide(void)
{
  (void)ShowWindow(this->viewerWidget, SW_HIDE);
}

void
SoWinFullViewer::selectedPrefs(void)
{
  this->createPrefSheet();
}

///////////////////////////////////////////////////////////////////
//
//  (protected)
//
//

HWND
SoWinFullViewer::buildWidget(HWND parent)
{
  // This method will always be called with a parent.

  assert(IsWindow(parent));
  
  this->viewerWidget = parent;
  this->renderAreaWidget = inherited::buildWidget(parent);
  assert(IsWindow(this->renderAreaWidget));

  // Change default cursor from pointer arrow, to *no* default
  // cursor. This must be done for the SetCursor()-call in
  // SoWinFullViewerP::callWndProc() to work even when the canvas has
  // not grabbed the mouse.
  SetClassLong(this->getGLWidget(), GCL_HCURSOR, NULL);
  
  if (PRIVATE(this)->menuenabled) { this->buildPopupMenu(); }
  if (PRIVATE(this)->decorations) { this->buildDecoration(parent); }

  return this->renderAreaWidget;
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
  this->buildLeftWheel(parent);
  this->buildBottomWheel(parent);
  this->buildRightWheel(parent);

  if (SoWinFullViewerP::doButtonBar) {

    this->buildViewerButtons(parent);
    
    SoWinFullViewerP::doneButtonBar = TRUE;
  }
}

HWND
SoWinFullViewer::buildLeftWheel(HWND parent)
{
  // Create coords are not needed - the widget is moved into place
  // by layoutWidgets
  this->leftWheel = new SoWinThumbWheel(SoWinThumbWheel::Vertical,
                                         parent,
                                         0,
                                         0,
                                         0,
                                         "RotX");
  this->leftWheel->registerCallback(PRIVATE(this)->leftWheelCB);
  this->leftWheel->registerViewer(this);
  this->leftWheel->setRangeBoundaryHandling(SoWinThumbWheel::MODULATE);
  this->leftWheel->setLabelOffset(0,
    ((DECORATION_SIZE - this->leftWheel->sizeHint().cx) / 2)
    + DECORATION_BUFFER + 1);

  return leftWheel->getWidget();
}

HWND
SoWinFullViewer::buildBottomWheel(HWND parent)
{
  // Create coords are not needed - the widget is moved into place
  // by layoutWidgets
  this->bottomWheel = new SoWinThumbWheel(SoWinThumbWheel::Horizontal,
                                           parent,
                                           1,
                                           0,
                                           0,
                                           "RotY");
  this->bottomWheel->registerCallback(PRIVATE(this)->bottomWheelCB);
  this->bottomWheel->registerViewer(this);
  this->bottomWheel->setRangeBoundaryHandling(SoWinThumbWheel::MODULATE);
  this->bottomWheel->setLabelOffset(-4, 0);

  return this->bottomWheel->getWidget();
}

HWND
SoWinFullViewer::buildRightWheel(HWND parent)
{
  // Create coords are not needed - the widget is moved into place
  // by layoutWidgets
  this->rightWheel = new SoWinThumbWheel(SoWinThumbWheel::Vertical,
                                          parent,
                                          2,
                                          0,
                                          0,
                                          "Dolly");
  this->rightWheel->registerCallback(PRIVATE(this)->rightWheelCB);
  this->rightWheel->registerViewer(this);
  this->rightWheel->setRangeBoundaryHandling(SoWinThumbWheel::ACCUMULATE);
  this->rightWheel->setLabelOffset(
    - (this->bottomWheel->getLabelSize().cx - this->rightWheel->sizeHint().cx),
    ((DECORATION_SIZE - this->leftWheel->sizeHint().cx) / 2)
    + DECORATION_BUFFER + 1);

  return this->rightWheel->getWidget();
}

HWND
SoWinFullViewer::buildViewerButtons(HWND parent)
{
  // Set id's so they can be used as indices in the list later (ie. viewerButtonList[id])

  RECT rect;
  Win32::GetClientRect(parent, & rect);

  int x = rect.right - DECORATION_SIZE;
  int y = 0;

  SoWinBitmapButton * button;

  button = new SoWinBitmapButton(parent, x, y, DECORATION_SIZE,
                                  DECORATION_SIZE, 24, "pick", NULL);
  button->addBitmap(pick_xpm);
  button->setBitmap(0); // use first (and only) bitmap
  button->setId(VIEWERBUTTON_PICK);
  viewerButtonList->append(button);
  button->setState(this->isViewing() ? FALSE : TRUE);
  y += DECORATION_SIZE;

  button = new SoWinBitmapButton(parent, x, y, DECORATION_SIZE,
                                  DECORATION_SIZE, 24, "view", NULL);
  button->addBitmap(view_xpm);
  button->setBitmap(0); // use first (and only) bitmap
  button->setId(VIEWERBUTTON_VIEW);
  viewerButtonList->append(button);
  button->setState(this->isViewing());
  y += DECORATION_SIZE;

  button = new SoWinBitmapButton(parent, x, y, DECORATION_SIZE,
                                  DECORATION_SIZE, 24, "help", NULL);
  button->addBitmap(help_xpm);
  button->setBitmap(0); // use first (and only) bitmap
  button->setId(VIEWERBUTTON_HELP);
  viewerButtonList->append(button);
  y += DECORATION_SIZE;

  button = new SoWinBitmapButton(parent, x, y, DECORATION_SIZE,
                                  DECORATION_SIZE, 24, "home", NULL);
  button->addBitmap(home_xpm);
  button->setBitmap(0); // use first (and only) bitmap
  button->setId(VIEWERBUTTON_HOME);
  viewerButtonList->append(button);
  y += DECORATION_SIZE;

  button = new SoWinBitmapButton(parent, x, y, DECORATION_SIZE,
                                  DECORATION_SIZE, 24, "set_home", NULL);
  button->addBitmap(set_home_xpm);
  button->setBitmap(0);
  button->setId(VIEWERBUTTON_SET_HOME);
  viewerButtonList->append(button);
  y += DECORATION_SIZE;

  button = new SoWinBitmapButton(parent, x, y, DECORATION_SIZE,
                                  DECORATION_SIZE, 24, "view_all", NULL);
  button->addBitmap(view_all_xpm);
  button->setBitmap(0); // use first (and only) bitmap
  button->setId(VIEWERBUTTON_VIEW_ALL);
  viewerButtonList->append(button);
  y += DECORATION_SIZE;

  button = new SoWinBitmapButton(parent, x, y, DECORATION_SIZE,
                                  DECORATION_SIZE, 24, "seek", NULL);
  button->addBitmap(seek_xpm);
  button->setBitmap(0); // use first (and only) bitmap
  button->setId(VIEWERBUTTON_SEEK);
  viewerButtonList->append(button);
  y += DECORATION_SIZE;

  this->buildViewerButtonsEx(parent, x, y, DECORATION_SIZE);

  // FIXME: there should be a valid return value here, as for the
  // other toolkits. 20020111 mortene.
  return NULL;
}

void
SoWinFullViewer::buildViewerButtonsEx(HWND parent, int x, int y, int size)
{
  // virtual - do nothing
}

void
SoWinFullViewer::buildPopupMenu(void)
{
  this->prefmenu = this->setupStandardPopupMenu();
}

void
SoWinFullViewer::openPopupMenu(const SbVec2s position)
{
  assert(this->prefmenu != NULL);
  this->prepareMenu(this->prefmenu);

  RECT clientrect;
  Win32::GetClientRect(this->renderAreaWidget, &clientrect);

  this->prefmenu->popUp(GetActiveWindow(),
                        position[0], clientrect.bottom - position[1]);
}

void
SoWinFullViewer::destroyPopupMenu(void)
{
  delete this->prefmenu;
  this->prefmenu = NULL;
}

void
SoWinFullViewer::setPrefSheetString(const char * name)
{
  this->prefsheet->setTitle(name);
}

void
SoWinFullViewer::createPrefSheet(void)
{

  this->prefsheet->create();

  this->prefsheet->createSeekWidgets(this);
  this->prefsheet->createZoomWidgets(this);
  this->prefsheet->createClippingWidgets(this);

  this->prefsheet->size(); // size to content

}

float
SoWinFullViewer::getLeftWheelValue(void) const
{
  return this->leftWheel->value();
}

void
SoWinFullViewer::setLeftWheelValue(const float value)
{
  this->leftWheel->setValue(value);
}

float
SoWinFullViewer::getBottomWheelValue(void) const
{
  return this->bottomWheel->value();
}

void
SoWinFullViewer::setBottomWheelValue(const float value)
{
  this->bottomWheel->setValue(value);
}

float
SoWinFullViewer::getRightWheelValue(void) const
{
  return this->rightWheel->value();
}

void
SoWinFullViewer::setRightWheelValue(const float value)
{
  this->rightWheel->setValue(value);
}

void
SoWinFullViewer::rightWheelFinish(void)
{
  this->interactiveCountDec();
}

void
SoWinFullViewer::bottomWheelStart(void)
{
  this->interactiveCountInc();
}

void
SoWinFullViewer::leftWheelStart(void)
{
  this->interactiveCountInc();
}

void
SoWinFullViewer::leftWheelMotion(float value)
{
  this->leftWheel->setValue(value);
}

void
SoWinFullViewer::leftWheelFinish(void)
{
  this->interactiveCountDec();
}

void
SoWinFullViewer::bottomWheelMotion(float value)
{
  this->bottomWheel->setValue(value);
}

void
SoWinFullViewer::bottomWheelFinish(void)
{
  this->interactiveCountDec();
}

void
SoWinFullViewer::rightWheelStart(void)
{
  this->interactiveCountInc();
}

void
SoWinFullViewer::rightWheelMotion(float value)
{
  this->rightWheel->setValue(value);
}

void
SoWinFullViewer::setLeftWheelString(const char * name)
{
  if(this->leftWheel)
    this->leftWheel->setLabelText((char *) name);
}

void
SoWinFullViewer::setBottomWheelString(const char * name)
{
  if(this->bottomWheel)
    this->bottomWheel->setLabelText((char *) name);
}

void
SoWinFullViewer::setRightWheelString(const char * name)
{
  if(this->rightWheel)
    this->rightWheel->setLabelText((char *) name);
}

void
SoWinFullViewer::openViewerHelpCard(void)
{
  // virtual; do nothing.
}

LRESULT
SoWinFullViewer::onCommand(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  int i;
  short nc = HIWORD(wparam);// notification code
  short id = LOWORD(wparam);// item, control, or accelerator identifier
  HWND hwnd = (HWND) lparam;// control handle

  switch(id) {

  case VIEWERBUTTON_PICK:
    PRIVATE(this)->interactbuttonClicked();
    break;

  case VIEWERBUTTON_VIEW:
    PRIVATE(this)->viewbuttonClicked();
    break;

  case VIEWERBUTTON_HELP:
    PRIVATE(this)->helpbuttonClicked();
    break;

  case VIEWERBUTTON_HOME:
    PRIVATE(this)->homebuttonClicked();
    break;

  case VIEWERBUTTON_SET_HOME:
    PRIVATE(this)->sethomebuttonClicked();
    break;

  case VIEWERBUTTON_VIEW_ALL:
    PRIVATE(this)->viewallbuttonClicked();
    break;

  case VIEWERBUTTON_SEEK:
    this->seekbuttonClicked();
    break;

  default:
    for (i = 0; i < this->appButtonList->getLength(); i++)
      if (Win32::GetWindowLong((HWND) (* this->appButtonList)[i], GWL_ID) == id) {
        if (PRIVATE(this)->appPushButtonCB)
          PRIVATE(this)->appPushButtonCB((HWND) (* this->appButtonList)[i],
                                            id, PRIVATE(this)->appPushButtonData, NULL);
        break;
      }
    break;
  }

  return 0;
}

LRESULT
SoWinFullViewer::onMeasureItem(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  UINT id = (UINT) wparam; // control identifier
  LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lparam; // item-size information

  for (int i = 0; i < this->appButtonList->getLength(); i++)
    if (Win32::GetWindowLong((HWND) (* this->appButtonList)[i], GWL_ID) == id) {
      if (PRIVATE(this)->createAppPushButtonCB)
        PRIVATE(this)->createAppPushButtonCB(lpmis, PRIVATE(this)->createAppPushButtonData);
      break;
    }
  return 0;
}

LRESULT
SoWinFullViewer::onDrawItem(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  UINT id = (UINT) wparam; // control identifier
  LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lparam; // item-drawing information

  for (int i = 0; i < this->appButtonList->getLength(); i++)
    if (Win32::GetWindowLong((HWND) (* this->appButtonList)[i], GWL_ID) == id) {
      if (PRIVATE(this)->redrawAppPushButtonCB)
        PRIVATE(this)->redrawAppPushButtonCB(lpdis, PRIVATE(this)->redrawAppPushButtonData);
      break;
    }
  return 0;
}

void
SoWinFullViewer::setCameraZoom(float val)
{
  SoCamera * cam = this->getCamera();
  if (! cam) return; // can happen for empty scenegraph

  SoType t = cam->getTypeId();

  if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
    ((SoPerspectiveCamera *) cam)->heightAngle = val * 2.0f * M_PI / 360.0f;
  else if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    ((SoOrthographicCamera *) cam)->height = val;

#if SOWIN_DEBUG
  else assert(0);
#endif // SOWIN_DEBUG
}

float
SoWinFullViewer::getCameraZoom(void)
{
  SoCamera * cam = this->getCamera();
  if (! cam) return 0.0f; // can happen for empty scenegraph

  SoType t = cam->getTypeId();

  if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
    return ((SoPerspectiveCamera *) cam)->heightAngle.getValue() /
      2.0f * 360.0f / M_PI;
  else if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    return ((SoOrthographicCamera *) cam)->height.getValue();

#if SOWIN_DEBUG
  assert(0);
#endif // SOWIN_DEBUG
  return 0.0f;
}

// SoAnyFullViewer needs this method to be protected. mariusbu 20010723.
// FIXME: SoAnyFullViewer now made obsolete. 20020111 mortene.
void
SoWinFullViewer::seekbuttonClicked(void)
{
  this->setSeekMode(this->isSeekMode() ? FALSE : TRUE);
}

///////////////////////////////////////////////////////////////////
//
//  (private)
//
//

void
SoWinFullViewerP::leftWheelCB(SoWinFullViewer * viewer, void ** data)
{

  if (data == NULL) {
    viewer->leftWheelStart();
    return;
  }

  if ((int) data == -1) {
    viewer->leftWheelFinish();
    return;
  }

  viewer->leftWheelMotion(** (float **) data);
}

void
SoWinFullViewerP::bottomWheelCB(SoWinFullViewer * viewer, void ** data)
{

  if (data == NULL) {
    viewer->bottomWheelStart();
    return;
  }

  if ((int) data == -1) {
    viewer->bottomWheelFinish();
    return;
  }

  viewer->bottomWheelMotion(** (float **) data);
}

void
SoWinFullViewerP::rightWheelCB(SoWinFullViewer * viewer, void ** data)
{

  if (data == NULL) {
    viewer->rightWheelStart();
    return;
  }

  if ((int) data == -1) {
    viewer->rightWheelFinish();
    return;
  }

  viewer->rightWheelMotion(** (float **) data);
}

void
SoWinFullViewerP::interactbuttonClicked(void)
{
  VIEWERBUTTON_O(SoWinFullViewer::ButtonId::VIEWERBUTTON_PICK)->setState(TRUE);
  VIEWERBUTTON_O(SoWinFullViewer::ButtonId::VIEWERBUTTON_VIEW)->setState(FALSE);
  if (this->owner->isViewing())
    this->owner->setViewing(FALSE);
}

void
SoWinFullViewerP::viewbuttonClicked(void)
{
  VIEWERBUTTON_O(SoWinFullViewer::ButtonId::VIEWERBUTTON_VIEW)->setState(TRUE);
  VIEWERBUTTON_O(SoWinFullViewer::ButtonId::VIEWERBUTTON_PICK)->setState(FALSE);
  if (! this->owner->isViewing())
    this->owner->setViewing(TRUE);
}

void
SoWinFullViewerP::helpbuttonClicked(void)
{
  this->owner->openViewerHelpCard();
}

void
SoWinFullViewerP::homebuttonClicked(void)
{
  this->owner->resetToHomePosition();
}

void
SoWinFullViewerP::sethomebuttonClicked(void)
{
  this->owner->saveHomePosition();
}

void
SoWinFullViewerP::viewallbuttonClicked(void)
{
  this->owner->viewAll();
}

int
SoWinFullViewerP::layoutWidgets(int cx, int cy)
{
  int i, x, y, width, height, bottom, right, top;
  int numViewerButtons = this->owner->viewerButtonList->getLength();
  int numAppButtons = this->owner->appButtonList->getLength();
  HWND renderArea = this->owner->getBaseWidget();
  UINT flags = SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW;
  
  // RenderArea
  assert(IsWindow(renderArea));

  if (this->decorations) {
    Win32::SetWindowPos(renderArea, NULL, DECORATION_SIZE, 0, 0, 0, flags);
  }
  else {
    Win32::SetWindowPos(renderArea, NULL, 0, 0, 0, 0, flags);
    return 0;
  }
  
  if (SoWinFullViewerP::doButtonBar) {

    // Viewer buttons
    for(i = 0; i < numViewerButtons; i++)
      VIEWERBUTTON_O(i)->move(cx - DECORATION_SIZE, DECORATION_SIZE * i);

    // App buttons
    for(i = 0; i < numAppButtons; i++) {
      Win32::MoveWindow(APPBUTTON_O(i),
                         0, (DECORATION_SIZE * (i + numViewerButtons)),
                         DECORATION_SIZE, DECORATION_SIZE, TRUE);
    }
  }

  // Wheels

  bottom = (cy - (DECORATION_SIZE + DECORATION_BUFFER));
  right = (cx - (
                  (this->owner->rightWheel ? this->owner->rightWheel->getLabelSize().cx : 0) + 8));

  // Left wheel
  if (this->owner->leftWheel) {

    x = (DECORATION_SIZE / 2) - (this->owner->leftWheel->sizeHint().cx / 2) - 1;
    width = this->owner->leftWheel->sizeHint().cx;

    top = numAppButtons * DECORATION_SIZE + DECORATION_BUFFER;

    // if area is large enough for full height
    if ((bottom - top) > this->owner->leftWheel->sizeHint().cy) {

      height = this->owner->leftWheel->sizeHint().cy;

      y = bottom - height;

    } // else we must use all available space
    else {

      y = top;

      height = bottom - top;

    }

    this->owner->leftWheel->move(x, y, width, height);
  }

  // Bottom wheel
  if (this->owner->bottomWheel) {

    x += this->owner->leftWheel->getLabelSize().cx +
      this->owner->bottomWheel->getLabelSize().cx + 8;
    y = (cy - DECORATION_SIZE) +
      ((DECORATION_SIZE / 2) - (this->owner->bottomWheel->sizeHint().cy / 2) + 1);

    height = this->owner->bottomWheel->sizeHint().cy;

    if (right < (x + this->owner->bottomWheel->sizeHint().cx)) {

      width = right - x;

    }
    else {

      width =  this->owner->bottomWheel->sizeHint().cx;

    }

    this->owner->bottomWheel->move(x, y, width, height);

  }

  // Right wheel
  if (this->owner->rightWheel) {

    width = this->owner->rightWheel->sizeHint().cx;

    x = (cx - DECORATION_SIZE) +
      ((DECORATION_SIZE / 2) - (width / 2) + 1);

    top = numViewerButtons * DECORATION_SIZE + DECORATION_BUFFER;

    // if area is large enough for original height
    if ((bottom - top) > this->owner->rightWheel->sizeHint().cy) {

      height = this->owner->rightWheel->sizeHint().cy;

      y = bottom - height;

    } // else we must use all available space
    else {

      y = top;

      height = bottom - top;

    }

    this->owner->rightWheel->move(x, y, width, height);
  }

  return 0;
}

LRESULT CALLBACK
SoWinFullViewerP::callWndProc(int code, WPARAM wparam, LPARAM lparam)
{
  CWPSTRUCT * msg = (CWPSTRUCT *)lparam;
  SoWinComponent * component = SoWinComponent::getComponent(msg->hwnd);
  SoType fullvt = SoWinFullViewer::getClassTypeId();
  if (component && component->getTypeId().isDerivedFrom(fullvt)) {
    SoWinFullViewer * object = (SoWinFullViewer *)component;

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
        SetFocus(object->getGLWidget());
        break;

        // Next 3 are for the UI decoration buttons.

      case WM_COMMAND:
        object->onCommand(msg->hwnd, msg->message, msg->wParam, msg->lParam);
        break;

      case WM_MEASUREITEM:
        object->onMeasureItem(msg->hwnd, msg->message, msg->wParam, msg->lParam);
        break;

      case WM_DRAWITEM:
        object->onDrawItem(msg->hwnd, msg->message, msg->wParam, msg->lParam);
        break;
      }
    }
  }

  return CallNextHookEx(SoWinFullViewerP::hookhandle, code, wparam, lparam);
}

// *************************************************************************

// FIXME: these are present in the other So* toolkits, but was missing
// in SoWin. Why? 20020111 mortene.

void
SoWinFullViewer::createViewerButtons(HWND parent, SbPList * buttonlist)
{
}

HWND
SoWinFullViewer::buildLeftTrim(HWND parent)
{
  return NULL;
}

HWND
SoWinFullViewer::buildBottomTrim(HWND parent)
{
  return NULL;
}

HWND
SoWinFullViewer::buildRightTrim(HWND parent)
{
  return NULL;
}
