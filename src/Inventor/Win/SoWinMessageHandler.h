/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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
\**************************************************************************/

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
