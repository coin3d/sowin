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

#ifndef SOWIN_BITMAPBUTTON_H
#define SOWIN_BITMAPBUTTON_H

#include <wtypes.h>
#include <Inventor/SbBasic.h>
#include <Inventor/Win/SoWinBasic.h>

class SoWinFullViewer;
class SbPList;

typedef void bitmapButtonCB( SoWinFullViewer * viewer, void ** data );

// *************************************************************************

class SOWIN_DLL_API SoWinBitmapButton {
public:
  SoWinBitmapButton( HWND parent,
		                 int x,
		                 int y,
		                 int width = 30,
		                 int height = 30,
		                 int depth = 0,
		                 const char * name = NULL,
										 void * bits = NULL );
	SoWinBitmapButton( HWND button );
  ~SoWinBitmapButton( void );

	void setId( long id );
	long getId( void );
	
  void setState( SbBool pushed );
  SbBool getState( void ) const;

  void setEnabled( SbBool enable );
  SbBool isEnabled( void ) const;

	void addBitmap( HBITMAP hbmp );
	void addBitmap( int width, int height, int bpp, void * src );
	void addBitmap( char ** xpm );
	HBITMAP getBitmap( int index );
	void setBitmap( int index );
	
  HWND getWidget( void );
  SIZE sizeHint( void ) const;
	
  int width( void );
  int height( void );
  void move( int x, int y );
	void move( int x, int y, int width, int height );
  void size( int width, int height );

	void show( void );
	void hide( void );
	
  void registerCallback( bitmapButtonCB * func );
	void registerViewer( SoWinFullViewer * viewer );
	
protected:

private:
  void constructor( void );
	void destructor( void );
  HWND buildWidget( HWND parent, RECT rect );
  HBITMAP createDIB( int width, int height, int bpp, void ** bits );
	HBITMAP parseXpm( char ** xpm, int dibDepth = 24 );
	int axtoi( char * str );
	
  HWND buttonWindow;
	SbPList * bitmapList;
  int depth;

  bitmapButtonCB * viewerCB;
	SoWinFullViewer * viewer; // owner object pointer
}; // class SoWinBitmapButton

// *************************************************************************

#endif // ! SOWIN_BITMAPBUTTON_H

