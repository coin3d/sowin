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
  \class SoWinInputFocus SoWinInputFocus.h Inventor/Win/devices/SoWinInputFocus.h
  \brief The SoWinInputFocus class ...
  \ingroup qtdevices

  FIXME: write class doc
*/

#include <sowindefs.h>
#include <Inventor/Win/devices/SoWinInputFocus.h>

// *************************************************************************

SOWIN_OBJECT_SOURCE(SoWinInputFocus);

// *************************************************************************

/*!
  Constructor.
*/

SoWinInputFocus::SoWinInputFocus( UINT mask )
{
  this->mask = mask;
} // SoWinInputFocus()

/*!
  Destructor.
*/

SoWinInputFocus::~SoWinInputFocus( void )
{
} // ~SoWinInputFocus()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoWinInputFocus::enable( HWND, // widget,
                         SoWinEventHandler *, // handler,
                         void * , // closure
                         HWND ) // window
{
  SOWIN_STUB();
} // enable()

/*!
  FIXME: write function documentation
*/

void
SoWinInputFocus::disable( HWND, // widget,
                          SoWinEventHandler *, // handler,
                          void * ) // closure )
{
  SOWIN_STUB();
} // disable()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

const SoEvent *
SoWinInputFocus::translateEvent( MSG * ) // event )
{
  /*
  long msec =  GetTickCount( );
  if ( soevent ) soevent->setTime( SbTime( ( msec / 1000 ), ( msec % 1000 ) * 1000 ) ) );
  */
  SOWIN_STUB();
  return NULL;
} // translateEvent()

// *************************************************************************
