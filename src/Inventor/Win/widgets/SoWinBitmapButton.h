#ifndef SOWIN_BITMAPBUTTON_H
#define SOWIN_BITMAPBUTTON_H

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

#ifndef SOWIN_INTERNAL
#error this is a private header file
#endif /* !SOWIN_INTERNAL */

#include <windows.h>

#include <Inventor/SbBasic.h>
#include <Inventor/Win/SoWinBasic.h>

class SoWinFullViewer;

// *************************************************************************

class SOWIN_DLL_API SoWinBitmapButton {

public:
  SoWinBitmapButton(HWND parent,
                    int x,
                    int y,
                    int width = 30,
                    int height = 30,
                    int depth = 0,
                    const char * name = NULL,
                    void * bits = NULL);
  SoWinBitmapButton(HWND parent,
                    int depth = 0,
                    const char * name = NULL,
                    void * bits = NULL);
  ~SoWinBitmapButton();

  void setEnabled(SbBool enable);
  SbBool isEnabled(void) const;

  void setPressedState(SbBool enable);
  SbBool getPressedState(void) const;

  void addBitmap(HBITMAP hbmp);
  void addBitmap(int width, int height, int bpp, void * src);
  void addBitmap(const char ** xpm, int bpp = 24);
  HBITMAP getBitmap(int index) const;
  void setBitmap(int index);

  HWND getWidget(void);

  int width(void) const;
  int height(void) const;
  void move(int x, int y);
  void move(int x, int y, int width, int height);
  void resize(int width, int height);

  void show(void);
  void hide(void);

  typedef void ClickedProc(SoWinBitmapButton * button, void * userdata);
  void registerClickedProc(ClickedProc * func, void * userdata);

private:
  class SoWinBitmapButtonP * pimpl;
  friend class SoWinBitmapButtonP;
};

// *************************************************************************

#endif // ! SOWIN_BITMAPBUTTON_H
