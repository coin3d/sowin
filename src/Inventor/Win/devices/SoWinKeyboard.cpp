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

struct key1map {
  int from;                // Win val
  SoKeyboardEvent::Key to; // So val
};

static struct key1map WinToSoMapping[] = {
  {SOWIN_KEY_ESC, SoKeyboardEvent::ESCAPE},
  {SOWIN_KEY_TAB, SoKeyboardEvent::TAB},
//    {Key_Backtab, SoKeyboardEvent::}, // FIXME
  {SOWIN_KEY_BACKSPACE, SoKeyboardEvent::BACKSPACE},
  {SOWIN_KEY_RETURN, SoKeyboardEvent::RETURN},
  {SOWIN_KEY_ENTER, SoKeyboardEvent::ENTER},
  {SOWIN_KEY_INSERT, SoKeyboardEvent::INSERT},
  {SOWIN_KEY_DELETE, SoKeyboardEvent::KEY_DELETE},
  {SOWIN_KEY_PAUSE, SoKeyboardEvent::PAUSE},
  {SOWIN_KEY_PRINT, SoKeyboardEvent::PRINT},
//    {Key_SysReq, SoKeyboardEvent::}, // FIXME
  {SOWIN_KEY_HOME, SoKeyboardEvent::HOME},
  {SOWIN_KEY_END, SoKeyboardEvent::END},
  {SOWIN_KEY_LEFT, SoKeyboardEvent::LEFT_ARROW},
  {SOWIN_KEY_UP, SoKeyboardEvent::UP_ARROW},
  {SOWIN_KEY_RIGHT, SoKeyboardEvent::RIGHT_ARROW},
  {SOWIN_KEY_DOWN, SoKeyboardEvent::DOWN_ARROW},
//  {Key_Prior, SoKeyboardEvent::PRIOR},
  {SOWIN_KEY_PGUP, SoKeyboardEvent::PAGE_UP},
//  {Key_Next, SoKeyboardEvent::NEXT},
  {SOWIN_KEY_DOWN, SoKeyboardEvent::PAGE_DOWN},

  {SOWIN_KEY_SHIFT, SoKeyboardEvent::LEFT_SHIFT},
  {SOWIN_KEY_CTRL, SoKeyboardEvent::LEFT_CONTROL},
//{Key_Meta, SoKeyboardEvent::LEFT_ALT},
  {SOWIN_KEY_ALT, SoKeyboardEvent::LEFT_ALT}, // FIXME: makes trouble
  {SOWIN_KEY_CAPS_LOCK, SoKeyboardEvent::CAPS_LOCK},
  {SOWIN_KEY_NUM_LOCK, SoKeyboardEvent::NUM_LOCK},
  {SOWIN_KEY_SCROLL_LOCK, SoKeyboardEvent::SCROLL_LOCK},

  {SOWIN_KEY_F1, SoKeyboardEvent::F1},
  {SOWIN_KEY_F2, SoKeyboardEvent::F2},
  {SOWIN_KEY_F3, SoKeyboardEvent::F3},
  {SOWIN_KEY_F4, SoKeyboardEvent::F4},
  {SOWIN_KEY_F5, SoKeyboardEvent::F5},
  {SOWIN_KEY_F6, SoKeyboardEvent::F6},
  {SOWIN_KEY_F7, SoKeyboardEvent::F7},
  {SOWIN_KEY_F8, SoKeyboardEvent::F8},
  {SOWIN_KEY_F9, SoKeyboardEvent::F9},
  {SOWIN_KEY_F10, SoKeyboardEvent::F10},
  {SOWIN_KEY_F11, SoKeyboardEvent::F11},
  {SOWIN_KEY_F12, SoKeyboardEvent::F12},
//    {Key_F13, SoKeyboardEvent::}, // FIXME
//    {Key_F14, SoKeyboardEvent::}, // FIXME
//    {Key_F15, SoKeyboardEvent::}, // FIXME
//    {Key_F16, SoKeyboardEvent::}, // FIXME
//    {Key_F17, SoKeyboardEvent::}, // FIXME
//    {Key_F18, SoKeyboardEvent::}, // FIXME
//    {Key_F19, SoKeyboardEvent::}, // FIXME
//    {Key_F20, SoKeyboardEvent::}, // FIXME
//    {Key_F21, SoKeyboardEvent::}, // FIXME
//    {Key_F22, SoKeyboardEvent::}, // FIXME
//    {Key_F23, SoKeyboardEvent::}, // FIXME
//    {Key_F24, SoKeyboardEvent::}, // FIXME
//    {Key_F25, SoKeyboardEvent::}, // FIXME
//    {Key_F26, SoKeyboardEvent::}, // FIXME
//    {Key_F27, SoKeyboardEvent::}, // FIXME
//    {Key_F28, SoKeyboardEvent::}, // FIXME
//    {Key_F29, SoKeyboardEvent::}, // FIXME
//    {Key_F30, SoKeyboardEvent::}, // FIXME
//    {Key_F31, SoKeyboardEvent::}, // FIXME
//    {Key_F32, SoKeyboardEvent::}, // FIXME
//    {Key_F33, SoKeyboardEvent::}, // FIXME
//    {Key_F34, SoKeyboardEvent::}, // FIXME
//    {Key_F35, SoKeyboardEvent::}, // FIXME

//    {Key_Super, SoKeyboardEvent::}, // FIXME
//    {Key_Super, SoKeyboardEvent::}, // FIXME
//    {Key_Menu, SoKeyboardEvent::}, // FIXME


  {SOWIN_KEY_SPACE, SoKeyboardEvent::SPACE},
//    {Key_Exclam, SoKeyboardEvent::}, // FIXME
//    {Key_QuoteDbl, SoKeyboardEvent::}, // FIXME
//    {Key_NumberSign, SoKeyboardEvent::}, // FIXME
//    {Key_Dollar, SoKeyboardEvent::}, // FIXME
//    {Key_Percent, SoKeyboardEvent::}, // FIXME
//    {Key_Ampersand, SoKeyboardEvent::}, // FIXME
  {SOWIN_KEY_OEM_5, SoKeyboardEvent::APOSTROPHE},
//    {Key_ParenLeft, SoKeyboardEvent::}, // FIXME
//    {Key_ParenRight, SoKeyboardEvent::}, // FIXME
//    {Key_Asterisk, SoKeyboardEvent::}, // FIXME
//    {Key_Plus, SoKeyboardEvent::}, // FIXME
  {SOWIN_KEY_OEM_COMMA, SoKeyboardEvent::COMMA},
  {SOWIN_KEY_OEM_SUBTRACT, SoKeyboardEvent::MINUS},
  {SOWIN_KEY_OEM_PERIOD, SoKeyboardEvent::PERIOD},
  {SOWIN_KEY_OEM_2, SoKeyboardEvent::SLASH},
  {SOWIN_KEY_0, SoKeyboardEvent::NUMBER_0},
  {SOWIN_KEY_1, SoKeyboardEvent::NUMBER_1},
  {SOWIN_KEY_2, SoKeyboardEvent::NUMBER_2},
  {SOWIN_KEY_3, SoKeyboardEvent::NUMBER_3},
  {SOWIN_KEY_4, SoKeyboardEvent::NUMBER_4},
  {SOWIN_KEY_5, SoKeyboardEvent::NUMBER_5},
  {SOWIN_KEY_6, SoKeyboardEvent::NUMBER_6},
  {SOWIN_KEY_7, SoKeyboardEvent::NUMBER_7},
  {SOWIN_KEY_8, SoKeyboardEvent::NUMBER_8},
  {SOWIN_KEY_9, SoKeyboardEvent::NUMBER_9},
//    {Key_Colon, SoKeyboardEvent::}, // FIXME
  {SOWIN_KEY_OEM_7, SoKeyboardEvent::SEMICOLON},
//    {Key_Less, SoKeyboardEvent::}, // FIXME
  {SOWIN_KEY_OEM_1, SoKeyboardEvent::EQUAL},
//    {Key_Greater, SoKeyboardEvent::}, // FIXME
//    {Key_Question, SoKeyboardEvent::}, // FIXME
//    {Key_At, SoKeyboardEvent::}, // FIXME
  {SOWIN_KEY_A, SoKeyboardEvent::A},
  {SOWIN_KEY_B, SoKeyboardEvent::B},
  {SOWIN_KEY_C, SoKeyboardEvent::C},
  {SOWIN_KEY_D, SoKeyboardEvent::D},
  {SOWIN_KEY_E, SoKeyboardEvent::E},
  {SOWIN_KEY_F, SoKeyboardEvent::F},
  {SOWIN_KEY_G, SoKeyboardEvent::G},
  {SOWIN_KEY_H, SoKeyboardEvent::H},
  {SOWIN_KEY_I, SoKeyboardEvent::I},
  {SOWIN_KEY_J, SoKeyboardEvent::J},
  {SOWIN_KEY_K, SoKeyboardEvent::K},
  {SOWIN_KEY_L, SoKeyboardEvent::L},
  {SOWIN_KEY_M, SoKeyboardEvent::M},
  {SOWIN_KEY_N, SoKeyboardEvent::N},
  {SOWIN_KEY_O, SoKeyboardEvent::O},
  {SOWIN_KEY_P, SoKeyboardEvent::P},
  {SOWIN_KEY_Q, SoKeyboardEvent::Q},
  {SOWIN_KEY_R, SoKeyboardEvent::R},
  {SOWIN_KEY_S, SoKeyboardEvent::S},
  {SOWIN_KEY_T, SoKeyboardEvent::T},
  {SOWIN_KEY_U, SoKeyboardEvent::U},
  {SOWIN_KEY_V, SoKeyboardEvent::V},
  {SOWIN_KEY_W, SoKeyboardEvent::W},
  {SOWIN_KEY_X, SoKeyboardEvent::X},
  {SOWIN_KEY_Y, SoKeyboardEvent::Y},
  {SOWIN_KEY_Z, SoKeyboardEvent::Z},
//  {Key_BracketLeft, SoKeyboardEvent::BRACKETLEFT},
  {SOWIN_KEY_OEM_102, SoKeyboardEvent::BACKSLASH},
//  {Key_BracketRight, SoKeyboardEvent::BRACKETRIGHT},
//    {Key_AsciiCircum, SoKeyboardEvent::}, // FIXME
//    {Key_Underscore, SoKeyboardEvent::}, // FIXME
//    {Key_QuoteLeft, SoKeyboardEvent::}, // FIXME
//    {Key_BraceLeft, SoKeyboardEvent::}, // FIXME
//    {Key_Bar, SoKeyboardEvent::}, // FIXME
//    {Key_BraceRight, SoKeyboardEvent::}, // FIXME
//  {Key_AsciiTilde, SoKeyboardEvent::GRAVE}, // FIXME: is this correct?

  // Latin-1
//    {Key_nobreakspace, SoKeyboardEvent::}, // FIXME
//    {Key_exclamdown, SoKeyboardEvent::}, // FIXME
//    {Key_cent, SoKeyboardEvent::}, // FIXME
//    {Key_sterling, SoKeyboardEvent::}, // FIXME
//    {Key_currency, SoKeyboardEvent::}, // FIXME
//    {Key_yen, SoKeyboardEvent::}, // FIXME
//    {Key_brokenbar, SoKeyboardEvent::}, // FIXME
//    {Key_section, SoKeyboardEvent::}, // FIXME
//    {Key_diaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_copyright, SoKeyboardEvent::}, // FIXME
//    {Key_ordfeminine, SoKeyboardEvent::}, // FIXME
//    {Key_guillemotleft, SoKeyboardEvent::}, // FIXME
//    {Key_notsign, SoKeyboardEvent::}, // FIXME
//    {Key_hyphen, SoKeyboardEvent::}, // FIXME
//    {Key_registered, SoKeyboardEvent::}, // FIXME
//    {Key_macron, SoKeyboardEvent::}, // FIXME
//    {Key_degree, SoKeyboardEvent::}, // FIXME
//    {Key_plusminus, SoKeyboardEvent::}, // FIXME
//    {Key_twosuperior, SoKeyboardEvent::}, // FIXME
//    {Key_threesuperior, SoKeyboardEvent::}, // FIXME
//    {Key_acute, SoKeyboardEvent::}, // FIXME
//    {Key_mu, SoKeyboardEvent::}, // FIXME
//    {Key_paragraph, SoKeyboardEvent::}, // FIXME
//    {Key_periodcentered, SoKeyboardEvent::}, // FIXME
//    {Key_cedilla, SoKeyboardEvent::}, // FIXME
//    {Key_onesuperior, SoKeyboardEvent::}, // FIXME
//    {Key_masculine, SoKeyboardEvent::}, // FIXME
//    {Key_guillemotright, SoKeyboardEvent::}, // FIXME
//    {Key_onequarter, SoKeyboardEvent::}, // FIXME
//    {Key_onehalf, SoKeyboardEvent::}, // FIXME
//    {Key_threequarters, SoKeyboardEvent::}, // FIXME
//    {Key_questiondown, SoKeyboardEvent::}, // FIXME
//    {Key_Agrave, SoKeyboardEvent::}, // FIXME
//    {Key_Aacute, SoKeyboardEvent::}, // FIXME
//    {Key_Acircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_Atilde, SoKeyboardEvent::}, // FIXME
//    {Key_Adiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_Aring, SoKeyboardEvent::}, // FIXME
//    {Key_AE, SoKeyboardEvent::}, // FIXME
//    {Key_Ccedilla, SoKeyboardEvent::}, // FIXME
//    {Key_Egrave, SoKeyboardEvent::}, // FIXME
//    {Key_Eacute, SoKeyboardEvent::}, // FIXME
//    {Key_Ecircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_Ediaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_Igrave, SoKeyboardEvent::}, // FIXME
//    {Key_Iacute, SoKeyboardEvent::}, // FIXME
//    {Key_Icircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_Idiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_ETH, SoKeyboardEvent::}, // FIXME
//    {Key_Ntilde, SoKeyboardEvent::}, // FIXME
//    {Key_Ograve, SoKeyboardEvent::}, // FIXME
//    {Key_Oacute, SoKeyboardEvent::}, // FIXME
//    {Key_Ocircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_Otilde, SoKeyboardEvent::}, // FIXME
//    {Key_Odiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_multiply, SoKeyboardEvent::}, // FIXME
//    {Key_Ooblique, SoKeyboardEvent::}, // FIXME
//    {Key_Ugrave, SoKeyboardEvent::}, // FIXME
//    {Key_Uacute, SoKeyboardEvent::}, // FIXME
//    {Key_Ucircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_Udiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_Yacute, SoKeyboardEvent::}, // FIXME
//    {Key_THORN, SoKeyboardEvent::}, // FIXME
//    {Key_ssharp, SoKeyboardEvent::}, // FIXME
//    {Key_agrave, SoKeyboardEvent::}, // FIXME
//    {Key_aacute, SoKeyboardEvent::}, // FIXME
//    {Key_acircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_atilde, SoKeyboardEvent::}, // FIXME
//    {Key_adiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_aring, SoKeyboardEvent::}, // FIXME
//    {Key_ae, SoKeyboardEvent::}, // FIXME
//    {Key_ccedilla, SoKeyboardEvent::}, // FIXME
//    {Key_egrave, SoKeyboardEvent::}, // FIXME
//    {Key_eacute, SoKeyboardEvent::}, // FIXME
//    {Key_ecircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_ediaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_igrave, SoKeyboardEvent::}, // FIXME
//    {Key_iacute, SoKeyboardEvent::}, // FIXME
//    {Key_icircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_idiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_eth, SoKeyboardEvent::}, // FIXME
//    {Key_ntilde, SoKeyboardEvent::}, // FIXME
//    {Key_ograve, SoKeyboardEvent::}, // FIXME
//    {Key_oacute, SoKeyboardEvent::}, // FIXME
//    {Key_ocircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_otilde, SoKeyboardEvent::}, // FIXME
//    {Key_odiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_division, SoKeyboardEvent::}, // FIXME
//    {Key_oslash, SoKeyboardEvent::}, // FIXME
//    {Key_ugrave, SoKeyboardEvent::}, // FIXME
//    {Key_uacute, SoKeyboardEvent::}, // FIXME
//    {Key_ucircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_udiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_yacute, SoKeyboardEvent::}, // FIXME
//    {Key_thorn, SoKeyboardEvent::}, // FIXME
//    {Key_ydiaeresis, SoKeyboardEvent::}, // FIXME

  {SOWIN_KEY_UNKNOWN, SoKeyboardEvent::ANY} // Ends table
};

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
