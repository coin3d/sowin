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

// Class documentation in common/SoGuiGLWidgetCommon.cpp.in.

// *************************************************************************

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/Win/common/gl.h>

#include <Inventor/SbVec2s.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/SoWinGLWidget.h>
#include <Inventor/Win/SoWinGLWidgetP.h>
#include <Inventor/Win/SoAny.h>
#include <sowindefs.h>
#include <Inventor/Win/Win32API.h>

#if SOWIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#include <conio.h>
#endif // SOWIN_DEBUG

static const int SO_BORDER_THICKNESS = 2;

SOWIN_OBJECT_ABSTRACT_SOURCE(SoWinGLWidget);

// The private data and code for the SoWinGLWidget.

SoWinGLWidgetP::SoWinGLWidgetP(SoWinGLWidget * o)
  : SoGuiGLWidgetP(o)
{
  this->bordersize = 0;
  this->lockcounter = 0;
  this->overlaylockcounter = 0;
}

// Destructor.
SoWinGLWidgetP::~SoWinGLWidgetP()
{
}

ATOM SoWinGLWidgetP::managerWndClassAtom = NULL;
ATOM SoWinGLWidgetP::glWndClassAtom = NULL;
int SoWinGLWidgetP::widgetCounter = 0;

///////////////////////////////////////////////////////////////////
//
//  Constructor / Destructor
//  (protected)
//

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SoWinGLWidget::SoWinGLWidget(HWND parent,
                              const char * name,
                              SbBool embed,
                              int glModes,
                              SbBool build)
  : SoWinComponent(parent, name, embed)
{
  this->pimpl = new SoWinGLWidgetP(this);
  this->waitForExpose = TRUE;
  this->parent = parent;

  PRIVATE(this)->managerWidget = NULL;
  PRIVATE(this)->normalWidget = NULL;
  PRIVATE(this)->overlayWidget = NULL;

  PRIVATE(this)->drawToFrontBuffer = FALSE;

  PRIVATE(this)->ctxNormal = NULL;
  PRIVATE(this)->ctxOverlay = NULL;

  PRIVATE(this)->hdcNormal = NULL;
  PRIVATE(this)->hdcOverlay = NULL;

  PRIVATE(this)->glModes = glModes;

  PRIVATE(this)->haveFocus = FALSE;
  PRIVATE(this)->stealFocus = FALSE;
  PRIVATE(this)->glRealized = FALSE;

  this->setClassName("SoWinGLWidget");
	
  if (! build) return;
	
  PRIVATE(this)->managerWidget = this->buildWidget(parent);
  this->setBaseWidget(PRIVATE(this)->managerWidget);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SoWinGLWidget::~SoWinGLWidget()
{
  if (IsWindow(PRIVATE(this)->managerWidget))
    Win32::DestroyWindow(PRIVATE(this)->managerWidget);
  if (IsWindow(PRIVATE(this)->normalWidget))
    Win32::DestroyWindow(PRIVATE(this)->normalWidget);
  if (IsWindow(PRIVATE(this)->overlayWidget))
    Win32::DestroyWindow(PRIVATE(this)->overlayWidget);
  SoWinGLWidgetP::widgetCounter--;
  if (SoWinGLWidgetP::widgetCounter <= 0) {
    Win32::UnregisterClass("Manager Widget", SoWin::getInstance());
    SoWinGLWidgetP::managerWndClassAtom = NULL;
    Win32::UnregisterClass("GL Widget", SoWin::getInstance());
    SoWinGLWidgetP::glWndClassAtom = NULL;
  }
  delete this->pimpl;
}

///////////////////////////////////////////////////////////////////
//
//  (public)
//

/*!
 */
HWND
SoWinGLWidget::getNormalWindow(void) const
{
  return PRIVATE(this)->normalWidget;
}

/*!
 */
HWND
SoWinGLWidget::getOverlayWindow(void) const
{
  // FIXME: overlay not supported yet. mariusbu 20010719.
  return PRIVATE(this)->overlayWidget;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
HWND
SoWinGLWidget::getNormalWidget(void) const
{
  return PRIVATE(this)->normalWidget;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
HWND
SoWinGLWidget::getOverlayWidget(void) const
{
  return PRIVATE(this)->overlayWidget;
}

/*!
  Returns the normal device context.
*/
HDC
SoWinGLWidget::getNormalDC(void) const
{
  assert(PRIVATE(this)->hdcNormal != NULL);
  return PRIVATE(this)->hdcNormal;
}

/*!
  Returns the overlay device context.
*/
HDC
SoWinGLWidget::getOverlayDC(void) const
{
  assert(PRIVATE(this)->hdcOverlay != NULL);
  return PRIVATE(this)->hdcOverlay;
}

/*!
 */
void
SoWinGLWidget::setStealFocus(SbBool doStealFocus)
{
  PRIVATE(this)->stealFocus = doStealFocus;
}

/*!
 */
void
SoWinGLWidget::setNormalVisual(PIXELFORMATDESCRIPTOR * vis)
{
  assert(vis != NULL);
  assert(PRIVATE(this)->hdcNormal != NULL);

  // FIXME: just overwriting the current format is not a good idea, in
  // case the new format doesn't work on our current display. 20011208 mortene.
  (void)memcpy((& PRIVATE(this)->pfdNormal), vis,
                sizeof(PIXELFORMATDESCRIPTOR));

  int format = SoWinGLWidgetP::ChoosePixelFormat(PRIVATE(this)->hdcNormal, vis);
  if (format == 0) { return; }

  this->setPixelFormat(format);
}

/*!
 */
PIXELFORMATDESCRIPTOR * // FIXME: shouldn't this return value be const? 20011208 mortene.
SoWinGLWidget::getNormalVisual(void)
{
  return (& PRIVATE(this)->pfdNormal);
}

/*!
 */
void
SoWinGLWidget::setOverlayVisual(PIXELFORMATDESCRIPTOR * vis)
{
  // FIXME: overlay not supported. mariusbu 20010719.
  assert(vis != NULL);
  assert(PRIVATE(this)->hdcNormal != NULL);

  // FIXME: just overwriting the current format is not a good idea, in
  // case the new format doesn't work on our current display. 20011208 mortene.
  (void)memcpy((& PRIVATE(this)->pfdOverlay), vis,
                sizeof(PIXELFORMATDESCRIPTOR));

  int format = SoWinGLWidgetP::ChoosePixelFormat(PRIVATE(this)->hdcOverlay, vis);
  if (format == 0) { return; }

  this->setPixelFormat(format);
  // FIXME: AFAICS, setPixelFormat() only takes care of the _normal_
  // OpenGL context / canvas, *not* the overlay context. 20011208 mortene.
}

/*!
 */
PIXELFORMATDESCRIPTOR * // FIXME: shouldn't this return value be const? 20011208 mortene.
SoWinGLWidget::getOverlayVisual(void)
{
  return (& PRIVATE(this)->pfdOverlay);
}

/*!
 */
void
SoWinGLWidget::setPixelFormat(int format)
{
  BOOL ok = SetPixelFormat(PRIVATE(this)->hdcNormal, format,
                           &PRIVATE(this)->pfdNormal);
  if (!ok) {
    DWORD dummy;
    SbString err = Win32::getWin32Err(dummy);
    SbString s = "SetPixelFormat(";
    s.addIntString(format);
    s += ") failed with error message ";
    s += err;
    SoDebugError::postWarning("SoWinGLWidget::setPixelFormat", s.getString());
  }

  // FIXME: does this function actually work as expected?
  // Test. 20011208 mortene.

  // FIXME: we should make sure we are robust if a non-supported
  // pixelformat is attempted set -- ie, the "old" format is continued
  // used. 20011208 mortene.

  // FIXME: on success, we need to update the glModes flags according
  // to the properties of the new format. 20011208 mortene.
}

/*!
 */
int
SoWinGLWidget::getPixelFormat(void)
{
  return GetPixelFormat(PRIVATE(this)->hdcNormal);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::setOverlayRender(const SbBool onoff)
{
  SOWIN_STUB();
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::isOverlayRender(void) const
{
  SOWIN_STUB();
  return FALSE;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::setDoubleBuffer(SbBool set)
{
  if (set) {
    PRIVATE(this)->glModes |= SO_GL_DOUBLE;
  }
  else {
    PRIVATE(this)->glModes &= ~SO_GL_DOUBLE;
  }
  Win32::DestroyWindow(this->getNormalWidget());
  PRIVATE(this)->buildNormalGLWidget(PRIVATE(this)->managerWidget);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::isDoubleBuffer(void) const
{
  return (PRIVATE(this)->glModes & SO_GL_DOUBLE ? TRUE : FALSE);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::setBorder(SbBool f)
{
  PRIVATE(this)->bordersize = f ? SO_BORDER_THICKNESS : 0;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::isBorder(void) const
{
  return PRIVATE(this)->bordersize == SO_BORDER_THICKNESS;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::setDrawToFrontBufferEnable(SbBool enable)
{
  PRIVATE(this)->drawToFrontBuffer = enable;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::isDrawToFrontBufferEnable(void) const
{
  return PRIVATE(this)->drawToFrontBuffer;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::setQuadBufferStereo(const SbBool enable)
{
  if (enable) {
    PRIVATE(this)->glModes |= SO_GL_STEREO;
  }
  else {
    PRIVATE(this)->glModes &= ~SO_GL_STEREO;
  }
  Win32::DestroyWindow(this->getNormalWidget());
  PRIVATE(this)->buildNormalGLWidget(PRIVATE(this)->managerWidget);
}


// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::setAccumulationBuffer(const SbBool enable)
{
  // FIXME: not implemented yet. 20020503 mortene.
  SOWIN_STUB();
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::getAccumulationBuffer(void) const
{
  return FALSE;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::setStencilBuffer(const SbBool enable)
{
  // FIXME: not implemented yet. 20020503 mortene.
  SOWIN_STUB();
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::getStencilBuffer(void) const
{
  return FALSE;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::isQuadBufferStereo(void) const
{
  return (PRIVATE(this)->glModes & SO_GL_STEREO ? TRUE : FALSE);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::hasOverlayGLArea(void) const
{
  return (IsWindow(this->getOverlayWidget()) ? TRUE : FALSE);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::hasNormalGLArea(void) const
{
  return (IsWindow(this->getNormalWidget()) ? TRUE : FALSE);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::glScheduleRedraw(void)
{
  return FALSE;
}

///////////////////////////////////////////////////////////////////
//
//  (protected)
//

LRESULT CALLBACK
SoWinGLWidget::mgrWidgetProc(HWND window, UINT message,
                             WPARAM wparam, LPARAM lparam)
{
  // does nothing
  return DefWindowProc(window, message, wparam, lparam);
}

LRESULT CALLBACK
SoWinGLWidget::glWidgetProc(HWND window, UINT message,
                            WPARAM wparam, LPARAM lparam)
{
  if (message == WM_CREATE) {
    CREATESTRUCT * createstruct = (CREATESTRUCT *) lparam;
    SoWinGLWidget * object = (SoWinGLWidget *)(createstruct->lpCreateParams);
    (void)Win32::SetWindowLong(window, GWL_USERDATA, (LONG)object);
    return PRIVATE(object)->onCreate(window, message, wparam, lparam);
  }

  SoWinGLWidget * object = (SoWinGLWidget *)Win32::GetWindowLong(window, GWL_USERDATA);

  if (object && window == object->getNormalWidget()) {

    MSG msg;
    POINT pt = { LOWORD(lparam), HIWORD(lparam) };
    msg.hwnd = window;
    msg.lParam = lparam;
    msg.message = message;
    msg.pt = pt;
    msg.time = GetTickCount();
    msg.wParam = wparam;

    // Get keystrokes
    if(((! PRIVATE(object)->haveFocus) && PRIVATE(object)->stealFocus) ||
        (message == WM_LBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_RBUTTONDOWN)) {
      PRIVATE(object)->haveFocus = (BOOL) SetFocus(window);
    }

    object->processEvent(&msg);

    switch (message) {

    case WM_PAINT:
      object->waitForExpose = FALSE; // flip flag on first expose
      return PRIVATE(object)->onPaint(window, message, wparam, lparam);

    case WM_DESTROY:
      return PRIVATE(object)->onDestroy(window, message, wparam, lparam);

    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
      (void)SetCapture(window);
      return 0;

    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
      (void)ReleaseCapture();
      return 0;

    case WM_KILLFOCUS:
      PRIVATE(object)->haveFocus = FALSE;
      return 0;
    }
  }
  return DefWindowProc(window, message, wparam, lparam);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::redraw(void)
{
  // virtual - does nothing
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::redrawOverlay(void)
{
  // virtual - does nothing
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::processEvent(MSG * msg)
{
  // Nothing is done here for the SoWinGLWidget, as the events we need
  // to handle for this superclass are caught by the method
  // SoWinGLWidget::glWidgetProc() and forwarded directly to
  // SoWinGLWidget::onPaint() etc.  The events we don't care about
  // (like mouse- and keyboard-interaction) are forwarded from
  // glWidgetProc() through this virtual method down to the
  // subclass(es).
  //                          mortene.
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::initGraphic(void)
{
  this->glLockNormal();
  glEnable(GL_DEPTH_TEST);
  this->glUnlockNormal();
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::initOverlayGraphic(void)
{
  // virtual - does nothing
}

// doc in super
void
SoWinGLWidget::sizeChanged(const SbVec2s & newSize)
{
  // virtual - does nothing
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::widgetChanged(HWND newWidget)
{
  // virtual
  // called whenever the widget is changed (i.e. at initialization
  // or after switching from single->double buffer)
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::setGLSize(SbVec2s newSize)
{
  if (newSize == PRIVATE(this)->glSize) return;
  PRIVATE(this)->glSize = newSize;

  UINT flags = SWP_NOMOVE | SWP_NOZORDER;
  Win32::SetWindowPos(PRIVATE(this)->managerWidget, NULL, 0, 0,
                         newSize[0], newSize[1], flags);

  flags = SWP_NOMOVE | SWP_NOZORDER;
  Win32::SetWindowPos(PRIVATE(this)->normalWidget,
                      NULL,
                      PRIVATE(this)->bordersize,
                      PRIVATE(this)->bordersize,
                      newSize[0] - 2 * PRIVATE(this)->bordersize,
                      newSize[1] - 2 * PRIVATE(this)->bordersize,
                      flags);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbVec2s
SoWinGLWidget::getGLSize(void) const
{
  return PRIVATE(this)->glSize;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
float
SoWinGLWidget::getGLAspectRatio(void) const
{
  return (float) PRIVATE(this)->glSize[0] /
    (float) PRIVATE(this)->glSize[1];
}

LRESULT // Used by SoWinRenderArea
SoWinGLWidgetP::eventHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return 0;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
unsigned long
SoWinGLWidget::getOverlayTransparentPixel(void)
{
  SOWIN_STUB();
  // FIXME: investigate if this function is really used for the other
  // toolkits. 20011012 mortene.
  return 0;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::isRGBMode(void)
{
  return (PRIVATE(this)->glModes & SO_GL_RGB);
}

int
SoWinGLWidget::getDisplayListShareGroup(HGLRC ctx)
{
  return 0; // FIXME: nothing done yet!
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
HWND
SoWinGLWidget::buildWidget(HWND parent)
{
  SoWinGLWidgetP::widgetCounter++;

  HMENU menu = NULL;

  // Build managerWidget.  Used only to draw borders.

  if (! SoWinGLWidgetP::managerWndClassAtom) {
    WNDCLASS windowclass;
    windowclass.lpszClassName = "Manager Widget";
    windowclass.hInstance = SoWin::getInstance();
    windowclass.lpfnWndProc = SoWinGLWidget::mgrWidgetProc;
    windowclass.style = NULL;
    windowclass.lpszMenuName = NULL;
    windowclass.hIcon = NULL;
    windowclass.hCursor = Win32::LoadCursor(NULL, IDC_ARROW);
    windowclass.hbrBackground = GetSysColorBrush(COLOR_3DSHADOW);
    windowclass.cbClsExtra = 0;
    windowclass.cbWndExtra = 4;

    SoWinGLWidgetP::managerWndClassAtom = Win32::RegisterClass(&windowclass);
  }

  RECT rect;
  assert(IsWindow(parent) && "buildWidget() argument erroneous");
  Win32::GetClientRect(parent, & rect);

  HWND managerwidget = Win32::CreateWindow_("Manager Widget",
                                            this->getTitle(),
                                            WS_VISIBLE |
                                            WS_CLIPSIBLINGS |
                                            WS_CLIPCHILDREN |
                                            WS_CHILD,
                                            rect.left,
                                            rect.top,
                                            rect.right,
                                            rect.bottom,
                                            parent,
                                            menu,
                                            SoWin::getInstance(),
                                            this);

  PRIVATE(this)->managerWidget = managerwidget;

  // FIXME: looks shaky to keep this here as long as overlay support
  // has not been implemented.  20010920 mortene.
  if (PRIVATE(this)->glModes & SO_GL_OVERLAY) {
    PRIVATE(this)->buildOverlayGLWidget(managerwidget);
  }

  PRIVATE(this)->buildNormalGLWidget(managerwidget);
  this->waitForExpose = TRUE;

  this->setFocusProxy(this->getNormalWidget());

  return managerwidget;
}

HWND
SoWinGLWidget::getManagerWidget(void)
{
  return PRIVATE(this)->managerWidget;
}
/*
HWND
SoWinGLWidget::getGlxMgrWidget(void)
{
  return this->getManagerWidget();
}
*/

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
HWND
SoWinGLWidget::getGLWidget(void) const
{
  return this->getNormalWindow();
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::glLockNormal(void)
{
  assert(PRIVATE(this)->hdcNormal != NULL);
  assert(PRIVATE(this)->lockcounter >= 0);

  PRIVATE(this)->lockcounter++;
  if (PRIVATE(this)->lockcounter == 1) {
    (void)SoWinGLWidgetP::wglMakeCurrent(PRIVATE(this)->hdcNormal,
                                         PRIVATE(this)->ctxNormal);
  }
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::glUnlockNormal(void)
{
  if (PRIVATE(this)->lockcounter == 0) {
#ifdef SOWIN_DEBUG
    SoDebugError::post("SoWinGLWidget::glUnlockNormal",
                       "GL-context lock counter too low (internal error)");
#endif // SOWIN_DEBUG
    return;
  }

  PRIVATE(this)->lockcounter--;

  if (PRIVATE(this)->lockcounter == 0) {
    // FIXME: shouldn't we rather reset to a stored previous context?
    // 20020718 mortene.
    (void)SoWinGLWidgetP::wglMakeCurrent(NULL, NULL);
  }
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::glLockOverlay(void)
{
  // FIXME: there should be a counter for the lock level here.
  // 20010924 mortene.

  (void)SoWinGLWidgetP::wglMakeCurrent(PRIVATE(this)->hdcOverlay,
                                       PRIVATE(this)->ctxOverlay);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::glUnlockOverlay(void)
{
  // FIXME: there should be a counter for the lock level here.
  // 20010924 mortene.

  (void)SoWinGLWidgetP::wglMakeCurrent(NULL, NULL);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::glSwapBuffers(void)
{
  assert(PRIVATE(this)->hdcNormal != NULL);
  BOOL ok = wglSwapLayerBuffers(PRIVATE(this)->hdcNormal, WGL_SWAP_MAIN_PLANE);
  // FIXME: should have better error reporting and handling. 20020528 mortene.
  assert(ok == TRUE);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::glFlushBuffer(void)
{
  // FIXME: make OpenGL context(s) current first? 20010924 mortene.
  glFlush();
}

///////////////////////////////////////////////////////////////////
//
//  (private)
//

void
SoWinGLWidgetP::buildNormalGLWidget(HWND manager)
{
  assert(IsWindow(manager) && "buildNormalGLWidget() argument is erroneous");
  const LPSTR wndclassname = "GL Widget";

  if (!SoWinGLWidgetP::glWndClassAtom) {
    WNDCLASS windowclass;
    windowclass.lpszClassName = wndclassname;
    windowclass.hInstance = SoWin::getInstance();
    windowclass.lpfnWndProc = SoWinGLWidget::glWidgetProc;
    windowclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowclass.lpszMenuName = NULL;
    windowclass.hIcon = NULL;
    windowclass.hCursor = Win32::LoadCursor(NULL, IDC_ARROW);
    windowclass.hbrBackground = NULL;
    windowclass.cbClsExtra = 0;
    windowclass.cbWndExtra = 4;

    SoWinGLWidgetP::glWndClassAtom = Win32::RegisterClass(&windowclass);
  }

  RECT rect;
  Win32::GetClientRect(manager, & rect);

  rect.left += this->bordersize;
  rect.top += this->bordersize;
  rect.right -= 2 * this->bordersize;
  rect.bottom -= 2 * this->bordersize;

  HWND normalwidget = Win32::CreateWindowEx_(NULL,
                                             wndclassname,
                                             wndclassname,
                                             WS_VISIBLE |
                                             WS_CLIPSIBLINGS |
                                             WS_CLIPCHILDREN |
                                             WS_CHILD,
                                             rect.left, rect.top,
                                             rect.right, rect.bottom,
                                             manager,
                                             NULL,
                                             SoWin::getInstance(),
                                             PUBLIC(this));

  this->normalWidget = normalwidget;
  PUBLIC(this)->setGLSize(SbVec2s(rect.right - rect.left,
                                  rect.bottom - rect.top));
}

void
SoWinGLWidgetP::buildOverlayGLWidget(HWND manager)
{
  // FIXME: function not implemented
  // FIXME: overlay not supported. mariusbu 20010719.
  SOWIN_STUB();
}

// Return value of SOWIN_DEBUG_GL_SETUP environment variable.
SbBool
SoWinGLWidgetP::debugGLContextCreation(void)
{
  static const char * debuggl = SoAny::si()->getenv("SOWIN_DEBUG_GL_SETUP");
  int val = debuggl ? atoi(debuggl) : 0;
  return val > 0;
}

// List all available pixel formats in an SoDebugError window for the
// given device context.
void
SoWinGLWidgetP::listAvailablePixelFormats(HDC hdc)
{
  PIXELFORMATDESCRIPTOR desc;
  int format = 1, maxformat = 1;

  while (format >= maxformat) {
    maxformat = DescribePixelFormat(hdc, format,
                                    sizeof(PIXELFORMATDESCRIPTOR), &desc);
    if (maxformat == 0) {
      DWORD dummy;
      SbString err = Win32::getWin32Err(dummy);
      SbString s = "DescribePixelFormat() failed with error message: ";
      s += err;
      SoDebugError::post("SoWinGLWidgetP::listAvailablePixelFormats",
                         s.getString());
      return;
    }

    struct dwFlagsPair { int flag; const char * name; };
    struct dwFlagsPair dwFlags[] = {
      { PFD_DRAW_TO_WINDOW, "DRAW_TO_WINDOW" },
      { PFD_DRAW_TO_BITMAP, "DRAW_TO_BITMAP" },
      { PFD_SUPPORT_GDI, "SUPPORT_GDI" },
      { PFD_SUPPORT_OPENGL, "SUPPORT_OPENGL" },
      { PFD_GENERIC_ACCELERATED, "GENERIC_ACCELERATED" },
      { PFD_GENERIC_FORMAT, "GENERIC_FORMAT" },
      { PFD_NEED_PALETTE, "NEED_PALETTE" },
      { PFD_NEED_SYSTEM_PALETTE, "NEED_SYSTEM_PALETTE" },
      { PFD_DOUBLEBUFFER, "DOUBLEBUFFER" },
      { PFD_STEREO, "STEREO" },
      { PFD_SWAP_LAYER_BUFFERS, "SWAP_LAYER_BUFFERS" },
      { PFD_SWAP_COPY, "SWAP_COPY" },
      { PFD_SWAP_EXCHANGE, "SWAP_EXCHANGE" }
    };

    SbString dwFlagsStr("");
    for (int i=0; i < (sizeof(dwFlags) / sizeof(dwFlags[0])); i++) {
      if (dwFlags[i].flag & desc.dwFlags) {
        if (dwFlagsStr.getLength() > 0) { dwFlagsStr += '|'; }
        dwFlagsStr += dwFlags[i].name;
      }
    }

    SbString iPixelType("unknown");
    if (desc.iPixelType == PFD_TYPE_RGBA) { iPixelType = "RGBA"; }
    if (desc.iPixelType == PFD_TYPE_COLORINDEX) { iPixelType = "COLORINDEX"; }

    SoDebugError::postInfo("SoWinGLWidgetP::listAvailablePixelFormats",
                           "\npixelformat %d:\n"
                           "  dwFlags==%s\n"
                           "  iPixelType==%s\n"
                           "  cColorBits==%d\n"
                           "  [cRedBits, cGreenBits, cBlueBits, cAlphaBits]==[%d, %d, %d, %d]\n"
                           "  [cRedShift, cGreenShift, cBlueShift, cAlphaShift]==[%d, %d, %d, %d]\n"
                           "  [cAccumBits, cAccumRedBits, cAccumGreenBits, cAccumBlueBits, cAccumAlphaBits]==[%d, %d, %d, %d, %d]\n"
                           "  cDepthBits==%d, cStencilBits==%d, cAuxBuffers==%d\n"
                           "  overlayplanes==%d, underlayplanes==%d\n"
                           "  transparent color or index == 0x%x\n"
                           , format
                           , dwFlagsStr.getString()
                           , iPixelType.getString()
                           , desc.cColorBits
                           , desc.cRedBits, desc.cGreenBits, desc.cBlueBits, desc.cAlphaBits
                           , desc.cRedShift, desc.cGreenShift, desc.cBlueShift, desc.cAlphaShift
                           , desc.cAccumBits, desc.cAccumRedBits, desc.cAccumGreenBits, desc.cAccumBlueBits, desc.cAccumAlphaBits
                           , desc.cDepthBits, desc.cStencilBits, desc.cAuxBuffers
                           , desc.bReserved & 0x7, (desc.bReserved & (0xff - 0x7)) >> 3
                           , desc.dwVisibleMask
                           );
    format++;
  }
}

BOOL
SoWinGLWidgetP::createGLContext(HWND window)
{
  assert(IsWindow(window) && "createGLContext() argument failed IsWindow() check!");

  // FIXME: overlay planes not properly supported yet. Returning FALSE
  // will cause the caller (SoWinGLWidgetP::onCreate()) to try without
  // the overlay planes. 20010920 mortene.
  if (this->glModes & SO_GL_OVERLAY) { return FALSE; }

  // All contexts were destroyed or released in onDestroy()

  this->hdcNormal = GetDC(window);
  assert(this->hdcNormal && "GetDC failed -- investigate");
  this->hdcOverlay = this->hdcNormal;

  if (SoWinGLWidgetP::debugGLContextCreation()) {
    SoWinGLWidgetP::listAvailablePixelFormats(this->hdcNormal);
  }

  (void)memset(&this->pfdNormal, 0, sizeof(PIXELFORMATDESCRIPTOR));
  this->pfdNormal.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  this->pfdNormal.nVersion = 1;
  this->pfdNormal.dwFlags =
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_SWAP_LAYER_BUFFERS |
    (this->glModes & SO_GL_STEREO ? PFD_STEREO : 0) |
    (this->glModes & SO_GL_DOUBLE ? PFD_DOUBLEBUFFER : 0);
  this->pfdNormal.iPixelType = PFD_TYPE_RGBA;
  this->pfdNormal.cColorBits = 24; // Total RGB bits, excluding alpha.
  this->pfdNormal.cDepthBits = 32;

  int pixelformat = SoWinGLWidgetP::ChoosePixelFormat(this->hdcNormal,
                                                      &this->pfdNormal);
  if (pixelformat == 0) { return FALSE; }

  // This is a woraround for problems we experienced with GeForce2MX
  // and GeForce2Go cards. If we requested a 32 bit depth buffer,
  // ChoosePixelFormat returned an 8 bit (or something) depth buffer,
  // since 32 bits is not supported on those cards. By testing the
  // returned pixel format, and trying 24 and 16 bits depth, a better
  // depth buffer precision was achieved.
  //
  // pederb.
	
  PIXELFORMATDESCRIPTOR tmpdescriptor;
  if (DescribePixelFormat(this->hdcNormal,
                          pixelformat,
                          sizeof(PIXELFORMATDESCRIPTOR),
                          &tmpdescriptor) != 0) {
    if (tmpdescriptor.cDepthBits < 24) {
      this->pfdNormal.cDepthBits = 24;
      pixelformat = SoWinGLWidgetP::ChoosePixelFormat(this->hdcNormal,
                                                      &this->pfdNormal);
      if (pixelformat == 0) return FALSE;
      if (DescribePixelFormat(this->hdcNormal,
                              pixelformat,
                              sizeof(PIXELFORMATDESCRIPTOR),
                              &tmpdescriptor) != 0) {
        if (tmpdescriptor.cDepthBits < 16) {
          this->pfdNormal.cDepthBits = 16;
          pixelformat = SoWinGLWidgetP::ChoosePixelFormat(this->hdcNormal,
                                                          &this->pfdNormal);
          if (pixelformat == 0) return FALSE;
        }
      }
    }
  }

  if (!SetPixelFormat(this->hdcNormal, pixelformat, &this->pfdNormal)) {
    DWORD dummy;
    SbString err = Win32::getWin32Err(dummy);
    SbString s = "SetPixelFormat(";
    s.addIntString(this->glModes);
    s += ") failed with error message ";
    s += err;
    SoDebugError::postWarning("SoWinGLWidgetP::createGLContext", s.getString());
    return FALSE;
  }

  // FIXME: if the pixelformat set up is _not_ an RGB (truecolor)
  // format, we should probably set up a DC palette here. 20011208 mortene.

  this->ctxNormal = wglCreateContext(this->hdcNormal);
  if (! this->ctxNormal) {
    DWORD dummy;
    SbString err = Win32::getWin32Err(dummy);
    SbString s = "The rendering context for format ";
    s.addIntString(this->glModes);
    s += " could not be created, as ";
    s += "wglCreateContext() failed with error message: ";
    s += err;
    SoDebugError::postWarning("SoWinGLWidgetP::createGLContext", s.getString());
    return FALSE;
  }

#if 0 // temporary disabled because overlay planes is not supported yet
  // create overlay
  if (this->glModes & SO_GL_OVERLAY) {
    this->ctxOverlay = wglCreateLayerContext(this->hdcOverlay, 1);

    // FIXME: set overlay plane. mariusbu 20010801.
  }
#endif // tmp disabled

  // share context
  SoWinGLWidget * share = (SoWinGLWidget *)
  SoAny::si()->getSharedGLContext(NULL, NULL);

  if (share != NULL) {
    BOOL ok = wglShareLists(PRIVATE(share)->ctxNormal, this->ctxNormal);
    // FIXME: how should we properly react to ok==FALSE?
    // 20010920 mortene.
  }

  SoAny::si()->registerGLContext((void *) PUBLIC(this), NULL, NULL);

  // FIXME: what's this good for -- first setting then unsetting?
  // 20010924 mortene.
  if (!SoWinGLWidgetP::wglMakeCurrent(this->hdcNormal, this->ctxNormal) ||
      !SoWinGLWidgetP::wglMakeCurrent(NULL, NULL)) {
    return FALSE;
  }

  // FIXME: need to set up the app-programmer visible format flags
  // from what kind of canvas we actually got. (Like we do in
  // SoQtGLWidget.cpp.)  20011018 mortene.

  return TRUE;
}

LRESULT
SoWinGLWidgetP::onCreate(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{

#if SOWIN_DEBUG && 0
  SoDebugError::postInfo("SoWinGLWidget::onCreate", "called");
#endif // SOWIN_DEBUG

  int orgmodes = this->glModes;
  SbBool tried_nostereo = FALSE;
  SbBool tried_nooverlay = FALSE;
  SbBool tried_nodouble = FALSE;
  SbBool tried_withdouble = FALSE;

  // FIXME: add more "downgrade" possibilities. mariusbu 20010802.
  // FIXME: also try combinations of several downgrade bits.  mortene 20010920.
label:
  if (! this->createGLContext(window)) {
    this->glModes = orgmodes; // reset before trying new setting

    // Downgrading is ordered from what seems "most likely to help".

    if ((orgmodes & SO_GL_OVERLAY) && !tried_nooverlay) {
      this->glModes &= ~SO_GL_OVERLAY;
      tried_nooverlay = TRUE;
      goto label;
    }
    else if ((orgmodes & SO_GL_STEREO) && !tried_nostereo) {
      this->glModes &= ~SO_GL_STEREO;
      tried_nostereo = TRUE;
      goto label;
    }
    else if ((orgmodes & SO_GL_DOUBLE) && !tried_nodouble) {
      this->glModes &= ~SO_GL_DOUBLE;
      tried_nodouble = TRUE;
      goto label;
    }
    else if (!(orgmodes & SO_GL_DOUBLE) && !tried_withdouble) {
      this->glModes |= SO_GL_DOUBLE;
      tried_withdouble = TRUE;
      goto label;
    }
    else {
      // FIXME: clean up as good as possible, in case the application
      // has registered a "fatal error" handler callback and is able
      // to run without the functionality provided by SoWin.
      //
      // Note that this must be done _before_ calling
      // SoAny::invokeFatalErrorHandler(), since the fatal error
      // handler might throw an exception -- in which case it will not
      // return by using our stack address.
      //
      // 20011014 mortene.

      // FIXME: should provide more details about the error condition,
      // if possible. Could for instance use the GL vendor and / or
      // version and / or renderer string to smoke out the exact ATI
      // driver known to cause problems in accelerated mode (when
      // DirectX is in non-accelerated mode at the same time) -- as
      // reported by Alan Walford of Eos. 20011014 mortene.
      SbString s = "Could not find any supported OpenGL mode on your system.";
      if (!SoAny::si()->invokeFatalErrorHandler(s, SoWin::NO_OPENGL_CANVAS)) {
        // FIXME: this will actually cause the application to exit
        // before the error dialog has been shown. 20011123 mortene.
        exit(1);
      }
    }
  }

  SetFocus(window);
  PUBLIC(this)->widgetChanged(window);
  return 0;
}

LRESULT
SoWinGLWidgetP::onPaint(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo("SoWinGLWidget::onPaint", "called");
#endif // SOWIN_DEBUG

  PAINTSTRUCT ps;
  this->hdcNormal = Win32::BeginPaint(window, & ps);

  if (!SoWinGLWidgetP::wglMakeCurrent(this->hdcNormal, this->ctxNormal)) {
    return 0;
  }

  if (! this->glRealized) {
    this->glRealized = TRUE;
    PUBLIC(this)->initGraphic();
  }
  if (! PUBLIC(this)->glScheduleRedraw()) {
    PUBLIC(this)->redraw();
  }

  // Release context.
  if (!SoWinGLWidgetP::wglMakeCurrent(NULL, NULL)) { return 0; }
  // FIXME: should perhaps the next call go before the gl-context
  // release?  20010925 mortene.
  Win32::EndPaint(window, & ps);
  return 0;
}

LRESULT
SoWinGLWidgetP::onDestroy(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  // Release context.
  if (!SoWinGLWidgetP::wglMakeCurrent(NULL, NULL)) { return 0; }

  SoAny::si()->unregisterGLContext((void *) PUBLIC(this));

  BOOL r = wglDeleteContext(this->ctxNormal);
  assert(r && "wglDeleteContext() failed -- investigate");
  this->ctxNormal = NULL;

  Win32::ReleaseDC(window, this->hdcNormal);
  this->hdcNormal = NULL;

  // FIXME: Overlay not supported. mariusbu 20010808.

  return 0;
}

// Wrap wglMakeCurrent() for convenience with regard to verbose
// warning output when it fails -- which it really shouldn't.  :-/
//
// FIXME: change function-signature to have a void return
// value. 20020718 mortene.
BOOL
SoWinGLWidgetP::wglMakeCurrent(HDC hdc, HGLRC hglrc)
{
  // FIXME: workaround for problems with wglMakeCurrent(NULL, NULL)
  // with the Microsoft GDI Generic 1.1.0 driver. 20010924 mortene.
  //
  // FIXME UPDATE: it seems necessary to be able to do
  // wglMakeCurrent(NULL, NULL) anyway, or there will be too little
  // updates. 20010924 mortene.
  //
  // if (hglrc == NULL) { glFlush(); return TRUE; }
  if (hglrc == NULL) { ::wglMakeCurrent(NULL, NULL); return TRUE; }

  if (::wglMakeCurrent(hdc, hglrc)) { return TRUE; }

  DWORD dummy;
  SbString err = Win32::getWin32Err(dummy);
  SbString s = "The rendering context <%p, %p>, could not be made current, ";
  s += "as wglMakeCurrent() failed with error message: ";
  s += err;
  SoDebugError::postWarning("SoWinGLWidgetP::wglMakeCurrent", s.getString(),
                            hdc, hglrc);
  return FALSE;
}

// Wrap ChoosePixelFormat() for convenience with regard to verbose
// warning output when it fails, which can easily happen.
int
SoWinGLWidgetP::ChoosePixelFormat(HDC hdc, CONST PIXELFORMATDESCRIPTOR * ppfd)
{
  int format = ::ChoosePixelFormat(hdc, ppfd);
  if (format == 0) {
    DWORD dummy;
    SbString err = Win32::getWin32Err(dummy);
    SbString s = "The given pixelformat could not be used, ";
    s += "ChoosePixelFormat() failed with: ";
    s += err;
    SoDebugError::postWarning("SoWinGLWidgetP::ChoosePixelFormat",
                              s.getString());
  }
  return format;
}
