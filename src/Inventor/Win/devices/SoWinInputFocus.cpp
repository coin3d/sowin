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
