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

#ifndef  SOWIN_DEVICE_H
#define  SOWIN_DEVICE_H

#include <Inventor/SbLinear.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/Win/SoWinObject.h>
#include <wtypes.h>

#define ButtonPressMask   0x01
#define ButtonReleaseMask 0x02
#define PointerMotionMask 0x04
#define ButtonMotionMask  0x08
#define KeyPressMask      0x10
#define KeyReleaseMask    0x20

#ifndef MK_ALT
#define MK_ALT 0x02
#endif


typedef void SoWinEventHandler(HWND, void *, MSG *, SbBool *);
typedef void (*SoWinEventHandlerPtr)(HWND, void *, MSG *, SbBool *);

class SoWinDevice : public SoWinObject {
    SOWIN_OBJECT_ABSTRACT_HEADER(SoWinDevice, SoWinObject);

public:
    SoWinDevice( void );
    ~SoWinDevice( void );

    virtual void enable( HWND widget, SoWinEventHandler * callbackproc, void * data, HWND window = NULL ) = 0;
    virtual void disable( HWND widget, SoWinEventHandler * callbackproc, void * data ) = 0;
    
    virtual const SoEvent * translateEvent( MSG * msg ) = 0;

    void setWindowSize( const SbVec2s newSize );
    const SbVec2s getWindowSize( void ) const;

    static void initClasses(void);

protected:
    // set the window coordinate from the passed x,y value. This will flip
    // the y value to convert from X coordinates to So coordinates.
    void setEventPosition( SoEvent * event, int x, int y ) const;
    static long modifierKeys;
    
private:
    SbVec2s size;
};

#endif // !SOWIN_DEVICE_H
