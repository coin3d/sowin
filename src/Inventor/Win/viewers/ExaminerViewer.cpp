/**************************************************************************
 *
 *  This file is part of the Coin SoWin GUI binding library.
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

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#if SOWIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOWIN_DEBUG

#include <sowindefs.h>

#include <Inventor/Win/SoWin.h>

#include <Inventor/Win/widgets/SoWinThumbWheel.h>
#include <Inventor/Win/widgets/SoWinBitmapButton.h>
#include <Inventor/Win/widgets/SoWinViewerPrefSheet.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>

#include <Inventor/Win/common/pixmaps/perspective.xpm>
#include <Inventor/Win/common/pixmaps/ortho.xpm>
#include <Inventor/Win/SoWinCursor.h>

/*!
  \class SoWinExaminerViewer SoWinExaminerViewer.h Inventor/Win/viewers/SoWinExaminerViewer.h
  \brief The SoWinExaminerViewer class is a full-fledged model viewer
  with functionality for rotation, pan, zoom, etc.
  \ingroup sowinviewers

  TODO: more doc
  ...overview of what this class provides over parent class...
  ...keyboard combinations...mousebutton combinations...explain pan,
  rotate, zoom, dolly, seek...explain the fact that we're moving the
  camera, not the scene...
  ...viewer modes (examine vs interact) w/ explanation of what they are
  useful for...
  ...screenshot...
  ...example code...

  \sa SoWinWalkViewer, SoWinFlyViewer, SoWinPlaneViewer, SoWinCollisionViewer
*/

/*�
  SoWinExaminerViewer is missing the class description documentation.
*/

// *************************************************************************

// The private data for the SoWinExaminerViewer.

class SoWinExaminerViewerP {

public:

  // Constructor.
  SoWinExaminerViewerP(SoWinExaminerViewer * o) {
    this->owner = o;
  }

  // Destructor.
  ~SoWinExaminerViewerP() {
  }

  void constructor(SbBool build);
  void cameratoggleClicked(void);

  SoWinBitmapButton * camerabutton;

private:
  SoWinExaminerViewer * owner;
};

#define PRIVATE(o) (o->pimpl)

// *************************************************************************

SOWIN_OBJECT_SOURCE(SoWinExaminerViewer);

// *************************************************************************

#define VIEWERBUTTON_CAMERA 0

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
  this->owner->genericConstructor();

  this->owner->setClassName("SoWinExaminerViewer");
  this->owner->setPopupMenuString("Examiner Viewer");
  this->owner->setPrefSheetString("Examiner Viewer Preference Sheet");

  if (! build) return;

  HWND widget = this->owner->buildWidget(this->owner->getParentWidget());
  this->owner->setBaseWidget(widget);

  this->owner->setLeftWheelString("RotX");
  this->owner->setBottomWheelString("RotY");

  this->owner->setCursorEnabled(TRUE);
  this->owner->setAnimationEnabled(TRUE);

  this->owner->setSize(SbVec2s(500, 421));
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
  delete this->pimpl;
  this->genericDestructor();
}

// *************************************************************************

/*!
  This method overloaded from parent class to make sure the mouse
  pointer cursor is updated.
*/

void
SoWinExaminerViewer::setViewing(SbBool enable)
{
  this->setMode(enable ?
                         SoWinExaminerViewer::EXAMINE :
                         SoWinExaminerViewer::INTERACT);
  inherited::setViewing(enable);
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
  Overloaded to provide the examiner viewer functionality on the left
  thumbwheel (x axis rotation).
*/

void
SoWinExaminerViewer::leftWheelMotion(float value)
{
  if (this->isAnimating())
    this->stopAnimating();

 inherited::leftWheelMotion(
  this->rotXWheelMotion(value, this->getLeftWheelValue()));
}

/*!
  Overloaded to provide the examiner viewer functionality on the bottom
  thumbwheel (y axis rotation).
*/

void
SoWinExaminerViewer::bottomWheelMotion(float value)
{
  if (this->isAnimating())
    this->stopAnimating();

  inherited::bottomWheelMotion(
  this->rotYWheelMotion(value, this->getBottomWheelValue()));
}

/*!
  Overloaded to provide the examiner viewer functionality on the left
  thumbwheel (dolly/zoom).
*/

void
SoWinExaminerViewer::rightWheelMotion(float value)
{
 this->zoom(this->getRightWheelValue() - value);
 inherited::rightWheelMotion(value);
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
  int i;
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

void
SoWinExaminerViewer::setCursorRepresentation(int mode)
{
  // FIXME: with the new So@Gui@Cursor class, this has actually become
  // a possibly generic method for all So* toolkits. Move to common
  // code. 20011125 mortene.

  if (!this->isCursorEnabled()) {
    this->setComponentCursor(SoWinCursor::getBlankCursor());
    return;
  }

  switch (mode) {
  case SoWinExaminerViewer::INTERACT:
    this->setComponentCursor(SoWinCursor(SoWinCursor::DEFAULT));
    break;

  case SoWinExaminerViewer::EXAMINE:
  case SoWinExaminerViewer::DRAGGING:
    this->setComponentCursor(SoWinCursor::getRotateCursor());
    break;

  case SoWinExaminerViewer::ZOOMING:
    this->setComponentCursor(SoWinCursor::getZoomCursor());
    break;

  case SoWinExaminerViewer::WAITING_FOR_SEEK:
    this->setComponentCursor(SoWinCursor(SoWinCursor::CROSSHAIR));
    break;

  case SoWinExaminerViewer::WAITING_FOR_PAN:
  case SoWinExaminerViewer::PANNING:
    this->setComponentCursor(SoWinCursor::getPanCursor());
    break;

  default: assert(0); break;
  }
}

// *************************************************************************

/*!
  \internal

  Create aditional preference dialog items.
*/
void
SoWinExaminerViewer::createPrefSheet(void)
{
  inherited::createPrefSheet(); // create standard parts
  this->prefsheet->createSpinWidgets(this);
  this->prefsheet->size();
}

/*!
*/
void
SoWinExaminerViewer::setAnimationEnabled(const SbBool enable)
{
  this->setGenericAnimationEnabled(enable);
}

/*!
*/
void
SoWinExaminerViewer::setFeedbackSize(const int size)
{
  this->setGenericFeedbackSize(size);
}

// *************************************************************************

/*!
*/
void
SoWinExaminerViewer::afterRealizeHook(void)
{
  this->setCursorRepresentation(this->currentmode);
  inherited::afterRealizeHook();
}

/*!
*/
void
SoWinExaminerViewerP::cameratoggleClicked(void)
{
  if (this->owner->getCamera()) this->owner->toggleCameraType();
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

HWND
SoWinExaminerViewer::makeSubPreferences(HWND parent)
{
  // FIXME: not activated in SoWinFullViewer yet. 20020111 mortene.
//    return inherited::makeSubPreferences(parent);
  return NULL;
}

