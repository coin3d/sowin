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

#ifndef SOWIN_MESSAGEHANDLER_H
#define SOWIN_MESSAGEHANDLER_H

#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/lists/SbList.h>

class SOWIN_DLL_API SoWinMessageHandler
{
public:
  SoWinMessageHandler( void );
  ~SoWinMessageHandler( void );
    
  /*void addCB( callbackfunction * function );
    void removeCB( callbackfunction * function );*/
  void addProcessEventFunction( processEventFunction * function );
  void removeProcessEventFunction( processEventFunction * function );

  void messageLoop( void );
  //void processMessage( MSG * msg );
  void processEvent( MSG * msg );

protected:

private:
  //SbList< callbackfunction * > * callbackList;
  SbList< processEventFunction * > * processList;
};  // class SoWinMessageHandler

#endif // !SOWIN_MESSAGEHANDLER_H
