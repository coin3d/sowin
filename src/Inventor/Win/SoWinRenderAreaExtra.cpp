/**************************************************************************
 *
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
 **************************************************************************/

#include <Inventor/SoSceneManager.h>

//#include <sowindefs.h>
#include <Inventor/Win/devices/SoWinMouse.h>
#include <Inventor/Win/devices/SoWinKeyboard.h>

#include <Inventor/Win/SoWinRenderArea.h>

// *************************************************************************

/*!
*/

void
SoWinRenderArea::processEvent( // virtual, protected
  MSG * msg )
{
    // FIXME: function not implemented
  if ( this->invokeAppCB( msg ) )
    return;

  inherited::processEvent( msg );

  const SoEvent * sceneEvent = NULL;

  if ( this->devices.extra )
    for ( int i = 0; i < this->devices.extra->getLength() && sceneEvent == NULL; i++ )
      sceneEvent = ((SoWinDevice *)(*this->devices.extra)[i])->translateEvent( msg );

  if ( ! sceneEvent && this->devices.mouse )
    sceneEvent = this->devices.mouse->translateEvent( msg );

  if ( ! sceneEvent && this->devices.keyboard )
    sceneEvent = this->devices.keyboard->translateEvent( msg );

  if ( sceneEvent != NULL ) {
    assert( this->normalManager != NULL );
    assert( this->overlayManager != NULL );
    if ( ! this->overlayManager->processEvent( sceneEvent ) )
      this->normalManager->processEvent( sceneEvent );
  }
} // processEvent()

// *************************************************************************
//
