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

#if SOWIN_DEBUG
static const char rcsid[] =
  "$Id$";
#endif

#include <Inventor/Win/SoWinObject.h>
#include <Inventor/Win/devices/SoWinDevice.h>
#include <Inventor/Win/SoWinComponent.h>

/*!
  \class SoWinObject Inventor/Win/SoWinObject.h
  \brief The SoWinObject class is for run-time type checking of the SoWin
  objects.
*/

// *************************************************************************

SoType SoWinObject::classTypeId; // static

void
SoWinObject::init( // static
  void )
{
  SoWinObject::initClass();
  SoWinDevice::initClasses();
  SoWinComponent::initClasses();
} // init()

void
SoWinObject::initClass( // static
  void )
{
  assert( SoWinObject::classTypeId == SoType::badType() );
  SoWinObject::classTypeId =
    SoType::createType( SoType::badType(), "SoWinObject");
} // initClass()

SbBool
SoWinObject::isOfType(
  SoType type ) const
{
  return this->getTypeId().isDerivedFrom(type);
} // isOfType()

SoType
SoWinObject::getClassTypeId( // static
  void ) 
{
  return SoWinObject::classTypeId;
} // getClassTypeId()

// *************************************************************************
