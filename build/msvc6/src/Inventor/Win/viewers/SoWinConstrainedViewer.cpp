/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2004 by Systems in Motion.  All rights reserved.
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
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

// src/Inventor/Win/viewers/SoWinConstrainedViewer.cpp.  Generated from SoGuiConstrainedViewer.cpp.in by configure.

/*!
  \class SoWinConstrainedViewer Inventor/Win/viewers/SoWinConstrainedViewer.h
  \brief The SoWinConstrainedViewer class is the superclass for viewers with constrains on the viewpoint.
  \ingroup components viewers

  This abstract viewer class adds new methods to keep the camera in an
  upright position according to some arbitrary up-direction. The
  up-direction can be decided by either the application programmer (by
  using SoWinConstrainedViewer::setUpDirection()) or the end-user,
  through interaction mechanisms defined by the subclasses.
*/

#include <Inventor/Win/viewers/SoWinConstrainedViewer.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/nodes/SoCamera.h>
#include <sowindefs.h>

// ************************************************************************

#ifndef DOXYGEN_SKIP_THIS

class SoWinConstrainedViewerP {
public:
  SoWinConstrainedViewerP(SoWinConstrainedViewer * owner) {
    this->publ = owner;
  }

  void rotateCamera(const float delta) const;

  SbVec3f upvechome;
  SbVec3f upvector; // The camera's "up" vector is contrained to be in this direction.

private:
  SoWinConstrainedViewer * publ;
};

#define PRIVATE(o) (o->pimpl)
#define PUBLIC(o) (o->publ)

void
SoWinConstrainedViewerP::rotateCamera(const float delta) const
{
  SoCamera * const camera = PUBLIC(this)->getCamera();
  if (camera == NULL) { return; } // if there's no scenegraph, for instance

  camera->orientation = camera->orientation.getValue() *
    SbRotation(PUBLIC(this)->getUpDirection(), -delta);
}

#endif // DOXYGEN_SKIP_THIS

// ************************************************************************

SOWIN_OBJECT_ABSTRACT_SOURCE(SoWinConstrainedViewer);

// ************************************************************************

/*!
  Constructor.
*/
SoWinConstrainedViewer::SoWinConstrainedViewer(HWND parent,
                                                   const char * const name,
                                                   SbBool embed,
                                                   SoWinFullViewer::BuildFlag flag,
                                                   SoWinViewer::Type type,
                                                   SbBool build)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoWinConstrainedViewerP(this);

  this->setClassName("SoWinConstrainedViewer");
  this->setLeftWheelString("Tilt");
  this->setBottomWheelString("Rotate");
  this->setRightWheelString("Dolly");

  PRIVATE(this)->upvector = SbVec3f(0.0f, 1.0f, 0.0f);
  PRIVATE(this)->upvechome = PRIVATE(this)->upvector;

  if (build) {
    HWND viewer = this->buildWidget(this->getParentWidget());
    this->setBaseWidget(viewer);
  }
}

// ************************************************************************

/*!
  Virtual destructor.
*/
SoWinConstrainedViewer::~SoWinConstrainedViewer()
{
  delete PRIVATE(this);
}

// ************************************************************************

/*!
  Set up-direction vector for the camera viewpoint.
*/
void
SoWinConstrainedViewer::setUpDirection(const SbVec3f & dir)
{
  SbRotation change(PRIVATE(this)->upvector, dir);
  PRIVATE(this)->upvector = dir;

  SoCamera * cam = this->getCamera();
  if (cam == NULL) { return; } // can happen for empty scene, for instance

  cam->orientation = change * cam->orientation.getValue();
  this->checkForCameraUpConstrain();
}

// ************************************************************************

/*!
  Return up-direction vector for the camera viewpoint.
*/
const SbVec3f &
SoWinConstrainedViewer::getUpDirection(void) const
{
  return PRIVATE(this)->upvector;
}

// ************************************************************************

// doc in super
void
SoWinConstrainedViewer::setCamera(SoCamera * newcam)
{
  inherited::setCamera(newcam);
  if (newcam != NULL) { this->checkForCameraUpConstrain(); }
}

// ************************************************************************

// doc in super
void
SoWinConstrainedViewer::saveHomePosition(void)
{
  inherited::saveHomePosition();
  PRIVATE(this)->upvechome = PRIVATE(this)->upvector;
}

// ************************************************************************

// doc in super
void
SoWinConstrainedViewer::resetToHomePosition(void)
{
  inherited::resetToHomePosition();
  PRIVATE(this)->upvector = PRIVATE(this)->upvechome;
  // should be unnecessary to reset camera position here (camera
  // should have been in a valid state on the last saveHomePosition()
  // call)
}

// ************************************************************************

/*!
  This method tilts the camera \a delta degrees closer to the up
  direction.
*/
void
SoWinConstrainedViewer::tiltCamera(float delta)
{
  SoCamera * const camera = this->getCamera();
  if (camera == NULL) { return; } // if there's no scenegraph, for instance

  SbVec3f camdir;
  camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), camdir);
  camera->orientation = camera->orientation.getValue() *
    SbRotation(this->getUpDirection().cross(camdir), delta);
}

// ************************************************************************

// doc in super
void
SoWinConstrainedViewer::bottomWheelMotion(float value)
{
  PRIVATE(this)->rotateCamera(value - this->getBottomWheelValue());
  inherited::bottomWheelMotion(value);
}

// ************************************************************************

// doc in super
void
SoWinConstrainedViewer::leftWheelMotion(float value)
{
  this->tiltCamera( this->getLeftWheelValue() - value);
  inherited::leftWheelMotion(value);
}

// ************************************************************************

// doc in super
void
SoWinConstrainedViewer::changeCameraValues(SoCamera * camera)
{
  inherited::changeCameraValues(camera);
  this->checkForCameraUpConstrain();
}

// ************************************************************************

/*!
  Executes a raypick at the given mousepointer location and sets the
  viewer's camera up-vector direction to the normal vector of the
  picked geometry.
*/
void
SoWinConstrainedViewer::findUpDirection(SbVec2s mouselocation)
{
  SoRayPickAction rp(this->getViewportRegion());
  rp.setPoint(mouselocation);

  // Use the full scenegraph, not just the user-set scenegraph (which
  // is what SoWinConstrainedViewer::getSceneGraph() would return).
  SoNode * realroot = this->getSceneManager()->getSceneGraph();
  rp.apply(realroot);

  SoPickedPoint * point = rp.getPickedPoint();
  if (point == NULL) { return; } // missed all geometry

  SbVec3f normvec = point->getNormal();
  // FIXME: need to flip normal if we hit the backside of a
  // polygon. 20010925 mortene.
  this->setUpDirection(normvec);
}

// ************************************************************************

/*!
  If necessary, "tilts" the camera sideways so the up-direction is
  heeded.
*/
void
SoWinConstrainedViewer::checkForCameraUpConstrain(void)
{
  SoCamera * cam = this->getCamera();
  assert(cam);

  SbRotation camorient = cam->orientation.getValue();

  SbVec3f campointdir;
  camorient.multVec(SbVec3f(0, 0, -1), campointdir);
  SbVec3f camrightdir;
  camorient.multVec(SbVec3f(1, 0, 0), camrightdir);

  SbVec3f correctrightdir = campointdir.cross(PRIVATE(this)->upvector);
  if (correctrightdir.length() == 0.0f) { return; } // upvector == pointdir

  SbRotation r(camrightdir, correctrightdir);
  SbRotation newcamorient = camorient * r;
  cam->orientation = newcamorient;
}

// ************************************************************************

#undef PRIVATE
#undef PUBLIC

