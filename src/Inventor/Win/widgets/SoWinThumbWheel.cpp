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

#include <Inventor/Win/widgets/SoWinThumbWheel.h>
#include <Inventor/Win/widgets/SoAnyThumbWheel.h>
#include <Inventor/Win/SoWin.h>
#include <sowindefs.h>

#include <math.h>
#include <assert.h>
#include <stdio.h>

// *************************************************************************

SoWinThumbWheel::SoWinThumbWheel( HWND parent,
                                  int x,
                                  int y,
                                  char * name )
{
  RECT rect = { x, y, x + this->sizeHint( ).cx, y + this->sizeHint( ).cy };
  this->constructor( SoWinThumbWheel::Vertical );
  this->buildWidget( parent, rect, name );
} // SoWinThumbWheel( )

SoWinThumbWheel::SoWinThumbWheel( Orientation orientation,
                                  HWND parent,
                                  int x,
                                  int y,
                                  char * name )
{
  RECT rect = { x, y, sizeHint( ).cx, sizeHint( ).cy };
    
  if ( orientation == SoWinThumbWheel::Vertical ) {
    rect.right = this->sizeHint( ).cy;
    rect.bottom = this->sizeHint( ).cx;
  }

  this->constructor( orientation );
  this->buildWidget( parent, rect, name );

	this->viewer = NULL;
	this->viewerCB = NULL;
	
} // SoWinThumbWheel()


SoWinThumbWheel::~SoWinThumbWheel( void )
{
  delete this->wheel;
  if ( this->pixmaps ) {
    for ( int i = 0; i < this->numPixmaps; i++ )
      DeleteObject( this->pixmaps[i] );
    delete [] this->pixmaps;
  }
} // ~SoWinThumbWheel()

SIZE
SoWinThumbWheel::sizeHint( void ) const
{
  const int length = 118;
  int thick = 14;
  SIZE size;

  if ( this->orient == SoWinThumbWheel::Horizontal ) {
    size.cx = length;
    size.cy = thick;
    return size;
  }
  else {
    size.cx = thick;
    size.cy = length;
    return size;
  }
} // sizeHint()

HWND
SoWinThumbWheel::getWidget( void )
{
  return this->wheelWindow;
}

void
SoWinThumbWheel::setOrientation( Orientation orientation )
{
  this->orient = orientation;
  UpdateWindow( this->wheelWindow );
} // setOrientation()

SoWinThumbWheel::Orientation
SoWinThumbWheel::orientation( void ) const
{
  return this->orient;
}

LRESULT CALLBACK
SoWinThumbWheel::onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  return 0;
}

LRESULT CALLBACK
SoWinThumbWheel::onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  return 0;
}

LRESULT CALLBACK
SoWinThumbWheel::onPaint( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint( window, & ps );

  int w, d;
  if ( this->orient == SoWinThumbWheel::Vertical ) {
    w = this->width( ) - 2;
    d = this->height( ) - 2;
  } else {
    w = this->height( ) - 2;
    d = this->width( ) - 2;
  }

  // Handle resizing to too small dimensions gracefully.
  if ( ( d <= 0 ) || ( w <= 0 ) ) return 0;

  this->initWheel( d, w );

  int pixmap = this->wheel->getBitmapForValue( this->tempWheelValue,
                                               ( this->state == SoWinThumbWheel::Disabled ) ?
                                               SoAnyThumbWheel::DISABLED : SoAnyThumbWheel::ENABLED );
	
	this->BlitBitmap( this->pixmaps[pixmap], hdc, 0, 0, this->width( ) - 2, this->height( ) - 2 );
	
  this->currentPixmap = pixmap;

  EndPaint( window, & ps );
  return 0;
}

LRESULT CALLBACK
SoWinThumbWheel::onLButtonDown( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  if ( this->state != SoWinThumbWheel::Idle )
    return 0;

	short x =  LOWORD( lparam );
	short y =  HIWORD( lparam );
	
	SetCapture( window );

  this->state = SoWinThumbWheel::Dragging;
  if ( this->orient == SoWinThumbWheel::Vertical )
    this->mouseDownPos = y;
  else
    this->mouseDownPos = x;

  this->mouseLastPos = this->mouseDownPos;
	
	assert( this->viewerCB != NULL );
	this->viewerCB( this->viewer, NULL ); // let CB know we want xxxWheelStart()

  return 0;
}

LRESULT CALLBACK
SoWinThumbWheel::onMouseMove( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  if ( this->state != SoWinThumbWheel::Dragging )
    return 0;

	short x =  LOWORD( lparam );
	short y =  HIWORD( lparam );
	
  if ( this->orient == SoWinThumbWheel::Vertical )
    this->mouseLastPos = y;
  else
    this->mouseLastPos = x;
	
  this->tempWheelValue = this->wheel->calculateValue( this->wheelValue,
                                                      this->mouseDownPos,
                                                      this->mouseLastPos - this->mouseDownPos );

  InvalidateRect( this->wheelWindow, NULL, FALSE );
	
  float * value = & this->tempWheelValue;
	assert( this->viewerCB != NULL );
  this->viewerCB( this->viewer, ( void ** ) & value );

	return 0;
}

LRESULT CALLBACK
SoWinThumbWheel::onLButtonUp( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  ReleaseCapture( );
  if ( this->state != SoWinThumbWheel::Dragging )
    return 0;

  this->wheelValue = this->tempWheelValue;
  this->mouseLastPos = this->mouseDownPos;
  this->state = SoWinThumbWheel::Idle;
	
	assert( this->viewerCB != NULL );
	this->viewerCB( this->viewer, ( void ** ) -1 ); // let CB know we want xxxWheelFinish()

  return 0;
}
   
LRESULT CALLBACK
SoWinThumbWheel::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  return 0;
}

LRESULT CALLBACK
SoWinThumbWheel::windowProc( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  if ( message == WM_CREATE ) {
    CREATESTRUCT * createstruct;
    createstruct = ( CREATESTRUCT * ) lparam;
    SetWindowLong( window, 0, (LONG) ( createstruct->lpCreateParams ) );

    SoWinThumbWheel * object = ( SoWinThumbWheel * )( createstruct->lpCreateParams );
    return object->onCreate( window, message, wparam, lparam );
  }

  SoWinThumbWheel * object = ( SoWinThumbWheel * ) GetWindowLong( window, 0 );

  if ( object && object->getWidget( ) ) {

    switch ( message )
      {
      case WM_SIZE:
        return object->onSize( window, message, wparam, lparam );

      case WM_PAINT:
        return object->onPaint( window, message, wparam, lparam );

      case WM_LBUTTONDOWN:
        return object->onLButtonDown( window, message, wparam, lparam );

      case WM_LBUTTONUP:
        return object->onLButtonUp( window, message, wparam, lparam );

      case WM_MOUSEMOVE:
        return object->onMouseMove( window, message, wparam, lparam );

      case WM_DESTROY:
        return object->onDestroy( window, message, wparam, lparam );
      }
  }
  return DefWindowProc( window, message, wparam, lparam );
}

int
SoWinThumbWheel::width( void )
{
	RECT rect;

	GetWindowRect( this->wheelWindow, & rect );

	return ( rect.right - rect.left );
	
  //return this->sizeHint( ).cx;
}

int
SoWinThumbWheel::height( void )
{
	RECT rect;
	
	GetWindowRect( this->wheelWindow, & rect );

	return ( rect.bottom - rect.top );
	
  //return this->sizeHint( ).cy;
}

void
SoWinThumbWheel::move( int x, int y )
{
	//this->move( x, y, this->width( ), this->height( ) );
	this->move( x, y, this->sizeHint( ).cx, this->sizeHint( ).cy );
}

void
SoWinThumbWheel::move( int x, int y, int width, int height )
{
	// Wheel

  MoveWindow( this->wheelWindow, x, y, width, height, TRUE );

	// Label

	char windowText[80]; // FIXME: use GetWindowTextLength
	int len = GetWindowText( this->labelWindow, windowText, 80 );

	HDC hdc = GetDC( this->labelWindow );

	SIZE textSize;
	GetTextExtentPoint( hdc, windowText, len, & textSize );
	
	// FIXME: compute correct position
	if ( this->orient == SoWinThumbWheel::Vertical )
		MoveWindow( this->labelWindow,
			          x + labelOffset.x,
			          y + this->height( ) + labelOffset.y,
			          textSize.cx + 2,
			          textSize.cy + 2,
			          TRUE );
	else
		MoveWindow( this->labelWindow,
			          x - textSize.cx + labelOffset.x,
			          y + labelOffset.y,
			          textSize.cx + 2,
			          textSize.cy + 2,
			          TRUE );
}

void
SoWinThumbWheel::show( void )
{
	ShowWindow( this->wheelWindow, SW_SHOW );
	ShowWindow( this->labelWindow, SW_SHOW );
}

void
SoWinThumbWheel::hide( void )
{
	ShowWindow( this->wheelWindow, SW_HIDE );
	ShowWindow( this->labelWindow, SW_HIDE );
}

void
SoWinThumbWheel::registerCallback( thumbWheelCB * func )
{
  this->viewerCB = func;
}

void
SoWinThumbWheel::registerViewer( SoWinFullViewer * viewer )
{
	this->viewer = viewer;
}

void
SoWinThumbWheel::constructor( Orientation orientation )
{
  this->orient = orientation;
  this->state = SoWinThumbWheel::Idle;
  this->wheelValue = this->tempWheelValue = 0.0f;
  this->wheel = new SoAnyThumbWheel;
  this->wheel->setMovement( SoAnyThumbWheel::UNIFORM );
  this->wheel->setGraphicsByteOrder( SoAnyThumbWheel::ARGB );
  this->wheel->setBoundaryHandling( SoAnyThumbWheel::MODULATE );
  this->pixmaps = NULL;
  this->numPixmaps = 0;
  this->currentPixmap = -1;
} // constructor()

HWND
SoWinThumbWheel::buildWidget( HWND parent, RECT rect, char * name )
{
  WNDCLASS windowclass;
  HMENU menu = NULL;
  HWND widget = NULL;
  //HBRUSH brush = ( HBRUSH ) GetSysColorBrush( COLOR_BTNFACE );
  LPSTR wndclassname = "SoWinThumbWheel_wheelWidget";

  windowclass.lpszClassName = wndclassname;
  windowclass.hInstance = SoWin::getInstance( );
  windowclass.lpfnWndProc = SoWinThumbWheel::windowProc;
  windowclass.style = NULL;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = NULL;
  windowclass.hCursor = NULL;
  windowclass.hbrBackground = NULL;//brush
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass( & windowclass );

  this->wheelWindow = CreateWindow(
                                    wndclassname,
                                    "ThumbWheel",
																		WS_VISIBLE |
                                    WS_CLIPCHILDREN |
                                    WS_CLIPSIBLINGS |
                                    WS_CHILD |
																		WS_BORDER,// |
                                    //WS_DLGFRAME,
                                    rect.left,
                                    rect.top,
                                    rect.right,
                                    rect.bottom,
                                    parent,
                                    menu,
                                    SoWin::getInstance( ),
                                    this );

  assert( IsWindow( this->wheelWindow ) );

	this->labelWindow = createLabel( parent, rect.right, rect.bottom, name );
	this->setLabelOffset( 0, 0 );
	
  return this->wheelWindow;
}

void
SoWinThumbWheel::initWheel( int diameter, int width )
{
  int d, w;
  this->wheel->getSize( d, w );
  if ( d == diameter && w == width ) return;

  this->wheel->setSize( diameter, width );

  int pwidth = width;
  int pheight = diameter;
  if ( this->orient == Horizontal ) {
    pwidth = diameter;
    pheight = width;
  }

  if ( this->pixmaps != NULL ) {
    for ( int i = 0; i < this->numPixmaps; i++ ) {
			DeleteObject( this->pixmaps[i] );
			this->pixmaps[i] = NULL;
    }
    delete [] this->pixmaps;
  }

  this->numPixmaps = this->wheel->getNumBitmaps( );
  void * bits = NULL;

  this->pixmaps = new HBITMAP[numPixmaps];

  for ( int i = 0; i < this->numPixmaps; i++ ) {
    this->pixmaps[i] = this->createDIB( pwidth, pheight, 32, &bits );
    this->wheel->drawBitmap( i, bits, ( this->orient == Vertical ) ?
                             SoAnyThumbWheel::VERTICAL : SoAnyThumbWheel::HORIZONTAL );
  }
} // initWheel()

// *************************************************************************

void
SoWinThumbWheel::setEnabled( bool enable )
{
  if ( enable )
    this->state = SoWinThumbWheel::Idle;
  else
    this->state = SoWinThumbWheel::Disabled;
	InvalidateRect( this->wheelWindow, NULL, FALSE );
} // setEnabled()

bool
SoWinThumbWheel::isEnabled( void ) const
{
  return ( this->state != SoWinThumbWheel::Disabled );
} // isEnabled()

void
SoWinThumbWheel::setValue( float value )
{
  this->wheelValue = this->tempWheelValue = value;
  this->mouseDownPos = this->mouseLastPos;
	InvalidateRect( this->wheelWindow, NULL, FALSE );
} // setValue()

float
SoWinThumbWheel::value( void ) const
{
  // FIXME: tempWheelValue ?
  return this->wheelValue;
}

float
SoWinThumbWheel::tmpValue( void ) const
{
  return this->tempWheelValue;
}

void
SoWinThumbWheel::setLabelText( char * text )
{
	SetWindowText( this->labelWindow, text );
	/*
	RECT rect;
	GetWindowRect( this->labelWindow, & rect );

	int len = strlen( text );

	HDC hdc = GetDC( this->labelWindow );

	SIZE size;
	GetTextExtentPoint( hdc, text, len, & size );
	
	MoveWindow( this->labelWindow, rect.left, rect.top, size.cx, size.cy, TRUE );
	*/
}

void
SoWinThumbWheel::setLabelOffset( int x, int y )
{
	this->labelOffset.x = x;
	this->labelOffset.y = y;
}

SIZE
SoWinThumbWheel::getLabelSize( void )
{
 	RECT rect;
  
	GetWindowRect( this->labelWindow, & rect );

  SIZE size = { rect.right - rect.left, rect.bottom - rect.top };

  return ( size );
}

// *************************************************************************

void
SoWinThumbWheel::setRangeBoundaryHandling( boundaryHandling handling )
{
  switch ( handling ) {
  case CLAMP:
    this->wheel->setBoundaryHandling( SoAnyThumbWheel::CLAMP );
    break;
  case MODULATE:
    this->wheel->setBoundaryHandling( SoAnyThumbWheel::MODULATE );
    break;
  case ACCUMULATE:
    this->wheel->setBoundaryHandling( SoAnyThumbWheel::ACCUMULATE );
    break;
  default:
    assert( 0 && "impossible" );
  }
} // setRangeBoundaryHandling()

// *************************************************************************

SoWinThumbWheel::boundaryHandling
SoWinThumbWheel::getRangeBoundaryHandling( void ) const
{
  switch ( this->wheel->getBoundaryHandling( ) ) {
  case SoAnyThumbWheel::CLAMP:
    return CLAMP;
  case SoAnyThumbWheel::MODULATE:
    return MODULATE;
  case SoAnyThumbWheel::ACCUMULATE:
    return ACCUMULATE;
  default:
    assert( 0 && "impossible" );
  }
  return CLAMP; // never reached
} // getRangeBoundaryHandling()

HWND
SoWinThumbWheel::createLabel( HWND parent, int x, int y, char * text )
{
	HWND hwnd = CreateWindow( "STATIC",
		                        ( text ? text : "" ),
		                        WS_VISIBLE | WS_CHILD | SS_CENTER,
		                        x, y,
		                        strlen( text ) * 8, 14, // SIZE
		                        parent,
		                        NULL,
		                        SoWin::getInstance( ),
		                        NULL );
	assert( IsWindow( hwnd ) );
	return hwnd;
}

HBITMAP
SoWinThumbWheel::createDIB( int width, int height, int bpp, void ** bits ) // 16||24||32 bpp
{
  assert( bpp > 8 );

  HBITMAP bitmap = NULL;
  HDC hdc = CreateCompatibleDC( NULL );
  int heapspace = sizeof( BITMAPINFOHEADER );

  HANDLE heap = GetProcessHeap( );
  BITMAPINFO * format = ( BITMAPINFO * ) HeapAlloc( heap, 0, heapspace );
	
  BITMAPINFOHEADER * header = ( BITMAPINFOHEADER * ) format;
  header->biSize = sizeof( BITMAPINFOHEADER );
  header->biWidth = width;
  header->biHeight = -height;
  header->biPlanes = 1;
  header->biBitCount = bpp;
  header->biCompression = BI_RGB;
  header->biSizeImage = 0;
  header->biXPelsPerMeter = 0;
  header->biYPelsPerMeter = 0;
  header->biClrUsed = 0;
  header->biClrImportant = 0;

  UINT flag = DIB_RGB_COLORS;
  bitmap = CreateDIBSection( hdc, format, flag, ( void ** ) bits, NULL, 0 );

  assert( * bits );

  HeapFree( heap, 0, format );
  DeleteDC( hdc );

  return bitmap;
}

void
SoWinThumbWheel::BlitBitmap( HBITMAP bitmap, HDC dc, int x,int y, int width, int height ) const {
  HDC memorydc = CreateCompatibleDC( dc );
  HBITMAP oldBitmap = ( HBITMAP ) SelectObject( memorydc, bitmap );
  BitBlt( dc, x, y, width, height, memorydc, 0, 0, SRCCOPY );
  SelectObject( memorydc, oldBitmap );
  DeleteDC( memorydc );
}
