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

static const char rcsid[] =
"$Id$";

#include <Inventor/errors/SoDebugError.h>

#include <sowindefs.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/widgets/SoWinThumbWheel.h>
#include <Inventor/Win/widgets/SoWinViewerPrefSheet.h>


SoWinViewerPrefSheet::SoWinViewerPrefSheet( void )
{
  this->constructor( );
}

SoWinViewerPrefSheet::~SoWinViewerPrefSheet( void )
{
    this->destroy( );
}

void SoWinViewerPrefSheet::create( HWND parent )
{
  this->createMainWidget( parent );
  this->createSeekWidgets( parent );
  this->createZoomWidgets( parent );
  this->createClippingWidgets( parent );
  this->createSpinnWidgets( parent );
}

void SoWinViewerPrefSheet::destroy( void )
{
  this->destroyMainWidget( );
  this->destroySeekWidgets( );
  this->destroyZoomWidgets( );
  this->destroyClippingWidgets( );
  this->destroySpinnWidgets( );
}

void SoWinViewerPrefSheet::show( SbBool show )
{
  ShowWindow( this->mainWidget, ( show ? SW_SHOW : SW_HIDE ) );
}

void SoWinViewerPrefSheet::setTitle( const char * title )
{
  SetWindowText( this->mainWidget, title );
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//  (protected)
//

void SoWinViewerPrefSheet::constructor( void )
{
  this->className = "SoWinViewerPrefSheet";
  this->mainWidget = NULL;
}

void SoWinViewerPrefSheet::createMainWidget( HWND parent )
{
  WNDCLASS windowclass;
  LPCTSTR icon = MAKEINTRESOURCE( IDI_APPLICATION );
  HMENU menu = NULL;
  HBRUSH brush = ( HBRUSH ) GetSysColorBrush( COLOR_BTNFACE );
  LPSTR wndclassname = ( LPSTR ) this->className;

  windowclass.lpszClassName = wndclassname;
  windowclass.hInstance = SoWin::getInstance( );
  windowclass.lpfnWndProc = SoWinViewerPrefSheet::processEvent;
  windowclass.style = CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon( NULL, icon );
  windowclass.hCursor = NULL;
  windowclass.hbrBackground = brush;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass( & windowclass );

  DWORD style = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE; // WS_OVERLAPETWINDOW

  this->mainWidget = CreateWindowEx( WS_EX_TOPMOST, // NULL
                                     wndclassname,
                                     wndclassname,
                                     style,
                                     CW_USEDEFAULT,
                                     CW_USEDEFAULT,
                                     400,
                                     400,
                                     parent,
                                     menu,
                                     SoWin::getInstance( ),
                                     this );
  
  assert( IsWindow( this->mainWidget ) );
}

void SoWinViewerPrefSheet::destroyMainWidget( void )
{
  DestroyWindow( this->mainWidget );
  UnregisterClass( this->className, SoWin::getInstance( ) );
}

void SoWinViewerPrefSheet::createSeekWidgets( HWND parent )
{

}

void SoWinViewerPrefSheet::destroySeekWidgets( void )
{

}

void SoWinViewerPrefSheet::createZoomWidgets( HWND parent )
{

}

void SoWinViewerPrefSheet::destroyZoomWidgets( void )
{

}

void SoWinViewerPrefSheet::createClippingWidgets( HWND parent )
{

}

void SoWinViewerPrefSheet::destroyClippingWidgets( void )
{

}

void SoWinViewerPrefSheet::createSpinnWidgets( HWND parent )
{

}

void SoWinViewerPrefSheet::destroySpinnWidgets( void )
{

}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//  (Event handlers)
//

LRESULT CALLBACK
SoWinViewerPrefSheet::processEvent( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  if ( message == WM_CREATE ) {
    CREATESTRUCT * createstruct;
    createstruct = ( CREATESTRUCT * ) lparam;
    SetWindowLong( window, 0, (LONG) ( createstruct->lpCreateParams ) );
    
    SoWinViewerPrefSheet * object = ( SoWinViewerPrefSheet * )( createstruct->lpCreateParams );
    return object->onCreate( window, message, wparam, lparam );
  }

  SoWinViewerPrefSheet * object = ( SoWinViewerPrefSheet * ) GetWindowLong( window, 0 );

  if ( object && IsWindow( object->mainWidget ) ) {

    switch ( message )
      {
      case WM_DESTROY:
        return object->onDestroy( window, message, wparam, lparam );
      }
  }
  return DefWindowProc( window, message, wparam, lparam );
}


LRESULT SoWinViewerPrefSheet::onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  return 0;
}

LRESULT SoWinViewerPrefSheet::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  this->destroy( );
  return 0;
}
