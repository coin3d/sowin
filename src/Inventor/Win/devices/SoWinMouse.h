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

#ifndef  SOWIN_MOUSE_H
#define  SOWIN_MOUSE_H

#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinDevice.h>

#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>

class SoWinMouse : public SoWinDevice {
  SOWIN_OBJECT_HEADER(SoWinMouse, SoWinDevice);

public:
  enum MouseEvents {
    BUTTON_PRESS = ButtonPressMask,         // 0x01
    BUTTON_RELEASE = ButtonReleaseMask,     // 0x02
    POINTER_MOTION = PointerMotionMask,     // 0x04 = motion, no buttons
    BUTTON_MOTION = ButtonMotionMask,       // 0x08 = motion + buttons
    ALL_EVENTS = BUTTON_PRESS | BUTTON_RELEASE | POINTER_MOTION | BUTTON_MOTION
  };

  SoWinMouse( UINT events = ALL_EVENTS );
  ~SoWinMouse( void );
    
  // Enable/disable this device for the passed widget.
  // Invoked when events occur in widget. Data is the clientData which will be passed.
  virtual void enable( HWND widget, SoWinEventHandler * callbackproc, void * data, HWND window = NULL );
  virtual void disable( HWND widget, SoWinEventHandler * callbackproc, void * data );
    
  virtual const SoEvent * translateEvent( MSG * msg );
  
private:
  SoLocation2Event * makeLocationEvent( MSG * msg );
  SoMouseButtonEvent * makeButtonEvent( MSG * msg, SoButtonEvent::State state );
  int	events;
  SoLocation2Event * locationEvent;	// mouse motion
  SoMouseButtonEvent * buttonEvent;	// mouse button
};

#define SO_WIN_ALL_MOUSE_EVENTS SoWinMouse::ALL_EVENTS

#endif // !SOWIN_MOUSE_H
