#ifndef SOWIN_SPACEBALLP_H
#define SOWIN_SPACEBALLP_H

/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
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
  SoWinSpaceballP(SoWinSpaceball * p) : SoGuiSpaceballP(p) { }
  virtual ~SoWinSpaceballP() { }

  class SoMotion3Event * motionEvent;
  class SoSpaceballButtonEvent * buttonEvent;
};

// *************************************************************************

#endif // !SOWIN_SPACEBALLP_H
