/**************************************************************************
 *
 *  This file is part of the Coin SoWin GUI binding library.
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of the distribution for
 *  more details.
 *
 *  If you want to use Coin SoWin for applications not compatible with the
 *  LGPL, please contact SIM to aquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoWinMessageHandler.h>

SoWinMessageHandler::SoWinMessageHandler( void )
{
  //this->callbackList = new SbList< callbackfunction * >;
  this->processList = new SbList< processEventFunction * >;
}

SoWinMessageHandler::~SoWinMessageHandler( void )
{
  //delete this->callbackList;
  delete this->processList;
}

void
SoWinMessageHandler::addProcessEventFunction( processEventFunction * function )
{
  this->processList->append( function );
}

void
SoWinMessageHandler::removeProcessEventFunction( processEventFunction * function )
{
  this->processList->removeItem( function );
}

/*
void SoWinMessageHandler::addCB( callbackfunction * function )
{
    this->callbackList->append( function );
}

void SoWinMessageHandler::removeCB( callbackfunction * function )
{
    this->callbackList->removeItem( function );
}*/

void
SoWinMessageHandler::messageLoop( void )
{
  MSG msg;
  while(TRUE) {
    if ( PeekMessage( & msg, NULL, 0, 0, PM_NOREMOVE ) ) {
      if ( GetMessage( & msg, NULL, 0, 0 ) ) {
        TranslateMessage( & msg );
        DispatchMessage( & msg );
        processEvent( & msg );
      } else break;   // recieved WM_QUIT
    } else SoWin::doIdleTasks( );
  }
}

void
SoWinMessageHandler::processEvent( MSG * msg )
{
  int length = processList->getLength( );
  processEventFunction * const * functions = (processEventFunction * const *) processList->getArrayPtr();
  for( int i = 0; i < length; i++ )
    functions[i]( msg );
}
