/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef SOWINGLWIDGETP_H
#define SOWINGLWIDGETP_H

#include <Inventor/Win/SoGuiGLWidgetP.h>

// ************************************************************************

// This class contains private data and methods used within the
// SoWinGLWidget class.

class SoWinGLWidgetP : public SoGuiGLWidgetP
{
public:
  SoWinGLWidgetP(SoWinGLWidget * publ);
  ~SoWinGLWidgetP();


  void buildNormalGLWidget(HWND manager);
  void buildOverlayGLWidget(HWND manager);
  BOOL createGLContext(HWND window);

  static LRESULT eventHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

  LRESULT onCreate(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  LRESULT onPaint(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  LRESULT onDestroy(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

  static BOOL wglMakeCurrent(HDC hdc, HGLRC hglrc);
  static int ChoosePixelFormat(HDC hdc, CONST PIXELFORMATDESCRIPTOR * ppfd);

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
  SbBool haveFocus;
  SbBool stealFocus;
  SbBool glRealized;

  int glModes;
  int bordersize;
  int lockcounter;
  int overlaylockcounter;

  static ATOM managerWndClassAtom;
  static ATOM glWndClassAtom;
  static int widgetCounter;
};

// ************************************************************************

#endif // !SOWINGLWIDGETP_H
