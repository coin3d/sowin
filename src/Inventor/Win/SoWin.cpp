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

// *************************************************************************

HINSTANCE SoWin::Instance = NULL;
HWND SoWin::mainWidget = NULL;
char * SoWin::appName = NULL;
char * SoWin::className = NULL;
SbBool SoWin::fullScreen = FALSE;
int SoWin::timerSensorId = 0;
SbBool SoWin::timerSensorActive = FALSE;
int SoWin::delaySensorId = 0;
SbBool SoWin::delaySensorActive = FALSE;
int SoWin::idleSensorId = 0;
SbBool SoWin::idleSensorActive = FALSE;
SbList< MessageHook * > * SoWin::messageHookList = NULL;

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
    SoWin::appName = strcpy( new char [ strlen( appName ) + 1 ], appName );
  if ( className )
    SoWin::className = strcpy( new char [ strlen( className ) + 1 ], className );

  SoWin::registerWindowClass( className );
	
  RECT rect = { 0, 0, SoWin_DefaultWidth, SoWin_DefaultHeight };

  HWND toplevel = SoWin::createWindow( ( char * ) appName, ( char * ) className, rect, NULL );
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

  SoDB::getSensorManager( )->setChangedCallback( SoWin::sensorQueueChanged, NULL );
  if ( IsWindow( topLevelWidget ) ) 
    SoWin::mainWidget = topLevelWidget;

  SoWin::messageHookList = new SbList< MessageHook * >;
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
    else if ( SoWin::idleSensorActive )
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

void
SoWin::doIdleTasks( void )
{
  SoDB::getSensorManager( )->processDelayQueue( TRUE ); // isidle = TRUE
  SoWin::sensorQueueChanged( NULL );
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
SoWin::hide(HWND const widget)
{
  ShowWindow( widget, SW_HIDE );
}

void
SoWin::setWidgetSize( HWND widget, const SbVec2s size )
{
  SIZE old_size;
  HDC hdc = GetDC( SoWin::mainWidget );

  SetWindowExtEx( hdc, size[ 0 ], size[ 1 ], & old_size );
} 

SbVec2s
SoWin::getWidgetSize( HWND widget )
{
  SIZE size;
  HDC hdc = GetDC( SoWin::mainWidget );

  if ( ! GetWindowExtEx( hdc, & size ) )
    {
      size.cx = -1;
      size.cy = -1;
    }
  return SbVec2s( ( short ) size.cx, ( short ) size.cy );
}

HWND
SoWin::getTopLevelWidget( void )
{
  return SoWin::mainWidget;
}

void
SoWin::createSimpleErrorDialog( HWND const widget, const char * const dialogTitle, const char * const errorStr1, const char * const errorStr2 )
{
  // FIXME: what to do with errorStr2?
  MessageBox( widget, errorStr1, dialogTitle, MB_OK | MB_ICONERROR );  
}

HWND
SoWin::createWindow( char * title, char * className, RECT rect, HWND parent, HMENU menu )
{
  DWORD style, exstyle;
  LPVOID params = NULL;

  if( SoWin::fullScreen ) {
    style = WS_POPUP;
    exstyle = WS_EX_TOPMOST;
  }
  else {
    style = WS_OVERLAPPEDWINDOW;
    exstyle = NULL;
  }

  SoWin::mainWidget = CreateWindowEx( exstyle,
		                                  className,
	                                    title,
                                      style,
                                      rect.left,
                                      rect.top,
                                      rect.right - rect.left,
                                      rect.bottom - rect.top,
                                      parent,
                                      menu,
                                      SoWin::Instance,
                                      params );

  return SoWin::mainWidget;
}

void
SoWin::terminate( long terminateSyncTime )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}

SbBool
SoWin::PreTranslateMessage( MSG * msg )
{
  // FIXME: not implemented
  SOWIN_STUB( );
  return FALSE;
}

SbBool
SoWin::nextEvent(int appContext, MSG * msg)
{
  // FIXME: not implemented
  return GetMessage( msg, NULL, 0, 0 );
}

int
SoWin::getAppContext( void )
{
  // FIXME: not implemented
  SOWIN_STUB( );
  return 0;
}

int *
SoWin::getDisplay( void )
{
  // FIXME: not implemented
  SOWIN_STUB( );
  return NULL;
}

HWND
SoWin::getShellWidget( HWND hwnd )
{
  assert( IsWindow( hwnd ) );

  // FIXME: ???

  HWND parent = NULL;
  HWND ancestor = NULL;
    
  parent = GetParent( hwnd );

  while ( parent )
    {
      ancestor = parent;
      parent = GetParent( ancestor );
    }

  return ancestor;
}

void
SoWin::getPopupArgs( int * display, int screen, char ** args, int * n )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}

void
SoWin::addColormapToShell( HWND widget, HWND shell )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}

LRESULT
SoWin::isInventorMessage( HWND hwnd,
                          UINT message,
                          WPARAM wParam,
                          LPARAM lParam )
{
  // FIXME: not implemented
  SOWIN_STUB( );
  return 0;
}

char *
SoWin::encodeString( char *string )
{
  // FIXME: not implemented
  SOWIN_STUB( );
  return NULL;
}

char *
SoWin::decodeString( char * wstring )
{
  // FIXME: not implemented
  SOWIN_STUB( );
  return NULL;
}

void
SoWin::setInstance( HINSTANCE instance )
{
  SoWin::Instance = instance;
}

HINSTANCE
SoWin::getInstance( void )
{
  return SoWin::Instance;
}

void
SoWin::errorHandlerCB( const SoError * error, void * data )
{
  SbString debugstring = error->getDebugString( );

  MessageBox( SoWin::mainWidget,
              ( LPCTSTR ) debugstring.getString( ),
              "SoError",
              MB_OK | MB_ICONERROR );
}

void
SoWin::addMessageHook( HWND hwnd, UINT message )
{
  MessageHook * hook = new MessageHook;
  hook->hWnd = hwnd;
  hook->message = message;

  SoWin::messageHookList->append( hook );
}

void
SoWin::removeMessageHook( HWND hwnd, UINT message )
{
  // FIXME: not implemented
}

void
SoWin::addExtensionEventHandler( HWND window,
                                 int extensionEventType,
                                 SoWinEventHandler * callbackproc,
                                 void * data )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}

void
SoWin::removeExtensionEventHandler( HWND window,
                                    int extensionEventType,
                                    SoWinEventHandler * callbackproc, 
                                    void * data )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}

ATOM
SoWin::registerClass( WNDCLASS * wndClass, char * className )
{
  // FIXME: not implemented
  return RegisterClass( wndClass );
}

SbBool
SoWin::getClassInfo( HINSTANCE dll,
                     const char * name,
                     char * className,
                     WNDCLASS * classInfo )
{
  // FIXME: not implemented
  SOWIN_STUB( );
  return FALSE;
}

void
SoWin::unregisterProcessClasses( void )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}


HINSTANCE
SoWin::getResDllHandle( void )
{
  // FIXME: not implemented
  SOWIN_STUB( );
  return NULL;
}

void
SoWin::setPrevInstance( HINSTANCE instance )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}

void
SoWin::setCmdLine( LPSTR cmdLine )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}

void
SoWin::setCmdShow( int cmdShow )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}

SoWinEventHandler *
SoWin::getEventHandler( void )
{
  // FIXME: not implemented
  SOWIN_STUB( );
  return NULL;
}

void
SoWin::forwardQueryPalette( HWND window )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}

void
SoWin::forwardPaletteChanged( HWND window )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}

SbBool
SoWin::handleCtl3DMessage( void )
{
  // FIXME: not implemented
  SOWIN_STUB( );
  return FALSE;
}

void
SoWin::setHandleCtl3DMessage( SbBool n )
{
  // FIXME: not implemented
  SOWIN_STUB( );
}

void
SoWin::Ctl3dColorChange( void )
{
  // FIXME: not implemented
  SOWIN_STUB( );
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
  windowclass.hInstance = SoWin::Instance;
  windowclass.lpfnWndProc = SoWin::windowProc;
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
SoWin::windowProc( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  SoWin::onAny( window, message, wparam, lparam );

  switch( message )
    {
    case WM_SIZE:
      return SoWin::onSize( window, message, wparam, lparam );

    case WM_DESTROY:
      return SoWin::onDestroy( window, message, wparam, lparam );
            
    case WM_QUIT:
      return SoWin::onQuit( window, message, wparam, lparam );
    }
  return DefWindowProc( window, message, wparam, lparam );
}

///////////////////////////////////////////////////////////////////
//
//  (private)
//

void CALLBACK
SoWin::timerSensorCB( HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWin::timerSensorCB", "called" );
#endif // SOWIN_DEBUG
  SoDB::getSensorManager( )->processTimerQueue( );
  SoWin::sensorQueueChanged( NULL );
}

void CALLBACK
SoWin::delaySensorCB( HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWin::delaySensorCB", "called" );
#endif // SOWIN_DEBUG
  SoDB::getSensorManager( )->processDelayQueue( FALSE );
  SoWin::sensorQueueChanged( NULL );
}

void CALLBACK
SoWin::idleSensorCB( HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWin::idleSensorCB", "called" );
#endif // SOWIN_DEBUG
  SoWin::doIdleTasks( );
}

void
SoWin::sensorQueueChanged( void * cbdata )
{
  SoSensorManager * sensormanager = SoDB::getSensorManager( );

  SbTime timevalue;
  if ( sensormanager->isTimerSensorPending( timevalue ) ) {
    SbTime interval = timevalue - SbTime::getTimeOfDay( );

    if ( interval.getValue( ) < 0.0 ) interval.setValue( 0.0 );
    if ( SoWin::timerSensorActive ) KillTimer( NULL, SoWin::timerSensorId );
    
    SoWin::timerSensorId = SetTimer( SoWin::mainWidget,//NULL,
                                     1,//0,
                                     interval.getMsecValue( ),
                                     SoWin::timerSensorCB );

    SoWin::timerSensorActive = TRUE;
  }
  else if ( SoWin::timerSensorActive ) {
    KillTimer( NULL, SoWin::timerSensorId );
    SoWin::timerSensorActive = FALSE;
  }

  if ( sensormanager->isDelaySensorPending( ) ) {
        
    if ( ! SoWin::idleSensorActive ) {
      SoWin::idleSensorId = SetTimer( SoWin::mainWidget,//NULL,
                                      2,//0,
                                      0,
                                      SoWin::idleSensorCB );
      SoWin::idleSensorActive = TRUE;
    }

    if ( ! SoWin::delaySensorActive ) {
      unsigned long timeout = SoDB::getDelaySensorTimeout( ).getMsecValue( );
      SoWin::delaySensorId = SetTimer( SoWin::mainWidget,//NULL,
                                       3,//0,
                                       timeout,
                                       SoWin::delaySensorCB );
      SoWin::delaySensorActive = TRUE;
    }
  }
  else {
                             
    if ( SoWin::idleSensorActive ) {
      KillTimer( NULL, SoWin::idleSensorId );
      SoWin::idleSensorActive = FALSE;
    }

    if ( SoWin::delaySensorActive ) {
      KillTimer( NULL, SoWin::delaySensorId );
      SoWin::delaySensorActive = FALSE;
    }
  }
}

LRESULT
SoWin::onAny( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  // Let windows with messagehooks get the message
  // FIXME: is this really needed (seems that all they need is W_SIZE)?
  /*
  BOOL messageHandeled = FALSE;
  
  if ( messageHookList ) {
    int length = messageHookList->getLength( );
    MessageHook * const * hookList = messageHookList->getArrayPtr( );
    for ( int i = 0; i < length; i++ )
      if ( hookList[ i ]->message == message ) {
        UpdateWindow( hookList[ i ]->hWnd );
        messageHandeled = TRUE;
      }
  }
  */
  return 0;
}

LRESULT
SoWin::onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
	// On resizing the mainWidget, resize all child windows too
 
  if ( messageHookList ) {
    int length = messageHookList->getLength( );
		MessageHook * hook;
    for ( int i = 0; i < length; i++ ) {
			hook = ( MessageHook * )( * messageHookList )[i];
      if ( hook->message == message ) { // WM_SIZE
        MoveWindow( hook->hWnd,
                    0,
                    0,
                    LOWORD( lparam ),
                    HIWORD( lparam ),
                    FALSE );
      }
		}
  }
	
	InvalidateRect( window, NULL, TRUE );
	
  return 0;
}

LRESULT
SoWin::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  PostQuitMessage( 0 );
  return 0;
}
 
LRESULT
SoWin::onQuit( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  delete SoWin::messageHookList;  // FIXME: remove hooks first

  if ( SoWin::idleSensorActive ) KillTimer( NULL, SoWin::idleSensorId );
  if ( SoWin::timerSensorActive ) KillTimer( NULL, SoWin::timerSensorId );
  if ( SoWin::delaySensorActive ) KillTimer( NULL, SoWin::delaySensorId );

  SoWin::unRegisterWindowClass( SoWin::className );

  return 0;
}










