/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 as published by the Free Software Foundation.  See the file
 *  LICENSE.LGPL at the root directory of the distribution for all the
 *  details.
 *
 *  If you want to use Coin SoWin for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

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

// ************************************************************************

#define VIEWERBUTTON_X (VIEWERBUTTON_SEEK + 1)
#define VIEWERBUTTON_Y (VIEWERBUTTON_SEEK + 2)
#define VIEWERBUTTON_Z (VIEWERBUTTON_SEEK + 3)
#define VIEWERBUTTON_CAMERA (VIEWERBUTTON_SEEK + 4)

// Documented in common/viewers/SoGuiPlaneViewer.cpp.in.
SoWinPlaneViewer::SoWinPlaneViewer(HWND parent,
                                   const char * const name, 
                                   SbBool embed,
                                   SoWinFullViewer::BuildFlag flag, 
                                   SoWinViewer::Type type)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoWinPlaneViewerP(this);
  PRIVATE(this)->constructor(TRUE);
}

// Documented in common/viewers/SoGuiPlaneViewer.cpp.in.
SoWinPlaneViewer::SoWinPlaneViewer(HWND parent,
                                   const char * const name, 
                                   SbBool embed, 
                                   SoWinFullViewer::BuildFlag flag, 
                                   SoWinViewer::Type type, 
                                   SbBool build)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoWinPlaneViewerP(this);
  PRIVATE(this)->constructor(build);
}

// Documented in common/viewers/SoGuiPlaneViewer.cpp.in.
SoWinPlaneViewer::~SoWinPlaneViewer()
{
  delete PRIVATE(this);
}

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::setCamera(// virtual
  SoCamera * camera)
{
  if (camera) {
    SoType type = camera->getTypeId();
    SbBool orthogonal =
      type.isDerivedFrom(SoOrthographicCamera::getClassTypeId());
    this->setRightWheelString(orthogonal ? "Zoom" : "Dolly");
    
    if (this->isDoButtonBar()) // may not be there if !doButtonBar
      ((SoWinBitmapButton *) (* this->viewerButtonList) [VIEWERBUTTON_CAMERA])->setBitmap(
        orthogonal ? 1 : 0);
  
  }
  inherited::setCamera(camera);
} // setCamera()

// ************************************************************************

/*!
  FIXME: write doc
*/

HWND
SoWinPlaneViewer::buildWidget(
  HWND parent)
{
  HWND widget = inherited::buildWidget(parent);
  ((SoWinThumbWheel *)this->leftWheel)->setRangeBoundaryHandling(SoWinThumbWheel::ACCUMULATE);
  ((SoWinThumbWheel *)this->bottomWheel)->setRangeBoundaryHandling(SoWinThumbWheel::ACCUMULATE);
  return widget;
} // buildWidget()

// ************************************************************************

/*!
  This method overloaded from parent class to handle button messages
  from viewer specific buttons (x, y, z and camera toggle).
*/

LRESULT
SoWinPlaneViewer::onCommand(// virtual
  HWND window,
  UINT message,
  WPARAM wparam,
  LPARAM lparam)
{
 int i;
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
} // onCommand()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::createPrefSheet(void)
{
  inherited::createPrefSheet();
}

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::buildViewerButtonsEx(// virtual
  HWND parent,
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
    
}

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::openViewerHelpCard(// virtual
  void)
{
  this->openHelpCard("SoWinPlaneViewer.help");
} // openViewerHelpCard()

// ************************************************************************

// FIXME: these are present in the other So* toolkits, but was missing
// in SoWin. Why? 20020111 mortene.

void
SoWinPlaneViewer::createViewerButtons(HWND parent, SbPList * buttonlist)
{
  // FIXME: not activated in SoWinFullViewer yet. 20020111 mortene.
//    inherited::createViewerButtons(parent, buttonlist);
}

void
SoWinPlaneViewer::processEvent(MSG * event)
{
  inherited::processEvent(event);
}
