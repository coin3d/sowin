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

SOWIN_OBJECT_SOURCE(SoWinMouse);

// *************************************************************************

SoWinMouse::SoWinMouse( UINT events )
{
  this->events = events;
  this->locationEvent = NULL;
  this->buttonEvent = NULL;
  this->downCount = 0;
} // SoWinMouse()

/*!
*/

SoWinMouse::~SoWinMouse( void )
{
  delete this->locationEvent;
  delete this->buttonEvent;
} // ~SoWinMouse()

// *************************************************************************

void
SoWinMouse::enable(HWND, SoWinEventHandler * , void *, HWND)
{
  // FIXME: function not implemented
  SOWIN_STUB( );
}

void
SoWinMouse::disable(HWND, SoWinEventHandler * , void * )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
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
    this->downCount++;
    if ( ! ( this->events & SoWinMouse::BUTTON_PRESS ) ) break;
    state = SoButtonEvent::DOWN;
    soevent = this->makeButtonEvent( msg, state );
    break;

  case WM_LBUTTONUP:
  case WM_MBUTTONUP:
  case WM_RBUTTONUP:
    this->downCount--;
    if ( this->downCount < 0 ) {
      this->downCount = 0;
      break;
    }
    if ( ! ( this->events & SoWinMouse::BUTTON_RELEASE ) ) break;
    state = SoButtonEvent::UP;
    soevent = this->makeButtonEvent( msg, state );
    break;

  case WM_MOUSEMOVE:
    if ( ! ( this->events & SoWinMouse::POINTER_MOTION ) ) break;
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

  long msec = GetTickCount( );
  if ( soevent ) soevent->setTime( SbTime( ( msec / 1000 ), ( msec % 1000 ) * 1000 ) );

  return (SoEvent *) soevent;
} // translateEvent()

// *************************************************************************

SoLocation2Event *
SoWinMouse::makeLocationEvent( MSG * msg )
{
  static POINT prevPos = { 0xFFFF, 0xFFFF };
  if ( ( msg->pt.x == prevPos.x ) && ( msg->pt.y == prevPos.y ) ) {
    return NULL;
  }
  else {
    prevPos = msg->pt;
  }
  
  if ( this->locationEvent == NULL ) 
    this->locationEvent = new SoLocation2Event;
  this->setEventPosition( this->locationEvent, msg->pt.x, msg->pt.y );

  this->locationEvent->setShiftDown( ( SoWinDevice::modifierKeys & MK_SHIFT ) ? TRUE : FALSE );
  this->locationEvent->setCtrlDown( ( SoWinDevice::modifierKeys & MK_CONTROL ) ? TRUE : FALSE );
  this->locationEvent->setAltDown( ( SoWinDevice::modifierKeys & MK_ALT ) ? TRUE : FALSE );

  return this->locationEvent;
} // makeLocationEvent()

SoMouseButtonEvent *
SoWinMouse::makeButtonEvent( MSG * msg, SoButtonEvent::State state )
{
  if (this->buttonEvent == NULL)
    this->buttonEvent = new SoMouseButtonEvent;

  this->buttonEvent->setState( state );

  switch ( msg->message ) {

  case WM_LBUTTONDOWN: // left button
  case WM_LBUTTONUP:
    this->buttonEvent->setButton( SoMouseButtonEvent::BUTTON1 );
    break;

  case WM_MBUTTONDOWN: // midbutton
  case WM_MBUTTONUP:
    this->buttonEvent->setButton( SoMouseButtonEvent::BUTTON3 );
    break;

  case WM_RBUTTONDOWN: // right button
  case WM_RBUTTONUP:
    this->buttonEvent->setButton( SoMouseButtonEvent::BUTTON2 );
    break;

#if 0   // FIXME: disabled until it's enabled again through autoconf test
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

  /*  if (this->locationEvent) {
    this->buttonEvent->setPosition(this->locationEvent->getPosition());
  }
  else {*/
    this->setEventPosition( this->buttonEvent, msg->pt.x, msg->pt.y );
    //}
  this->buttonEvent->setShiftDown( ( SoWinDevice::modifierKeys & MK_SHIFT ) ? TRUE : FALSE );
  this->buttonEvent->setCtrlDown( ( SoWinDevice::modifierKeys & MK_CONTROL ) ? TRUE : FALSE );
  this->buttonEvent->setAltDown( ( SoWinDevice::modifierKeys & MK_ALT ) ? TRUE : FALSE );
  
  return this->buttonEvent;
} // makeButtonEvent()

// *************************************************************************
