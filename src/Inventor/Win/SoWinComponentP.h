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

#ifndef SOWINCOMPONENTP_H
#define SOWINCOMPONENTP_H

#include <Inventor/Win/SoGuiComponentP.h>
#include <Inventor/Win/SoWinCursor.h>

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


  static HHOOK hookhandle; // for (global) system message queue interception
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

  const SoWinCursor * cursor;
  SbBool realized;

private:
  static SbDict * cursordict;
};

// ************************************************************************

#endif // !SOWINCOMPONENTP_H
