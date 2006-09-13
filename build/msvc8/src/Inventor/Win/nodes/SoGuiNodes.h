#ifndef COIN_SOGUINODES_H
#define COIN_SOGUINODES_H

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

#include <Inventor/Win/nodes/SoGuiSceneTexture2.h>
#include <Inventor/Win/nodes/SoGuiViewportFix.h>
#include <Inventor/Win/nodes/SoGuiPane.h>
#include <Inventor/Win/nodes/SoGuiPosition.h>
#include <Inventor/Win/nodes/SoGuiTranslation.h>
#include <Inventor/Win/nodes/SoGuiFrame.h>
#include <Inventor/Win/nodes/SoGuiImage.h>
#include <Inventor/Win/nodes/SoGuiLabel.h>
#include <Inventor/Win/nodes/SoGuiToggleButton.h>
#include <Inventor/Win/nodes/SoGuiRadioButton.h>
#include <Inventor/Win/nodes/SoGuiClickCounter.h>
#include <Inventor/Win/nodes/SoGuiSlider1.h>
#include <Inventor/Win/nodes/SoGuiSlider2.h>
#include <Inventor/Win/nodes/SoGuiColorEditor.h>
#include <Inventor/Win/nodes/SoGuiMaterialEditor.h>
#include <Inventor/Win/nodes/SoGuiViewpointWrapper.h>

class SoGuiNodes {
public:
  static void initClasses(void);

};

#endif // !COIN_SOGUINODES_H
