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
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinFullViewer.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/Win/viewers/SoAnyExaminerViewer.h>
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
  if ( IsWindow( this->mainWidget ) ) {
    SetActiveWindow( this->mainWidget );
    return;
  }

  this->x = 10;
  this->y = 10;
  
  this->createMainWidget( parent );
  this->lineHeight = this->getFontHeight( this->mainWidget ) + 10;
}

void SoWinViewerPrefSheet::size( void )
{ 
  RECT rect;
  int height;

  GetClientRect( this->mainWidget, & rect );
  height = rect.bottom;
  
  GetWindowRect( this->mainWidget, & rect );

  MoveWindow( this->mainWidget,
              rect.left,
              rect.top,
              ( rect.right - rect.left ), // FIXME no adjustment to width yet
              ( rect.bottom - rect.top ) + ( ( this->y + 10 )  - height ),
              TRUE );
}
/*
void SoWinViewerPrefSheet::init( SoWinFullViewer * viewer )
{
  this->viewer = viewer;
  this->initSeekWidgets( viewer );
  this->initZoomWidgets( viewer );
  this->initClippingWidgets( viewer );
  this->initSpinnWidgets( viewer );
}
*/
void SoWinViewerPrefSheet::destroy( void )
{
  if ( IsWindow (this->mainWidget ) )
    this->destroyMainWidget( );
  if ( this->seekViewer )
    this->destroySeekWidgets( );
  if ( this->zoomViewer )
    this->destroyZoomWidgets( );
  if ( this->clippingViewer )
    this->destroyClippingWidgets( );
  if ( this->spinnViewer )
    this->destroySpinnWidgets( );
  this->x = this->y = 0;
}

void SoWinViewerPrefSheet::show( SbBool show )
{
  // FIXME: update all widgets ( init )
  ShowWindow( this->mainWidget, ( show ? SW_SHOW : SW_HIDE ) );
}

HWND SoWinViewerPrefSheet::getWidget( void )
{
  return this->mainWidget;
}

void SoWinViewerPrefSheet::setTitle( const char * title )
{
  if ( this->mainWidget )
    SetWindowText( this->mainWidget, title );
  this->title = title;
}

void SoWinViewerPrefSheet::createSeekWidgets( SoWinFullViewer * viewer )
{
  assert( IsWindow( this->mainWidget ) );

  if ( this->seekViewer )// already created, destroy first
    return;
  
  this->seekViewer = viewer;
  
  this->seekWidgets[0] = this->createLabelWidget( this->mainWidget, "Seek animation time:", this->x, this->y );
  this->seekWidgets[1] = this->createEditWidget( this->mainWidget, 0, 64, this->x + 175, this->y );
  this->seekWidgets[2] = this->createLabelWidget( this->mainWidget, "seconds", this->x + 245, this->y );
  this->y += this->lineHeight;
  
  this->seekWidgets[3] = this->createLabelWidget( this->mainWidget, "Seek to:", this->x, this->y );
  this->seekWidgets[4] = this->createRadioWidget( this->mainWidget, 1, "point", this->x + 90, this->y );
  this->seekWidgets[5] = this->createRadioWidget( this->mainWidget, 2, "object", this->x + 190, this->y );
  this->y += this->lineHeight;

  this->seekWidgets[6] = this->createLabelWidget( this->mainWidget, "Seek distance:", this->x, this->y );
  this->seekDistWheel = new SoWinThumbWheel( SoWinThumbWheel::Horizontal, this->mainWidget, 3, this->x + 140, this->y );
  this->seekWidgets[7] = this->createEditWidget( this->mainWidget, 4, 64, this->x + 270, this->y );
  this->y += this->lineHeight;

  this->seekWidgets[8] = this->createRadioWidget( this->mainWidget, 5, "percentage", this->x, this->y );
  this->seekWidgets[9] = this->createRadioWidget( this->mainWidget, 6, "absolute", this->x + 100, this->y );
  this->y += this->lineHeight;

  this->initSeekWidgets( viewer );
}

void SoWinViewerPrefSheet::createZoomWidgets( SoWinFullViewer * viewer )
{
  assert( IsWindow( this->mainWidget ) );
  
  if ( this->zoomViewer )// already created, destroy first
    return;

  this->zoomViewer = viewer;

  this->zoomWidgets[0] = this->createLabelWidget( this->mainWidget, "Camera zoom:", this->x, this->y );
  this->zoomWidgets[1] = this->createSliderWidget( this->mainWidget, 7, 118, this->x + 140, this->y );
  this->zoomWidgets[2] = this->createEditWidget( this->mainWidget, 8, 64, this->x + 270, this->y );
  this->y += this->lineHeight;

  this->zoomWidgets[3] = this->createLabelWidget( this->mainWidget, "Zoom slider ranges from:", this->x, this->y );
  this->zoomWidgets[4] = this->createEditWidget( this->mainWidget, 9, 64, this->x + 175, this->y );
  this->zoomWidgets[5] = this->createLabelWidget( this->mainWidget, "to:", this->x + 245, this->y );
  this->zoomWidgets[6] = this->createEditWidget( this->mainWidget, 10, 64, this->x + 270, this->y );
  this->y += this->lineHeight;

  this->initZoomWidgets( viewer );
}

void SoWinViewerPrefSheet::createClippingWidgets( SoWinFullViewer * viewer )
{
  assert( IsWindow( this->mainWidget ) );
  
  if ( this->clippingViewer )// already created, destroy first
    return;

  this->clippingViewer = viewer;

  this->clippingWidgets[0] = this->createCheckWidget( this->mainWidget, 11, "Auto clipping planes", this->x, this->y );
  this->y += this->lineHeight;

  this->clippingWidgets[1] = this->createLabelWidget( this->mainWidget, "Near plane:", this->x, this->y );
  this->nearPlaneWheel = new SoWinThumbWheel( SoWinThumbWheel::Horizontal, this->mainWidget, 11, this->x + 140, this->y );
  this->clippingWidgets[2] = this->createEditWidget( this->mainWidget, 12, 64, this->x + 270, this->y );
  this->y += this->lineHeight;
  
  this->clippingWidgets[3] = this->createLabelWidget( this->mainWidget, "Far plane:", this->x, this->y );
  this->farPlaneWheel = new SoWinThumbWheel( SoWinThumbWheel::Horizontal, this->mainWidget, 13, x + 140, this->y );
  this->clippingWidgets[4] = this->createEditWidget( this->mainWidget, 14, 64, this->x + 270, this->y );
  this->y += this->lineHeight;

  this->initClippingWidgets( viewer );
}

void SoWinViewerPrefSheet::createSpinnWidgets( SoWinExaminerViewer * viewer )
{
  assert( IsWindow( this->mainWidget ) );
  
  if ( this->spinnViewer )// already created, destroy first
    return;

  this->spinnViewer = viewer;

  this->spinnWidgets[0] = this->createCheckWidget( this->mainWidget, 15, "Enable spinn animation", this->x, this->y );
  this->y += this->lineHeight;

  this->spinnWidgets[1] = this->createCheckWidget( this->mainWidget, 16, "Show point of rotation axes", this->x, this->y );
  this->y += this->lineHeight;
  
  this->spinnWidgets[2] = this->createLabelWidget( this->mainWidget, "Axes size:", this->x, this->y );
  this->axesSizeWheel = new SoWinThumbWheel( SoWinThumbWheel::Horizontal, this->mainWidget, 17, this->x + 140, this->y );
  this->spinnWidgets[3] = this->createEditWidget( this->mainWidget, 18, 64, this->x + 270, this->y );
  this->y += this->lineHeight;

  this->initSpinnWidgets( viewer );
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
  this->title = NULL;

  this->seekViewer = NULL;
  this->zoomViewer = NULL;
  this->clippingViewer = NULL;
  this->spinnViewer = NULL;  
}

void SoWinViewerPrefSheet::createMainWidget( HWND parent )
{
  WNDCLASS windowclass;
  LPCTSTR icon = MAKEINTRESOURCE( IDI_APPLICATION );
	LPCTSTR cursor = MAKEINTRESOURCE( IDC_ARROW );  
  HMENU menu = NULL;
  HBRUSH brush = ( HBRUSH ) GetSysColorBrush( COLOR_BTNFACE );
  LPSTR wndclassname = ( LPSTR ) this->className;

  windowclass.lpszClassName = wndclassname;
  windowclass.hInstance = SoWin::getInstance( );
  windowclass.lpfnWndProc = SoWinViewerPrefSheet::processEvent;
  windowclass.style = CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon( NULL, icon );
  windowclass.hCursor = LoadCursor( SoWin::getInstance( ), cursor );
  windowclass.hbrBackground = brush;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass( & windowclass );

  DWORD style = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE;// | WS_OVERLAPPEDWINDOW;

  this->mainWidget = CreateWindowEx( NULL,//WS_EX_TOPMOST,
                                     wndclassname,
                                     ( this->title ? this->title : "" ),
                                     style,
                                     CW_USEDEFAULT,
                                     CW_USEDEFAULT,
                                     370,
                                     400,
                                     parent,
                                     menu,
                                     SoWin::getInstance( ),
                                     this );
  
  assert( IsWindow( this->mainWidget ) );
}

void SoWinViewerPrefSheet::initSeekWidgets( SoWinFullViewer * viewer )
{
  char str[32];

  sprintf( str, "%.4f", viewer->getSeekTime( ) );
  SetWindowText( this->seekWidgets[1], str );

  this->setChecked( this->seekWidgets[4], viewer->isDetailSeek( ) );
  this->setChecked( this->seekWidgets[5], ! viewer->isDetailSeek( ) );

  float distance =  viewer->getSeekDistance( );
  sprintf( str, "%.4f", distance );
  SetWindowText( this->seekWidgets[7], str );
    
  this->seekDistWheel->setRangeBoundaryHandling( SoWinThumbWheel::ACCUMULATE );
  this->seekDistWheel->setValue( distance );

  this->setChecked( this->seekWidgets[8], viewer->isSeekValuePercentage( ) );
  this->setChecked( this->seekWidgets[9], ! viewer->isSeekValuePercentage( ) );
}

void SoWinViewerPrefSheet::initZoomWidgets( SoWinFullViewer * viewer )
{
  char str[32];
  float zoom = viewer->getCameraZoom( );

  this->setSliderRange( this->zoomWidgets[1],
    ( int ) viewer->zoomrange[0],
    ( int ) viewer->zoomrange[1] );

  this->setSliderValue( this->zoomWidgets[1], ( int ) zoom );

  sprintf( str, "%.4f", zoom );
  SetWindowText( this->zoomWidgets[2], str );

  sprintf( str, "%.4f",  viewer->zoomrange[0] );
  SetWindowText( this->zoomWidgets[4], str );
  
  sprintf( str, "%.4f",  viewer->zoomrange[1] );
  SetWindowText( this->zoomWidgets[6], str );
}

void SoWinViewerPrefSheet::initClippingWidgets( SoWinFullViewer * viewer )
{
  BOOL autoCl =  viewer->isAutoClipping( );
  this->setChecked( this->clippingWidgets[0], autoCl );
  
  char str[32];
  
  SoCamera * cam = viewer->getCamera( );
  if( ! cam ) return;
  
  float nearDist = cam->nearDistance.getValue( );
  float farDist = cam->farDistance.getValue( );

  this->nearPlaneWheel->setRangeBoundaryHandling( SoWinThumbWheel::ACCUMULATE );
  this->nearPlaneWheel->setValue( nearDist );
  
  sprintf( str, "%f", nearDist );
  SetWindowText( this->clippingWidgets[2], str );

  this->farPlaneWheel->setRangeBoundaryHandling( SoWinThumbWheel::ACCUMULATE );  
  this->farPlaneWheel->setValue( farDist );
  
  sprintf( str, "%f", farDist );
  SetWindowText( this->clippingWidgets[4], str );
  
  //enableClippingWidgets( autoCl ); // NB! checkbox is always enabled
  if ( autoCl ) {
    this->nearPlaneWheel->setEnabled( FALSE );
    this->farPlaneWheel->setEnabled( FALSE );
    for ( int i = 1; i < 5; i++ )
      this->setEnabled( this->clippingWidgets[i], FALSE );
  }
}

void SoWinViewerPrefSheet::initSpinnWidgets( SoWinExaminerViewer * viewer )
{
  BOOL anim = viewer->common->isAnimationEnabled( );
  this->setChecked( this->spinnWidgets[0], anim );

  BOOL visible = viewer->common->isFeedbackVisible( );
  this->setChecked( this->spinnWidgets[1], visible );

  float size = viewer->common->getFeedbackSize( );
  this->axesSizeWheel->setRangeBoundaryHandling( SoWinThumbWheel::ACCUMULATE );
  this->axesSizeWheel->setValue( size );

  char str[32];
  
  sprintf( str, "%f", size );
  SetWindowText( this->spinnWidgets[3], str );

  //enableSpinnWidgets( anim ); // NB! checkbox is always enabled
  if ( ! anim )
    setEnabled( this->spinnWidgets[1], FALSE );
  
  if ( ! ( visible && anim ) ) {
    setEnabled( this->spinnWidgets[2], FALSE );
    setEnabled( this->spinnWidgets[3], FALSE );
    this->axesSizeWheel->setEnabled( FALSE );
  }
}

void SoWinViewerPrefSheet::destroyMainWidget( void )
{
  DestroyWindow( this->mainWidget );
  UnregisterClass( this->className, SoWin::getInstance( ) );
  this->mainWidget = NULL;
}

void SoWinViewerPrefSheet::destroySeekWidgets( void )
{
  for ( int i = 0; i < 10; i++ )
    if ( IsWindow( this->seekWidgets[i] ) )
      DestroyWindow( this->seekWidgets[i] );
  //if ( this->seekDistWheel )
  //delete this->seekDistWheel;
  this->seekViewer = NULL;
}

void SoWinViewerPrefSheet::destroyZoomWidgets( void )
{
  for ( int i = 0; i < 7; i++ )
    if ( IsWindow( this->zoomWidgets[i] ) )
      DestroyWindow( this->zoomWidgets[i] );
  this->zoomViewer = NULL;
}

void SoWinViewerPrefSheet::destroyClippingWidgets( void )
{
  for ( int i = 0; i < 5; i++ )
    if ( IsWindow( this->clippingWidgets[i] ) )
      DestroyWindow( this->clippingWidgets[i] );
  // delete nearPlaneWheel;
  // delete farPlaneWheel;
  this->clippingViewer = NULL;
}

void SoWinViewerPrefSheet::destroySpinnWidgets( void )
{
  for ( int i = 0; i < 4; i++ )
    if ( IsWindow( this->spinnWidgets[i] ) )
      DestroyWindow( this->spinnWidgets[i] );
  // delete axisSizeWheel;
  this->spinnViewer = NULL;
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
      case WM_COMMAND:
        return object->onCommand( window, message, wparam, lparam );
      case WM_THUMBWHEEL:
        return object->onThumbWheel( window, message, wparam, lparam );  
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

LRESULT SoWinViewerPrefSheet::onCommand( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  return 0;
}

LRESULT SoWinViewerPrefSheet::onThumbWheel( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  //_cprintf( "WM_THUMBWHEEL: %f\n", * ( float * ) lparam );
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

HWND SoWinViewerPrefSheet::createEditWidget( HWND parent, long id, int width, int x, int y )
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
  SetWindowLong( hwnd, GWL_ID, id ); 
	return hwnd;  
}

HWND SoWinViewerPrefSheet::createRadioWidget( HWND parent, long id, const char * text, int x, int y )
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
  SetWindowLong( hwnd, GWL_ID, id );
	return hwnd;  
}

HWND SoWinViewerPrefSheet::createSliderWidget( HWND parent, long id, int width, int x, int y )
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
  SetWindowLong( hwnd, GWL_ID, id );
	return hwnd;  
}

HWND SoWinViewerPrefSheet::createCheckWidget( HWND parent, long id, const char * text, int x, int y )
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
  SetWindowLong( hwnd, GWL_ID, id );
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

// Slider funcs

void SoWinViewerPrefSheet::setSliderValue( HWND slider, int value )
{
	SCROLLINFO scrollInfo;
	ZeroMemory( & scrollInfo, sizeof( SCROLLINFO ) );
	scrollInfo.cbSize = sizeof( SCROLLINFO );
	scrollInfo.fMask = SIF_POS;
	scrollInfo.nPos = value;
	
	SetScrollInfo( slider,
		/*SB_CTL |*/
    /*( this->orient == Horizontal ) SB_HORZ : SB_VERT )*/
    SB_HORZ,
		& scrollInfo,
    TRUE ); // FIXME: redraw needed?
}

int SoWinViewerPrefSheet::getSliderValue( HWND slider )
{
	SCROLLINFO scrollInfo;
	ZeroMemory( & scrollInfo, sizeof( SCROLLINFO ) );
	scrollInfo.cbSize = sizeof( SCROLLINFO );
	scrollInfo.fMask = SIF_POS;

	GetScrollInfo( slider,
		/*SB_CTL |*/
    /*( this->orient == Horizontal ) SB_HORZ : SB_VERT )*/
    SB_HORZ,
		& scrollInfo );

	return ( scrollInfo.nPos );
}

void SoWinViewerPrefSheet::setSliderRange( HWND slider, int min, int max )
{
	SCROLLINFO scrollInfo;
	ZeroMemory( & scrollInfo, sizeof( SCROLLINFO ) );
	scrollInfo.cbSize = sizeof( SCROLLINFO );
	scrollInfo.fMask = SIF_RANGE;
	scrollInfo.nMin = min;
	scrollInfo.nMax = max;
	
	SetScrollInfo( slider, /*SB_CTL*/ 0, & scrollInfo, TRUE );
}

SIZE SoWinViewerPrefSheet::getSliderRange( HWND slider )
{
	SCROLLINFO scrollInfo;
	ZeroMemory( & scrollInfo, sizeof( SCROLLINFO ) );
	scrollInfo.cbSize = sizeof( SCROLLINFO );
	scrollInfo.fMask = SIF_RANGE;

	GetScrollInfo( slider,
		/*SB_CTL |*/
    /*( this->orient == Horizontal ) SB_HORZ : SB_VERT ),*/
    SB_HORZ,
		& scrollInfo );

  SIZE range = { scrollInfo.nMin, scrollInfo.nMax }; 
	return range;
}

void SoWinViewerPrefSheet::setChecked( HWND hwnd, BOOL check )
{  
	SendMessage( hwnd, BM_SETCHECK, ( WPARAM ) ( check ? BST_CHECKED : BST_UNCHECKED ), 0 );
}

void SoWinViewerPrefSheet::setEnabled( HWND hwnd, BOOL enable )
{
  long style = GetWindowLong( hwnd, GWL_STYLE );

	if ( enable )
		style &= ~WS_DISABLED;
	else
		style |= WS_DISABLED;

	SetWindowLong( hwnd, GWL_STYLE, style );
  //InvalidateRect( hwnd, NULL, FALSE );
  //UpdateWindow( hwnd );
}
