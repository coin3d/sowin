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

#include <assert.h>
#include <string.h>
#include <windows.h>

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SoLists.h>
#include <Inventor/errors/SoDebugError.h>

#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoWinComponent.h>
#include <Inventor/Win/SoWinGLWidget.h>
#include <Inventor/Win/SoWinRenderArea.h>
#include <Inventor/Win/viewers/SoWinViewer.h>
#include <Inventor/Win/viewers/SoWinFullViewer.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/Win/viewers/SoWinPlaneViewer.h>
#include <sowindefs.h> // SOWIN_STUB
#include <Inventor/Win/Win32API.h>

// *************************************************************************

SOWIN_OBJECT_ABSTRACT_SOURCE(SoWinComponent);

// *************************************************************************

// The private data for the SoWinComponent.

class SoWinComponentP {
  
public:
  // Constructor.
  SoWinComponentP(SoWinComponent * o)
  {

    this->owner = o;

    if (! SoWinComponentP::sowincomplist)
      SoWinComponentP::sowincomplist = new SbPList;
    SoWinComponentP::sowincomplist->append((void *) this->owner);
  }

  // Destructor.
  ~SoWinComponentP() {

    if (SoWinComponentP::sowincomplist) {
      SoWinComponentP::sowincomplist->removeItem(this->owner);
      if (SoWinComponentP::sowincomplist->getLength() == 0) {
        delete SoWinComponentP::sowincomplist;
        SoWinComponentP::sowincomplist = NULL;

        // FIXME: only unregister classname when all component windows
        // have been destroyed.  CreateWindow get the default "Win
        // Component" name, even when created by viewers like
        // SoWinExaminerViewer. Is this a bug? In that case fix this
        // too!
        //
        // mariusbu 20010803.
        
        if (SoWinComponentP::wndClassAtom) { // if wndclass is registered
          Win32::UnregisterClass("Component Widget", SoWin::getInstance());
          SoWinComponentP::wndClassAtom = NULL;
        }
      }
    }
  }

  // event handler
  static LRESULT CALLBACK
  eventHandler(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
  {
    SoWinComponent * component = SoWinComponent::getComponent(window);

    // FIXME?: there's a potential problem here for the application
    // programmer, which was reported by Alan Walford of Eos. It is a
    // complex issue where a bug can be triggered like this:
    // 
    // 0) the construction of a SoWinGLWidget-derived instance (like
    // for instance a renderarea) fails due to lack of or faulty
    // OpenGL-support -- or due to any other fatal error condition
    //
    // 1) SoWinGLWidget::buildGLWidget() (for instance) then calls
    // SoAny::invokeFatalErrorHandler()
    //
    // 2) the app-programmer's registered fatal error handler throws a
    // C++ exception which is caught "higher up", so the construction
    // of the SoWinGLWidget-derived instance is never completed, and
    // neither has it been destructed -- it is therefore in an invalid
    // state, which goes undetected from within SoWin
    //
    // 3) in the process of cleaning up, the application client code
    // causes a message to be sent to the SoWinGLWidget-instance's
    // window, which triggers the function this FIXME comment is
    // placed inside
    //
    // 4) below, operations on the instance is done -- which of course
    // causes a crash, since it was never properly initialized
    //
    // This is a hard bug to detect and solve for the application
    // programmers, so anything we could do to either detect and work
    // around the problem -- or at least trigger a helpful assert() --
    // would be a good thing.
    //
    // 20011018 mortene (thanks to Alan for explaining the problem).

    if (component) {

      switch (message) {
      
        case WM_SIZE:
          component->sizeChanged(SbVec2s(LOWORD(lparam), HIWORD(lparam)));
          break;
          
        case WM_CLOSE:
          component->hide();
          component->windowCloseAction();
          return 0;
      
        case WM_SETFOCUS:
          if (IsWindow(component->pimpl->focusProxy)) {
            SetFocus(component->pimpl->focusProxy);
          }
          return 0;
          
        case WM_SHOWWINDOW:
          if (! component->realized) {
            component->afterRealizeHook();
            component->realized = TRUE;
          }
          break;
          
      }
    }
    
    return DefWindowProc(window, message, wparam, lparam);
  }
  
  // Message hook
  static LRESULT CALLBACK
  callWndProc(int code, WPARAM wparam, LPARAM lparam)
  {
    CWPSTRUCT * msg = (CWPSTRUCT *) lparam;
    if (HC_ACTION);// must process message
    
    SoWinComponent * component = SoWinComponent::getComponent(msg->hwnd);
    if (component) {
      if (code >= 0) {

        switch (msg->message) {
        
          case WM_SIZE:
            component->sizeChanged(SbVec2s(LOWORD(msg->lParam), HIWORD(msg->lParam)));
            break;
        
          case WM_SETFOCUS:
            if (IsWindow(component->pimpl->focusProxy)) {
              SetFocus(component->pimpl->focusProxy);
            }
            break;

          case WM_CLOSE:
            component->windowCloseAction();
            break;
            
          case WM_SHOWWINDOW:
          if (! component->realized) {
            component->afterRealizeHook();
            component->realized = TRUE;
          }
          break;
            
        }
      }
      return CallNextHookEx(component->pimpl->msgHook, code, wparam, lparam);
    }
    return 0;
  }

  // Variables.
  HHOOK msgHook;
  HWND parent;
  HWND widget;
  HWND focusProxy;
  SbBool embedded;
  SbString classname, widgetname, title;
  SoWinComponentCB * closeCB;
  void * closeCBdata;
  SbPList * visibilitychangeCBs;

  // This is the atom returned when the component
  // window class is registered.
  static ATOM wndClassAtom;
  
  // List of all SoWinComponent instances. Needed for the
  // SoWinComponent::getComponent() function.
  static SbPList * sowincomplist;

  struct FullscreenData {
    FullscreenData(void)
      : on(FALSE)
    { }

    SbBool on;
    SbVec2s pos;
    SbVec2s size;
    LONG style;
    LONG exstyle;
  };

  struct FullscreenData fullscreendata;

private:
  
  SoWinComponent * owner;
  
};

ATOM SoWinComponentP::wndClassAtom = NULL;
SbPList * SoWinComponentP::sowincomplist = NULL;

#define PRIVATE(o) (o->pimpl)

// *************************************************************************

/*!
  \internal
  This function initializes the type system for all the component classes.
  It is called indirectly when you call SoWin::init().
*/
void
SoWinComponent::initClasses(void)
{
  SoWinComponent::initClass();
  SoWinGLWidget::initClass();
  SoWinRenderArea::initClass();
  SoWinViewer::initClass();
  SoWinFullViewer::initClass();
  SoWinExaminerViewer::initClass();
  SoWinPlaneViewer::initClass();
} // initClasses()

// *************************************************************************

///////////////////////////////////////////////////////////////////
//
//  Constructor/Destructor
//  (protected)
//

/*!
  Constructor.

  \a parent is the widget we'll build this component inside. If \a
  parent is \c NULL, make a new toplevel window.

  \a name is mostly interesting for debugging purposes.

  \a buildInsideParent specifies whether or not we should make a new
  toplevel window for the component even when we've got a non-NULL \a
  parent.
*/
SoWinComponent::SoWinComponent(const HWND parent,
                               const char * const name,
                               const SbBool embed)
{
  this->pimpl = new SoWinComponentP(this);
  this->realized = FALSE;

  PRIVATE(this)->focusProxy = NULL;
  
  PRIVATE(this)->closeCB = NULL;
  PRIVATE(this)->closeCBdata = NULL;
  PRIVATE(this)->visibilitychangeCBs = new SbPList;
 
  PRIVATE(this)->widget = NULL;
  PRIVATE(this)->embedded = embed;

  if (IsWindow(parent) && embed) {
    PRIVATE(this)->parent = parent;
    PRIVATE(this)->msgHook =
      Win32::SetWindowsHookEx(WH_CALLWNDPROC, SoWinComponentP::callWndProc,
                              NULL, GetCurrentThreadId());
  }
  else {
    PRIVATE(this)->parent = this->buildFormWidget(parent);
    PRIVATE(this)->msgHook = NULL;
  }

  if (name) {
    PRIVATE(this)->widgetname = name;
    this->setTitle(name);
  }
} // SoWinComponent()

///////////////////////////////////////////////////////////////////
//
//  (public)
//

/*!
  Destructor.
*/
SoWinComponent::~SoWinComponent(void)
{
  if (PRIVATE(this)->msgHook)
    UnhookWindowsHookEx(PRIVATE(this)->msgHook);
  
  for (int i = PRIVATE(this)->visibilitychangeCBs->getLength();
        i > 0; i--) {
    PRIVATE(this)->visibilitychangeCBs->remove(i);
  }
  delete PRIVATE(this)->visibilitychangeCBs;
  
  if (IsWindow(PRIVATE(this)->parent)) {
    Win32::DestroyWindow(PRIVATE(this)->parent);
  }
  
  delete this->pimpl;
} //~SoWinComponent()

/*!
  This will show the widget, deiconifiying and raising it if
  necessary.

  \sa hide(), isVisible()
*/
void
SoWinComponent::show(void)
{
  (void)ShowWindow(PRIVATE(this)->parent, SW_SHOW);
  Win32::InvalidateRect(PRIVATE(this)->parent, NULL, FALSE);
} // show()

/*!
  This will hide the widget.

  \sa show(), isVisible()
*/
void
SoWinComponent::hide(void)
{
  (void)ShowWindow(PRIVATE(this)->parent, SW_HIDE);
} // hide()

/*!
  Toggle full screen mode for this component, if possible.

  Returns \c FALSE if operation failed.  This might happen if the
  toolkit doesn't support attempts at making the component cover the
  complete screen or if the component is not a toplevel window.
*/
SbBool
SoWinComponent::setFullScreen(const SbBool enable)
{
  SoWinComponentP::FullscreenData * data = &(PRIVATE(this)->fullscreendata);
  if (enable == data->on) { return TRUE; }
  data->on = enable;
  
  HWND hwnd = this->getParentWidget();
  if (hwnd != this->getShellWidget()) {
    return FALSE;
  }

  if (enable) {
    // Save size, position and styles.
    RECT rect;
    Win32::GetWindowRect(hwnd, & rect);
    data->style = Win32::SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    data->exstyle = Win32::SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_TOPMOST);
    
    if (data->style & WS_MAXIMIZE) {
      data->pos.setValue(0, 0);
      data->size.setValue(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN));
    }
    else {
      data->pos.setValue(rect.left, rect.top);
      data->size.setValue(rect.right - rect.left, rect.bottom - rect.top);
    }
    // Go fullscreen.
    
    Win32::MoveWindow(hwnd,
                       0,
                       0,
                       GetSystemMetrics(SM_CXSCREEN),
                       GetSystemMetrics(SM_CYSCREEN),
                       TRUE);
    
    // FIXME: isn't there a specific method in the Win32 API for
    // maximizing a window? If yes, use that mechanism instead of this
    // "homegrown" method with MoveWindow() resizing. 20010820 mortene.
    // ShowWindow(hwnd, SW_MAXIMIZE);
  }
  else {
    // Go "normal".
    // ShowWindow(hwnd, SW_RESTORE);
    (void)Win32::SetWindowLong(hwnd, GWL_STYLE, data->style | WS_VISIBLE);
    (void)Win32::SetWindowLong(hwnd, GWL_EXSTYLE, data->exstyle);
    
    Win32::MoveWindow(hwnd,
                       (data->pos[0] > -1 ? data->pos[0] :
                         ((GetSystemMetrics(SM_CXSCREEN) / 2) - 210)),
                       (data->pos[1] > -1 ? data->pos[1] :
                         ((GetSystemMetrics(SM_CYSCREEN) / 2) - 250)),
                       (data->size[0] > 0 ? data->size[0] : 420),
                       (data->size[1] > 0 ? data->size[1] : 500),
                       TRUE);
    
  }

  return TRUE;
} //setFullScreen()

/*!
  Returns if this widget/component is in full screen mode.

  \sa setFullScreen()
*/
SbBool
SoWinComponent::isFullScreen(void) const
{
  return PRIVATE(this)->fullscreendata.on;
} // isFullScreen()

/*!
  Returns visibility status on the widget. If any parents of this
  widget or this widget itself is hidden, returns \c FALSE.

  Note that a widget which is just obscured by other windows on the
  desktop is not hidden in this sense, and \c TRUE will be returned.

  \sa show(), hide()
*/
SbBool
SoWinComponent::isVisible(void)
{
  return IsWindowVisible(PRIVATE(this)->widget);
} // isVisible()

/*!
  Returns a pointer to the component's window system widget.

  \sa getShellWidget(), getParentWidget()
*/
HWND
SoWinComponent::getWidget(void) const
{
  return PRIVATE(this)->widget;
} // getWidget()

/*!
  An SoWinComponent may be composed of any number of widgets in
  parent-children relationships in a tree structure with any depth.
  This method will return the root widget in that tree.

  \sa setBaseWidget()
*/
HWND
SoWinComponent::baseWidget(void) const
{
  return this->getBaseWidget();
} // baseWidget()

/*!
  An SoWinComponent may be composed of any number of widgets in
  parent-children relationships in a tree structure with any depth.
  This method will return the root widget in that tree.

  \sa setBaseWidget()
*/
HWND
SoWinComponent::getBaseWidget(void) const
{
  return this->getWidget();
} // getBaseWidget()

/*!
  Returns \c TRUE if this component is a toplevel shell, i.e. it has a
  window representation on the desktop.

  \sa getShellWidget()
*/
SbBool
SoWinComponent::isTopLevelShell(void) const
{
  return (PRIVATE(this)->embedded ? FALSE : TRUE);
  // FIXME: compare with SoWin::getTopLevelWidget() ? mariusbu 20010806.
} // isTopLevelShell()

/*!
  Returns the toplevel shell widget for this component. The toplevel
  shell is the desktop window which contains the component.

  \sa isTopLevelShell(), getWidget()
*/
HWND
SoWinComponent::getShellWidget(void) const
{
  LONG style;
  HWND hwnd;
  HWND parent = PRIVATE(this)->parent;
  
  do {
    hwnd = parent;
    style = Win32::GetWindowLong(hwnd, GWL_STYLE);
    if (style & WS_OVERLAPPEDWINDOW) break;
    parent = GetParent(hwnd);
  } while(IsWindow(parent));
  
  return hwnd;
} // getShellWidget()

/*!
  Returns the widget which is the parent (i.e. contains) this
  component's base widget.

  \sa getWidget(), baseWidget(), isTopLevelShell()
*/
HWND
SoWinComponent::getParentWidget(void) const
{
  return PRIVATE(this)->parent;
} // getParentWidget()

/*!
  Resize the component widget.

  \sa getSize()
*/
void
SoWinComponent::setSize(const SbVec2s size)
{
  UINT flags = SWP_NOMOVE | SWP_NOZORDER; // do redraw
  Win32::SetWindowPos(this->getShellWidget(), NULL, 0, 0,
                       size[0], size[1], flags);
} // setSize()

/*!
  Returns the component widget size.

  \sa setSize()
*/
SbVec2s
SoWinComponent::getSize(void) const
{
  RECT rect;
  Win32::GetWindowRect(this->getShellWidget(), & rect);
  return SbVec2s(rect.right - rect.left, rect.bottom - rect.top);
} // getSize()

/*!
  Returns name of the widget.
*/
const char *
SoWinComponent::getWidgetName(void) const
{
  return PRIVATE(this)->widgetname.getLength() ?
    PRIVATE(this)->widgetname.getString() : this->getDefaultWidgetName();
} // getWidgetName()

/*!
  Returns class name of widget.
*/
const char *
SoWinComponent::getClassName(void) const
{
  return PRIVATE(this)->classname.getString();
} // getClassName()

/*!
  Set the window title of this component. This will not work unless
  the component is a toplevel shell.

  \sa getTitle(), setIconTitle(), isTopLevelShell()
*/
void
SoWinComponent::setTitle(const char * const title)
{
  if (title) {
    PRIVATE(this)->title = title;
  }
  else {
    PRIVATE(this)->title = "";
  }

  HWND shellWidget = this->getShellWidget();
  if (shellWidget == SoWin::getTopLevelWidget() ||
       shellWidget == this->getParentWidget()) {
    Win32::SetWindowText(shellWidget, PRIVATE(this)->title.getString());
  }
} // setTitle()

/*!
  Returns the window title. The component should be a toplevel shell
  if you call this method.

  \sa setTitle(), isTopLevelShell()
*/
const char *
SoWinComponent::getTitle(void) const
{
  return (PRIVATE(this)->title.getLength() > 0 ?
    PRIVATE(this)->title.getString() : this->getDefaultTitle());
} // getTitle()

/*! FIXME: doc */
void
SoWinComponent::setIconTitle(const char * const title)
{
  // FIXME: seems to easy.. is this really correct? 20011012 mortene.
  this->setTitle(title);
}

/*! FIXME: doc */
const char *
SoWinComponent::getIconTitle(void) const
{
  // FIXME: seems to easy.. is this really correct? 20011012 mortene.
  return this->getTitle();
}

/*! FIXME: doc */
const char *
SoWinComponent::getDefaultIconTitle(void) const
{
  // FIXME: seems to easy.. is this really correct? 20011012 mortene.
  return this->getDefaultTitle();
}

/*!
  Set up a callback function to use when the component gets closed. A
  component must be a toplevel shell for this to have any effect.

  For toplevel shells with no close callback set, the window will
  simply be hidden. The typical action to take in the callback would
  be to delete the component.

  \sa isTopLevelShell()
*/
void
SoWinComponent::setWindowCloseCallback(SoWinComponentCB * func, void * data)
{
  PRIVATE(this)->closeCB = func;
  PRIVATE(this)->closeCBdata = data; 
} // setWindowCloseCallback()

/*!
  Finds and returns the SoWinComponent corresponding to the given
  HWND, if any. If no SoWinComponent is the "owner" of the widget,
  \c NULL will be returned.
*/
SoWinComponent *
SoWinComponent::getComponent(HWND const widget)
{
  for (int i = 0; i < SoWinComponentP::sowincomplist->getLength(); i++) {
    SoWinComponent * c = (SoWinComponent *) SoWinComponentP::sowincomplist->get(i);
    if (c->getParentWidget() == widget) return c;
  }
  return NULL;
} // getComponent()

/*!
  Set \a widget as focus proxy. Returns previously set focus proxy.

  \sa getFocusProxy()
*/
HWND
SoWinComponent::setFocusProxy(HWND widget)
{
  HWND w = PRIVATE(this)->focusProxy;
  PRIVATE(this)->focusProxy = widget;
  return w;
} // setFocusProxy()

/*!
  Get currently set focus proxy. Returns NULL if no focus proxy is set.

  \sa setFocusProxy()
*/
HWND
SoWinComponent::getFocusProxy(void)
{
  return PRIVATE(this)->focusProxy;
} // getFocusProxy()

///////////////////////////////////////////////////////////////////
//
//  (protected)
//

/*!
  Set the core widget for this SoWin component. It is important that
  subclasses get this correct, as the widget set here will be the
  widget returned from query methods.

  \sa baseWidget()
*/
void
SoWinComponent::setBaseWidget(HWND widget)
{
  assert(IsWindow(widget));
  PRIVATE(this)->widget = widget;
} // setBaseWidget()

/*!
  Set class name of widget.

  \sa getClassName(), componentClassName()
*/
void
SoWinComponent::setClassName(const char * const name)
{
  if (name)
    PRIVATE(this)->classname = name;
  else
    PRIVATE(this)->classname = "";
} // setClassName()

/*!
 */  
HWND
SoWinComponent::buildFormWidget(HWND parent)
{

  if (! SoWinComponentP::wndClassAtom) {

    WNDCLASS windowclass;
    
    LPCTSTR icon = MAKEINTRESOURCE(IDI_APPLICATION);
    LPCTSTR cursor = MAKEINTRESOURCE(IDC_ARROW);
    HBRUSH brush = (HBRUSH) GetSysColorBrush(COLOR_BTNFACE);

    windowclass.lpszClassName = "Component Widget";
    windowclass.hInstance = SoWin::getInstance();
    windowclass.lpfnWndProc = SoWinComponentP::eventHandler;
    windowclass.style = CS_OWNDC;
    windowclass.lpszMenuName = NULL;
    windowclass.hIcon = LoadIcon(SoWin::getInstance(), icon);
    windowclass.hCursor = LoadCursor(SoWin::getInstance(), cursor);
    windowclass.hbrBackground = brush;
    windowclass.cbClsExtra = 0;
    windowclass.cbWndExtra = 4;

    SoWinComponentP::wndClassAtom = Win32::RegisterClass(& windowclass);

  }

  HWND parentWidget = NULL;

  // When this method is called, the component is *not* embedded. mariusbu 20010727.
  parentWidget = CreateWindow("Component Widget",
                               this->getTitle(),
                               WS_OVERLAPPEDWINDOW |
                               WS_VISIBLE |
                               WS_CLIPSIBLINGS |
                               WS_CLIPCHILDREN,
                               CW_USEDEFAULT,
                               CW_USEDEFAULT,
                               500,
                               500,
                               parent,
                               NULL,
                               SoWin::getInstance(),
                               this);

  assert(IsWindow(parentWidget));
  return parentWidget;
} // buildFormWidget()

/*!
  This method is invoked to notify the component that the size has
  changed.  It is called from the top and all the way down to the
  bottom, the size being adjusted to take into account extra
  decorations having been added at each level in the component class
  hierarchy.
*/
void
SoWinComponent::sizeChanged(const SbVec2s & size)
{

  // The default implementation does nothing.
} // sizeChanged()

/*!
  Returns the default name of an SoQtComponent widget. Should be
  overloaded by subclasses.
*/
const char *
SoWinComponent::getDefaultWidgetName(void) const
{
  static const char defaultWidgetName[] = "SoWinComponent";
  return defaultWidgetName;
} // getDefaultWidgetName()

/*!
  Returns the default window caption string of this component. Should
  be overloaded by subclasses.
*/
const char *
SoWinComponent::getDefaultTitle(void) const
{
  static const char defaultTitle[] = "Win Component";
  return defaultTitle;
} // getDefaultTitle()

/*!
*/
void
SoWinComponent::windowCloseAction(void)
{
  if (PRIVATE(this)->closeCB)
    PRIVATE(this)->closeCB(PRIVATE(this)->closeCBdata, this);
} // windowCloseAction()

/*!
*/  
void
SoWinComponent::afterRealizeHook(void) // virtual
{
  // Set shell widget title.
  HWND shellWidget = this->getShellWidget();
  if (PRIVATE(this)->title.getLength() == 0 &&
    (shellWidget == SoWin::getTopLevelWidget() ||
      shellWidget == this->getParentWidget())) {
    this->setTitle(this->getDefaultTitle());
  }
} // afterRealizeHook()

/*!
  Add a callback which will be called whenever the widget component
  changes visibility status (because of iconification or
  deiconification, for instance).

  \sa removeVisibilityChangeCallback(), isVisible()
*/
void
SoWinComponent::addVisibilityChangeCallback(SoWinComponentVisibilityCB * func, void * user)
{
  void ** combo = new void * [2];
  combo[0] = func;
  combo[1] = user;
  PRIVATE(this)->visibilitychangeCBs->append(combo);
  //FIXME: the functions are never called. mariusbu 20010824.
} // addVisibilityChangeCallback()

/*!
  Remove one of the callbacks from the list of visibility notification
  callbacks.

  \sa addVisibilityChangeCallback(), isVisible()
*/
void
SoWinComponent::removeVisibilityChangeCallback(SoWinComponentVisibilityCB * func, void * user)
{
  void ** combo;
  for (int i = 0; i < PRIVATE(this)->visibilitychangeCBs->getLength(); i++) {
    combo = (void **) PRIVATE(this)->visibilitychangeCBs->get(i);
    if ((combo[0] == func) &&  (combo[1] == user)) {
      PRIVATE(this)->visibilitychangeCBs->remove(i);
      delete combo;
      return;
    }
  }
} // removeVisibilityChangeCallback()/

/*!
  Open a dialog providing help about use of this component.

  NB: no help system has been implemented yet, so for the time being
  this will only pop up an error message.
*/
void
SoWinComponent::openHelpCard(const char * name)
{
  MessageBox(PRIVATE(this)->parent,
    "The help functionality has not been implemented.",
    "SoWin", MB_ICONEXCLAMATION | MB_OK);
} // openHelpCard()

///////////////////////////////////////////////////////////////////
//
//  (private)
//
