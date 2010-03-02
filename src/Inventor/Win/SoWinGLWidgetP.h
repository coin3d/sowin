#ifndef SOWINGLWIDGETP_H
#define SOWINGLWIDGETP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#ifndef SOWIN_INTERNAL
#error this is a private header file
#endif /* !SOWIN_INTERNAL */

#include <Inventor/Win/SoGuiGLWidgetP.h>

// ************************************************************************

// This class contains private data and methods used within the
// SoWinGLWidget class.

class SoWinGLWidgetP : public SoGuiGLWidgetP
{
public:
  SoWinGLWidgetP(SoWinGLWidget * publ);
  ~SoWinGLWidgetP();

  static SbBool debugGLContextCreation(void);
  static void dumpPixelFormat(HDC hdc, int format);
  static double weighPixelFormat(const PIXELFORMATDESCRIPTOR * pfd,
                                 SbBool want_rgb = TRUE,
                                 SbBool want_dblbuffer = TRUE,
                                 SbBool want_zbuffer = TRUE,
                                 SbBool want_stereo = FALSE,
                                 SbBool want_accum = FALSE,
                                 SbBool want_stencil = FALSE,
                                 SbBool want_overlay = FALSE,
				 SbBool want_alphachannel = FALSE);

  void buildNormalGLWidget(HWND manager);
  void buildOverlayGLWidget(HWND manager);
  void createGLContext(HWND window);

  static LRESULT eventHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

  LRESULT onCreate(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  LRESULT onPaint(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  void destroyWindow(HWND window);

  static BOOL wglMakeCurrent(HDC hdc, HGLRC hglrc);

  static LRESULT CALLBACK glWidgetProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  static LRESULT CALLBACK mgrWidgetProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

  HWND managerWidget;
  HWND normalWidget;
  HWND overlayWidget;

  HGLRC ctxNormal;
  HGLRC ctxOverlay;

  HDC hdcNormal;
  HDC hdcOverlay;

  SbVec2s glSize;

  PIXELFORMATDESCRIPTOR pfdNormal;
  PIXELFORMATDESCRIPTOR pfdOverlay;

  SbBool drawToFrontBuffer;
  SbBool glRealized;
  SbBool havefocus;

  int glModes;
  SbBool accumulationenabled, stencilenabled, alphachannelenabled;
  int bordersize;
  int lockcounter;
  int overlaylockcounter;

  static ATOM managerWndClassAtom;
  static ATOM glWndClassAtom;
  static ATOM glWidgetTmpAtom;
  static int widgetCounter;

protected:
  virtual SbBool isDirectRendering(void);
};

// ************************************************************************

#endif // !SOWINGLWIDGETP_H
