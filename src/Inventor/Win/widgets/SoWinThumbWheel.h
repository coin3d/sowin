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

#ifndef SOWIN_THUMBWHEEL_H
#define SOWIN_THUMBWHEEL_H


#include <Inventor/Win/SoWinBasic.h>
//#include <sowindefs.h>

class SoAnyThumbWheel;
class SoWinFullViewer;

typedef void thumbWheelCB( SoWinFullViewer * viewer, void ** data );

// *************************************************************************

class SoWinThumbWheel
{

public:
    enum Orientation { Horizontal, Vertical };
    enum boundaryHandling {
        CLAMP,
        MODULATE,
        ACCUMULATE
    };
    enum State { Idle, Dragging, Disabled };

    SoWinThumbWheel( HWND parent = 0, int x = 0, int y = 0, const char * name = 0 );
    SoWinThumbWheel( Orientation, HWND parent = 0, int x = 0, int y = 0, const char * name = 0 );
    ~SoWinThumbWheel(void);

    void setOrientation( Orientation );
    Orientation orientation(void) const;

    void setValue( float value );
    float value( void ) const;

    void setEnabled( bool enable );
    bool isEnabled( void ) const;

    void setRangeBoundaryHandling( boundaryHandling handling );
    boundaryHandling getRangeBoundaryHandling( void ) const;

    HWND getWidget( void );
    SIZE sizeHint( void ) const;
    int width( void );
    int height( void );
    void move( int x, int y );
    void registerCallback( thumbWheelCB * func );

protected:

    LRESULT CALLBACK onCreate( HWND window,
                               UINT message,
                               WPARAM wparam,
                               LPARAM lparam );

    LRESULT CALLBACK onSize( HWND window,
                             UINT message,
                             WPARAM wparam,
                             LPARAM lparam );

    LRESULT CALLBACK onPaint( HWND window,
                              UINT message,
                              WPARAM wparam,
                              LPARAM lparam );

    LRESULT CALLBACK onLButtonDown( HWND window,
                                    UINT message,
                                    WPARAM wparam,
                                    LPARAM lparam );

    LRESULT CALLBACK onLButtonUp( HWND window,
                                  UINT message,
                                  WPARAM wparam,
                                  LPARAM lparam );

    LRESULT CALLBACK onMouseMove( HWND window,
                                  UINT message,
                                  WPARAM wparam,
                                  LPARAM lparam );

    LRESULT CALLBACK onDestroy( HWND window,
                                UINT message,
                                WPARAM wparam,
                                LPARAM lparam );

    static LRESULT CALLBACK windowProc( HWND window,
                                        UINT message,
		 					            WPARAM wparam,
                                        LPARAM lparam );

private:
    void constructor( Orientation );
    HWND buildWidget( HWND parent, RECT rect );
    void initWheel( int diameter, int width );
    HBITMAP createDIB( int width, int height, int bpp, void ** bits );
    void BlitBitmap( HBITMAP bitmap, HDC dc, int x,int y, int width, int height ) const;
    void drawShadePanel( HDC hdc, int x, int y, int width, int height, int border, SbBool elevated );
    void drawPlainRect( HDC hdc, int x, int y, int width, int height, COLORREF color );

    Orientation orient;
    State state;
    float wheelValue, tempWheelValue;
    int mouseDownPos, mouseLastPos;

    SoAnyThumbWheel * wheel;
    HBITMAP * pixmaps;
    int numPixmaps;
    int currentPixmap;

    HWND windowHandle;
    RECT rect;

    thumbWheelCB * viewerCB;
}; // class SoWinThumbWheel

// *************************************************************************

#endif // ! SOWIN_THUMBWHEEL_H
