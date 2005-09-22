#ifndef SOWIN_DEVICEP_H
#define SOWIN_DEVICEP_H

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

#ifndef SOWIN_INTERNAL
#error this is a private header file
#endif /* !SOWIN_INTERNAL */

// FIXME: ugly hack done by mariusbu to share this define between
// SoWinMouse and SoWinKeyboard. Should instead find out how we could
// properly handle modifiers. 20020624 mortene.
#ifndef MK_ALT
#define MK_ALT 0x02
#endif

#include <Inventor/Win/devices/SoGuiDeviceP.h>

class SoWinDeviceP : public SoGuiDeviceP {
public:
  SoWinDeviceP(SoWinDevice * p) : SoGuiDeviceP(p) { }
  virtual ~SoWinDeviceP() { }

  // FIXME: ugly hack done by mariusbu to share this define between
  // SoWinMouse and SoWinKeyboard. Should instead find out how we
  // could properly handle modifiers. 20020624 mortene.
  static long modifierKeys;
};

#endif // !SOWIN_DEVICEP_H
