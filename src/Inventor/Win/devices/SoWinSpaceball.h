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

#ifndef  SOWIN_SPACEBALL_H
#define  SOWIN_SPACEBALL_H

#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/devices/SoWinDevice.h>

#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>

class SoWinSpaceball : public SoWinDevice {
  SOWIN_OBJECT_HEADER(SoWinSpaceball, SoWinDevice);

public:
  enum Mask {
    MOTION_EVENT  = 0x01,  MOTION = MOTION_EVENT,
    PRESS_EVENT   = 0x02,  PRESS = PRESS_EVENT,
    RELEASE_EVENT = 0x04,  RELEASE = RELEASE_EVENT,
    ALL_EVENTS = MOTION_EVENT | PRESS_EVENT | RELEASE_EVENT,
    ALL = ALL_EVENTS
  };

  SoWinSpaceball( UINT mask = ALL_EVENTS );
  ~SoWinSpaceball( void );
    
  virtual void enable( HWND, SoWinEventHandler * , void *, HWND = NULL );
  virtual void disable( HWND, SoWinEventHandler * , void * );

  virtual const SoEvent * translateEvent( MSG * msg );
  
  void setRotationScaleFactor( float factor );
  float getRotationScaleFactor( void ) const;
  void setTranslationScaleFactor( float factor );
  float getTranslationScaleFactor( void ) const;

  static SbBool exists( void );
 
  void setFocusToWindow(SbBool flag);
  SbBool isFocusToWindow( void ) const;
   
private:
  UINT eventMask;
  SoMotion3Event * motionEvent;
  SoSpaceballButtonEvent * buttonEvent;
 
  HWND parentWidget;

  float rotScale;
  float transScale;

  SoMotion3Event * translateMotionEvent( MSG * motionEvent );
  SoSpaceballButtonEvent * translateButtonEvent( MSG * buttonEvent,
                                                 SoButtonEvent::State whichState );
  SoMotion3Event * translateMotionEventMagellan( MSG * motionEvent );
	
  //struct _MagellanControl_ *magellanHandle; 
};

#define SO_WIN_ALL_SPACEBALL_EVENTS SoWinSpaceball::ALL_EVENTS

#endif // !SOWIN_SPACEBALL_H
