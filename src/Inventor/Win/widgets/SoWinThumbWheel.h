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

#ifndef SOWIN_THUMBWHEEL_H
#define SOWIN_THUMBWHEEL_H

#include <wtypes.h>
#include <Inventor/SbBasic.h>
#include <Inventor/Win/SoWinBasic.h>

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
  ~SoWinThumbWheel( void );

  void setOrientation( Orientation );
  Orientation orientation( void ) const;

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
	void registerViewer( SoWinFullViewer * viewer );

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

  thumbWheelCB * viewerCB;
	SoWinFullViewer * viewer; // owner object pointer
}; // class SoWinThumbWheel

// *************************************************************************

#endif // ! SOWIN_THUMBWHEEL_H
