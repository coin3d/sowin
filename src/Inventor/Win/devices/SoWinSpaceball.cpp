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
#include <Inventor/events/SoSpaceballButtonEvent.h>

#include <sowindefs.h>
#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinSpaceball.h>
#include <Inventor/Win/devices/SoWinSpaceballP.h>

// *************************************************************************

SoWinSpaceball::SoWinSpaceball(int mask)
{
  PRIVATE(this) = new SoWinSpaceballP(this);
  SOWIN_STUB();
}

SoWinSpaceball::~SoWinSpaceball(void)
{
  SOWIN_STUB();
  delete PRIVATE(this);
}
    
void
SoWinSpaceball::enable(HWND, SoWinEventHandler * , void *)
{
  SOWIN_STUB();
}

void
SoWinSpaceball::disable(HWND, SoWinEventHandler * , void *)
{
  SOWIN_STUB();
}

const SoEvent *
SoWinSpaceball::translateEvent(MSG * msg)
{
  /*
  long msec =  GetTickCount();
  if (soevent) soevent->setTime(SbTime((msec / 1000), (msec % 1000) * 1000)));
  */
  // FIXME: function not implemented
  SOWIN_STUB();
  
  return (SoEvent *) NULL;
}

SbBool
SoWinSpaceball::exists(void)
{
  return FALSE;
}
 
void
SoWinSpaceball::setFocusToWindow(SbBool flag)
{
  SOWIN_STUB();
}

SbBool
SoWinSpaceball::isFocusToWindow(void) const
{
  SOWIN_STUB();
  return FALSE;
}
