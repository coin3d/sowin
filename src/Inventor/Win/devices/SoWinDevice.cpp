/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
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
