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

  int y = 10;
  this->lineHeight = this->getFontHeight( this->mainWidget ) + 10;
    
  y = this->createSeekWidgets( this->mainWidget, 0, y );
  y = this->createZoomWidgets( this->mainWidget, 0, y );
  y = this->createClippingWidgets( this->mainWidget, 0, y );
  y = this->createSpinnWidgets( this->mainWidget, 0, y );

  y += 10;
  
  RECT rect;
  int height;

  GetClientRect( this->mainWidget, & rect );
  height = rect.bottom;
  
  GetWindowRect( this->mainWidget, & rect );

  MoveWindow( this->mainWidget,
              rect.left,
              rect.top,
              ( rect.right - rect.left ), // FIXME no adjustment to width yet
              ( rect.bottom - rect.top ) + ( y - height ),
              TRUE );
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
  this->lineHeight = 0;
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

  this->mainWidget = CreateWindowEx( NULL,//WS_EX_TOPMOST,
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

int SoWinViewerPrefSheet::createSeekWidgets( HWND parent, int x, int y )
{
  assert( IsWindow( parent ) );
  
  this->seekWidgets[0] = this->createLabelWidget( parent, "Seek animation time:", 10, y );
  this->seekWidgets[1] = this->createEditWidget( parent, 64, 185, y );
  this->seekWidgets[2] = this->createLabelWidget( parent, "seconds", 255, y );
  y += this->lineHeight;
  
  this->seekWidgets[3] = this->createLabelWidget( parent, "Seek to:", 10, y );
  this->seekWidgets[4] = this->createRadioWidget( parent, "point", 100, y );
  this->seekWidgets[5] = this->createRadioWidget( parent, "object", 200, y );
  y += this->lineHeight;

  this->seekWidgets[6] = this->createLabelWidget( parent, "Seek distance:", 10, y );
  this->seekDistWheel = new SoWinThumbWheel( SoWinThumbWheel::Horizontal, parent, 150, y );
  this->seekWidgets[7] = this->createEditWidget( parent, 64, 280, y );
  y += this->lineHeight;

  this->seekWidgets[8] = this->createRadioWidget( parent, "percentage", 10, y );
  this->seekWidgets[9] = this->createRadioWidget( parent, "absolute", 110, y );
  y += this->lineHeight;
  
  return y;
}

void SoWinViewerPrefSheet::destroySeekWidgets( void )
{
  for ( int i = 0; i < 10; i++ )
    if ( IsWindow( this->seekWidgets[i] ) )
      DestroyWindow( this->seekWidgets[i] );
  //if ( this->seekDistWheel )
  //delete this->seekDistWheel;
}

int SoWinViewerPrefSheet::createZoomWidgets( HWND parent, int x, int y )
{
  assert( IsWindow( parent ) );

  this->zoomWidgets[0] = this->createLabelWidget( parent, "Camera zoom:", 10, y );
  this->zoomWidgets[1] = this->createSliderWidget( parent, 118, 150, y );
  this->zoomWidgets[2] = this->createEditWidget( parent, 64, 280, y );
  y += this->lineHeight;

  this->zoomWidgets[3] = this->createLabelWidget( parent, "Zoom slider ranges from:", 10, y );
  this->zoomWidgets[4] = this->createEditWidget( parent, 64, 185, y );
  this->zoomWidgets[5] = this->createLabelWidget( parent, "to:", 255, y );
  this->zoomWidgets[6] = this->createEditWidget( parent, 64, 280, y );
  y += this->lineHeight;
    
  return y;
}

void SoWinViewerPrefSheet::destroyZoomWidgets( void )
{
  for ( int i = 0; i < 7; i++ )
    if ( IsWindow( this->zoomWidgets[i] ) )
      DestroyWindow( this->zoomWidgets[i] );
}

int SoWinViewerPrefSheet::createClippingWidgets( HWND parent, int x, int y )
{
  assert( IsWindow( parent ) );

  this->clippingWidgets[0] = this->createCheckWidget( parent, "Auto clipping planes", 10, y );
  y += this->lineHeight;

  this->clippingWidgets[1] = this->createLabelWidget( parent, "Near plane:", 10, y );
  this->nearPlaneWheel = new SoWinThumbWheel( SoWinThumbWheel::Horizontal, parent, 150, y );
  this->clippingWidgets[2] = this->createEditWidget( parent, 64, 280, y );
  y += this->lineHeight;
  
  this->clippingWidgets[3] = this->createLabelWidget( parent, "Far plane:", 10, y );
  this->farPlaneWheel = new SoWinThumbWheel( SoWinThumbWheel::Horizontal, parent, 150, y );
  this->clippingWidgets[4] = this->createEditWidget( parent, 64, 280, y );
  y += this->lineHeight;
  
  return y;
}

void SoWinViewerPrefSheet::destroyClippingWidgets( void )
{
  for ( int i = 0; i < 5; i++ )
    if ( IsWindow( this->clippingWidgets[i] ) )
      DestroyWindow( this->clippingWidgets[i] );
  // delete nearPlaneWheel;
  // delete farPlaneWheel;
}

int SoWinViewerPrefSheet::createSpinnWidgets( HWND parent, int x, int y )
{
  assert( IsWindow( parent ) );

  this->spinnWidgets[0] = this->createCheckWidget( parent, "Enable spinn animation", 10, y );
  y += this->lineHeight;

  this->spinnWidgets[1] = this->createCheckWidget( parent, "Show point of rotation axes", 10, y );
  y += this->lineHeight;
  
  this->spinnWidgets[2] = this->createLabelWidget( parent, "Axes size:", 10, y );
  this->axesSizeWheel = new SoWinThumbWheel( SoWinThumbWheel::Horizontal, parent, 150, y );
  this->spinnWidgets[3] = this->createEditWidget( parent, 64, 280, y );
  y += this->lineHeight;
  
  
  return y;
}

void SoWinViewerPrefSheet::destroySpinnWidgets( void )
{
  for ( int i = 0; i < 4; i++ )
    if ( IsWindow( this->spinnWidgets[i] ) )
      DestroyWindow( this->spinnWidgets[i] );
  // delete axisSizeWheel;
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
  SetActiveWindow( window );
  SetFocus( window );
  ReleaseCapture( );
  return 0;
}

LRESULT SoWinViewerPrefSheet::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  this->destroy( );
  return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
//
//  (private)
//

HWND SoWinViewerPrefSheet::createLabelWidget( HWND parent, const char * text, int x, int y )
{
  assert( IsWindow( parent ) );
  SIZE textSize = this->getTextSize( parent, text ); // FIXME: assumes the same font as parent
	HWND hwnd = CreateWindowEx( NULL,
                              "STATIC",
		                          ( text ? text : "" ),
		                          WS_VISIBLE | WS_CHILD | SS_LEFT,
		                          x, y,
		                          textSize.cx, textSize.cy,
		                          parent,
		                          NULL,
		                          SoWin::getInstance( ),
		                          NULL );
	assert( IsWindow( hwnd ) );
	return hwnd;  
}

HWND SoWinViewerPrefSheet::createEditWidget( HWND parent, int width, int x, int y )
{
  assert( IsWindow( parent ) );
	HWND hwnd = CreateWindowEx( WS_EX_CLIENTEDGE,
                              "EDIT",
		                          "",
                              WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,// | ES_NUMBER,
		                          x, y,
		                          width, this->getFontHeight( parent ) + 4,
		                          parent,
		                          NULL,
		                          SoWin::getInstance( ),
		                          NULL );
	assert( IsWindow( hwnd ) );
	return hwnd;  
}

HWND SoWinViewerPrefSheet::createRadioWidget( HWND parent, const char * text, int x, int y )
{
  assert( IsWindow( parent ) );
  SIZE textSize = this->getTextSize( parent, text ); // FIXME: assumes the same font as parent  
	HWND hwnd = CreateWindowEx( NULL,
                              "BUTTON",
		                          ( text ? text : "" ),
                              WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON | BS_LEFT,
		                          x, y,
		                          30 + textSize.cx, textSize.cy,
		                          parent,
		                          NULL,
		                          SoWin::getInstance( ),
		                          NULL );
	assert( IsWindow( hwnd ) );
	return hwnd;  
}

HWND SoWinViewerPrefSheet::createSliderWidget( HWND parent, int width, int x, int y )
{
  assert( IsWindow( parent ) );
	HWND hwnd = CreateWindowEx( NULL, //WS_EX_CLIENTEDGE
                              "SCROLLBAR",
                              "",
                              WS_CHILD | WS_VISIBLE | SBS_HORZ,
		                          x, y,
                              width, this->getFontHeight( parent ) + 2,
                              parent,
                              NULL,
                              SoWin::getInstance( ),
                              NULL );
	assert( IsWindow( hwnd ) );
	return hwnd;  
}

HWND SoWinViewerPrefSheet::createCheckWidget( HWND parent, const char * text, int x, int y )
{
  assert( IsWindow( parent ) );
  SIZE textSize = this->getTextSize( parent, text ); // FIXME: assumes the same font as parent  
	HWND hwnd = CreateWindowEx( NULL,
                              "BUTTON",
		                          ( text ? text : "" ),
                              WS_VISIBLE | WS_CHILD | BS_CHECKBOX | BS_LEFT,
		                          x, y,
		                          30 + textSize.cx, textSize.cy,
		                          parent,
		                          NULL,
		                          SoWin::getInstance( ),
		                          NULL );
	assert( IsWindow( hwnd ) );
	return hwnd;  
}

SIZE SoWinViewerPrefSheet::getTextSize( HWND window, const char * text )
{
  assert( IsWindow( window ) );
  
	int len = strlen( text );
	HDC hdc = GetDC( window );

	SIZE size;
	GetTextExtentPoint( hdc, text, len, & size );

  return size;
}

int SoWinViewerPrefSheet::getFontHeight( HWND window )
{
  return this->getTextSize( window, "Ig" ).cy;
}
