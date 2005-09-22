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

// ************************************************************************

// Class is documented in common/viewers/SoGuiWalkViewer.cpp.in.

// ************************************************************************

#include <sowindefs.h>
#include <Inventor/Win/viewers/SoWinWalkViewer.h>
#include <Inventor/Win/viewers/SoGuiWalkViewerP.h>

// ************************************************************************

SOWIN_OBJECT_SOURCE(SoWinWalkViewer);

// ************************************************************************

class SoWinWalkViewerP : public SoGuiWalkViewerP {
public:
  SoWinWalkViewerP(SoWinWalkViewer * o)
    : SoGuiWalkViewerP(o)
  {
  }
};

#define PRIVATE(ptr) ptr->pimpl
#define PUBLIC(ptr) ptr->pub

// ************************************************************************

/*!
  The public constructor.
*/

SoWinWalkViewer::SoWinWalkViewer(
  HWND parent,
  const char * name,
  SbBool embed,
  SoWinFullViewer::BuildFlag flag,
  SoWinViewer::Type type)
: inherited(parent, name, embed, flag, type, TRUE)
{
  PRIVATE(this) = new SoWinWalkViewerP(this);
//  this->constructor(TRUE);
} // SoWinWalkViewer()

// ************************************************************************

/*!
  A protected constructor.
*/

SoWinWalkViewer::SoWinWalkViewer(// protected
  HWND parent,
  const char * name,
  SbBool embed,
  SoWinFullViewer::BuildFlag flag,
  SoWinViewer::Type type,
  SbBool build)
: inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoWinWalkViewerP(this);
//  this->constructor(build);
} // SoWinWalkViewer()

// ************************************************************************

/*!
  The destructor.
*/

SoWinWalkViewer::~SoWinWalkViewer()
{
  delete PRIVATE(this);
} // ~SoWinWalkViewer()

// ************************************************************************

/*!
*/

void
SoWinWalkViewer::setViewing(// virtual
  SbBool enable)
{
} // setViewing()

// ************************************************************************

// Documented in superclass.
void
SoWinWalkViewer::setCamera(SoCamera * camera)
{
}

// ************************************************************************

/*!
*/

void
SoWinWalkViewer::setCursorEnabled(// virtual
  SbBool enable)
{
} // setCursorEnabled()

// ************************************************************************

/*!
*/

void
SoWinWalkViewer::setCameraType(// virtual
  SoType type)
{
} // setCameraType()

// ************************************************************************

/*!
*/

const char *
SoWinWalkViewer::getDefaultWidgetName(// virtual
  void) const
{
  static const char defaultWidgetName[] = "";
  return defaultWidgetName;
} // getDefaultWidgetName()

// ************************************************************************

/*!
*/

const char *
SoWinWalkViewer::getDefaultTitle(// virtual
  void) const
{
  static const char defaultTitle[] = "Walk Viewer";
  return defaultTitle;
} // getDefaultTitle()

// ************************************************************************

/*!
*/

const char *
SoWinWalkViewer::getDefaultIconTitle(// virtual
  void) const
{
  static const char defaultIconTitle[] = "";
  return defaultIconTitle;
} // getDefaultIconTitle()

// ************************************************************************

/*!
*/

void
SoWinWalkViewer::processEvent(// virtual
  MSG * event)
{
} // processEvent()

// ************************************************************************

/*!
*/

void
SoWinWalkViewer::setSeekMode(// virtual
  SbBool enable)
{
} // setSeekMode()

// ************************************************************************

/*!
*/

void
SoWinWalkViewer::actualRedraw(// virtual
  void)
{
} // actualRedraw()

// ************************************************************************

/*!
*/

void
SoWinWalkViewer::rightWheelMotion(// virtual
  float value)
{
} // rightWheelMotion()

// ************************************************************************

/*!
*/

HWND
SoWinWalkViewer::buildLeftTrim(// virtual
  HWND parent)
{
  return NULL;
} // buildLeftTrim()

// ************************************************************************
