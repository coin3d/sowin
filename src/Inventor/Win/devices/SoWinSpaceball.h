/**************************************************************************
 *
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
 **************************************************************************/

#ifndef  SOWIN_SPACEBALL_H
#define  SOWIN_SPACEBALL_H

#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/devices/SoWinDevice.h>

#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>

class SoWinSpaceball : public SoWinDevice {
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
    
    virtual void enable( HWND, SoWinEventHandler * , void *, HWND );
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

#endif // SOWIN_SPACEBALL_H
