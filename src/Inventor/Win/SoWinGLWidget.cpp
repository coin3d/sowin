/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and / or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use this library in software that is incompatible
 *  with the GNU GPL, and / or you would like to take advantage of the
 *  additional benefits with regard to our support services, please
 *  contact Systems in Motion about acquiring a Coin Professional
 *  Edition License.  See <URL:http://www.coin3d.org> for more
 *  information.
 *
 *  Systems in Motion, Abels gate 5, Teknobyen, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

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
#include <Inventor/errors/SoDebugError.h>
#include <float.h> // FLT_MAX

static const int SO_BORDER_THICKNESS = 2;

SOWIN_OBJECT_ABSTRACT_SOURCE(SoWinGLWidget);


// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SoWinGLWidget::SoWinGLWidget(HWND const parent,
                             const char * const name,
                             const SbBool embed,
                             const int glmodes,
                             const SbBool build)
  : SoWinComponent(parent, name, embed)
{
  this->pimpl = new SoWinGLWidgetP(this);
  this->waitForExpose = TRUE;

  PRIVATE(this)->managerWidget = NULL;
  PRIVATE(this)->normalWidget = NULL;
  PRIVATE(this)->overlayWidget = NULL;

  PRIVATE(this)->drawToFrontBuffer = FALSE;

  PRIVATE(this)->ctxNormal = NULL;
  PRIVATE(this)->ctxOverlay = NULL;

  PRIVATE(this)->hdcNormal = NULL;
  PRIVATE(this)->hdcOverlay = NULL;

  PRIVATE(this)->glModes = glmodes;
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
    Win32::UnregisterClass("Manager Widget", NULL);
    SoWinGLWidgetP::managerWndClassAtom = 0;
    Win32::UnregisterClass("GL Widget", NULL);
    SoWinGLWidgetP::glWndClassAtom = 0;
  }
  delete this->pimpl;
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

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::setOverlayRender(const SbBool onoff)
{
  PRIVATE(this)->glModes |= SO_GL_OVERLAY;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
SbBool
SoWinGLWidget::isOverlayRender(void) const
{
  return (PRIVATE(this)->glModes & SO_GL_OVERLAY) != 0;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::setDoubleBuffer(SbBool flag)
{
  int old = PRIVATE(this)->glModes;
  if (flag) { PRIVATE(this)->glModes |= SO_GL_DOUBLE; }
  else { PRIVATE(this)->glModes &= ~SO_GL_DOUBLE; }

  if (PRIVATE(this)->glModes == old) { return; }

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
SoWinGLWidget::setQuadBufferStereo(const SbBool flag)
{
  int old = PRIVATE(this)->glModes;
  if (flag) { PRIVATE(this)->glModes |= SO_GL_STEREO; }
  else { PRIVATE(this)->glModes &= ~SO_GL_STEREO; }

  if (PRIVATE(this)->glModes == old) { return; }

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
  // SoWinGLWidgetP::glWidgetProc() and forwarded directly to
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
    windowclass.hInstance = NULL;
    windowclass.lpfnWndProc = SoWinGLWidgetP::mgrWidgetProc;
    windowclass.style = 0;
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
                                            NULL,
                                            this);

  PRIVATE(this)->managerWidget = managerwidget;

  // FIXME: looks shaky to keep this here as long as overlay support
  // has not been implemented.  20010920 mortene.
  if (PRIVATE(this)->glModes & SO_GL_OVERLAY) {
    PRIVATE(this)->buildOverlayGLWidget(managerwidget);
  }

  PRIVATE(this)->buildNormalGLWidget(managerwidget);
  this->waitForExpose = TRUE;

  return managerwidget;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
HWND
SoWinGLWidget::getGLWidget(void) const
{
  return PRIVATE(this)->normalWidget;
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::glLockNormal(void)
{
  assert(PRIVATE(this)->hdcNormal != NULL);
  assert(PRIVATE(this)->lockcounter >= 0);

#if defined(SOWIN_DEBUG) && 0 // debug
  SoDebugError::postInfo("SoWinGLWidget::glLockNormal",
                         "lockcounter: %d => %d",
                         PRIVATE(this)->lockcounter,
                         PRIVATE(this)->lockcounter + 1);
#endif // debug


  PRIVATE(this)->lockcounter++;

  // Make context current no matter what the value of the lock-counter
  // is, or we could get crash bugs if the context has been released
  // from somewhere else (for instance from application code).
  (void)SoWinGLWidgetP::wglMakeCurrent(PRIVATE(this)->hdcNormal,
                                       PRIVATE(this)->ctxNormal);
}

// Documented in common/SoGuiGLWidgetCommon.cpp.in.
void
SoWinGLWidget::glUnlockNormal(void)
{
#if defined(SOWIN_DEBUG) && 0 // debug
  SoDebugError::postInfo("SoWinGLWidget::glUnlockNormal",
                         "lockcounter: %d => %d",
                         PRIVATE(this)->lockcounter,
                         PRIVATE(this)->lockcounter - 1);
#endif // debug

  if (PRIVATE(this)->lockcounter == 0) {
#if defined(SOWIN_DEBUG)
    SoDebugError::post("SoWinGLWidget::glUnlockNormal",
                       "GL-context lock counter too low (internal error)");
#endif // SOWIN_DEBUG
    return;
  }

  PRIVATE(this)->lockcounter--;

  // Must wait until lockcounter goes to 0 before resetting, or we
  // could get problems from any internal SoWin code snippet that goes
  // like this:
  //
  // glLockNormal();
  // [OpenGL commands here];
  // someOtherSoWinFunctionWithLockUnlockPairing();
  // [OpenGL commands here]; /* <-- crash here because no current context */
  // glUnlockNormal();

  if (PRIVATE(this)->lockcounter == 0) {
    // FIXME: shouldn't we rather reset to a stored previous context?
    // 20020718 mortene.
    (void)SoWinGLWidgetP::wglMakeCurrent(NULL, NULL);
    // FIXME: should also investigate if we really have to unlock an
    // OpenGL context under Win32 WGL. Will save us some trouble if
    // it's unnecessary (like under GLX). 20020930 mortene.
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
//  Pimpl class follows. The private data and code for the
//  SoWinGLWidget.

#ifndef DOXYGEN_SKIP_THIS

ATOM SoWinGLWidgetP::managerWndClassAtom = 0;
ATOM SoWinGLWidgetP::glWndClassAtom = 0;
int SoWinGLWidgetP::widgetCounter = 0;

SoWinGLWidgetP::SoWinGLWidgetP(SoWinGLWidget * o)
  : SoGuiGLWidgetP(o)
{
  this->bordersize = 0;
  this->lockcounter = 0;
  this->overlaylockcounter = 0;
  this->havefocus = FALSE;
}

// Destructor.
SoWinGLWidgetP::~SoWinGLWidgetP()
{
}

LRESULT CALLBACK
SoWinGLWidgetP::mgrWidgetProc(HWND window, UINT message,
                              WPARAM wparam, LPARAM lparam)
{
  // does nothing
  return DefWindowProc(window, message, wparam, lparam);
}

LRESULT CALLBACK
SoWinGLWidgetP::glWidgetProc(HWND window, UINT message,
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

    // Grab focus so keystrokes are piped in our direction.
    //
    // Note that the focus grabbing has one known flaw: when using
    // e.g. Alt+TAB to select an SoWinComponent window, the form
    // widget will get the focus, and not the GL widget. For built-in,
    // non-abstract classes this only has practical consequences for
    // the SoWinRenderArea, as SoWinFullViewer passes on focus to the
    // GL widget when it receives WM_SETFOCUS messages.  -mortene.
    if (!PRIVATE(object)->havefocus) {
      switch (message) {
      case WM_LBUTTONDOWN:
      case WM_MBUTTONDOWN:
      case WM_RBUTTONDOWN:
      case WM_MOUSEMOVE:
        (void)Win32::SetFocus(window);
        PRIVATE(object)->havefocus = TRUE;
        break;
      default: break;
      }
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
      PRIVATE(object)->havefocus = FALSE;
      return 0;

    case WM_SETFOCUS:
      PRIVATE(object)->havefocus = TRUE;
      return 0;
    }
  }
  return DefWindowProc(window, message, wparam, lparam);
}

LRESULT // Used by SoWinRenderArea
SoWinGLWidgetP::eventHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  // FIXME: the function gets registered and all in SoWinRenderArea,
  // so why does event handling differ in SoWin versus SoXt and SoQt?
  // 20030411 mortene.
  assert(FALSE && "should not be in use");
  return 0;
}

void
SoWinGLWidgetP::buildNormalGLWidget(HWND manager)
{
  assert(IsWindow(manager) && "buildNormalGLWidget() argument is erroneous");
  const LPSTR wndclassname = "GL Widget";

  if (!SoWinGLWidgetP::glWndClassAtom) {
    WNDCLASS windowclass;
    windowclass.lpszClassName = wndclassname;
    windowclass.hInstance = NULL;
    windowclass.lpfnWndProc = SoWinGLWidgetP::glWidgetProc;
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

  HWND normalwidget = Win32::CreateWindowEx_(0,
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
                                             NULL,
                                             PUBLIC(this));

  this->normalWidget = normalwidget;
  PUBLIC(this)->setGLSize(SbVec2s((short)(rect.right - rect.left),
                                  (short)(rect.bottom - rect.top)));
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

// This is our replacement for the Win32 / OpenGL ChoosePixelFormat()
// function. Returns -FLT_MAX for pixelformats incompatible with
// OpenGL rendering (in onscreen windows), otherwise a value that
// indicates it's "goodness", where larger value means it seems better
// suited for what is requested.
double
SoWinGLWidgetP::weighPixelFormat(const PIXELFORMATDESCRIPTOR * pfd,
                                 SbBool want_rgb, /* default TRUE */
                                 SbBool want_dblbuffer, /* default TRUE */
                                 SbBool want_zbuffer, /* default TRUE */
                                 SbBool want_stereo, /* default FALSE */
                                 SbBool want_overlay) /* default FALSE */
{
  if ((pfd->dwFlags & PFD_SUPPORT_OPENGL) == 0) { return -FLT_MAX; }
  // We only care for on-screen windows for now. If we ever want to
  // use this weighting method for offscreen buffers aswell, we should
  // extend with another argument for the function signature to check
  // specifically for this.
  if ((pfd->dwFlags & PFD_DRAW_TO_WINDOW) == 0) { return -FLT_MAX; }

  // FIXME: I believe these pixelformats to be unsupported, as we
  // don't set up any palettes yet:
  if ((pfd->dwFlags & (PFD_NEED_PALETTE|PFD_NEED_SYSTEM_PALETTE)) != 0) { return -FLT_MAX; }


  // *** set up parameter constants for weighing *****************

  // a baseline value
  const double MAX_IMPORTANCE = 1000.0;

  // very important to get right, as it will have a _major_ impact on
  // the rendering
  const double RGBA_VS_COLORINDEX = MAX_IMPORTANCE;

  // equally important -- no zbuffer means rendering will be
  // incomprehensible
  const double ZBUFFER_PRESENT = MAX_IMPORTANCE;

  // veeery close to being as important as the two first "musts" (as
  // we generally _will_ have non-accelerated pixelformats available
  // even on drivers with vendor-specific OpenGL ICDs for gfx
  // hardware)
  const double HARDWARE_ACCELERATED = MAX_IMPORTANCE - 1;

  // singlebuffer sucks when you want doublebuffer
  const double DOUBLEBUFFER_PRESENT = MAX_IMPORTANCE / 2;

  // the next three are often hard to find
  const double STEREO_PRESENT = MAX_IMPORTANCE / 10;
  const double OVERLAYS_AVAILABLE = MAX_IMPORTANCE / 30;
  const double PER_OVERLAY_PLANE = MAX_IMPORTANCE / 90;

  // Depth buffer resolution is a lot more important than color
  // resolution, actually, as really low z-buffer resolution (8 or
  // even 16 bits) causes unexpected nasty visual artifacts for many
  // types of scenes.
  //
  // Setting depth resolution to be this much more important than
  // color resolution also fixes a problem with Win32
  // ChoosePixelFormat() we've experienced with some NVidia drivers
  // (with GeForce2MX and GeForce2Go cards): if we requested a 32 bit
  // depth buffer, ChoosePixelFormat() returned an 8 bit (or
  // something) depth buffer, since 32 bits resolution is not
  // supported on those cards (only 16 and / or 24 bits resolution).
  const double PER_COLOR_BIT = 1;
  const double PER_DEPTH_BIT = 2.5;


  // *** calculate weight for given pixelformat ******************

  double weight = 0.0;

  // want_rgb && PFD_TYPE_RGBA         =>  +1
  // want_rgb && PFD_TYPE_COLORINDEX   =>  -1
  // !want_rgb && PFD_TYPE_RGBA        =>  -1
  // !want_rgb && PFD_TYPE_COLORINDEX  =>  +1
  int sign = (want_rgb ? 1 : -1) * ((pfd->iPixelType == PFD_TYPE_RGBA) ? 1 : -1);
  weight += RGBA_VS_COLORINDEX * sign;

  const SbBool has_zbuffer = (pfd->cDepthBits > 0);
  // want_zbuffer && has_zbuffer    =>  +1
  // want_zbuffer && !has_zbuffer   =>  -1
  // !want_zbuffer && has_zbuffer   =>  -1
  // !want_zbuffer && !has_zbuffer  =>  +1
  sign = (want_zbuffer ? 1 : -1) * (has_zbuffer ? 1 : -1);
  weight += ZBUFFER_PRESENT * sign;

  const SbBool has_dblbuffer = ((pfd->dwFlags & PFD_DOUBLEBUFFER) != 0);
  if (want_dblbuffer && has_dblbuffer) { weight += DOUBLEBUFFER_PRESENT; }
  // otherwise ignore -- no need to punish doublebuffer mode if we
  // requested singlebuffer mode, as singlebuffer can flawlessly be
  // "faked" in doublebuffer

  const SbBool has_stereo = ((pfd->dwFlags & PFD_STEREO) != 0);
  if (want_stereo && has_stereo) { weight += STEREO_PRESENT; }
  // otherwise ignore -- no need to punish stereo mode if we requested mono

  if (want_overlay) {
    const int nr_planes = pfd->bReserved & 0x07;
    weight += ((nr_planes > 0) ? 1 : 0) * OVERLAYS_AVAILABLE;
    weight += PER_OVERLAY_PLANE * nr_planes;
    weight += OVERLAYS_AVAILABLE / 10 *
      ((pfd->dwFlags & PFD_SWAP_LAYER_BUFFERS) ? 1 : 0);
  }

  const SbBool hw_accel = ((pfd->dwFlags & PFD_GENERIC_FORMAT) == 0);
  // Note: there are two types of possible "non-generic"
  // configurations. From a 1996 Usenet posting by a Microsoft
  // engineer:
  //
  // ---8<--- [snip] --------8<--- [snip] --------8<--- [snip] -----
  //
  // [...] In the upcoming OpenGL 1.1 for Windows NT/95, we have added
  // a new flag PFD_GENERIC_ACCELERATED (0x00001000) to identify an
  // OpenGL Mini Client Driver (MCD).  [...]
  //
  // So there are now 3 different classes of hardware identified by pixel 
  // formats:
  //
  // 1. (pfd->flags & (PFD_GENERIC_FORMAT | PFD_GENERIC_ACCELERATED)) == 0
  //     => OpenGL Installable Client Driver (e.g. Intergraph, AccelGraphics...)
  //
  // 2. (pfd->flags & (PFD_GENERIC_FORMAT | PFD_GENERIC_ACCELERATED)) == (PFD_GENERIC_FORMAT | PFD_GENERIC_ACCELERATE)
  //     => OpenGL Mini Client Driver (e.g. Matrox Millennium...)
  //
  // 3. (pfd->flags & (PFD_GENERIC_FORMAT | PFD_GENERIC_ACCELERATED)) == PFD_GENERIC_FORMAT
  //     => OpenGL Generic (software) Implementation
  //
  // Hock San Lee
  // Microsoft
  //
  // ---8<--- [snip] --------8<--- [snip] --------8<--- [snip] -----
  //
  // I couldn't figure out whether there are any quality differences
  // between a "Mini Client Driver" and an "Installable Client
  // Driver", or even if they can be present at the same time, but it
  // seems safe to assume that just not having PFD_GENERIC_FORMAT
  // present means we have hardware-accelerated rendering.
  //
  // Anyone reading this who could educate me further on MS OpenGL
  // acceleration issues and hardware drivers -- please feel free to
  // do so.
  //
  // mortene.
  weight += (hw_accel ? 1 : 0) * HARDWARE_ACCELERATED;


  weight += pfd->cDepthBits * PER_DEPTH_BIT;
  weight += pfd->cColorBits * PER_COLOR_BIT;

  // The following are "don't care" properties for now (which is
  // likely to change when we implement missing pieces of
  // SoWinGLWidget):
  //
  // dwFlags:
  //   - PFD_DRAW_TO_BITMAP
  //   - PFD_SUPPORT_GDI
  //   - PFD_SWAP_COPY
  //   - PFD_SWAP_EXCHANGE
  //
  // - individual color bit settings (cRedBits, cGreenBits, cBlueBits)
  // - cAlphaBits
  // - cAccumBits (with individual R, G, B, A)
  // - cStencilBits
  // - cAuxBuffers

  return weight;
}

// List all available pixel formats in an SoDebugError window for the
// given device context.
void
SoWinGLWidgetP::dumpPixelFormat(HDC hdc, int format)
{
  PIXELFORMATDESCRIPTOR desc;
  int maxformat = DescribePixelFormat(hdc, format,
                                      sizeof(PIXELFORMATDESCRIPTOR), &desc);
  if (maxformat == 0) {
    DWORD dummy;
    SbString err = Win32::getWin32Err(dummy);
    SbString s = "DescribePixelFormat() failed with error message: ";
    s += err;
    SoDebugError::post("SoWinGLWidgetP::dumpPixelFormat", s.getString());
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
  for (int i=0; i < (int)(sizeof(dwFlags) / sizeof(dwFlags[0])); i++) {
    if (dwFlags[i].flag & desc.dwFlags) {
      if (dwFlagsStr.getLength() > 0) { dwFlagsStr += '|'; }
      dwFlagsStr += dwFlags[i].name;
    }
  }

  SbString iPixelType("unknown");
  if (desc.iPixelType == PFD_TYPE_RGBA) { iPixelType = "RGBA"; }
  if (desc.iPixelType == PFD_TYPE_COLORINDEX) { iPixelType = "COLORINDEX"; }

  SoDebugError::postInfo("SoWinGLWidgetP::dumpPixelFormat",
                         "\npixelformat %d:\n"
                         "  dwFlags==%s (0x%x)\n"
                         "  iPixelType==%s\n"
                         "  cColorBits==%d\n"
                         "  [cRedBits, cGreenBits, cBlueBits, cAlphaBits]==[%d, %d, %d, %d]\n"
                         "  [cRedShift, cGreenShift, cBlueShift, cAlphaShift]==[%d, %d, %d, %d]\n"
                         "  cAccumBits==%d\n"
                         "  [cAccumRedBits, cAccumGreenBits, cAccumBlueBits, cAccumAlphaBits]==[%d, %d, %d, %d]\n"
                         "  cDepthBits==%d\n"
                         "  cStencilBits==%d\n"
                         "  cAuxBuffers==%d\n"
                         "  overlayplanes==%d, underlayplanes==%d  (0x%x)\n"
                         "  transparent color or index == 0x%x"
                         , format
                         , dwFlagsStr.getString(), desc.dwFlags
                         , iPixelType.getString()
                         , desc.cColorBits
                         , desc.cRedBits, desc.cGreenBits, desc.cBlueBits, desc.cAlphaBits
                         , desc.cRedShift, desc.cGreenShift, desc.cBlueShift, desc.cAlphaShift
                         , desc.cAccumBits, desc.cAccumRedBits, desc.cAccumGreenBits, desc.cAccumBlueBits, desc.cAccumAlphaBits
                         , desc.cDepthBits, desc.cStencilBits, desc.cAuxBuffers
                         , desc.bReserved & 0x7, (desc.bReserved & (0xff - 0x7)) >> 3, desc.bReserved
                         , desc.dwVisibleMask
                         );
}

void
SoWinGLWidgetP::createGLContext(HWND window)
{
  assert(IsWindow(window));

  SoWinGLWidget * share = NULL;

  // All contexts were destroyed or released in onDestroy().

  this->hdcNormal = GetDC(window);
  assert(this->hdcNormal && "GetDC failed -- investigate");
  this->hdcOverlay = this->hdcNormal;

  int format = 1, maxformat = -1, bestformat = -1;
  double maxweight = -FLT_MAX;
  PIXELFORMATDESCRIPTOR desc;
  do {
    maxformat = DescribePixelFormat(this->hdcNormal, format,
                                    sizeof(PIXELFORMATDESCRIPTOR), &desc);
    if (maxformat == 0) {
      DWORD dummy;
      SbString err = Win32::getWin32Err(dummy);
      SbString s = "DescribePixelFormat() failed with error message: ";
      s += err;
      SoDebugError::post("SoWinGLWidgetP::createGLContext", s.getString());
      goto panic;
    }

    double weight =
      SoWinGLWidgetP::weighPixelFormat(&desc,
                                       (this->glModes & SO_GL_RGB) != 0,
                                       (this->glModes & SO_GL_DOUBLE) != 0,
                                       (this->glModes & SO_GL_ZBUFFER) != 0,
                                       (this->glModes & SO_GL_STEREO) != 0,
                                       // FIXME: overlay support not
                                       // implemented yet. 20020720 mortene.
                                       FALSE);

    if (SoWinGLWidgetP::debugGLContextCreation()) {
      SoWinGLWidgetP::dumpPixelFormat(this->hdcNormal, format);
      SoDebugError::postInfo("SoWinGLWidgetP::createGLContext",
                             "weight==%f\n", weight);
    }

    if (weight >= maxweight) {
      maxweight = weight;
      bestformat = format;
      (void)memcpy(&this->pfdNormal, &desc, sizeof(PIXELFORMATDESCRIPTOR));
    }

    format++;
  } while (format <= maxformat);

  if (SoWinGLWidgetP::debugGLContextCreation()) {
    SoDebugError::postInfo("SoWinGLWidgetP::createGLContext",
                           "bestformat==%d, maxweight==%f",
                           bestformat, maxweight);
  }

  if (!SetPixelFormat(this->hdcNormal, bestformat, &this->pfdNormal)) {
    DWORD dummy;
    SbString err = Win32::getWin32Err(dummy);
    SbString s = "SetPixelFormat(";
    s.addIntString(bestformat);
    s += ") failed with error message ";
    s += err;
    SoDebugError::postWarning("SoWinGLWidgetP::createGLContext", s.getString());
    goto panic;
  }

  // FIXME: if the pixelformat set up is _not_ an RGB (truecolor)
  // format, we should set up a DC palette here.
  //
  // Something like this:
  //
  // ---8<--- [snip] ------8<--- [snip] ------8<--- [snip] ---
  //    if (pfd.dwFlags & PFD_NEED_PALETTE ||
  //        pfd.iPixelType == PFD_TYPE_COLORINDEX) {
  //
  //      n = 1 << pfd.cColorBits;
  //      if (n > 256) n = 256;
  //
  //      lpPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +
  //                                  sizeof(PALETTEENTRY) * n);
  //      memset(lpPal, 0, sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * n);
  //      lpPal->palVersion = 0x300;
  //      lpPal->palNumEntries = n;
  //
  //      GetSystemPaletteEntries(hDC, 0, n, &lpPal->palPalEntry[0]);
  //
  //      /* if the pixel type is RGBA, then we want to make an RGB ramp,
  //      otherwise (color index) set individual colors. */
  //      if (pfd.iPixelType == PFD_TYPE_RGBA) {
  //        int redMask = (1 << pfd.cRedBits) - 1;
  //        int greenMask = (1 << pfd.cGreenBits) - 1;
  //        int blueMask = (1 << pfd.cBlueBits) - 1;
  //        int i;
  //
  //        /* fill in the entries with an RGB color ramp. */
  //        for (i = 0; i < n; ++i) {
  //          lpPal->palPalEntry[i].peRed =
  //            (((i >> pfd.cRedShift)   & redMask)   * 255) / redMask;
  //          lpPal->palPalEntry[i].peGreen =
  //            (((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask;
  //          lpPal->palPalEntry[i].peBlue =
  //            (((i >> pfd.cBlueShift)  & blueMask)  * 255) / blueMask;
  //          lpPal->palPalEntry[i].peFlags = 0;
  //        }
  //      } else {
  //        lpPal->palPalEntry[0].peRed = 0;
  //        lpPal->palPalEntry[0].peGreen = 0;
  //        lpPal->palPalEntry[0].peBlue = 0;
  //        lpPal->palPalEntry[0].peFlags = PC_NOCOLLAPSE;
  //        lpPal->palPalEntry[1].peRed = 255;
  //        lpPal->palPalEntry[1].peGreen = 0;
  //        lpPal->palPalEntry[1].peBlue = 0;
  //        lpPal->palPalEntry[1].peFlags = PC_NOCOLLAPSE;
  //        lpPal->palPalEntry[2].peRed = 0;
  //        lpPal->palPalEntry[2].peGreen = 255;
  //        lpPal->palPalEntry[2].peBlue = 0;
  //        lpPal->palPalEntry[2].peFlags = PC_NOCOLLAPSE;
  //        lpPal->palPalEntry[3].peRed = 0;
  //        lpPal->palPalEntry[3].peGreen = 0;
  //        lpPal->palPalEntry[3].peBlue = 255;
  //        lpPal->palPalEntry[3].peFlags = PC_NOCOLLAPSE;
  //      }
  //
  //      hPalette = CreatePalette(lpPal);
  //      if (hPalette) {
  //        SelectPalette(hDC, hPalette, FALSE);
  //        RealizePalette(hDC);
  //      }
  //
  //      free(lpPal);
  //    }
  // ---8<--- [snip] ------8<--- [snip] ------8<--- [snip] ---
  // 20020719 mortene.

  this->ctxNormal = wglCreateContext(this->hdcNormal);
  if (! this->ctxNormal) {
    DWORD dummy;
    SbString err = Win32::getWin32Err(dummy);
    SbString s = "The rendering context for pixel format ";
    s.addIntString(bestformat);
    s += " could not be created, as ";
    s += "wglCreateContext() failed with error message: ";
    s += err;
    SoDebugError::postWarning("SoWinGLWidgetP::createGLContext", s.getString());
    goto panic;
  }

#if 0 // temporary disabled because overlay planes is not supported yet
  // create overlay
  if (overlay) {
    this->ctxOverlay = wglCreateLayerContext(this->hdcOverlay, 1);
    // FIXME: set overlay plane. mariusbu 20010801.
  }
#endif // tmp disabled

  // share context
  share = (SoWinGLWidget *)SoAny::si()->getSharedGLContext(NULL, NULL);

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
    SoDebugError::post("SoWinGLWidgetP::createGLContext",
                       "Couldn't make the picked GL context current! "
                       "Something is seriously wrong on this system!");
    goto panic;
  }

  // Sets up the app-programmer visible format flags from what kind of
  // canvas we actually got.
  {
    this->glModes = 0;
    this->glModes |= (this->pfdNormal.iPixelType == PFD_TYPE_RGBA) ? SO_GL_RGB : 0;
    this->glModes |= (this->pfdNormal.dwFlags & PFD_DOUBLEBUFFER) ? SO_GL_DOUBLE : 0;
    this->glModes |= (this->pfdNormal.cDepthBits > 0) ? SO_GL_ZBUFFER : 0;
    this->glModes |= (this->pfdNormal.dwFlags & PFD_STEREO) ? SO_GL_STEREO : 0;
    // FIXME: check for overlay planes when support for this is
    // implemented. 20020719 mortene.
  }

  return;

panic:
  // FIXME: clean up as good as possible, in case the application has
  // registered a "fatal error" handler callback and is able to run
  // without the functionality provided by SoWin.
  //
  // Note that this must be done _before_ calling
  // SoAny::invokeFatalErrorHandler(), since the fatal error handler
  // might throw an exception -- in which case it will not return by
  // using our stack address.
  //
  // 20011014 mortene.

  // FIXME: should provide more details about the error condition, if
  // possible. Could for instance use the GL vendor and / or version
  // and / or renderer string to smoke out the exact ATI driver known
  // to cause problems in accelerated mode (when DirectX is in
  // non-accelerated mode at the same time) -- as reported by Alan
  // Walford of Eos. 20011014 mortene.
  SbString s = "Could not find any supported OpenGL mode on your system.";
  if (!SoAny::si()->invokeFatalErrorHandler(s, SoWin::NO_OPENGL_CANVAS)) {
    // FIXME: this will actually cause the application to exit before
    // the error dialog has been shown. 20011123 mortene.
    exit(1);
  }
  return;
}

LRESULT
SoWinGLWidgetP::onCreate(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  int orgmodes = this->glModes;
  this->createGLContext(window);
  if (SoWinGLWidgetP::debugGLContextCreation() && (orgmodes != this->glModes)) {
    SoDebugError::postWarning("SoWinGLWidgetP::onCreate",
                              "wanted glModes==0x%x, got 0x%x",
                              orgmodes, this->glModes);
  }

  (void)Win32::SetFocus(window);
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

// Return a flag indicating whether or not OpenGL rendering is
// happening directly from the CPU(s) to the GPU(s), ie on a local
// display. With GLX on X11, it is possible to do remote rendering.
SbBool
SoWinGLWidgetP::isDirectRendering(void)
{
  return TRUE;
}

#endif // ! DOXYGEN_SKIP_THIS
