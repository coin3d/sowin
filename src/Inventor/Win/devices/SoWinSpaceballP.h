#ifndef SOWIN_SPACEBALLP_H
#define SOWIN_SPACEBALLP_H

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

#ifndef SOWIN_INTERNAL
#error this is a private header file
#endif /* !SOWIN_INTERNAL */

// *************************************************************************

#include <Inventor/Win/devices/SoGuiSpaceballP.h>

// *************************************************************************

class SoWinSpaceballP : public SoGuiSpaceballP {

public:
  SoWinSpaceballP(SoWinSpaceball * p);
  virtual ~SoWinSpaceballP();

  void * Spw_DeviceHandle;

  SbRotation makeRotation(const float rx, const float ry, const float rz) const;
  SbVec3f makeTranslation(const float tx, const float ty, const float tz) const;

  class SoMotion3Event * motion3Event;
  class SoSpaceballButtonEvent * buttonEvent;
};

// *************************************************************************

#endif // !SOWIN_SPACEBALLP_H
