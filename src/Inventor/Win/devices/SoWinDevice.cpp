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
#include <Inventor/Win/devices/SoWinDevice.h>
#include <Inventor/Win/devices/SoWinDeviceP.h>

#define PRIVATE(obj) ((obj)->pimpl)

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

long SoWinDeviceP::modifierKeys = 0;

#endif // !DOXYGEN_SKIP_THIS

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

#undef PRIVATE
