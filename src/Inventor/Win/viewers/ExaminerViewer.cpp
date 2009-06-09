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

// Class documentation in common/viewers/SoGuiExaminerViewer.cpp.in.

// *************************************************************************

#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoWinCursor.h>
#include <Inventor/Win/common/pixmaps/ortho.xpm>
#include <Inventor/Win/common/pixmaps/perspective.xpm>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/Win/viewers/SoWinExaminerViewerP.h>
#include <Inventor/Win/widgets/SoWinBitmapButton.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <sowindefs.h>

#define PRIVATE(obj) ((obj)->pimpl)
#define PUBLIC(obj) ((obj)->pub)

// *************************************************************************

// The private data for the SoWinExaminerViewer.

#ifndef DOXYGEN_SKIP_THIS

SoWinExaminerViewerP::SoWinExaminerViewerP(SoWinExaminerViewer * o)
  : SoGuiExaminerViewerP(o)
{
  this->camerabutton = NULL;
}

SoWinExaminerViewerP::~SoWinExaminerViewerP()
{
}

// This contains the real constructor code (the two constructors are
// only entry points for this method).
void
SoWinExaminerViewerP::constructor(SbBool build)
{
  this->genericConstructor();

  PUBLIC(this)->setClassName("SoWinExaminerViewer");
  PUBLIC(this)->setPopupMenuString("Examiner Viewer");

  if (! build) return;

  HWND widget = PUBLIC(this)->buildWidget(PUBLIC(this)->getParentWidget());
  PUBLIC(this)->setBaseWidget(widget);

  PUBLIC(this)->setLeftWheelString("RotX");
  PUBLIC(this)->setBottomWheelString("RotY");

  PUBLIC(this)->setCursorEnabled(TRUE);
  PUBLIC(this)->setAnimationEnabled(TRUE);

  PUBLIC(this)->setSize(SbVec2s(500, 421));
  // FIXME: If the new size is the same as the old size, Windows will
  // never size the widget, and layoutWidgets() will never be
  // called. mariusbu 20010823.

}

void
SoWinExaminerViewerP::cameraButtonProc(SoWinBitmapButton * b, void * userdata)
{
  SoWinExaminerViewer * that = (SoWinExaminerViewer *)userdata;
  if (that->getCamera()) that->toggleCameraType();
}

#endif // DOXYGEN_SKIP_THIS

// *************************************************************************

SOWIN_OBJECT_SOURCE(SoWinExaminerViewer);

// *************************************************************************

// Documented in common/viewers/SoGuiExaminerViewer.cpp.in.
SoWinExaminerViewer::SoWinExaminerViewer(HWND parent,
                                         const char * name,
                                         SbBool embed,
                                         SoWinFullViewer::BuildFlag flag,
                                         SoWinViewer::Type type)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoWinExaminerViewerP(this);
  PRIVATE(this)->constructor(TRUE);
}

// *************************************************************************

// Documented in common/viewers/SoGuiExaminerViewer.cpp.in.
SoWinExaminerViewer::SoWinExaminerViewer(HWND parent,
                                         const char * name,
                                         SbBool embed,
                                         SoWinFullViewer::BuildFlag flag,
                                         SoWinViewer::Type type,
                                         SbBool build)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoWinExaminerViewerP(this);
  PRIVATE(this)->constructor(build);
}

// *************************************************************************

SoWinExaminerViewer::~SoWinExaminerViewer()
{
  PRIVATE(this)->genericDestructor();
  delete PRIVATE(this);
}

// *************************************************************************

// Documented in superclass.
void
SoWinExaminerViewer::setCamera(SoCamera * newCamera)
{
  // This method overridden from parent class to toggle the camera
  // type selection button pixmap and string of the zoom/dolly
  // thumbwheel.

  inherited::setCamera(newCamera);

  if (! newCamera)
    return;

  SoType camtype = newCamera->getTypeId();
  SbBool orthogonal =
    camtype.isDerivedFrom(SoOrthographicCamera::getClassTypeId());

  const char * oldLabel = this->getRightWheelString();
  if (oldLabel) {
    if (orthogonal) {
      if (strcmp("Dolly",oldLabel) == 0)
        this->setRightWheelString("Zoom");
    }
    else if (strcmp("Zoom",oldLabel) == 0)
      this->setRightWheelString("Dolly");
  }
  SoWinBitmapButton * wbtn = PRIVATE(this)->camerabutton;
  // If viewer was made without decorations, button will not have been
  // made yet.
  if (wbtn) { wbtn->setBitmap(orthogonal ? 1 : 0); }
}

// *************************************************************************

// Documented in superclass.
void
SoWinExaminerViewer::createViewerButtons(HWND parent, SbPList * buttonlist)
{
  inherited::createViewerButtons(parent, buttonlist);

  SoWinBitmapButton * b = PRIVATE(this)->camerabutton =
    new SoWinBitmapButton(parent, 24, "perspective", NULL);
  b->addBitmap(perspective_xpm);
  b->addBitmap(ortho_xpm);
  b->setBitmap(0);
  b->registerClickedProc(SoWinExaminerViewerP::cameraButtonProc, this);
  buttonlist->append(b);
}

// *************************************************************************

#undef PRIVATE
#undef PUBLIC
