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

#include <assert.h>

#if SOWIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOWIN_DEBUG

#include <Inventor/misc/SoBasic.h>
#include <Inventor/events/SoEvent.h>

#include <sowindefs.h>
#include <Inventor/Win/devices/SoWinDevice.h>
#include <Inventor/Win/devices/SoWinInputFocus.h>
#include <Inventor/Win/devices/SoWinKeyboard.h>
#include <Inventor/Win/devices/SoWinMouse.h>
#include <Inventor/Win/devices/SoWinSpaceball.h>

long SoWinDevice::modifierKeys = 0;

// *************************************************************************

SOWIN_OBJECT_ABSTRACT_SOURCE(SoWinDevice);

void
SoWinDevice::initClasses(void)
{
  SoWinDevice::initClass();
  SoWinInputFocus::initClass();
  SoWinKeyboard::initClass();
  SoWinMouse::initClass();
  SoWinSpaceball::initClass();
} // initClasses()

// *************************************************************************

SoWinDevice::SoWinDevice(void)
  : size(0, 0)
{
}

SoWinDevice::~SoWinDevice(void)
{

}

void
SoWinDevice::setWindowSize(const SbVec2s newSize)
{
  size = newSize;
}

const SbVec2s 
SoWinDevice::getWindowSize(void) const
{
  return this->size;
}

void
SoWinDevice::setEventPosition(SoEvent *event, int x, int y) const
{
  assert(event != NULL);
  SbVec2s position(x, this->size[1] - y - 1);
  event->setPosition(position);
}

// *************************************************************************
