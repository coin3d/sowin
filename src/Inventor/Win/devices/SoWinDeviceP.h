#ifndef SOWIN_DEVICEP_H
#define SOWIN_DEVICEP_H

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
