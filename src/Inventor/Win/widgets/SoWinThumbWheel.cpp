/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
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

static const char rcsid[] =
  "$Id$";

#include <math.h>
#include <assert.h>
#include <stdio.h>

#include <Inventor/SbBasic.h>

#include <sowindefs.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/widgets/SoAnyThumbWheel.h>
#include <Inventor/Win/widgets/SoWinThumbWheel.h>

// *************************************************************************

static const int SHADEBORDERWIDTH = 2;

SoWinThumbWheel::SoWinThumbWheel( HWND parent, int x, int y, const char * name )
{
    RECT rect = { x, y, sizeHint( ).cx, sizeHint( ).cy };
    this->constructor( SoWinThumbWheel::Vertical );
    this->buildWidget( parent, rect );
} // SoWinThumbWheel()

SoWinThumbWheel::SoWinThumbWheel( Orientation orientation, HWND parent, int x, int y, const char * name )
{
    RECT rect = { x, y, sizeHint( ).cx, sizeHint( ).cy };
    this->constructor( orientation );
    this->buildWidget( parent, rect );
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

SIZE SoWinThumbWheel::sizeHint(void) const
{
    const int length = 88;
    int thick = 24;
    SIZE size;

    if ( this->orient == SoWinThumbWheel::Horizontal ) {
        size.cx = length;
        size.cy = thick;
        return size;
    } else {
        size.cx = thick;
        size.cy = length;
        return size;
    }
} // sizeHint()

HWND SoWinThumbWheel::getWidget( void )
{
    return this->windowHandle;
}

void SoWinThumbWheel::setOrientation( Orientation orientation )
{
  this->orient = orientation;
  UpdateWindow( this->windowHandle );
} // setOrientation()

SoWinThumbWheel::Orientation SoWinThumbWheel::orientation( void ) const
{
    return this->orient;
}

LRESULT CALLBACK SoWinThumbWheel::onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
    return 0;
}

LRESULT CALLBACK SoWinThumbWheel::onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
    return 0;
}

LRESULT CALLBACK SoWinThumbWheel::onPaint( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint( window, & ps );
    int w, d;
    if ( this->orient == SoWinThumbWheel::Vertical ) {
        w = this->width( ) - 2*SHADEBORDERWIDTH - 6;
        d = this->height( ) - 2*SHADEBORDERWIDTH - 12;
    } else {
        w = this->height( ) - 2*SHADEBORDERWIDTH - 6;
        d = this->width( ) - 2*SHADEBORDERWIDTH - 12;
    }

  // Handle resizing to too small dimensions gracefully.
    if ( ( d <= 0 ) || ( w <= 0 ) ) return 0;

    this->initWheel( d, w );

    int pixmap = this->wheel->GetBitmapForValue( this->tempWheelValue,
        ( this->state == SoWinThumbWheel::Disabled ) ?
        SoAnyThumbWheel::DISABLED : SoAnyThumbWheel::ENABLED );


    RECT wheelrect = { SHADEBORDERWIDTH, SHADEBORDERWIDTH,
                     this->width( ) - 2*SHADEBORDERWIDTH,
                     this->height( ) - 2*SHADEBORDERWIDTH };
/*
  qDrawShadePanel( &p, 0, 0, this->width( ), this->height( ),
                   g, FALSE, SHADEBORDERWIDTH, NULL );
*/
    if ( this->orient == Vertical ) {
        wheelrect.top = wheelrect.top + 5;
        wheelrect.bottom = wheelrect.bottom - 5;
        wheelrect.left = wheelrect.left + 2;
        wheelrect.right = wheelrect.right - 2;
    } else {
        wheelrect.top = wheelrect.top + 2;
        wheelrect.bottom = wheelrect.bottom - 2;
        wheelrect.left = wheelrect.left + 5;
        wheelrect.right = wheelrect.right - 5;
    }
/* 
  qDrawPlainRect( &p, wheelrect.left(), wheelrect.top(), wheelrect.width(),
                  wheelrect.height(), QColor( 0, 0, 0 ), 1 );
*/
    wheelrect.top = wheelrect.top + 1;
    wheelrect.bottom = wheelrect.bottom - 1;
    wheelrect.left = wheelrect.left + 1;
    wheelrect.right = wheelrect.right - 1;
  // wheelrect is now wheel-only

    if ( this->orient == Vertical )
        this->BlitBitmap( this->pixmaps[pixmap], hdc, 0, 0, w, d );
    else
        this->BlitBitmap( this->pixmaps[pixmap], hdc, 0, 0, d, w );

    this->currentPixmap = pixmap;

    EndPaint( window, & ps );
    return 0;
}

LRESULT CALLBACK SoWinThumbWheel::onLButtonDown( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
    SetCapture( window );
    if ( this->state != SoWinThumbWheel::Idle )
        return 0;

    RECT wheel;
    if ( this->orient == Vertical ) {
        wheel.left =  SHADEBORDERWIDTH + 3;
        wheel.top = SHADEBORDERWIDTH + 6;
        wheel.right = this->width( ) - SHADEBORDERWIDTH - 3;
        wheel.bottom = this->height( ) - SHADEBORDERWIDTH - 6;
    } else {
        wheel.left = SHADEBORDERWIDTH + 6;
        wheel.top = SHADEBORDERWIDTH + 3;
        wheel.right = this->width( ) - SHADEBORDERWIDTH - 6;
        wheel.bottom = this->height( ) - SHADEBORDERWIDTH - 3;
    }

/*  if ( ! wheel.contains( event->pos( ) ) )
    return 0;*/

    this->state = SoWinThumbWheel::Dragging;

    int yPos = HIWORD(lparam);
    int xPos = LOWORD(lparam);

    if ( this->orient == SoWinThumbWheel::Vertical )
        this->mouseDownPos = yPos - SHADEBORDERWIDTH - 6;
    else
        this->mouseDownPos = xPos - SHADEBORDERWIDTH - 6;

    this->mouseLastPos = this->mouseDownPos;
    return 0;
}

LRESULT CALLBACK SoWinThumbWheel::onLButtonUp( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
    ReleaseCapture( );
    if ( this->state != SoWinThumbWheel::Dragging )
        return 0;

    this->wheelValue = this->tempWheelValue;
    this->mouseLastPos = this->mouseDownPos;
    this->state = SoWinThumbWheel::Idle;
    return 0;
}

LRESULT CALLBACK SoWinThumbWheel::onMouseMove( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
    if ( this->state != SoWinThumbWheel::Dragging )
        return 0;

    int yPos = HIWORD(lparam);
    int xPos = LOWORD(lparam);

    if ( this->orient == SoWinThumbWheel::Vertical )
        this->mouseLastPos = yPos - SHADEBORDERWIDTH - 6;
    else
        this->mouseLastPos = xPos - SHADEBORDERWIDTH - 6;
 
    this->tempWheelValue = this->wheel->CalculateValue( this->wheelValue,
        this->mouseDownPos, this->mouseLastPos - this->mouseDownPos );

    UpdateWindow( this->windowHandle );
    return 0;
}
   
LRESULT CALLBACK SoWinThumbWheel::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
    return 0;
}

LRESULT CALLBACK SoWinThumbWheel::windowProc( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
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

            case WM_DESTROY:
                return object->onDestroy( window, message, wparam, lparam );

            case WM_LBUTTONDOWN:
                return object->onLButtonDown( window, message, wparam, lparam );

            case WM_LBUTTONUP:
                return object->onLButtonUp( window, message, wparam, lparam );

            case WM_MOUSEMOVE:
                return object->onMouseMove( window, message, wparam, lparam );
        }
	}
	return DefWindowProc( window, message, wparam, lparam );
}

int SoWinThumbWheel::width( void )
{
    return( this->rect.right - this->rect.left );
}

int SoWinThumbWheel::height( void )
{
    return( this->rect.bottom - this->rect.top );
}

void SoWinThumbWheel::constructor( Orientation orientation )
{
  this->orient = orientation;
  this->state = SoWinThumbWheel::Idle;
  this->wheelValue = this->tempWheelValue = 0.0f;
  this->wheel = new SoAnyThumbWheel;
  this->wheel->SetWheelMotionMethod( SoAnyThumbWheel::UNIFORM );
  this->wheel->SetGraphicsByteOrder( SoAnyThumbWheel::ARGB );
  this->wheel->SetWheelRangeBoundaryHandling( SoAnyThumbWheel::MODULATE );
  this->pixmaps = NULL;
  this->numPixmaps = 0;
  this->currentPixmap = -1;
} // constructor()

HWND SoWinThumbWheel::buildWidget( HWND parent, RECT rect )
{
    WNDCLASS windowclass;
    HMENU menu = NULL;
    HWND widget = NULL;
    LPSTR wndclassname = "SoWinThumbWheel_wheelWidget";

    windowclass.lpszClassName = wndclassname;
    windowclass.hInstance = SoWin::getInstance( );
    windowclass.lpfnWndProc = this->windowProc;
    windowclass.style = NULL;
    windowclass.lpszMenuName = NULL;
    windowclass.hIcon = NULL;
    windowclass.hCursor = NULL;
    windowclass.hbrBackground = NULL;
    windowclass.cbClsExtra = 0;
    windowclass.cbWndExtra = 4;

    RegisterClass( & windowclass );

    this->windowHandle = CreateWindow(
                            wndclassname,
						    wndclassname,
						    WS_CLIPCHILDREN|
                            WS_CLIPSIBLINGS|
                            WS_CHILD,/*|
                            WS_BORDER,*/
						    rect.top,
                            rect.left,
                            rect.right,
                            rect.bottom,
						    parent,
						    menu,
						    SoWin::getInstance( ),
						    this );

    assert( IsWindow( this->windowHandle ) );

    //SoWin::addMessageHook( this->windowHandle, WM_SIZE );

    return this->windowHandle;
}

void SoWinThumbWheel::initWheel( int diameter, int width )
{
    int d, w;
    this->wheel->GetWheelSize( d, w );
    if ( d == diameter && w == width ) return;

    this->wheel->SetWheelSize( diameter, width );

    int pwidth = width;
    int pheight = diameter;
    if ( this->orient == Horizontal ) {
        pwidth = diameter;
        pheight = width;
    }

    if ( this->pixmaps != NULL ) {
        for ( int i = 0; i < this->numPixmaps; i++ ) {
            //delete this->pixmaps[i]->bmBits
            delete this->pixmaps[i];
        }
        delete [] this->pixmaps;
    }

    this->numPixmaps = this->wheel->BitmapsRequired( );
    void * bits = NULL;

    for ( int i = 0; i < this->numPixmaps; i++ ) {
        this->pixmaps[i] = this->createDIB( pwidth, pheight, 32, bits );
        this->wheel->DrawBitmap( i, bits, ( this->orient == Vertical ) ?
            SoAnyThumbWheel::VERTICAL : SoAnyThumbWheel::HORIZONTAL );
    }
} // initWheel()

// *************************************************************************

void SoWinThumbWheel::setEnabled( bool enable )
{
    if ( enable )
        this->state = SoWinThumbWheel::Idle;
    else
        this->state = SoWinThumbWheel::Disabled;
    UpdateWindow( this->windowHandle );
} // setEnabled()

bool SoWinThumbWheel::isEnabled( void ) const
{
    return ( this->state != SoWinThumbWheel::Disabled );
} // isEnabled()

void SoWinThumbWheel::setValue( float value )
{
    this->wheelValue = this->tempWheelValue = value;
    this->mouseDownPos = this->mouseLastPos;
    UpdateWindow( this->windowHandle );
} // setValue()

// *************************************************************************

void SoWinThumbWheel::setRangeBoundaryHandling( boundaryHandling handling )
{
    switch ( handling ) {
        case CLAMP:
            this->wheel->SetWheelRangeBoundaryHandling( SoAnyThumbWheel::CLAMP );
            break;
        case MODULATE:
            this->wheel->SetWheelRangeBoundaryHandling( SoAnyThumbWheel::MODULATE );
            break;
        case ACCUMULATE:
            this->wheel->SetWheelRangeBoundaryHandling( SoAnyThumbWheel::ACCUMULATE );
            break;
        default:
            assert( 0 && "impossible" );
    }
} // setRangeBoundaryHandling()

// *************************************************************************

SoWinThumbWheel::boundaryHandling SoWinThumbWheel::getRangeBoundaryHandling( void ) const
{
    switch ( this->wheel->GetWheelRangeBoundaryHandling( ) ) {
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


HBITMAP SoWinThumbWheel::createDIB( int width, int height, int bpp, void * bits ) // 16||24||32 bpp
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
	bitmap = CreateDIBSection( hdc, format, flag, ( void ** ) & bits, NULL, 0 );

	HeapFree( heap, 0, format );
	DeleteDC( hdc );

    return bitmap;
}

void SoWinThumbWheel::BlitBitmap( HBITMAP bitmap, HDC dc, int x,int y, int width, int height ) const {
	HDC memorydc = CreateCompatibleDC( dc );
	HBITMAP oldBitmap = ( HBITMAP ) SelectObject( memorydc, bitmap );
	BitBlt( dc, x, y, width, height, memorydc, 0, 0, SRCCOPY );
    SelectObject( memorydc, oldBitmap );
    DeleteDC( memorydc );
}
