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

#ifndef SOWIN_INPUTFOCUS_H
#define SOWIN_INPUTFOCUS_H

#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinDevice.h>

#define sowinEnterWindowMask 0x01
#define sowinLeaveWindowMask 0x02

#define SO_WIN_ALL_FOCUS_EVENTS (sowinEnterWindowMask | sowinLeaveWindowMask)

class SOWIN_DLL_API SoWinInputFocus : public SoWinDevice {
  SOWIN_OBJECT_HEADER(SoWinInputFocus, SoWinDevice);

public:
  SoWinInputFocus(UINT mask = SO_WIN_ALL_FOCUS_EVENTS);
  virtual ~SoWinInputFocus(void);

  virtual void enable( HWND widget, SoWinEventHandler * handler, void * closure, HWND window = NULL );
  virtual void disable( HWND widget, SoWinEventHandler * handler, void * closure );

  virtual const SoEvent * translateEvent( MSG * event );

private:
  UINT mask;
}; // class SoWinInputFocus

#endif // !SOWIN_INPUTFOCUS_H
