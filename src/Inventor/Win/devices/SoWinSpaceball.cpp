/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and / or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use this library in software that is incompatible
 *  with the GNU GPL, and / or you would like to take advantage of the
 *  additional benefits with regard to our support services, please
 *  contact Systems in Motion about acquiring a Coin Professional
 *  Edition License.  See <URL:http://www.coin3d.org> for more
 *  information.
 *
 *  Systems in Motion, Abels gate 5, Teknobyen, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

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
