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

// default values when creating window ( !embed )
const int SoWin_DefaultWidth = 500;
const int SoWin_DefaultHeight = 500;

// *************************************************************************

class SOWIN_DLL_API SoWin
{

public:
  static HWND init( const char * const appName,
                    const char * const className = "SoWin" );
  static HWND init( int argc, char ** argv,           // FIXME: coin spesific
                    const char * const appName,
                    const char * const className = "SoWin" );
  static void init( HWND const topLevelWidget );
  static void init( void );

  static void mainLoop( void );
  static void exitMainLoop( void );
  static void doIdleTasks( void );
  static BOOL dispatchEvent( MSG * msg );

  static void show( HWND const widget );
  static void hide( HWND const widget);

  static void setWidgetSize( HWND widget, const SbVec2s size );
  static SbVec2s getWidgetSize( HWND widget );
  static HWND getTopLevelWidget( void );

  static void createSimpleErrorDialog( HWND const widget,
                                       const char * const dialogTitle,
                                       const char * const errorStr1,
                                       const char * const errorStr2 = NULL );
	
  // Not implemented (not critical)
  static void terminate( long terminateSyncTime = 100 );
  static SbBool PreTranslateMessage( MSG * msg );
  static SbBool nextEvent( int appContext, MSG * msg );
  static int getAppContext( void );
  static int * getDisplay( void );
  static HWND getShellWidget( HWND widget );
  static void	getPopupArgs( int * display, int screen, char ** args, int * n );
  static void	addColormapToShell( HWND widget, HWND shell );
  static LRESULT isInventorMessage( HWND hwnd,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam );
  char * encodeString( char * string );
  char * decodeString( char * wstring );

  static UINT wmTimerMsg;
  static UINT wmWorkMsg;

  static void setInstance( HINSTANCE instance );
  static HINSTANCE getInstance( void );

  // "SoWININTERNAL public"
  static void errorHandlerCB( const SoError * error, void * data );
  //
  static void addExtensionEventHandler( HWND window,
                                        int extensionEventType,
                                        SoWinEventHandler * callbackproc,
                                        void * data );
  static void removeExtensionEventHandler( HWND window,
                                           int extensionEventType,
                                           SoWinEventHandler * callbackproc, 
                                           void * data );
  static ATOM registerClass( WNDCLASS * wndClass, char * className );
  static SbBool getClassInfo( HINSTANCE dll,
                              const char * name,
                              char * className,
                              WNDCLASS * classInfo );
  static void unregisterProcessClasses( void );

  static HINSTANCE getResDllHandle( void );
  static void setPrevInstance( HINSTANCE instance );
  static void setCmdLine( LPSTR cmdLine );
  static void setCmdShow( int cmdShow );
  static SoWinEventHandler * getEventHandler( void );
  static void forwardQueryPalette( HWND window ) ;
  static void forwardPaletteChanged( HWND window ) ;
  static SbBool handleCtl3DMessage( void );
  static void setHandleCtl3DMessage( SbBool n );
  static void Ctl3dColorChange( void );
  //

protected:
  static void registerWindowClass( const char * const className );
  static void unRegisterWindowClass( const char * const className );
  static HWND createWindow( char * title,
                            char * className,
                            SIZE size,
                            HWND parent = (HWND) NULL,
                            HMENU menu = (HMENU) NULL );

  static LRESULT CALLBACK windowProc( HWND window,
                                      UINT message,
                                      WPARAM wparam,
                                      LPARAM lparam );

    
  static BOOL CALLBACK sizeChildProc( HWND window, LPARAM lparam );

  /*
    static FARPROC m_procCtl3dColorChange;
    static HINSTANCE m_hCtl3d;
    static void	getExtensionEventHandler(
    MSG * msg, 
    HWND &w, 
    LRESULT CALLBACK &proc, 
    void * &clientData);
  */
private:
  
  static void sensorQueueChanged( void * cbdata );

  static int timerSensorId;
  static SbBool timerSensorActive;
  static void CALLBACK timerSensorCB( HWND window,
                                      UINT message,
                                      UINT idevent,
                                      DWORD dwtime );

  static int delaySensorId;
  static SbBool delaySensorActive;
  static void CALLBACK delaySensorCB( HWND window,
                                      UINT message,
                                      UINT idevent,
                                      DWORD dwtime );

  static int idleSensorId;
  static SbBool idleSensorActive;
  static void CALLBACK idleSensorCB( HWND window,
                                     UINT message,
                                     UINT idevent,
                                     DWORD dwtime );
  
  static LRESULT onSize( HWND window,
                         UINT message,
                         WPARAM wparam,
                         LPARAM lparam );
  static LRESULT onDestroy( HWND window,
                            UINT message,
                            WPARAM wparam,
                            LPARAM lparam );
  static LRESULT onQuit( HWND window,
                         UINT message,
                         WPARAM wparam,
                         LPARAM lparam );

  static HINSTANCE Instance;
  static HWND mainWidget;
  static char * appName;
  static char * className;

}; // class SoWin

#endif // !SOWIN_H
