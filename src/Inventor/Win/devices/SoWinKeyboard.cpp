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


// *************************************************************************

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

#include <Inventor/Win/devices/SoWinKeyCodes.h>
#include <sowindefs.h>
#include <Inventor/Win/SoWinBasic.h>

#include <Inventor/Win/devices/SoWinKeyboard.h>

// *************************************************************************

/*!
  \enum SoWinKeyboard::KeyboardEvents

  Enumeration over supported event types.
*/

SbDict * SoWinKeyboard::translatetable = NULL;

void
SoWinKeyboard::makeTranslationTable(
    void )
{
//    assert(SoWinKeyboard::translatetable == NULL);
    // FIXME: deallocate on exit. 20000311 mortene.
    SoWinKeyboard::translatetable = new SbDict;

    int i=0;
    while (WinToSoMapping[i].from != SOWIN_UNKNOWN) {
        SoWinKeyboard::translatetable->enter(WinToSoMapping[i].from,
                                        (void *)WinToSoMapping[i].to);
        i++;
    }
} // makeTranslationTable()


// *************************************************************************

/*!
  Public constructor.
*/

SoWinKeyboard::SoWinKeyboard(
  int events )
{
  this->events = events;
  this->keyboardEvent = NULL;
} // SoWinKeyboard()

/*!
  Destructor.
*/

SoWinKeyboard::~SoWinKeyboard( // virtual
  void )
{
  delete this->keyboardEvent;
} // ~SoWinKeyboard()

// *************************************************************************

/*!
  This method is not implemented.
*/

void
SoWinKeyboard::enable( // virtual
    HWND, // widget,
    LRESULT CALLBACK, // func,
    void *, // data,
    HWND ) // window )
{
  SOWIN_STUB();
} // enable()

/*!
  This methid is not implemented.
*/

void
SoWinKeyboard::disable( // virtual
    HWND, // widget,
    LRESULT CALLBACK, // func,
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
SoWinKeyboard::translateEvent( // virtual
    MSG * msg )
{
  switch ( msg->message ) {
  // events we should catch:
  case WM_KEYDOWN:
    return this->makeKeyboardEvent( msg, SoButtonEvent::DOWN);
    break;
  case WM_KEYUP:
    return this->makeKeyboardEvent( msg, SoButtonEvent::UP );
    break;

  // events we should ignore:
  default:
    break;

  } // switch ( event->type )
  return (SoEvent *) NULL;
} // translateEvent()

// *************************************************************************


/*!
  This method creates an SoKeyboardEvent from an win32 MSG.
*/

SoKeyboardEvent *
SoWinKeyboard::makeKeyboardEvent( // private
  MSG * msg,
  SoButtonEvent::State state )
{

    delete this->keyboardEvent;
    this->keyboardEvent = new SoKeyboardEvent;
    this->keyboardEvent->setState( state );

    //unsigned char repeat = ( unsigned char )( msg.lParam & 0x0f );

    void * sokey;
    if ( !(msg->lParam & 0x80000000) ) { // if key pressed
        if (SoWinKeyboard::translatetable->find( MapVirtualKey(msg->wParam,0), sokey)) {
            this->keyboardEvent->setKey((SoKeyboardEvent::Key)(int)sokey);
        } else {
            this->keyboardEvent->setKey( SoKeyboardEvent::ANY );
            return NULL;
        }
    }   // if

  // modifiers:
    this->keyboardEvent->setShiftDown( (LOWORD(msg->wParam) & VK_SHIFT) ? TRUE : FALSE );
    this->keyboardEvent->setCtrlDown( (LOWORD(msg->wParam) & VK_CONTROL) ? TRUE : FALSE );
    this->keyboardEvent->setAltDown( (LOWORD(msg->wParam) & SOWIN_ALT) ? TRUE : FALSE );

  return this->keyboardEvent;
} // makeKeyboardEvent()

// *************************************************************************
