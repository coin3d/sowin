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

#ifndef  SOWIN_KEYBOARD_H
#define  SOWIN_KEYBOARD_H

#include <Inventor/events/SoKeyboardEvent.h>

#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinDevice.h>

class SOWIN_DLL_API SoWinKeyboard : public SoWinDevice {
  SOWIN_OBJECT_HEADER(SoWinKeyboard, SoWinDevice);

public:
  enum KeyboardEvents {
    KEY_PRESS = KeyPressMask,               // 0x01,
    KEY_RELEASE = KeyReleaseMask,           // 0x02,
    ALL_EVENTS = KEY_PRESS | KEY_RELEASE
  };

  SoWinKeyboard(UINT mask = ALL_EVENTS);
  ~SoWinKeyboard(void);
    
  virtual void enable(HWND widget, SoWinEventHandler * callbackproc, void * data, HWND window = NULL);
  virtual void disable(HWND widget, SoWinEventHandler * callbackproc, void * data);
    
  virtual const SoEvent * translateEvent(MSG * msg);
  
private:
  static void makeTranslationTable(void);
    
  UINT events;
  static SoKeyboardEvent * keyboardEvent; // keyboard press or release
  SoKeyboardEvent * makeKeyboardEvent(MSG * msg, SoButtonEvent::State s);

  // Mapping from WIN32 virtual keys to SoKeyboardEvent::Key enum
  static SbDict * translatetable;
  static int keyMapInitFlag;
};

#define SO_WIN_ALL_KEYBOARD_EVENTS SoWinKeyboard::ALL_EVENTS

#endif // !SOWIN_KEYBOARD_H
