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

#ifndef  SOWIN_VIEWERPREFSHEET_H
#define  SOWIN_VIEWERPREFSHEET_H

class SoWinThumbWheel;

class SOWIN_DLL_API SoWinViewerPrefSheet {
  
public:
  SoWinViewerPrefSheet( void );
  ~SoWinViewerPrefSheet( void );
  void create( HWND parent = NULL );
  void destroy( void );
  void show( SbBool show );
  void setTitle( const char * title );
  
protected:
  void constructor( void );

  void createMainWidget( HWND parent);
  void destroyMainWidget( void );

  int createSeekWidgets( HWND parent, int x, int y );
  void destroySeekWidgets( void );

  int createZoomWidgets( HWND parent, int x, int y );
  void destroyZoomWidgets( void );

  int createClippingWidgets( HWND parent, int x, int y );
  void destroyClippingWidgets( void );

  int createSpinnWidgets( HWND parent, int x, int y );
  void destroySpinnWidgets( void );

  // Event handlers

  static LRESULT CALLBACK processEvent( HWND window,
                                        UINT message,
                                        WPARAM wparam,
                                        LPARAM lparam );

  LRESULT onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  LRESULT onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  
private:
  HWND createLabelWidget( HWND parent, const char * text = NULL, int x = 0, int y = 0 );
  HWND createEditWidget( HWND parent, int width = 64, int x = 0, int y = 0 );
  HWND createRadioWidget( HWND parent, const char * text = NULL, int x = 0, int y = 0 );
  HWND createSliderWidget( HWND parent, int width = 64, int x = 0, int y = 0 );
  HWND createCheckWidget( HWND parent, const char * text = NULL, int x = 0, int y = 0 );

  int lineHeight;
  const char * className;
  
  HWND mainWidget;
  
  HWND seekWidgets[10];
  SoWinThumbWheel * seekDistWheel;

  HWND zoomWidgets[7];

  HWND clippingWidgets[5];
  SoWinThumbWheel * nearPlaneWheel;
  SoWinThumbWheel * farPlaneWheel;

  HWND spinnWidgets[4];
  SoWinThumbWheel * axesSizeWheel;
};

#endif  // SOWIN_VIEWERPREFSHEET_H



