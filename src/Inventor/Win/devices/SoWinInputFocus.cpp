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

/*!
  \class SoWinInputFocus SoWinInputFocus.h Inventor/Win/devices/SoWinInputFocus.h
  \brief The SoWinInputFocus class ...
  \ingroup qtdevices

  FIXME: write class doc
*/

#include <sowindefs.h>
#include <Inventor/Win/devices/SoWinInputFocus.h>

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
SoWinInputFocus::enable(
    HWND, // widget,
    SoWinEventHandler *, // handler,
    void * ) // closure )
{
    SOWIN_STUB();
} // enable()

/*!
  FIXME: write function documentation
*/

void
SoWinInputFocus::disable(
    HWND, // widget,
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
SoWinInputFocus::translateEvent(
    MSG * ) // event )
{
    SOWIN_STUB();
    return NULL;
} // translateEvent()

// *************************************************************************

