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

//  $Id$

#ifndef SOWIN_H
#define SOWIN_H

#include <math.h>
#include <windows.h>
#include <Gl/gl.h>

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>

#include <Inventor/Win/SoWinBasic.h>

class SoSensor;
class SoWinMessageHandler;

// default values when creating window ( !embed )
const int SoWin_DefaultWidth = 500;
const int SoWin_DefaultHeight = 500;

// *************************************************************************

class SOWIN_DLL_EXPORT SoWin
{

public:
    static HWND init( const char * const appName,
                      const char * const className = "SoWin" );
    static HWND init( int argc, char ** argv,           // FIXME: oiv don't have this...
                      const char * const appName,
                      const char * const className = "SoWin" );
    static void init( HWND const topLevelWidget );
    static void init( void );

    static void mainLoop( void );
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


    // TGS sh*t - not implemented
    static void terminate( long terminateSyncTime = 100 );
    static SbBool PreTranslateMessage( MSG * msg );
    static SbBool nextEvent( int appContext, MSG * msg );
    static int getAppContext( void );
    static int * getDisplay( void );
    static HWND getShellWidget(HWND widget);
    static void	getPopupArgs( int * display, int screen, char ** args, int * n );
    static void	addColormapToShell( HWND widget, HWND shell );
    static LRESULT isInventorMessage( HWND hwnd,
                                      UINT message,
                                      WPARAM wParam,
                                      LPARAM lParam );
    char * encodeString( char *string );
    char * decodeString( char * wstring );

    static UINT wmTimerMsg;
    static UINT wmWorkMsg;

    static void setInstance( HINSTANCE instance );
    static HINSTANCE getInstance( void );


    // "SoWININTERNAL public"
//  static void errorHandlerCB( const SoError *error, void *data );
    static void addMessageHook( HWND hwnd, UINT message );
    static void removeMessageHook( HWND hwnd, UINT message );

    // Coin spesific
    static void deInit( void );

    void addProcessEventFunction( processEventFunction * function );
    void removeProcessEventFunction( processEventFunction * function );

protected:
    static void registerWindowClass( const char * const className );
    static void unRegisterWindowClass( const char * const className );
    static HWND createWindow( char * title,
                              char * className,
                              RECT rect,
                              HWND parent = (HWND) NULL,
                              HMENU menu = (HMENU) NULL );
    static LRESULT CALLBACK windowCB( HWND window,
                                      UINT message,
                                      WPARAM wparam,
                                      LPARAM lparam );

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

    static HINSTANCE Instance;
    static HWND mainWidget;
    static char * appName;
    static char * className;

    static SoWinMessageHandler * messageHandler;

}; // class SoWin

// *************************************************************************
// Globals

#ifdef _DEBUG

void WinDisplayLastError( void );

#endif // _DEBUG

#ifndef SOWIN_INTERNAL

//int ivMain(int argc, char ** argv);
void ivMain(int argc, char ** argv);
int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

#endif // !SOWIN_INTERNAL

// !Globals
// *************************************************************************

#endif // ! SOWIN_H