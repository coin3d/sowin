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

// *************************************************************************

// Class is documented in common/viewers/SoGuiPlaneViewer.cpp.in.

// *************************************************************************

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>

#include <sowindefs.h>
#include <Inventor/Win/widgets/SoWinThumbWheel.h>
#include <Inventor/Win/widgets/SoWinBitmapButton.h>

#include <Inventor/Win/viewers/SoWinPlaneViewer.h>
#include <Inventor/Win/viewers/SoWinPlaneViewerP.h>

#include <Inventor/Win/common/pixmaps/ortho.xpm>
#include <Inventor/Win/common/pixmaps/perspective.xpm>
#include <Inventor/Win/common/pixmaps/x.xpm>
#include <Inventor/Win/common/pixmaps/y.xpm>
#include <Inventor/Win/common/pixmaps/z.xpm>

// ************************************************************************

// SoQtPlaneViewerP "private implementation" class.

#ifndef DOXYGEN_SKIP_THIS

#define PUBLIC(ptr) (ptr->pub)
#define PRIVATE(ptr) (ptr->pimpl)

SoWinPlaneViewerP::SoWinPlaneViewerP(SoWinPlaneViewer * publ)
  : SoGuiPlaneViewerP(publ)
{
}

SoWinPlaneViewerP::~SoWinPlaneViewerP()
{
}

// This contains the real constructor code (the two constructors are only
// entry points for this method).
void
SoWinPlaneViewerP::constructor(SbBool build)
{
  this->commonConstructor(); // init generic stuff

  PUBLIC(this)->setClassName("SoWinPlaneViewer");
  
  if (! build) return;

  HWND viewer = PUBLIC(this)->buildWidget(PUBLIC(this)->getParentWidget());
  PUBLIC(this)->setBaseWidget(viewer);
  
  PUBLIC(this)->setLeftWheelString("TransY");
  PUBLIC(this)->setBottomWheelString("TransX");  

  PUBLIC(this)->setSize(SbVec2s(555, 515));
}

void
SoWinPlaneViewerP::xClicked(void)
{
  this->viewPlaneX();
}

void
SoWinPlaneViewerP::yClicked(void)
{
  this->viewPlaneY();
}

void
SoWinPlaneViewerP::zClicked(void)
{
  this->viewPlaneZ();
}

void
SoWinPlaneViewerP::cameratoggleClicked(void)
{
  PUBLIC(this)->toggleCameraType();
}

#endif // DOXYGEN_SKIP_THIS

// ************************************************************************

// FIXME: this has got to be guaranteed unique versus the FullViewer
// button ids. This is just a quick hack. 20020719 mortene.
#define VIEWERBUTTON_STARTID 4242
#define VIEWERBUTTON_X (0+VIEWERBUTTON_STARTID)
#define VIEWERBUTTON_Y (1+VIEWERBUTTON_STARTID)
#define VIEWERBUTTON_Z (2+VIEWERBUTTON_STARTID)
#define VIEWERBUTTON_CAMERA (3+VIEWERBUTTON_STARTID)

// ************************************************************************

// Documented in superclass.
void
SoWinPlaneViewer::setCamera(SoCamera * camera)
{
  if (camera) {
    SoType type = camera->getTypeId();
    SbBool orthogonal =
      type.isDerivedFrom(SoOrthographicCamera::getClassTypeId());
    this->setRightWheelString(orthogonal ? "Zoom" : "Dolly");
    
    if (this->isDoButtonBar()) // may not be there if !doButtonBar
      ((SoWinBitmapButton *)PRIVATE(this)->camerabutton)->setBitmap(orthogonal ? 1 : 0);
  }
  inherited::setCamera(camera);
}

// ************************************************************************

// Documented in superclass.
HWND
SoWinPlaneViewer::buildWidget(HWND parent)
{
  return inherited::buildWidget(parent);
}

// ************************************************************************

/*!
  This method overloaded from parent class to handle button messages
  from viewer specific buttons (x, y, z and camera toggle).
*/

LRESULT
SoWinPlaneViewer::onCommand(HWND window,
                            UINT message,
                            WPARAM wparam,
                            LPARAM lparam)
{
 short nc = HIWORD(wparam);// notification code
 short id = LOWORD(wparam);// item, control, or accelerator identifier
 HWND hwnd = (HWND) lparam;// control handle

 switch (id) {

 case VIEWERBUTTON_CAMERA:
   PRIVATE(this)->cameratoggleClicked();
   return 0;
   
 case VIEWERBUTTON_X:
   PRIVATE(this)->xClicked();
   return 0;

 case VIEWERBUTTON_Y:
   PRIVATE(this)->yClicked();
   return 0;

 case VIEWERBUTTON_Z:
   PRIVATE(this)->zClicked();
   return 0;

 default:
   return inherited::onCommand(window, message, wparam, lparam);
 }

  return 0;
}

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::buildViewerButtonsEx(HWND parent,
                                       int x,
                                       int y,
                                       int size)
{
  SoWinBitmapButton * button;

  button = new SoWinBitmapButton(parent, x, y, size, size, 24, "x", NULL);
  button->addBitmap(x_xpm);
  button->setBitmap(0);
  button->setId(VIEWERBUTTON_X);
  this->viewerButtonList->append(button);
  
  button = new SoWinBitmapButton(parent, x, y, size, size, 24, "y", NULL);
  button->addBitmap(y_xpm);
  button->setBitmap(0);
  button->setId(VIEWERBUTTON_Y);
  this->viewerButtonList->append(button);

  button = new SoWinBitmapButton(parent, x, y, size, size, 24, "z", NULL);
  button->addBitmap(z_xpm);
  button->setBitmap(0);
  button->setId(VIEWERBUTTON_Z);
  this->viewerButtonList->append(button);
  
  button = new SoWinBitmapButton(parent, x, y, size, size, 24, "camera", NULL);
  button->addBitmap(perspective_xpm);
  button->addBitmap(ortho_xpm);
  button->setBitmap(0);
  button->setId(VIEWERBUTTON_CAMERA);
  this->viewerButtonList->append(button);
  PRIVATE(this)->camerabutton = button;
}

// ************************************************************************

// FIXME: these are present in the other So* toolkits, but was missing
// in SoWin. Why? 20020111 mortene.

void
SoWinPlaneViewer::createViewerButtons(HWND parent, SbPList * buttonlist)
{
  // FIXME: not activated in SoWinFullViewer yet. 20020111 mortene.
//    inherited::createViewerButtons(parent, buttonlist);
}
