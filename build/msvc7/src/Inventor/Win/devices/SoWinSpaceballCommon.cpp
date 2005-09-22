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

/*!
  \class SoWinSpaceball SoWinSpaceball.h Inventor/Win/devices/SoWinSpaceball.h
  \brief The SoWinSpaceball class is the spaceball input device abstraction.
  \ingroup devices

  The SoWinSpaceball class is the glue between native spaceball
  handling and how those events translates to generic events for the
  Inventor API scenegraph.
*/

// *************************************************************************

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/Win/devices/SoWinSpaceball.h>
#include <Inventor/Win/devices/SoWinSpaceballP.h>

#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->pub)

// *************************************************************************

SOWIN_OBJECT_SOURCE(SoWinSpaceball);

// *************************************************************************

/*!
  \enum SoWinSpaceball::DeviceType

  Enumeration of spaceball input device types.
*/
/*!
  \enum SoWinSpaceball::Mask
  Enumeration of spaceball input device event types.
*/

/*!
  \fn SoWinSpaceball::SoWinSpaceball(int mask)

  Public constructor. The \a mask argument specifies which events we
  are interested in.
*/

/*!
  \fn SoWinSpaceball::~SoWinSpaceball()
  Destructor.
*/

// *************************************************************************

/*!
  This method sets the scale factor for the spaceball rotation vectors.
*/
void
SoWinSpaceball::setRotationScaleFactor(float f)
{
  PRIVATE(this)->rotationscale = f;
}

/*!
  This method returns the scale factor for the spaceball rotation vectors.
*/
float
SoWinSpaceball::getRotationScaleFactor(void) const
{
  return PRIVATE(this)->rotationscale;
}

/*!
  This method sets the scale factor for the spaceball translation vectors.
*/
void
SoWinSpaceball::setTranslationScaleFactor(float f)
{
  PRIVATE(this)->translationscale = f;
}

/*!
  This method returns the scale factor for the spaceball translation vectors.
*/
float
SoWinSpaceball::getTranslationScaleFactor(void) const
{
  return PRIVATE(this)->translationscale;
}

// *************************************************************************

/*!
  \fn SbBool SoWinSpaceball::exists(void)

  Returns \c TRUE iff there could be a device of this type available
  on the system.

  Note that a return value of \c TRUE does \e not signify that there
  is such a device active.
*/

// *************************************************************************

/*!
  \fn void SoWinSpaceball::setFocusToWindow(SbBool flag)

  Set to \c TRUE if you want spaceball events to be received even when
  the component does not have focus.
*/

/*!
  \fn SbBool SoWinSpaceball::isFocusToWindow(void) const

  Returns whether or not spaceball events are caught even when the
  component does not have focus.
*/

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

SoGuiSpaceballP::SoGuiSpaceballP(SoWinSpaceball * p)
{
  this->pub = p;
}

SoGuiSpaceballP::~SoGuiSpaceballP()
{
}

#endif // !DOXYGEN_SKIP_THIS

// *************************************************************************

#undef PRIVATE
#undef PUBLIC

