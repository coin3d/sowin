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
#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>

#include <sowindefs.h>
#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinSpaceball.h>
#include <Inventor/Win/devices/SoWinSpaceballP.h>

extern "C" {
#include <Inventor/Win/devices/spwinput_win32.h>
}

// *************************************************************************

SoWinSpaceballP::SoWinSpaceballP(SoWinSpaceball * p)
  : SoGuiSpaceballP(p)
{
  this->rotationscale = .001f;
  this->translationscale = .001f;
  this->motion3Event = new SoMotion3Event;
  this->buttonEvent = new SoSpaceballButtonEvent;
  this->Spw_DeviceHandle = SI_NO_HANDLE;
  SiInitialize();
}

SoWinSpaceballP::~SoWinSpaceballP()
{
  delete this->motion3Event;
  delete this->buttonEvent;
  SiClose(this->Spw_DeviceHandle);
  SiTerminate();
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
  SiOpenData oData;
  SiOpenWinInit(&oData, hwnd);
  PRIVATE(this)->Spw_DeviceHandle = SiOpen("", SI_ANY_DEVICE, SI_NO_MASK, SI_EVENT, &oData);
  if (PRIVATE(this)->Spw_DeviceHandle != SI_NO_HANDLE) {
  }
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
  SiGetEventData eventdata;
  SiSpwEvent spwEvent;

  if (PRIVATE(this)->Spw_DeviceHandle != SI_NO_HANDLE) {
     SiGetEventWinInit (&eventdata, msg->message, msg->wParam, msg->lParam);
     if (SiGetEvent (PRIVATE(this)->Spw_DeviceHandle, 0, &eventdata, &spwEvent) == SI_IS_EVENT) {
        if (spwEvent.type == SI_MOTION_EVENT) {           
           long * data = spwEvent.u.spwData.mData;
           
           PRIVATE(this)->motion3Event->setTranslation(
             PRIVATE(this)->makeTranslation((float)data[SI_TX],(float)data[SI_TY],(float)data[SI_TZ]));

           PRIVATE(this)->motion3Event->setRotation(
             PRIVATE(this)->makeRotation((float)data[SI_RX],(float)data[SI_RY],(float)data[SI_RZ]));

           return (SoEvent *) NULL;//PRIVATE(this)->motion3Event;
        }
        else if (spwEvent.type == SI_BUTTON_EVENT) {
          return (SoEvent *) NULL;
        }
     } 
  }
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
