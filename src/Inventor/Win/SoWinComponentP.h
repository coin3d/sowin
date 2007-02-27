#ifndef SOWINCOMPONENTP_H
#define SOWINCOMPONENTP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SOWIN_INTERNAL
#error this is a private header file
#endif /* !SOWIN_INTERNAL */

#include <Inventor/Win/SoGuiComponentP.h>
#include <Inventor/Win/SoWinCursor.h>

class SbStorage;

// ************************************************************************

// "Hidden" class for storing private data (to avoid cluttering up the
// header file, and to make it easier to keep ABI compatibility upon
// changes.)

class SoWinComponentP : public SoGuiComponentP
{
public:
  SoWinComponentP(SoWinComponent * publ);
  ~SoWinComponentP();


  static HCURSOR getNativeCursor(const SoWinCursor::CustomCursor * cc);

  static void fatalerrorHandler(void * userdata);
  void cleanupWin32References(void);

  static LRESULT CALLBACK frameWindowHandler(HWND window, UINT message,
                                             WPARAM wparam, LPARAM lparam);

  void commonEventHandler(UINT message, WPARAM wparam, LPARAM lparam);
  static LRESULT CALLBACK systemEventFilter(int code, WPARAM wparam, LPARAM lparam);

  HWND buildFormWidget(HWND parent);

  static SbStorage * hookhandle; // for (global) system message queue interception
  HWND parent;
  HWND widget;
  HWND focusProxy;
  SbBool embedded;
  SbString classname, widgetname, title;
  SoWinComponentCB * closeCB;
  void * closeCBdata;
  SbPList * visibilitychangeCBs;
  static SbDict * embeddedparents;

  // This is the atom returned when the component
  // window class is registered.
  static ATOM wndClassAtom;

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

  SbBool hascursor;
  SoWinCursor currcursor;
  SbBool realized;

private:
  static SbDict * cursordict;
};

// ************************************************************************

#endif // !SOWINCOMPONENTP_H
