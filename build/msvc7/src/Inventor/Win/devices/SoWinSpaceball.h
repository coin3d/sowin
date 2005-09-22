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

#ifndef SOWIN_SPACEBALL_H
#define SOWIN_SPACEBALL_H

#include <Inventor/Win/devices/SoWinDevice.h>
#include <Inventor/SbLinear.h>

// *************************************************************************

class SOWIN_DLL_API SoWinSpaceball : public SoWinDevice {
  SOWIN_OBJECT_HEADER(SoWinSpaceball, SoWinDevice);

public:
  enum Mask {
    MOTION_EVENT  = 0x01,  MOTION = MOTION_EVENT,
    PRESS_EVENT   = 0x02,  PRESS = PRESS_EVENT,
    RELEASE_EVENT = 0x04,  RELEASE = RELEASE_EVENT,
    ALL_EVENTS = MOTION_EVENT | PRESS_EVENT | RELEASE_EVENT,
    ALL = ALL_EVENTS
  };

  enum DeviceType {
    SPACE_BALL             = 0x01,
    MAGELLAN_SPACE_MOUSE   = 0x02
  };

  SoWinSpaceball(int events = ALL_EVENTS);
  virtual ~SoWinSpaceball();

  virtual void enable(HWND widget, SoWinEventHandler * handler, void * closure);
  virtual void disable(HWND widget, SoWinEventHandler * handler, void * closure);

  virtual const SoEvent * translateEvent(MSG * event);

  void setRotationScaleFactor(float f);
  float getRotationScaleFactor(void) const;
  void setTranslationScaleFactor(float f);
  float getTranslationScaleFactor(void) const;

  static SbBool exists(void);

  void setFocusToWindow(SbBool flag);
  SbBool isFocusToWindow(void) const;

private:
  class SoWinSpaceballP * pimpl;
};

// *************************************************************************

#endif // ! SOWIN_SPACEBALL_H
