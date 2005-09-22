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

#ifndef SOWIN_KEYBOARD_H
#define SOWIN_KEYBOARD_H

#include <Inventor/Win/devices/SoWinDevice.h>

class SoKeyboardEvent;

// *************************************************************************

#define SO_WIN_ALL_KEYBOARD_EVENTS SoWinKeyboard::ALL

class SOWIN_DLL_API SoWinKeyboard : public SoWinDevice {
  SOWIN_OBJECT_HEADER(SoWinKeyboard, SoWinDevice);

public:
  enum Events {
    KEY_PRESS = 0x01,
    KEY_RELEASE = 0x02,
    ALL_EVENTS = KEY_PRESS | KEY_RELEASE
  };

  SoWinKeyboard(int eventmask = ALL_EVENTS);
  virtual ~SoWinKeyboard(void);

  virtual void enable(HWND widget, SoWinEventHandler * handler, void * closure);
  virtual void disable(HWND widget, SoWinEventHandler * handler, void * closure);

  virtual const SoEvent * translateEvent(MSG * event);

private:
  class SoWinKeyboardP * pimpl;
  friend class SoWinKeyboardP;
  friend class SoGuiKeyboardP;
};

// *************************************************************************

#endif // ! SOWIN_KEYBOARD_H
