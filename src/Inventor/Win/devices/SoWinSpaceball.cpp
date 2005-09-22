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

#include <windows.h>

#if SOWIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOWIN_DEBUG

#include <Inventor/misc/SoBasic.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>

#include <sowindefs.h>
#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinSpaceball.h>
#include <Inventor/Win/devices/SoWinSpaceballP.h>

#include <Inventor/Win/devices/spwinput_win32.h>

#define PRIVATE(obj) ((obj)->pimpl)

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

SoWinSpaceballP::SoWinSpaceballP(SoWinSpaceball * p)
  : SoGuiSpaceballP(p)
{
  this->rotationscale = .001f;
  this->translationscale = .001f;
  this->motion3Event = new SoMotion3Event;
  this->buttonEvent = new SoSpaceballButtonEvent;
}

SoWinSpaceballP::~SoWinSpaceballP()
{
  delete this->motion3Event;
  delete this->buttonEvent;
}

SbRotation
SoWinSpaceballP::makeRotation(const float rx, const float ry, const float rz) const
{
  SbRotation xrot(SbVec3f(1, 0, 0), rx * this->rotationscale);
  SbRotation yrot(SbVec3f(0, 1, 0), ry * this->rotationscale);
  SbRotation zrot(SbVec3f(0, 0,-1), rz * this->rotationscale);
  return xrot * yrot * zrot;
}

SbVec3f
SoWinSpaceballP::makeTranslation(const float tx, const float ty, const float tz) const
{
  return SbVec3f(tx * this->translationscale,
                 ty * this->translationscale,
               - tz * this->translationscale);
}

#endif // !DOXYGEN_SKIP_THIS

// *************************************************************************

SoWinSpaceball::SoWinSpaceball(int mask)
{
  PRIVATE(this) = new SoWinSpaceballP(this);
}

SoWinSpaceball::~SoWinSpaceball(void)
{
  delete PRIVATE(this);
}

void
SoWinSpaceball::enable(HWND hwnd, SoWinEventHandler * , void *)
{
  if (SPW_CheckForSpaceballWin32(hwnd) == TRUE) {
    
  }
}

void
SoWinSpaceball::disable(HWND, SoWinEventHandler * , void *)
{
  SPW_disableSpaceBallWin32();
}

const SoEvent *
SoWinSpaceball::translateEvent(MSG * msg)
{
  SPW_InputEvent sbEvent;
  if (SPW_TranslateEventWin32(msg, &sbEvent) == TRUE) {
  
    switch (sbEvent.type) {
    case SPW_InputMotionEvent:
      PRIVATE(this)->motion3Event->setTranslation(PRIVATE(this)->makeTranslation(sbEvent.sData[0],
                                                                                 sbEvent.sData[1],
                                                                                 sbEvent.sData[2]));
      PRIVATE(this)->motion3Event->setRotation(PRIVATE(this)->makeRotation(sbEvent.sData[3],
                                                                           sbEvent.sData[4],
                                                                           sbEvent.sData[5]));
      
      return PRIVATE(this)->motion3Event;
    case SPW_InputButtonPressEvent:
      return (SoEvent*) NULL;
    case SPW_InputButtonReleaseEvent:
      return (SoEvent*) NULL;
    default:
      return (SoEvent*) NULL;
    }
  }
  return (SoEvent *) NULL;
}

SbBool
SoWinSpaceball::exists(void)
{
  return SPW_SpaceBallExistsWin32();
}

void
SoWinSpaceball::setFocusToWindow(SbBool flag)
{
  // FIXME: should be implemented..? 20030812 mortene.
  SOWIN_STUB();
}

SbBool
SoWinSpaceball::isFocusToWindow(void) const
{
  // FIXME: should be implemented..? 20030812 mortene.
  SOWIN_STUB();
  return FALSE;
}

#undef PRIVATE
