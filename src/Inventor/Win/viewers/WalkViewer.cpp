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

#include <sowindefs.h>
#include <Inventor/Win/viewers/SoWinWalkViewer.h>
#include <Inventor/Win/viewers/SoGuiWalkViewerP.h>

/*!
  \class SoWinWalkViewer Inventor/Win/viewers/SoWinWalkViewers.h
  \brief The SoWinWalkViewer class is yet to be documented...
  \ingroup sowinviewers
*/

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

/*!
*/

void
SoWinWalkViewer::createPrefSheet(// virtual
  void)
{
} // createPrefSheet()

// ************************************************************************

/*!
*/

void
SoWinWalkViewer::openViewerHelpCard(// virtual
  void)
{
} // openViewerHelpCard()

// ************************************************************************
