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
#include <Inventor/Win/SoWinComponent.h>

// *************************************************************************

HINSTANCE SoWin::Instance = NULL;
HWND SoWin::mainWidget = NULL;
char * SoWin::appName = NULL;
char * SoWin::className = NULL;
int SoWin::timerSensorId = 0;
SbBool SoWin::timerSensorActive = FALSE;
int SoWin::delaySensorId = 0;
SbBool SoWin::delaySensorActive = FALSE;
int SoWin::idleSensorId = 0;
SbBool SoWin::idleSensorActive = FALSE;
SbList< MessageHook * > * SoWin::messageHookList = NULL;    //hook

// *************************************************************************


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
    SoWin::appName = strcpy( new char [strlen( appName ) + 1], appName );
  if ( className )
    SoWin::className = strcpy( new char [strlen( className ) + 1], className );

  SoWin::registerWindowClass( className );

  RECT rect = { 0, 0, SoWin_DefaultWidth, SoWin_DefaultHeight };  // default window size
  HWND toplevel =  SoWin::createWindow( ( char * ) appName, ( char * ) className, rect, NULL );
  SoWin::init( toplevel );
  return toplevel;
}

void
SoWin::init( HWND const topLevelWidget )
{
  SoDB::init( );
  SoNodeKit::init( );
  SoInteraction::init( );

  SoDebugError::setHandlerCallback( SoWin::errorHandlerCB, NULL );    // initialize error handeling

  SoWinObject::init();

  SoDB::getSensorManager( )->setChangedCallback( SoWin::sensorQueueChanged, NULL );
  if(topLevelWidget)
    SoWin::mainWidget = topLevelWidget;

  SoWin::messageHookList = new SbList< MessageHook * >;   // add hook
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
    WaitMessage( );
    if ( GetMessage( & msg, NULL, 0, 0 ) ) {
      TranslateMessage( & msg );
      DispatchMessage( & msg );
    } else break;
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
  SoWin::idleSensorId = 0;
  SoWin::idleSensorActive = FALSE;
  SoDB::getSensorManager( )->processDelayQueue( TRUE );
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
  HDC hdc = GetDC( mainWidget );

  SetWindowExtEx( hdc, size[0], size[1], & old_size );
} 

SbVec2s
SoWin::getWidgetSize( HWND widget )
{
  SIZE size;
  HDC hdc = GetDC(mainWidget);

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
  return SoWin::mainWidget; // FIXME: ???
}

void
SoWin::createSimpleErrorDialog( HWND const widget, const char * const dialogTitle, const char * const errorStr1, const char * const errorStr2)
{
  MessageBox( widget, errorStr1, dialogTitle, MB_OK | MB_ICONERROR );  
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

#if SOWIN_DEBUG
  _cprintf(   "%s\n", debugstring.getString( ) );
#else
  MessageBox( NULL,
              ( LPCTSTR ) debugstring.getString( ),
              "SoError",
              MB_OK | MB_ICONERROR );
#endif // SOWIN_DEBUG

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
  LPCTSTR icon,cursor;
  HBRUSH brush;

  icon = MAKEINTRESOURCE( IDI_APPLICATION );
  cursor = MAKEINTRESOURCE( IDC_ARROW );
  brush = ( HBRUSH ) GetStockObject( COLOR_BACKGROUND );

  windowclass.lpszClassName = className;
  windowclass.hInstance = SoWin::Instance;
  windowclass.lpfnWndProc = SoWin::windowProc;
  windowclass.style = /*CS_HREDRAW|CS_VREDRAW|*/CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon( NULL, icon );
  windowclass.hCursor = LoadCursor( NULL, cursor );
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

HWND
SoWin::createWindow( char * title, char * className, RECT rect, HWND parent, HMENU menu )
{
  DWORD style = WS_OVERLAPPEDWINDOW;
  LPVOID params = NULL;

  SoWin::mainWidget = CreateWindow( className,
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
  SoWin::timerSensorId = 0;
  SoWin::timerSensorActive = FALSE;
  SoDB::getSensorManager( )->processTimerQueue( );
  SoWin::sensorQueueChanged( NULL );
}

void CALLBACK
SoWin::delaySensorCB( HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWin::delaySensorCB", "called" );
#endif // SOWIN_DEBUG
  SoWin::delaySensorId = 0;
  SoWin::delaySensorActive = FALSE;
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
    
    SoWin::timerSensorId = SetTimer( NULL,
                                     0,
                                     interval.getMsecValue( ),
                                     SoWin::timerSensorCB );

    SoWin::timerSensorActive = TRUE;
  } else if ( SoWin::timerSensorActive ) {
    KillTimer( NULL, SoWin::timerSensorId );
    SoWin::timerSensorId = 0;
    SoWin::timerSensorActive = FALSE;
  }

  if ( sensormanager->isDelaySensorPending( ) ) {
        
    if ( ! SoWin::idleSensorActive ) {
      SoWin::idleSensorId = SetTimer( NULL,
                                      0,
                                      0,
                                      SoWin::idleSensorCB );
      SoWin::idleSensorActive = TRUE;
    }

    if ( ! SoWin::delaySensorActive ) {
      unsigned long timeout = SoDB::getDelaySensorTimeout( ).getMsecValue( );
      SoWin::delaySensorId = SetTimer( NULL,
                                       0,
                                       timeout,
                                       SoWin::delaySensorCB );
      SoWin::delaySensorActive = TRUE;
    }
  } else {
                             
    if ( SoWin::idleSensorActive ) {
      KillTimer( NULL, SoWin::idleSensorId );
      SoWin::idleSensorId = 0;
      SoWin::idleSensorActive = FALSE;
    }

    if ( SoWin::delaySensorActive ) {
      KillTimer( NULL, SoWin::delaySensorId );
      SoWin::delaySensorId = 0;
      SoWin::delaySensorActive = FALSE;
    }
  }
}

LRESULT
SoWin::onAny( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  BOOL messageHandeled = FALSE;

  if ( messageHookList ) {
    int length = messageHookList->getLength( );
    MessageHook * const * hookList = messageHookList->getArrayPtr( );
    for ( int i = 0; i < length; i++ )
      if ( hookList[i]->message == message ) {
        MoveWindow( hookList[i]->hWnd,
                    0,
                    0,
                    LOWORD( lparam ),
                    HIWORD( lparam ),
                    TRUE );
        messageHandeled = TRUE;
      }
  }
  return 0;
}

LRESULT
SoWin::onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  UpdateWindow( window );
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

#if 0 // FIXME: see comment at the end of SoWin.h. 20001123 mortene.
///////////////////////////////////////////////////////////////////
//
//  (globals)
//

#if SOWIN_DEBUG

void
WinDisplayLastError( void )
{
  LPSTR lpMsgBuf;
  FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                 FORMAT_MESSAGE_FROM_SYSTEM | 
                 FORMAT_MESSAGE_IGNORE_INSERTS,
                 NULL,
                 GetLastError( ),
                 MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), // Default language
                 ( LPTSTR ) & lpMsgBuf,
                 0,
                 NULL );
  MessageBox( NULL,
              ( LPCTSTR ) lpMsgBuf,
              "Error",
              MB_OK |
              MB_ICONINFORMATION );
  LocalFree( lpMsgBuf );
}

#endif // SOWIN_DEBUG

#ifndef SOWIN_INTERNAL

int WINAPI
WinMain( HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  char ** argv;
  int argc = 0;
  int i = 0;
  int retval, strsize;
  char * chrptr; // string pointer to first instance of character
  char * argstr; // string pointer to argument
  char * argptr;
  char * cmdline;

  SoWin::setInstance( instance );

  // count args
  if( cmdline = GetCommandLine( ) )  // get entire command line (including program name)
    argc++;
  while( chrptr = strchr( cmdline, ' ' ) )   // search for ' '
    {
      argc++;
      cmdline = chrptr + 1;
    }
  argv = ( char ** ) malloc( sizeof( char * ) * argc );

  // get arguments
  i = strlen( GetCommandLine( ) );
  cmdline = ( char * ) malloc( i + 1 );
  strcpy( cmdline, GetCommandLine( ) );
  cmdline[ i ] = ' ';
  cmdline[ i + 1] = '\0';

  argptr = cmdline;
  i = 0;
  while(chrptr = strchr( argptr, ' ' ) )   // search for ' '
    {
      strsize = chrptr - argptr;         // get string size
      argstr = ( char *) malloc( strsize + 1 ); 
      memcpy( argstr, argptr, strsize );
      argstr[strsize] = '\0'; // add '\0' to string
      argv[i++] = argstr; // add string to argv
      argptr = chrptr + 1;   // next argument ( + skip the ' ' )
    }
  free( cmdline );

#if SOWIN_DEBUG
  AllocConsole( );
  _cprintf( "Console open...\n" );
  for (i = 0; i < argc; i++ )
    _cprintf( "Argv[%d] = %s\n", i, argv[i] ); 
#endif  // SOWIN_DEBUG

  //retval = ivMain( argc, argv );
  ivMain( argc, argv );
  retval = 0;

#if SOWIN_DEBUG
  _cprintf( "Closing console...\n" );
  FreeConsole( );
#endif // SOWIN_DEBUG

  // free allocated memory
  for( i = 0; i < argc; i++)
    free( argv[i] );
  free( argv );

  return retval;
}

#endif // !SOWIN_INTERNAL

// Globals
#endif // tmp (?) disabled
