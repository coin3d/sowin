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

/*!
  \class SoWinKeyboard Inventor/Win/devices/SoWinKeyboard.h
  \brief The SoWinKeyboard class glues Win32 keyboard interaction together
  with the Open Inventor scene graph.
  \ingroup devices

  All components derived from the SoWinRenderArea have got an SoWinKeyboard 
  device attached by default.
*/

// *************************************************************************

#include <ctype.h> // toupper()

#include <Inventor/misc/SoBasic.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/errors/SoDebugError.h>

#include <sowindefs.h>
#include <Inventor/Win/devices/SoWinKeyCodes.h>
#include <Inventor/Win/devices/SoWinKeyboard.h>
#include <Inventor/Win/SoWinBasic.h>

// *************************************************************************

SOWIN_OBJECT_SOURCE(SoWinKeyboard);

// *************************************************************************

/*!
  \enum SoWinKeyboard::KeyboardEvents

  Enumeration over supported event types.
*/

SbDict * SoWinKeyboard::translatetable = NULL;
SoKeyboardEvent * SoWinKeyboard::keyboardEvent = NULL;

void
SoWinKeyboard::makeTranslationTable( void )
{
  // assert(SoWinKeyboard::translatetable == NULL);
  // FIXME: deallocate on exit. 20000811 mortene.
  SoWinKeyboard::translatetable = new SbDict;

  int i=0;
  while ( WinToSoMapping[i].from != SOWIN_KEY_UNKNOWN ) {
    SoWinKeyboard::translatetable->enter( WinToSoMapping[i].from,
                                          ( void * )WinToSoMapping[i].to );
    i++;
  }
} // makeTranslationTable()


// *************************************************************************

/*!
  Public constructor.
*/

SoWinKeyboard::SoWinKeyboard( UINT events )
{
  this->events = events;
  SoWinKeyboard::keyboardEvent = new SoKeyboardEvent;
  this->makeTranslationTable( );
} // SoWinKeyboard()

/*!
  Destructor.
*/

SoWinKeyboard::~SoWinKeyboard( void )
{
  //delete this->translatetable;
  delete SoWinKeyboard::keyboardEvent;
} // ~SoWinKeyboard()

// *************************************************************************

/*!
  This method is not implemented.
*/

void
SoWinKeyboard::enable( HWND, // widget,
                       SoWinEventHandler * , // callbackproc,
                       void *, // data,
                       HWND ) // window )
{
  SOWIN_STUB();
} // enable()

/*!
  This methid is not implemented.
*/

void
SoWinKeyboard::disable( HWND, // widget,
                        SoWinEventHandler * , // callbackproc,
                        void * ) // data )
{
  SOWIN_STUB();
} // disable()

// *************************************************************************

/*!
  This method translates between Win32 messages and Open Inventor events.

  If the win32 message is a WM_KEYDOWN, an event of the type SoKeyboardEvent
  is returned.  Otherwise, NULL is returned.
*/

const SoEvent *
SoWinKeyboard::translateEvent( MSG * msg )
{
  switch ( msg->message ) {
    // events we should catch:
  case WM_KEYDOWN:
    return this->makeKeyboardEvent( msg, SoButtonEvent::DOWN);
  case WM_KEYUP:
    return this->makeKeyboardEvent( msg, SoButtonEvent::UP );
    // events we should ignore:
  default:
    break;

  } // switch ( msg->message )
  return ( SoEvent * ) NULL;
} // translateEvent()

// *************************************************************************


/*!
  This method creates an SoKeyboardEvent from an win32 MSG *.
*/

SoKeyboardEvent *
SoWinKeyboard::makeKeyboardEvent( MSG * msg,
                                  SoButtonEvent::State state )
{
  SoWinKeyboard::keyboardEvent->setState( state );

  //unsigned char repeat = ( unsigned char )( msg.lParam & 0x0f );
  void * sokey;
  if ( SoWinKeyboard::translatetable->find( MapVirtualKey(msg->wParam,0), sokey ) ) {
    SoWinKeyboard::keyboardEvent->setKey( ( SoKeyboardEvent::Key )( int )sokey );
  } else {
    SoWinKeyboard::keyboardEvent->setKey( SoKeyboardEvent::ANY );
    return NULL;
  }

  // modifiers:
  if ( ( int )sokey == SoKeyboardEvent::LEFT_SHIFT ) {
    if ( state == SoButtonEvent::UP ) {
      SoWinDevice::modifierKeys ^= MK_SHIFT;
      //return NULL;
    } else {    // SoButtonEvent::DOWN
      if ( SoWinDevice::modifierKeys & MK_SHIFT ) return NULL;
      SoWinDevice::modifierKeys |= MK_SHIFT;
    }
  }

  if ( ( int )sokey == SoKeyboardEvent::LEFT_CONTROL ) {
    if ( state == SoButtonEvent::UP ) {
      SoWinDevice::modifierKeys ^= MK_CONTROL;
      //return NULL;
    } else {    // SoButtonEvent::DOWN
      if ( SoWinDevice::modifierKeys & MK_CONTROL ) return NULL;
      SoWinDevice::modifierKeys |= MK_CONTROL;
    }
  }

  if ( ( int )sokey == SoKeyboardEvent::LEFT_ALT ) {
    if ( state == SoButtonEvent::UP ) {
      SoWinDevice::modifierKeys ^= MK_ALT;
      //return NULL;
    } else {    // SoButtonEvent::DOWN
      if ( SoWinDevice::modifierKeys & MK_ALT ) return NULL;
      SoWinDevice::modifierKeys |= MK_ALT;
    }
  }

  SoWinKeyboard::keyboardEvent->setShiftDown( ( SoWinDevice::modifierKeys & MK_SHIFT ) ? TRUE : FALSE );
  SoWinKeyboard::keyboardEvent->setCtrlDown( ( SoWinDevice::modifierKeys & MK_CONTROL ) ? TRUE : FALSE );
  SoWinKeyboard::keyboardEvent->setAltDown( ( SoWinDevice::modifierKeys & MK_ALT ) ? TRUE : FALSE );

  return SoWinKeyboard::keyboardEvent;
} // makeKeyboardEvent()

// *************************************************************************
