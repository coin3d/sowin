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

#include <conio.h>

#include <Inventor/SbTime.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodekits/SoNodeKit.h>

#include <sowindefs.h> // SOWIN_STUB
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/devices/SoWinDevice.h>
#include <Inventor/Win/SoWinComponent.h>

// The private data for the SoWin.

class SoWinP {
  
public:

  static BOOL CALLBACK sizeChildProc( HWND window, LPARAM lparam );
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
  
  static LRESULT onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  static LRESULT onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  static LRESULT onQuit( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  
  static HINSTANCE Instance;
  static HWND mainWidget;
  static char * appName;
  static char * className;

  static SbBool useParentEventHandler;
  static WNDPROC parentEventHandler;

private:
  SoWin * owner;
  
};

  // Variables.

// *************************************************************************

HINSTANCE SoWinP::Instance = NULL;
HWND SoWinP::mainWidget = NULL;
char * SoWinP::appName = NULL;
char * SoWinP::className = NULL;
int SoWinP::timerSensorId = 0;
SbBool SoWinP::timerSensorActive = FALSE;
int SoWinP::delaySensorId = 0;
SbBool SoWinP::delaySensorActive = FALSE;
int SoWinP::idleSensorId = 0;
SbBool SoWinP::idleSensorActive = FALSE;
WNDPROC SoWinP::parentEventHandler = NULL;
SbBool SoWinP::useParentEventHandler = TRUE;

// *************************************************************************

void
SoWinObject::init( void )
{
  SoWinObject::initClass( );
  SoWinDevice::initClasses( );
  SoWinComponent::initClasses( );
}

///////////////////////////////////////////////////////////////////
//
//  (public)
//

HWND
SoWin::init( const char * const appName,
             const char * const className )
{
  int argc = 1;
  char * argv[] = { ( char * ) appName, NULL };
  return SoWin::init( argc, argv, appName, className );
}

HWND
SoWin::init( int argc,
             char ** argv,
             const char * const appName,
             const char * const className )
{
  if ( appName )
    SoWinP::appName = strcpy( new char [ strlen( appName ) + 1 ], appName );
  if ( className )
    SoWinP::className = strcpy( new char [ strlen( className ) + 1 ], className );

  SoWin::registerWindowClass( className );
 
  SIZE size = { 500, 500 };
  HWND toplevel = SoWin::createWindow( ( char * ) appName, ( char * ) className, size, NULL );
  SoWinP::useParentEventHandler = FALSE;
  
  SoWin::init( toplevel );
  
  return toplevel;
}

void
SoWin::init( HWND const topLevelWidget )
{
  SoDB::init( );
  SoNodeKit::init( );
  SoInteraction::init( );
  SoWinObject::init( );

  SoDebugError::setHandlerCallback( SoWin::errorHandlerCB, NULL );

  SoDB::getSensorManager( )->setChangedCallback( SoWinP::sensorQueueChanged, NULL );
  if ( IsWindow( topLevelWidget ) ) 
    SoWinP::mainWidget = topLevelWidget;

  if ( SoWinP::useParentEventHandler ) {
    SoWinP::parentEventHandler = ( WNDPROC ) GetWindowLong( topLevelWidget, GWL_WNDPROC );
    SetWindowLong( topLevelWidget, GWL_WNDPROC, ( long ) SoWin::eventHandler );
  }
}

void
SoWin::init( void )
{
  SoWin::init( "SoWin", "SoWin" );
}

void
SoWin::mainLoop( void )
{
  MSG msg;
  while ( TRUE ) {
    if ( GetQueueStatus( QS_ALLINPUT ) != 0 ) { // if messagequeue != empty
      if ( GetMessage( & msg, NULL, 0, 0 ) ) { // if msg != WM_QUIT
        TranslateMessage( & msg );
        DispatchMessage( & msg );
      }
      else break; // msg == WM_QUIT
    }
    else if ( SoWinP::idleSensorActive )
      SoWin::doIdleTasks( );
    else // !idleSensorActive
      WaitMessage( );
  }
}

void
SoWin::exitMainLoop( void )
{
  PostQuitMessage( 0 );
}

BOOL
SoWin::dispatchEvent( MSG * msg )
{
  TranslateMessage( msg );
  DispatchMessage( msg );
  return TRUE;
}

void
SoWin::show( HWND const widget )
{
  ShowWindow( widget, SW_SHOW );
}

void
SoWin::hide( HWND const widget )
{
  ShowWindow( widget, SW_HIDE );
}

void
SoWin::setWidgetSize( HWND widget, const SbVec2s size )
{
 UINT flags = SWP_NOMOVE | SWP_NOZORDER;
 SetWindowPos( widget, NULL, 0, 0, size[0], size[1], flags);
} 

SbVec2s
SoWin::getWidgetSize( HWND widget )
{
  SIZE size;
  HDC hdc = GetDC( SoWinP::mainWidget );

  if ( ! GetWindowExtEx( hdc, & size ) ) {
    size.cx = -1;
    size.cy = -1;
  }
  return SbVec2s( ( short ) size.cx, ( short ) size.cy );
}

HWND
SoWin::getTopLevelWidget( void )
{
  return SoWinP::mainWidget;
}

void
SoWin::createSimpleErrorDialog( HWND const widget, const char * const dialogTitle, const char * const errorStr1, const char * const errorStr2 )
{
  // FIXME: what to do with errorStr2?
  MessageBox( widget, errorStr1, dialogTitle, MB_OK | MB_ICONERROR );  
}

HWND
SoWin::createWindow( char * title, char * className, SIZE size, HWND parent, HMENU menu )
{
  DWORD style, exstyle;
  LPVOID params = NULL;

  style = WS_OVERLAPPEDWINDOW;
  exstyle = NULL;

  HWND widget = CreateWindowEx( exstyle,
                              className,
                               title,
                                style,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                size.cx,
                                size.cy,
                                parent,
                                menu,
                                SoWin::getInstance( ),
                                params );
  return widget;
}

SbBool
SoWin::nextEvent( int appContext, MSG * msg )
{
  return GetMessage( msg, NULL, 0, 0 );
}

HWND
SoWin::getShellWidget( HWND hwnd )
{
  LONG style;
  HWND parent = hwnd;
  
  do {
    hwnd = parent;
    style = GetWindowLong( hwnd, GWL_STYLE );
    if ( style & WS_OVERLAPPEDWINDOW ) break;
    parent = GetParent( hwnd );
  } while( IsWindow( parent ) );
  
  return hwnd;
}

void
SoWin::setInstance( HINSTANCE instance )
{
  SoWinP::Instance = instance;
}

HINSTANCE
SoWin::getInstance( void )
{
  return SoWinP::Instance;
}

void
SoWin::errorHandlerCB( const SoError * error, void * data )
{
  SbString debugstring = error->getDebugString( );

  MessageBox( SoWinP::mainWidget,
              ( LPCTSTR ) debugstring.getString( ),
              "SoError",
              MB_OK | MB_ICONERROR );
}

void
SoWin::doIdleTasks( void )
{
  SoDB::getSensorManager( )->processTimerQueue( );
  SoDB::getSensorManager( )->processDelayQueue( TRUE ); // isidle = TRUE
  SoWinP::sensorQueueChanged( NULL );
}

///////////////////////////////////////////////////////////////////
//
//  (protected)
//

void
SoWin::registerWindowClass( const char * const className )
{
  WNDCLASS windowclass;

  LPCTSTR icon = MAKEINTRESOURCE( IDI_APPLICATION );
 LPCTSTR cursor = MAKEINTRESOURCE( IDC_ARROW );
  HBRUSH brush = ( HBRUSH ) GetSysColorBrush( COLOR_BTNFACE );

  windowclass.lpszClassName = className;
  windowclass.hInstance = SoWin::getInstance( );
  windowclass.lpfnWndProc = SoWin::eventHandler;
  windowclass.style = CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon( SoWin::getInstance( ), icon );
  windowclass.hCursor = LoadCursor( SoWin::getInstance( ), cursor );
  windowclass.hbrBackground = brush;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass( & windowclass );
}

void
SoWin::unRegisterWindowClass( const char * const className )
{
  UnregisterClass( className, SoWin::getInstance( ) );
}

LRESULT CALLBACK
SoWin::eventHandler( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  LRESULT retval = 0;
  BOOL handled = FALSE;
  
  switch( message )
    {
    case WM_SIZE:
      if( ! SoWinP::useParentEventHandler ) {
        retval =  SoWinP::onSize( window, message, wparam, lparam );
        handled = TRUE;
      }
      break;

    case WM_DESTROY:
      if ( ! SoWinP::useParentEventHandler ) {
        retval = SoWinP::onDestroy( window, message, wparam, lparam );
        handled = TRUE;
      }
      break;
            
    case WM_QUIT:
      retval = SoWinP::onQuit( window, message, wparam, lparam );
      handled = TRUE;
      break;
    }

  if ( SoWinP::useParentEventHandler && SoWinP::parentEventHandler )
    return SoWinP::parentEventHandler( window, message, wparam, lparam );

  if ( handled )
    return retval;
    
  return DefWindowProc( window, message, wparam, lparam );
}

///////////////////////////////////////////////////////////////////
//
//  (private)
//

void CALLBACK
SoWinP::timerSensorCB( HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWin::timerSensorCB", "called" );
#endif // SOWIN_DEBUG
  SoDB::getSensorManager( )->processTimerQueue( );
  SoWinP::sensorQueueChanged( NULL );
}

void CALLBACK
SoWinP::delaySensorCB( HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWin::delaySensorCB", "called" );
#endif // SOWIN_DEBUG
  SoDB::getSensorManager( )->processDelayQueue( FALSE );
  SoWinP::sensorQueueChanged( NULL );
}

void CALLBACK
SoWinP::idleSensorCB( HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWin::idleSensorCB", "called" );
#endif // SOWIN_DEBUG
  SoWin::doIdleTasks( );
}

void
SoWinP::sensorQueueChanged( void * cbdata )
{
  SoSensorManager * sensormanager = SoDB::getSensorManager( );

  SbTime timevalue;
  if ( sensormanager->isTimerSensorPending( timevalue ) ) {
    SbTime interval = timevalue - SbTime::getTimeOfDay( );

    if ( interval.getValue( ) < 0.0 ) interval.setValue( 0.0 );
    if ( SoWinP::timerSensorActive ) KillTimer( NULL, SoWinP::timerSensorId );
    
    SoWinP::timerSensorId = SetTimer( SoWinP::mainWidget,
                                      1,
                                      interval.getMsecValue( ),
                                      SoWinP::timerSensorCB );

    SoWinP::timerSensorActive = TRUE;
  }
  else if ( SoWinP::timerSensorActive ) {
    KillTimer( NULL, SoWinP::timerSensorId );
    SoWinP::timerSensorActive = FALSE;
  }

  if ( sensormanager->isDelaySensorPending( ) ) {
        
    if ( ! SoWinP::idleSensorActive ) {
      SoWinP::idleSensorId = SetTimer( SoWinP::mainWidget,
                                       2,
                                       0,
                                       SoWinP::idleSensorCB );
      SoWinP::idleSensorActive = TRUE;
    }

    if ( ! SoWinP::delaySensorActive ) {
      unsigned long timeout = SoDB::getDelaySensorTimeout( ).getMsecValue( );
      SoWinP::delaySensorId = SetTimer( SoWinP::mainWidget,
                                        3,
                                        timeout,
                                        SoWinP::delaySensorCB );
      SoWinP::delaySensorActive = TRUE;
    }
  }
  else {
                             
    if ( SoWinP::idleSensorActive ) {
      KillTimer( NULL, SoWinP::idleSensorId );
      SoWinP::idleSensorActive = FALSE;
    }

    if ( SoWinP::delaySensorActive ) {
      KillTimer( NULL, SoWinP::delaySensorId );
      SoWinP::delaySensorActive = FALSE;
    }
  }
}

LRESULT
SoWinP::onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  EnumChildWindows( window, SoWinP::sizeChildProc, lparam );
  return 0;
}

BOOL CALLBACK
SoWinP::sizeChildProc( HWND window, LPARAM lparam )
{
  if ( GetParent( window ) == SoWin::getTopLevelWidget( ) ) {
    UINT flags = SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW;
    SetWindowPos( window, NULL, 0, 0, LOWORD( lparam ), HIWORD( lparam ), flags );
  }
  return TRUE;
}

LRESULT
SoWinP::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  PostQuitMessage( 0 );
  return 0;
}
 
LRESULT
SoWinP::onQuit( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  if ( SoWinP::idleSensorActive ) KillTimer( NULL, SoWinP::idleSensorId );
  if ( SoWinP::timerSensorActive ) KillTimer( NULL, SoWinP::timerSensorId );
  if ( SoWinP::delaySensorActive ) KillTimer( NULL, SoWinP::delaySensorId );

  SoWin::unRegisterWindowClass( SoWinP::className );

  return 0;
}
