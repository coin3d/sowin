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
#include <Inventor/Win/devices/SoWinKeyboard.h>
#include <Inventor/Win/SoWinBasic.h>
#include <winuser.h> // VK_ defines

// *************************************************************************

SOWIN_OBJECT_SOURCE(SoWinKeyboard);

// *************************************************************************

#define VK_OEM_SCROLL 0x91
#define VK_OEM_1 0xBA
#define VK_OEM_PLUS 0xBB
#define VK_OEM_COMMA 0xBC
#define VK_OEM_MINUS 0xBD
#define VK_OEM_PERIOD 0xBE
#define VK_OEM_2 0xBF
#define VK_OEM_3 0xC0
#define VK_OEM_4 0xDB
#define VK_OEM_5 0xDC
#define VK_OEM_6 0xDD
#define VK_OEM_7 0xDE
#define VK_OEM_8 0xDF
#define VK_ICO_F17 0xE0
#define VK_ICO_F18 0xE1
#define VK_OEM102 0xE2
#define VK_ICO_HELP 0xE3
#define VK_ICO_00 0xE4
#define VK_ICO_CLEAR 0xE6
#define VK_OEM_RESET 0xE9
#define VK_OEM_JUMP 0xEA
#define VK_OEM_PA1 0xEB
#define VK_OEM_PA2 0xEC
#define VK_OEM_PA3 0xED
#define VK_OEM_WSCTRL 0xEE
#define VK_OEM_CUSEL 0xEF
#define VK_OEM_ATTN 0xF0
#define VK_OEM_FINNISH 0xF1
#define VK_OEM_COPY 0xF2
#define VK_OEM_AUTO 0xF3
#define VK_OEM_ENLW 0xF4
#define VK_OEM_BACKTAB 0xF5
#define VK_ATTN 0xF6
#define VK_CRSEL 0xF7
#define VK_EXSEL 0xF8
#define VK_EREOF 0xF9
#define VK_PLAY 0xFA
#define VK_ZOOM 0xFB
#define VK_NONAME 0xFC
#define VK_PA1 0xFD
#define VK_OEM_CLEAR 0xFE

#define VK_UNKNOWN 0xFF

// *************************************************************************

struct key1map {
  int from;                // Win val
  SoKeyboardEvent::Key to; // So val
};

static struct key1map WinToSoMapping[] = {
  {VK_ESCAPE, SoKeyboardEvent::ESCAPE},
  {VK_TAB, SoKeyboardEvent::TAB},
  {VK_BACK, SoKeyboardEvent::BACKSPACE},
  {VK_RETURN, SoKeyboardEvent::RETURN},
//{VK_RETURN, SoKeyboardEvent::ENTER},
  {VK_INSERT, SoKeyboardEvent::INSERT},
  {VK_DELETE, SoKeyboardEvent::KEY_DELETE},
  {VK_PAUSE, SoKeyboardEvent::PAUSE},
  {VK_SNAPSHOT, SoKeyboardEvent::PRINT},
  {VK_HOME, SoKeyboardEvent::HOME},
  {VK_END, SoKeyboardEvent::END},
  {VK_LEFT, SoKeyboardEvent::LEFT_ARROW},
  {VK_UP, SoKeyboardEvent::UP_ARROW},
  {VK_RIGHT, SoKeyboardEvent::RIGHT_ARROW},
  {VK_DOWN, SoKeyboardEvent::DOWN_ARROW},
//{VK_PRIOR, SoKeyboardEvent::PRIOR},
  {VK_PRIOR, SoKeyboardEvent::PAGE_UP},
//{VK_NEXT, SoKeyboardEvent::NEXT},
  {VK_NEXT, SoKeyboardEvent::PAGE_DOWN},
  {VK_SHIFT, SoKeyboardEvent::LEFT_SHIFT},
  {VK_CONTROL, SoKeyboardEvent::LEFT_CONTROL}, // ANY CTRL
  {VK_MENU, SoKeyboardEvent::LEFT_ALT}, // ANY ALT
  {VK_CAPITAL, SoKeyboardEvent::CAPS_LOCK},
  {VK_NUMLOCK, SoKeyboardEvent::NUM_LOCK},
  {VK_OEM_SCROLL, SoKeyboardEvent::SCROLL_LOCK},
  {VK_F1, SoKeyboardEvent::F1},
  {VK_F2, SoKeyboardEvent::F2},
  {VK_F3, SoKeyboardEvent::F3},
  {VK_F4, SoKeyboardEvent::F4},
  {VK_F5, SoKeyboardEvent::F5},
  {VK_F6, SoKeyboardEvent::F6},
  {VK_F7, SoKeyboardEvent::F7},
  {VK_F8, SoKeyboardEvent::F8},
  {VK_F9, SoKeyboardEvent::F9},
  {VK_F10, SoKeyboardEvent::F10},
  {VK_F11, SoKeyboardEvent::F11},
  {VK_F12, SoKeyboardEvent::F12},
  {VK_SPACE, SoKeyboardEvent::SPACE},
  {VK_OEM_COMMA, SoKeyboardEvent::COMMA},
  {VK_OEM_MINUS, SoKeyboardEvent::MINUS},
  {VK_OEM_PLUS, SoKeyboardEvent::EQUAL},
  {VK_OEM_PERIOD, SoKeyboardEvent::PERIOD},
  {VK_OEM_1, SoKeyboardEvent::SEMICOLON},
  {VK_OEM_2, SoKeyboardEvent::SLASH},
  {VK_OEM_3, SoKeyboardEvent::APOSTROPHE},
  {VK_OEM_4, SoKeyboardEvent::BRACKETLEFT},
  {VK_OEM_5, SoKeyboardEvent::BACKSLASH},
  {VK_OEM_6, SoKeyboardEvent::BRACKETRIGHT},
  {'0', SoKeyboardEvent::NUMBER_0},
  {'1', SoKeyboardEvent::NUMBER_1},
  {'2', SoKeyboardEvent::NUMBER_2},
  {'3', SoKeyboardEvent::NUMBER_3},
  {'4', SoKeyboardEvent::NUMBER_4},
  {'5', SoKeyboardEvent::NUMBER_5},
  {'6', SoKeyboardEvent::NUMBER_6},
  {'7', SoKeyboardEvent::NUMBER_7},
  {'8', SoKeyboardEvent::NUMBER_8},
  {'9', SoKeyboardEvent::NUMBER_9},
  {VK_SUBTRACT, SoKeyboardEvent::PAD_SUBTRACT},
  {VK_ADD, SoKeyboardEvent::PAD_ADD},
  {VK_DIVIDE, SoKeyboardEvent::PAD_DIVIDE},
  {VK_MULTIPLY, SoKeyboardEvent::PAD_MULTIPLY},
  {VK_NUMPAD0, SoKeyboardEvent::PAD_0},
  {VK_NUMPAD1, SoKeyboardEvent::PAD_1},
  {VK_NUMPAD2, SoKeyboardEvent::PAD_2},
  {VK_NUMPAD3, SoKeyboardEvent::PAD_3},
  {VK_NUMPAD4, SoKeyboardEvent::PAD_4},
  {VK_NUMPAD5, SoKeyboardEvent::PAD_5},
  {VK_NUMPAD6, SoKeyboardEvent::PAD_6},
  {VK_NUMPAD7, SoKeyboardEvent::PAD_7},
  {VK_NUMPAD8, SoKeyboardEvent::PAD_8},
  {VK_NUMPAD9, SoKeyboardEvent::PAD_9},
  {'A', SoKeyboardEvent::A},
  {'B', SoKeyboardEvent::B},
  {'C', SoKeyboardEvent::C},
  {'D', SoKeyboardEvent::D},
  {'E', SoKeyboardEvent::E},
  {'F', SoKeyboardEvent::F},
  {'G', SoKeyboardEvent::G},
  {'H', SoKeyboardEvent::H},
  {'I', SoKeyboardEvent::I},
  {'J', SoKeyboardEvent::J},
  {'K', SoKeyboardEvent::K},
  {'L', SoKeyboardEvent::L},
  {'M', SoKeyboardEvent::M},
  {'N', SoKeyboardEvent::N},
  {'O', SoKeyboardEvent::O},
  {'P', SoKeyboardEvent::P},
  {'Q', SoKeyboardEvent::Q},
  {'R', SoKeyboardEvent::R},
  {'S', SoKeyboardEvent::S},
  {'T', SoKeyboardEvent::T},
  {'U', SoKeyboardEvent::U},
  {'V', SoKeyboardEvent::V},
  {'W', SoKeyboardEvent::W},
  {'X', SoKeyboardEvent::X},
  {'Y', SoKeyboardEvent::Y},
  {'Z', SoKeyboardEvent::Z},
//{Key_Backtab, SoKeyboardEvent::}, // FIXME  
//{Key_F13, SoKeyboardEvent::}, // FIXME
//{Key_F14, SoKeyboardEvent::}, // FIXME
//{Key_F15, SoKeyboardEvent::}, // FIXME
//{Key_F16, SoKeyboardEvent::}, // FIXME
//{Key_F17, SoKeyboardEvent::}, // FIXME
//{Key_F18, SoKeyboardEvent::}, // FIXME
//{Key_F19, SoKeyboardEvent::}, // FIXME
//{Key_F20, SoKeyboardEvent::}, // FIXME
//{Key_F21, SoKeyboardEvent::}, // FIXME
//{Key_F22, SoKeyboardEvent::}, // FIXME
//{Key_F23, SoKeyboardEvent::}, // FIXME
//{Key_F24, SoKeyboardEvent::}, // FIXME
//{Key_F25, SoKeyboardEvent::}, // FIXME
//{Key_F26, SoKeyboardEvent::}, // FIXME
//{Key_F27, SoKeyboardEvent::}, // FIXME
//{Key_F28, SoKeyboardEvent::}, // FIXME
//{Key_F29, SoKeyboardEvent::}, // FIXME
//{Key_F30, SoKeyboardEvent::}, // FIXME
//{Key_F31, SoKeyboardEvent::}, // FIXME
//{Key_F32, SoKeyboardEvent::}, // FIXME
//{Key_F33, SoKeyboardEvent::}, // FIXME
//{Key_F34, SoKeyboardEvent::}, // FIXME
//{Key_F35, SoKeyboardEvent::}, // FIXME
//{Key_Super, SoKeyboardEvent::}, // FIXME
//{Key_Super, SoKeyboardEvent::}, // FIXME
//{Key_Menu, SoKeyboardEvent::}, // FIXME
//{Key_Exclam, SoKeyboardEvent::}, // FIXME
//{Key_QuoteDbl, SoKeyboardEvent::}, // FIXME
//{Key_NumberSign, SoKeyboardEvent::}, // FIXME
//{Key_Dollar, SoKeyboardEvent::}, // FIXME
//{Key_Percent, SoKeyboardEvent::}, // FIXME
//{Key_Ampersand, SoKeyboardEvent::}, // FIXME
//{Key_ParenLeft, SoKeyboardEvent::}, // FIXME
//{Key_ParenRight, SoKeyboardEvent::}, // FIXME
//{Key_Asterisk, SoKeyboardEvent::}, // FIXME
//{Key_Plus, SoKeyboardEvent::}, // FIXME
//{Key_Colon, SoKeyboardEvent::}, // FIXME
//{Key_Less, SoKeyboardEvent::}, // FIXME
//{Key_Greater, SoKeyboardEvent::}, // FIXME
//{Key_Question, SoKeyboardEvent::}, // FIXME
//{Key_At, SoKeyboardEvent::}, // FIXME  
//{Key_AsciiCircum, SoKeyboardEvent::}, // FIXME
//{Key_Underscore, SoKeyboardEvent::}, // FIXME
//{Key_QuoteLeft, SoKeyboardEvent::}, // FIXME
//{Key_BraceLeft, SoKeyboardEvent::}, // FIXME
//{Key_Bar, SoKeyboardEvent::}, // FIXME
//{Key_BraceRight, SoKeyboardEvent::}, // FIXME
//Key_AsciiTilde, SoKeyboardEvent::GRAVE}, // FIXME: is this correct?

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

  {VK_UNKNOWN, SoKeyboardEvent::ANY} // Ends table
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
  while ( WinToSoMapping[i].from != VK_UNKNOWN ) {
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
  FIXME: doc
*/

void
SoWinKeyboard::enable( HWND, // widget,
                       SoWinEventHandler * , // callbackproc,
                       void *, // data,
                       HWND ) // window )
{
  // Win32 has no way of enabling the keyboard. mariusbu 20010823.
  // Do nothing.
} // enable()

/*!
  FIXME: doc
*/

void
SoWinKeyboard::disable( HWND, // widget,
                        SoWinEventHandler * , // callbackproc,
                        void * ) // data )
{
  // Win32 has no way of disabling the keyboard. mariusbu 20010823.
  // Do nothing.
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

#if SOWIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoWinKeyboard::makeKeyboardEvent",
                         "MapVirtualKey(msg->wParam,0) == %d",
                         MapVirtualKey(msg->wParam, 0) );
#endif // debug

  //unsigned char repeat = ( unsigned char )( msg.lParam & 0x0f );
  void * sokey;
  if ( SoWinKeyboard::translatetable->find( msg->wParam, sokey ) ) {
    SoWinKeyboard::keyboardEvent->setKey( ( SoKeyboardEvent::Key )( int )sokey );
  }
  else {
    SoWinKeyboard::keyboardEvent->setKey( SoKeyboardEvent::ANY );
    return NULL;
  }

  // modifiers:
  if ( ( int )sokey == SoKeyboardEvent::LEFT_SHIFT ) {
    if ( state == SoButtonEvent::UP ) {
      SoWinDevice::modifierKeys &= ~MK_SHIFT;
      //return NULL;
    }
    else {    // SoButtonEvent::DOWN
      if ( SoWinDevice::modifierKeys & MK_SHIFT ) return NULL;
      SoWinDevice::modifierKeys |= MK_SHIFT;
    }
  }

  if ( ( int )sokey == SoKeyboardEvent::LEFT_CONTROL ) {
    if ( state == SoButtonEvent::UP ) {
      SoWinDevice::modifierKeys &= ~MK_CONTROL;
      //return NULL;
    }
    else {    // SoButtonEvent::DOWN
      if ( SoWinDevice::modifierKeys & MK_CONTROL ) return NULL;
      SoWinDevice::modifierKeys |= MK_CONTROL;
    }
  }

  if ( ( int )sokey == SoKeyboardEvent::LEFT_ALT ) {
    if ( state == SoButtonEvent::UP ) {
      SoWinDevice::modifierKeys &= ~MK_ALT;
      //return NULL;
    }
    else {    // SoButtonEvent::DOWN
      if ( SoWinDevice::modifierKeys & MK_ALT ) return NULL;
      SoWinDevice::modifierKeys |= MK_ALT;
    }
  }

  SoWinKeyboard::keyboardEvent->setShiftDown( ( SoWinDevice::modifierKeys & MK_SHIFT ) ? TRUE : FALSE );
  SoWinKeyboard::keyboardEvent->setCtrlDown( ( SoWinDevice::modifierKeys & MK_CONTROL ) ? TRUE : FALSE );
  SoWinKeyboard::keyboardEvent->setAltDown( ( SoWinDevice::modifierKeys & MK_ALT ) ? TRUE : FALSE );
  
  long msec =  GetTickCount( );
  SoWinKeyboard::keyboardEvent->setTime( SbTime( ( msec / 1000 ), ( msec % 1000 ) * 1000 ) );

  return SoWinKeyboard::keyboardEvent;
} // makeKeyboardEvent()

// *************************************************************************
