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

// *************************************************************************

// The private data for the SoWinExaminerViewer.

SoWinExaminerViewerP::SoWinExaminerViewerP(SoWinExaminerViewer * o)
  : SoGuiExaminerViewerP(o)
{
}

SoWinExaminerViewerP::~SoWinExaminerViewerP()
{
}

// *************************************************************************

SOWIN_OBJECT_SOURCE(SoWinExaminerViewer);

// *************************************************************************

// FIXME: this has got to be guaranteed unique versus the FullViewer
// button ids. This is just a quick hack. 20020719 mortene.
#define VIEWERBUTTON_CAMERA 4242

/*!
  Constructor.  See parent class for explanation of arguments.
  Calling this constructor will make sure the examiner viewer widget
  will be built immediately.
*/

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

/*!
  Constructor. See parent class for explanation of arguments.
*/

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

/*!
  \internal

  This contains the real constructor code (the two constructors are only
  entry points for this method).
*/

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

// *************************************************************************

/*!
  Destructor.
*/

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

  SbBool isorthotype =
    newCamera->getTypeId().isDerivedFrom(SoOrthographicCamera::getClassTypeId());

  this->setRightWheelString(isorthotype ? "Zoom" : "Dolly");

  if (this->isDoButtonBar()) { // may not be there if !doButtonBar
    SoWinBitmapButton * wbtn = PRIVATE(this)->camerabutton;
    // If viewer was made without decorations, button will not have
    // been made yet.
    if (wbtn) { wbtn->setBitmap(isorthotype ? 1 : 0); }
  }

}

// FIXME: avoid having this special method for SoWin, instead of just
// buildViewerButtons(). 20020524 mortene.
/*!
  This method overloaded from parent class to build viewer buttons
  specific for this viewer.
*/

void
SoWinExaminerViewer::buildViewerButtonsEx(HWND parent,
                                          int x,
                                          int y,
                                          int size)
{
  PRIVATE(this)->camerabutton = new SoWinBitmapButton(parent, x, y, size, size, 24, "perspective", NULL);
  PRIVATE(this)->camerabutton->addBitmap(perspective_xpm);
  PRIVATE(this)->camerabutton->addBitmap(ortho_xpm);
  PRIVATE(this)->camerabutton->setBitmap(0);
  PRIVATE(this)->camerabutton->setId(VIEWERBUTTON_CAMERA);
  this->viewerButtonList->append(PRIVATE(this)->camerabutton);
}

// *************************************************************************

/*!
  This method overloaded from parent class to handle button messages
  from viewer specific buttons (camera toggle).
*/

LRESULT
SoWinExaminerViewer::onCommand(HWND window,
                               UINT message,
                               WPARAM wparam,
                               LPARAM lparam)
{
  short nc = HIWORD(wparam);// notification code
  short id = LOWORD(wparam);// item, control, or accelerator identifier
  HWND hwnd = (HWND) lparam;// control handle

  if (id == VIEWERBUTTON_CAMERA)
    PRIVATE(this)->cameratoggleClicked();
  else
    return inherited::onCommand(window, message, wparam, lparam);

  return 0;
}

// *************************************************************************

/*!
*/
void
SoWinExaminerViewerP::cameratoggleClicked(void)
{
  if (PUBLIC(this)->getCamera()) PUBLIC(this)->toggleCameraType();
}

// *************************************************************************

// FIXME: these are present in the other So* toolkits, but was missing
// in SoWin. Why? 20020111 mortene.

void
SoWinExaminerViewer::createViewerButtons(HWND parent, SbPList * buttonlist)
{
  // FIXME: not activated in SoWinFullViewer yet. 20020111 mortene.
//    inherited::createViewerButtons(parent, buttonlist);
}
