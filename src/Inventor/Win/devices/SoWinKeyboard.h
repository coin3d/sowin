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

#ifndef  SO_WIN_KEYBOARD
#define  SO_WIN_KEYBOARD

#include <Inventor/events/SoKeyboardEvent.h>

#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinDevice.h>

class SoWinKeyboard : public SoWinDevice {

    enum KeyboardEvents {
        KEY_PRESS = KeyPressMask,               // 0x01,
        KEY_RELEASE = KeyReleaseMask,           // 0x02,
        ALL_EVENTS = KEY_PRESS | KEY_RELEASE
    };

public:
    SoWinKeyboard( UINT mask = ALL_EVENTS );
    ~SoWinKeyboard( void );
    
    virtual void enable( HWND widget, SoWinEventHandler * callbackproc, void * data, HWND window = NULL );
    virtual void disable( HWND widget, SoWinEventHandler * callbackproc, void * data );
    
    virtual const SoEvent * translateEvent( MSG * msg );
  
private:
    static void makeTranslationTable( void );
    
    UINT events;
    static SoKeyboardEvent * keyboardEvent;	// keyboard press or release
    SoKeyboardEvent	* makeKeyboardEvent( MSG * msg, SoButtonEvent::State s );

    // Mapping from WIN32 virtual keys to SoKeyboardEvent::Key enum
    static SbDict * translatetable;
    static int keyMapInitFlag;
};

#define SO_WIN_ALL_KEYBOARD_EVENTS SoWinKeyboard::ALL_EVENTS

#endif