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

#include <windows.h>

#if SOWIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOWIN_DEBUG

#include <Inventor/misc/SoBasic.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>

#include <sowindefs.h>
#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinMouse.h>

/*
  FIXME: implement BUTTON_MOTION filtering
*/

// *************************************************************************

SoWinMouse::SoWinMouse(
  int events )
{
    this->events = events;
    this->locationEvent = NULL;
    this->buttonEvent = NULL;
} // SoWinMouse()

/*!
*/

SoWinMouse::~SoWinMouse( // virtual
    void )
{
    delete this->locationEvent;
    delete this->buttonEvent;
} // ~SoWinMouse()

// *************************************************************************

void
SoWinMouse::enable(HWND, LRESULT CALLBACK, void *, HWND)
{
    // FIXME: function not implemented
}

void
SoWinMouse::disable(HWND, LRESULT CALLBACK, void * )
{
    // FIXME: function not implemented
}

// *************************************************************************

const SoEvent *
SoWinMouse::translateEvent( MSG * msg )
{
    SoEvent * soevent = (SoEvent *) NULL;
    SoButtonEvent::State state = SoButtonEvent::UNKNOWN;

    switch ( msg->message ) {

        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
            if ( ! (this->events & SoWinMouse::BUTTON_PRESS) ) break;
            state = SoButtonEvent::DOWN;
            soevent = this->makeButtonEvent( msg, state );
            break;

        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
            if ( ! (this->events & SoWinMouse::BUTTON_RELEASE) ) break;
            state = SoButtonEvent::UP;
            soevent = this->makeButtonEvent( msg, state );
            break;

        case WM_MOUSEMOVE:
            if ( ! (this->events & SoWinMouse::POINTER_MOTION) ) break;
            soevent = this->makeLocationEvent( msg );
            break;

        case WM_SETFOCUS:
        case WM_KILLFOCUS:

            // should we make location-events for these?
            do {
                // FIXME: not implemented
            } while ( FALSE );
            break;

          // events we should ignore:
          default:
            break;

    } // switch ( event->type )

    return (SoEvent *) soevent;
} // translateEvent()

// *************************************************************************

SoLocation2Event *
SoWinMouse::makeLocationEvent( MSG * msg )
{
    delete this->locationEvent;
    this->locationEvent = new SoLocation2Event;
    this->setEventPosition( this->locationEvent, LOWORD(msg->lParam), HIWORD(msg->lParam) );

    this->locationEvent->setShiftDown( (LOWORD(msg->wParam) & MK_SHIFT) ? TRUE : FALSE );
    this->locationEvent->setCtrlDown( (LOWORD(msg->wParam) & MK_CONTROL) ? TRUE : FALSE );
//  this->locationEvent->setAltDown( (LOWORD(msg->wParam) & Mod1Mask) ? TRUE : FALSE );

  return this->locationEvent;
} // makeLocationEvent()

SoMouseButtonEvent *
SoWinMouse::makeButtonEvent( MSG * msg, SoButtonEvent::State state )
{
    delete this->buttonEvent;
    this->buttonEvent = new SoMouseButtonEvent;
    this->buttonEvent->setState( state );

    switch ( msg->message ) {

        case WM_LBUTTONDOWN: // left button
            this->buttonEvent->setButton( SoMouseButtonEvent::BUTTON1 );
            break;

        case WM_MBUTTONDOWN: // midbutton
            this->buttonEvent->setButton( SoMouseButtonEvent::BUTTON2 );
            break;

        case WM_RBUTTONDOWN: // right button
            this->buttonEvent->setButton( SoMouseButtonEvent::BUTTON3 );
            break;

#if 0 // FIXME: disabled until it's enabled again through autoconf test
        case WM_MOUSEWHEEL:
            if ( HIWORD(message->wParam) < 0) {  // delta z = WHEEL_DELTA = 120
                this->buttonEvent->setButton( SoMouseButtonEvent::BUTTON4 );
            } else {
                this->buttonEvent->setButton( SoMouseButtonEvent::BUTTON5 );
            }
            break;
#endif
        default:
            this->buttonEvent->setButton( SoMouseButtonEvent::ANY );
        break;
        } // switch ( message.message)
    this->setEventPosition( this->buttonEvent, LOWORD(msg->lParam), HIWORD(msg->lParam) );

    this->buttonEvent->setShiftDown( (LOWORD(msg->wParam) & MK_SHIFT) ? TRUE : FALSE );
    this->buttonEvent->setCtrlDown( (LOWORD(msg->wParam) & MK_CONTROL) ? TRUE : FALSE );
//  this->buttonEvent->setAltDown( (LOWORD(msg->wParam) & Mod1Mask) ? TRUE : FALSE );

    return this->buttonEvent;
} // makeButtonEvent()

// *************************************************************************
