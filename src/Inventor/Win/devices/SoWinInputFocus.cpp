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

#include <sowindefs.h>
#include <Inventor/Win/devices/SoWinInputFocus.h>
#include <Inventor/Win/devices/SoGuiInputFocusP.h>

// *************************************************************************

class SoWinInputFocusP : public SoGuiInputFocusP {
public:
  SoWinInputFocusP(SoWinInputFocus * p) : SoGuiInputFocusP(p) { }
};

// *************************************************************************

SoWinInputFocus::SoWinInputFocus(int mask)
{
  PRIVATE(this) = new SoWinInputFocusP(this);
  PRIVATE(this)->eventmask = mask;
}

SoWinInputFocus::~SoWinInputFocus()
{
  delete PRIVATE(this);
}

// *************************************************************************

void
SoWinInputFocus::enable(HWND, // widget,
                        SoWinEventHandler *, // handler,
                        void *)
{
  SOWIN_STUB();
}

void
SoWinInputFocus::disable(HWND, // widget,
                         SoWinEventHandler *, // handler,
                         void *) // closure)
{
  SOWIN_STUB();
}

// *************************************************************************

const SoEvent *
SoWinInputFocus::translateEvent(MSG *) // event)
{
  /*
  long msec =  GetTickCount();
  if (soevent) soevent->setTime(SbTime((msec / 1000), (msec % 1000) * 1000)));
  */
  SOWIN_STUB();
  return NULL;
}

// *************************************************************************
