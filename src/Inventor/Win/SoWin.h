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

#ifndef SOWIN_H
#define SOWIN_H

#include <math.h>
#include <windows.h>

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>

#include <Inventor/lists/SbList.h>
#include <Inventor/errors/SoError.h>

#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinDevice.h>

class SoSensor;
class SoWinP;

// *************************************************************************

class SOWIN_DLL_API SoWin
{
  friend class SoWinP;
  
public:
  
  static HWND init( const char * const appName,
                    const char * const className = "SoWin" );
  static HWND init( int argc, char ** argv,
                    const char * const appName,
                    const char * const className = "SoWin" );
  static void init( HWND const topLevelWidget );
  static void init( void );

  static void mainLoop( void );
  static void exitMainLoop( void );
  static BOOL dispatchEvent( MSG * msg );

  static void show( HWND const widget );
  static void hide( HWND const widget );

  static void setWidgetSize( HWND widget, const SbVec2s size );
  static SbVec2s getWidgetSize( HWND widget );
  static HWND getTopLevelWidget( void );

  static void createSimpleErrorDialog( HWND const widget,
                                       const char * const dialogTitle,
                                       const char * const errorStr1,
                                       const char * const errorStr2 = NULL );
  
  static SbBool nextEvent( int appContext, MSG * msg );
  
  static HWND getShellWidget( HWND widget );

  static void setInstance( HINSTANCE instance );
  static HINSTANCE getInstance( void );
  static void errorHandlerCB( const SoError * error, void * data );

protected:
  
  static void doIdleTasks( void );
    
  static void registerWindowClass( const char * const className );
  static void unRegisterWindowClass( const char * const className );

  static HWND createWindow( char * title,
                            char * className,
                            SIZE size,
                            HWND parent = ( HWND ) NULL,
                            HMENU menu = ( HMENU ) NULL );

  static LRESULT CALLBACK eventHandler( HWND window,
                                        UINT message,
                                        WPARAM wparam,
                                        LPARAM lparam );

}; // class SoWin

#endif // !SOWIN_H
