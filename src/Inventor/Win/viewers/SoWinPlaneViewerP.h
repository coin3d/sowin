#ifndef SOWINPLANEVIEWERP_H
#define SOWINPLANEVIEWERP_H

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

#include <Inventor/Win/viewers/SoGuiPlaneViewerP.h>

class SoWinPlaneViewer;

// ************************************************************************

// This class contains private data and methods used within the
// SoWinPlaneViewer class.

class SoWinPlaneViewerP : public SoGuiPlaneViewerP
{
public:
  SoWinPlaneViewerP(SoWinPlaneViewer * publ);
  ~SoWinPlaneViewerP();

  void constructor(SbBool build);
 
  static void xButtonProc(class SoWinBitmapButton * b, void * userdata);
  static void yButtonProc(class SoWinBitmapButton * b, void * userdata);
  static void zButtonProc(class SoWinBitmapButton * b, void * userdata);
  static void cameraButtonProc(class SoWinBitmapButton * b, void * userdata);

  class SoWinBitmapButton * camerabutton;
};

// ************************************************************************

#endif // ! SOWINPLANEVIEWERP_H
