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
#include <Inventor/Win/devices/SoWinDevice.h>
#include <Inventor/Win/devices/SoWinDeviceP.h>

// *************************************************************************

long SoWinDeviceP::modifierKeys = 0;

// *************************************************************************

SoWinDevice::SoWinDevice(void)
{
  PRIVATE(this) = new SoWinDeviceP(this);
}

SoWinDevice::~SoWinDevice()
{
  delete PRIVATE(this);
}

void
SoWinDevice::invokeHandlers(MSG * event)
{
  // FIXME: implementation missing for SoWin (but present on other So*
  // toolkits (?)). 20020624 mortene.
  SOWIN_STUB();
}

// *************************************************************************
