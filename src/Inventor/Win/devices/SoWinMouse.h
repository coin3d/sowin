/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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
\**************************************************************************/

#ifndef  SO_WIN_MOUSE
#define  SO_WIN_MOUSE

#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinDevice.h>

#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>

class SoWinMouse : public SoWinDevice {
    enum MouseEvents {
        BUTTON_PRESS = ButtonPressMask,         // 0x01
        BUTTON_RELEASE = ButtonReleaseMask,     // 0x02
        POINTER_MOTION = PointerMotionMask,     // 0x04 = motion, no buttons
        BUTTON_MOTION = ButtonMotionMask,       // 0x08 = motion + buttons
        ALL_EVENTS = BUTTON_PRESS | BUTTON_RELEASE | POINTER_MOTION | BUTTON_MOTION
    };
public:

    SoWinMouse( UINT events = ALL_EVENTS );
    ~SoWinMouse( void );
    
    // Enable/disable this device for the passed widget.
    // Invoked when events occur in widget. Data is the clientData which will be passed.
    virtual void enable( HWND widget, LRESULT CALLBACK func, void * data, HWND window = NULL );
    virtual void disable( HWND widget, LRESULT CALLBACK func, void * data );
    
    virtual const SoEvent * translateEvent( MSG * msg );
  
  private:
    SoLocation2Event * makeLocationEvent( MSG * msg );
    SoMouseButtonEvent * makeButtonEvent( MSG * msg, SoButtonEvent::State state );
    int	events;
    SoLocation2Event * locationEvent;	// mouse motion
    SoMouseButtonEvent * buttonEvent;	// mouse button
};

#define SO_WIN_ALL_MOUSE_EVENTS SoWinMouse::ALL_EVENTS

#endif /* SO_WIN_MOUSE */