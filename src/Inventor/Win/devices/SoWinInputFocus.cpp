/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#include <sowindefs.h>
#include <Inventor/Win/devices/SoWinInputFocus.h>
#include <Inventor/Win/devices/SoGuiInputFocusP.h>

#define PRIVATE(obj) ((obj)->pimpl)

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

#undef PRIVATE
