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

#include <windows.h>
#include <GL/gl.h>

#include <Inventor/SbVec2s.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/SoWinGLWidget.h>
#include <Inventor/Win/SoAny.h>
#include <sowindefs.h>
#include <Inventor/Win/Win32API.h>

#if SOWIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#include <conio.h>
#endif // SOWIN_DEBUG

SOWIN_OBJECT_ABSTRACT_SOURCE( SoWinGLWidget );

// The private data for the SoWinGLWidget.

class SoWinGLWidgetP {
  
public:
  
  // Constructor.
  SoWinGLWidgetP( SoWinGLWidget * o ) {
    this->owner = o;
  }

  // Destructor.
  ~SoWinGLWidgetP( ) {
  }

  void buildNormalGLWidget( HWND manager );
  void buildOverlayGLWidget( HWND manager );
  BOOL createGLContext( HWND window );

  LRESULT onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  LRESULT onPaint( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  LRESULT onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam );

  HWND managerWidget;
  HWND normalWidget;
  HWND overlayWidget;

  HGLRC ctxNormal;
  HGLRC ctxOverlay;

  HDC hdcNormal;
  HDC hdcOverlay;

  SbVec2s glSize;

  PIXELFORMATDESCRIPTOR pfdNormal;
  PIXELFORMATDESCRIPTOR pfdOverlay;
  
  SbBool drawToFrontBuffer;
  SbBool haveFocus;
  SbBool stealFocus;
  SbBool haveBorder;
  HCURSOR currentCursor;

  int glModes;
  int borderSize;

  static ATOM managerWndClassAtom;
  static ATOM glWndClassAtom;
  static int widgetCounter;

private:
  
  SoWinGLWidget * owner;
  
};

ATOM SoWinGLWidgetP::managerWndClassAtom = NULL;
ATOM SoWinGLWidgetP::glWndClassAtom = NULL;
int SoWinGLWidgetP::widgetCounter = 0;

#define PRIVATE( o ) ( o->pimpl )

///////////////////////////////////////////////////////////////////
//
//  Constructor / Destructor
//  (protected)
//

SoWinGLWidget::SoWinGLWidget( HWND parent,
                              const char * name,
                              SbBool embed,
                              int glModes,
                              SbBool build )
  : SoWinComponent( parent, name, embed )
{
  this->pimpl = new SoWinGLWidgetP( this );
  this->waitForExpose = TRUE;
  this->parent = parent;
  
  PRIVATE( this )->managerWidget = NULL;
  PRIVATE( this )->normalWidget = NULL;
  PRIVATE( this )->overlayWidget = NULL;

  PRIVATE( this )->drawToFrontBuffer = FALSE;

  PRIVATE( this )->ctxNormal = NULL;
  PRIVATE( this )->ctxOverlay = NULL;

  PRIVATE( this )->hdcNormal = NULL;
  PRIVATE( this )->hdcOverlay = NULL;

  PRIVATE( this )->glModes = glModes;
  PRIVATE( this )->borderSize = 0;
  PRIVATE( this )->haveBorder = FALSE;
  PRIVATE( this )->currentCursor = NULL;

  PRIVATE( this )->haveFocus = FALSE;
  PRIVATE( this )->stealFocus = FALSE;

  this->setClassName( "SoWinGLWidget" );
	
  if ( ! build ) return;
	
  PRIVATE( this )->managerWidget = this->buildWidget( parent );
  this->setBaseWidget( PRIVATE( this )->managerWidget );
}

SoWinGLWidget::~SoWinGLWidget( void )
{
  if ( IsWindow( PRIVATE( this )->managerWidget ) )
    Win32::DestroyWindow( PRIVATE( this )->managerWidget );
  if ( IsWindow( PRIVATE( this )->normalWidget ) )  
    Win32::DestroyWindow( PRIVATE( this )->normalWidget );
  if ( IsWindow( PRIVATE( this )->overlayWidget ) ) 
    Win32::DestroyWindow( PRIVATE( this )->overlayWidget );
  SoWinGLWidgetP::widgetCounter--;
  if ( SoWinGLWidgetP::widgetCounter <= 0 ) {
    Win32::UnregisterClass( "Manager Widget", SoWin::getInstance( ) );
    SoWinGLWidgetP::managerWndClassAtom = NULL;
    Win32::UnregisterClass( "GL Widget", SoWin::getInstance( ) );
    SoWinGLWidgetP::glWndClassAtom = NULL;
  }
  delete this->pimpl;
}

///////////////////////////////////////////////////////////////////
//
//  (public)
//

HWND
SoWinGLWidget::getNormalWindow( void )
{
  return PRIVATE( this )->normalWidget;
}

HWND
SoWinGLWidget::getOverlayWindow( void )
{
  // FIXME: overlay not supported. mariusbu 20010719.
  return PRIVATE( this )->overlayWidget;
}

HWND
SoWinGLWidget::getNormalWidget( void )
{
  return PRIVATE( this )->normalWidget;
}

HWND
SoWinGLWidget::getOverlayWidget( void )
{
  return PRIVATE( this )->overlayWidget;
}

HDC
SoWinGLWidget::getNormalDC( void )
{
  assert( PRIVATE( this )->hdcNormal != NULL );
  return PRIVATE( this )->hdcNormal;
}

HDC
SoWinGLWidget::getOverlayDC( void )
{
  assert( PRIVATE( this )->hdcOverlay != NULL );
  return PRIVATE( this )->hdcOverlay;
}

HGLRC
SoWinGLWidget::getNormalContext( void )
{
  assert( PRIVATE( this )->ctxNormal != NULL );
  return PRIVATE( this )->ctxNormal;
}

HGLRC
SoWinGLWidget::getOverlayContext( void )
{
  return PRIVATE( this )->ctxOverlay;
}

void
SoWinGLWidget::setStealFocus( SbBool doStealFocus )
{
  PRIVATE( this )->stealFocus = doStealFocus;
}

void
SoWinGLWidget::setNormalVisual( PIXELFORMATDESCRIPTOR * vis )
{
  assert( vis != NULL );
  assert( PRIVATE( this )->hdcNormal != NULL );

  memcpy( ( & PRIVATE( this )->pfdNormal ), vis, sizeof( PIXELFORMATDESCRIPTOR ) );

  int format = ChoosePixelFormat( PRIVATE( this )->hdcNormal, vis );
  this->setPixelFormat( format );
}

PIXELFORMATDESCRIPTOR *
SoWinGLWidget::getNormalVisual( void )
{
  return ( & PRIVATE( this )->pfdNormal );
}

void
SoWinGLWidget::setOverlayVisual( PIXELFORMATDESCRIPTOR * vis )
{
  // FIXME: overlay not supported. mariusbu 20010719.
  assert( vis != NULL );
  assert( PRIVATE( this )->hdcNormal != NULL );
  
  memcpy( ( & PRIVATE( this )->pfdOverlay ), vis, sizeof( PIXELFORMATDESCRIPTOR ) );
  
  int format = ChoosePixelFormat( PRIVATE( this )->hdcOverlay, vis );
  this->setPixelFormat( format );
}

PIXELFORMATDESCRIPTOR *
SoWinGLWidget::getOverlayVisual( void )
{
  return ( & PRIVATE( this )->pfdOverlay );
}

void
SoWinGLWidget::setPixelFormat( int format )
{
  BOOL ok = SetPixelFormat( PRIVATE( this )->hdcNormal, format, & PRIVATE( this )->pfdNormal );
  assert( ok );
}

int
SoWinGLWidget::getPixelFormat( void )
{
  return GetPixelFormat( PRIVATE( this )->hdcNormal );
}

void
SoWinGLWidget::setDoubleBuffer( SbBool set )
{
  if ( set ) {
    PRIVATE( this )->glModes |= SO_GL_DOUBLE;
  }
  else {
    PRIVATE( this )->glModes &= ~SO_GL_DOUBLE;
  }
  Win32::DestroyWindow( this->getNormalWidget( ) );
  PRIVATE( this )->buildNormalGLWidget( PRIVATE( this )->managerWidget );
}

SbBool
SoWinGLWidget::isDoubleBuffer( void )
{
  return ( PRIVATE( this )->glModes & SO_GL_DOUBLE ? TRUE : FALSE );
}

void
SoWinGLWidget::setBorder( SbBool set )
{
  PRIVATE( this )->haveBorder = TRUE;
  // FIXME: Win32::SetWindowLong() or paint border? mariusbu 20010719.
}

int
SoWinGLWidget::getBorderSize( void )
{
  return PRIVATE( this )->borderSize;
}

SbBool
SoWinGLWidget::isBorder( void ) const
{
  return PRIVATE( this )->haveBorder;
}

void
SoWinGLWidget::setDrawToFrontBufferEnable( SbBool enable )
{
  PRIVATE( this )->drawToFrontBuffer = enable;
}

SbBool
SoWinGLWidget::isDrawToFrontBufferEnable( void ) const
{
  return PRIVATE( this )->drawToFrontBuffer;
}

/*!
  Enables or disables quad buffer stereo.
*/
void
SoWinGLWidget::setQuadBufferStereo( const SbBool enable )
{
  if ( enable ) {
    PRIVATE( this )->glModes |= SO_GL_STEREO;
  }
  else {
    PRIVATE( this )->glModes &= ~SO_GL_STEREO;
  }
  Win32::DestroyWindow( this->getNormalWidget( ) );
  PRIVATE( this )->buildNormalGLWidget( PRIVATE( this )->managerWidget );
}

/*!
  Returns \c TRUE if quad buffer stereo is enabled for this widget.
*/
SbBool
SoWinGLWidget::isQuadBufferStereo( void ) const
{
  return ( PRIVATE( this )->glModes & SO_GL_STEREO ? TRUE : FALSE );
}

void
SoWinGLWidget::setCursor( HCURSOR newCursor )
{
  assert( newCursor != NULL );
  PRIVATE( this )->currentCursor = newCursor;
  SetCursor( newCursor );
}

HCURSOR
SoWinGLWidget::getCursor( void )
{
  return PRIVATE( this )->currentCursor;
}

SbBool
SoWinGLWidget::hasOverlayGLArea( void )
{
  return ( IsWindow( this->getOverlayWidget( ) ) ? TRUE : FALSE );
}

SbBool
SoWinGLWidget::hasNormalGLArea( void )
{
  return ( IsWindow( this->getNormalWidget( ) ) ? TRUE : FALSE );
}

SbBool
SoWinGLWidget::glScheduleRedraw( void )
{
  return FALSE;
}

///////////////////////////////////////////////////////////////////
//
//  (protected)
//

LRESULT CALLBACK
SoWinGLWidget::mgrWidgetProc( HWND window,
                              UINT message,
                              WPARAM wparam,
                              LPARAM lparam )
{
  // does nothing
  return DefWindowProc( window, message, wparam, lparam );
}

LRESULT CALLBACK
SoWinGLWidget::glWidgetProc( HWND window,
                             UINT message,
                             WPARAM wparam,
                             LPARAM lparam )
{
  if ( message == WM_CREATE ) {
    CREATESTRUCT * createstruct = ( CREATESTRUCT * ) lparam;
		
    ( void ) Win32::SetWindowLong( window, GWL_USERDATA, ( LONG ) ( createstruct->lpCreateParams ) );
		
    SoWinGLWidget * object = ( SoWinGLWidget * )( createstruct->lpCreateParams );
    return PRIVATE( object )->onCreate( window, message, wparam, lparam );
  }

  SoWinGLWidget * object = ( SoWinGLWidget * ) Win32::GetWindowLong( window, GWL_USERDATA );

  if ( object && window == object->getNormalWidget( ) ) {

    MSG msg;
    POINT pt = { LOWORD( lparam ), HIWORD( lparam ) };
    msg.hwnd = window;
    msg.lParam = lparam;
    msg.message = message;
    msg.pt = pt;
    msg.time = GetTickCount( );
    msg.wParam = wparam;
    
    // Get keystrokes
    if( ( ( ! PRIVATE( object )->haveFocus ) && PRIVATE( object )->stealFocus ) ||
        ( message == WM_LBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_RBUTTONDOWN ) ) {
      PRIVATE( object )->haveFocus = ( BOOL ) SetFocus( window );
    }

    object->processEvent( & msg );
    
    switch ( message ) {

    case WM_PAINT:
      object->waitForExpose = FALSE; // flip flag on first expose
      return PRIVATE( object )->onPaint( window, message, wparam, lparam );

    case WM_DESTROY:
      return PRIVATE( object )->onDestroy( window, message, wparam, lparam );

    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
      (void)SetCapture( window );
      return 0;

    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
      (void)ReleaseCapture( );
      return 0;

    case WM_KILLFOCUS:
      PRIVATE( object )->haveFocus = FALSE;
      return 0;

    case WM_SETCURSOR:
      (void)SetCursor( object->getCursor( ) );
      return 0;
 
    }
  }
  return DefWindowProc( window, message, wparam, lparam );
}

void
SoWinGLWidget::redraw( void )
{
  // virtual - does nothing
}

void
SoWinGLWidget::redrawOverlay( void )
{
  // virtual - does nothing
}

void
SoWinGLWidget::processEvent( MSG * msg )
{
  // virtual - does nothing
  // FIXME: move some event processing here. mariusbu 20010719.
}

void
SoWinGLWidget::initGraphic( void )
{
  glLockNormal( );
  glEnable( GL_DEPTH_TEST );
  glUnlockNormal( );
}

void
SoWinGLWidget::initOverlayGraphic( void )
{
  // virtual - does nothing
}

void
SoWinGLWidget::sizeChanged( const SbVec2s newSize )
{
  // virtual - does nothing
}

void
SoWinGLWidget::widgetChanged( HWND newWidget )
{
  // virtual
  // called whenever the widget is changed (i.e. at initialization
  // or after switching from single->double buffer)
}

void
SoWinGLWidget::setGLSize( SbVec2s newSize )
{
  if ( newSize == PRIVATE( this )->glSize ) return;
  PRIVATE( this )->glSize = newSize;

  UINT flags = SWP_NOMOVE | SWP_NOZORDER;
  Win32::SetWindowPos( PRIVATE( this )->managerWidget, NULL, 0, 0,
                         newSize[0], newSize[1], flags );
  
  flags = SWP_NOMOVE | SWP_NOZORDER;
  if ( PRIVATE( this )->haveBorder ) {
    Win32::SetWindowPos( PRIVATE( this )->normalWidget,
                         NULL,
                         PRIVATE( this )->borderSize,
                         PRIVATE( this )->borderSize,
                         newSize[0] - 2 * PRIVATE( this )->borderSize,
                         newSize[1] - 2 * PRIVATE( this )->borderSize,
                         flags );
  }
  else {
    Win32::SetWindowPos( PRIVATE( this )->normalWidget, NULL, 0, 0,
                         newSize[0], newSize[1], flags );
  }
}

SbVec2s
SoWinGLWidget::getGLSize( void ) const
{
  return PRIVATE( this )->glSize;
}

float
SoWinGLWidget::getGLAspectRatio( void ) const
{
  return ( float ) PRIVATE( this )->glSize[0] / ( float ) PRIVATE( this )->glSize[1];
}

LRESULT // FIXME: used by SoWinRenderArea
SoWinGLWidget::eventHandler( HWND hwnd,
                             UINT message,
                             WPARAM wParam,
                             LPARAM lParam )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
  return 0;
}

void
SoWinGLWidget::setStereoBuffer( SbBool set )
{
  this->setQuadBufferStereo( set );
}

SbBool
SoWinGLWidget::isStereoBuffer( void )
{
  return this->isQuadBufferStereo( );
}

SbBool
SoWinGLWidget::isRGBMode( void )
{
  return ( PRIVATE( this )->glModes & SO_GL_RGB );
}

int
SoWinGLWidget::getDisplayListShareGroup( HGLRC ctx )
{
  return 0; // FIXME: nothing done yet!
}

HWND
SoWinGLWidget::buildWidget( HWND parent )
{
  // Build managerWidget
  // Used only to draw borders and handle resize

  SoWinGLWidgetP::widgetCounter++;

  HMENU menu = NULL;

  if ( ! SoWinGLWidgetP::managerWndClassAtom ) {

    WNDCLASS windowclass;
    
    windowclass.lpszClassName = "Manager Widget";
    windowclass.hInstance = SoWin::getInstance( );
    windowclass.lpfnWndProc = SoWinGLWidget::mgrWidgetProc;
    windowclass.style = NULL;
    windowclass.lpszMenuName = NULL;
    windowclass.hIcon = NULL;
    windowclass.hCursor = NULL;
    windowclass.hbrBackground =  ( HBRUSH ) GetSysColorBrush( COLOR_3DSHADOW );//NULL;
    windowclass.cbClsExtra = 0;
    windowclass.cbWndExtra = 4;

    SoWinGLWidgetP::managerWndClassAtom = Win32::RegisterClass( & windowclass );
    
  }

  RECT rect;
	assert ( IsWindow( parent ) );
  Win32::GetClientRect( parent, & rect );

  HWND managerwidget = CreateWindow( "Manager Widget",
                                     this->getTitle( ),
		                                 WS_VISIBLE |
		                                 WS_CLIPSIBLINGS |
		                                 WS_CLIPCHILDREN |
                                     WS_CHILD,
                                     rect.left,
                                     rect.top,
                                     rect.right,
                                     rect.bottom,
                                     parent,
                                     menu,
                                     SoWin::getInstance( ),
                                     this );

  assert( IsWindow( managerwidget ) );

  PRIVATE( this )->managerWidget = managerwidget;

  if ( PRIVATE( this )->glModes & SO_GL_OVERLAY )
    PRIVATE( this )->buildOverlayGLWidget( managerwidget );

  PRIVATE( this )->buildNormalGLWidget( managerwidget );

  this->waitForExpose = TRUE;
  
  return managerwidget;
}

HWND
SoWinGLWidget::getManagerWidget( void )
{
  return PRIVATE( this )->managerWidget;
}
/*
HWND
SoWinGLWidget::getGlxMgrWidget( void )
{
  return this->getManagerWidget( );
}
*/
HWND
SoWinGLWidget::getGLWidget( void )
{
	// FIXME: return manager ? mariusbu 20010803.
  return this->getNormalWindow( );
}

SbBool
SoWinGLWidget::makeNormalCurrent( void )
{
  // FIXME: wglRealizeLayerPalette() ? mariusbu 20010801
  return ( wglMakeCurrent( ( HDC ) PRIVATE( this )->hdcNormal, PRIVATE( this )->ctxNormal ) );
}

SbBool
SoWinGLWidget::swapNormalBuffers( void )
{
  // FIXME: not in use..? 20010803 mortene.

  if ( ! ( PRIVATE( this )->glModes & SO_GL_DOUBLE ) )
    return FALSE;
  
  return ( SwapBuffers( ( HDC ) PRIVATE( this )->hdcNormal ) );
}

SbBool
SoWinGLWidget::swapOverlayBuffers( void )
{
  return ( wglSwapLayerBuffers( ( HDC ) PRIVATE( this )->hdcOverlay, WGL_SWAP_OVERLAY1 ) );
}

void
SoWinGLWidget::glLockNormal( void )
{
  assert( PRIVATE( this )->hdcNormal != NULL );
  wglMakeCurrent( PRIVATE( this )->hdcNormal, PRIVATE( this )->ctxNormal );
}

void
SoWinGLWidget::glUnlockNormal( void )
{
  wglMakeCurrent( NULL, NULL );
}

void
SoWinGLWidget::glLockOverlay( void )
{
  wglMakeCurrent( PRIVATE( this )->hdcOverlay, PRIVATE( this )->ctxOverlay ); 
}

void
SoWinGLWidget::glUnlockOverlay( void )
{
  wglMakeCurrent( NULL, NULL );
}

void
SoWinGLWidget::glSwapBuffers( void )
{
  assert( PRIVATE( this )->hdcNormal != NULL );
  Win32::SwapBuffers( PRIVATE( this )->hdcNormal );
}

void
SoWinGLWidget::glFlushBuffer( void )
{
  glFlush( );
}

///////////////////////////////////////////////////////////////////
//
//  (private)
//

void
SoWinGLWidgetP::buildNormalGLWidget( HWND manager )
{
  LPSTR wndclassname = "GL Widget";
  HMENU menu = NULL;
  
  if ( ! SoWinGLWidgetP::glWndClassAtom ) {

    WNDCLASS windowclass;
    windowclass.lpszClassName = wndclassname;
    windowclass.hInstance = SoWin::getInstance( );
    windowclass.lpfnWndProc = SoWinGLWidget::glWidgetProc;
    windowclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowclass.lpszMenuName = NULL;
    windowclass.hIcon = NULL;
    windowclass.hCursor =  NULL;
    windowclass.hbrBackground = NULL;
    windowclass.cbClsExtra = 0;
    windowclass.cbWndExtra = 4;

    SoWinGLWidgetP::glWndClassAtom = Win32::RegisterClass( & windowclass );

  }
 
  this->currentCursor = LoadCursor( SoWin::getInstance( ), IDC_ARROW );

	assert( IsWindow( manager ) );
	
  RECT rect;
  Win32::GetClientRect( manager, & rect );

  if ( this->haveBorder ) {
    rect.left += this->borderSize;
    rect.top += this->borderSize;
    rect.right -= 2 * this->borderSize;
    rect.bottom -= 2 * this->borderSize;
  }

  HWND normalwidget = CreateWindowEx( NULL,
                                      wndclassname,
                                      wndclassname,
                                      WS_VISIBLE |
		                                  WS_CLIPSIBLINGS |
		                                  WS_CLIPCHILDREN |
                                      WS_CHILD,
                                      rect.left,
                                      rect.top,
                                      rect.right,
                                      rect.bottom,
                                      manager,
                                      menu,
                                      SoWin::getInstance( ),
                                      this->owner );

  assert( IsWindow( normalwidget ) );
  this->owner->realized = FALSE;
  this->normalWidget = normalwidget;
  this->owner->setGLSize( SbVec2s( rect.right - rect.left,
    rect.bottom - rect.top ) );
}

void
SoWinGLWidgetP::buildOverlayGLWidget( HWND manager )
{
  // FIXME: function not implemented
  // FIXME: overlay not supported. mariusbu 20010719.
  SOWIN_STUB( );
}

BOOL
SoWinGLWidgetP::createGLContext( HWND window )
{
  int pixelFormat;
  BOOL ok;

	assert( IsWindow( window ) );

  // All contexts were destroyed or released in onDestroy()
  
  this->hdcNormal = GetDC( window );
	assert( this->hdcNormal && "GetDC failed -- investigate" );
  this->hdcOverlay = this->hdcNormal;
  
  memset( & this->pfdNormal, 0, sizeof( PIXELFORMATDESCRIPTOR ) );
  this->pfdNormal.nSize = sizeof( PIXELFORMATDESCRIPTOR );
  this->pfdNormal.nVersion = 1;
  this->pfdNormal.dwFlags = PFD_DRAW_TO_WINDOW |
                            PFD_SUPPORT_OPENGL |
                            PFD_SWAP_LAYER_BUFFERS |
                            ( this->glModes & SO_GL_STEREO ?
                            PFD_STEREO : 0 ) |
                            ( this->glModes & SO_GL_DOUBLE ?
                            PFD_DOUBLEBUFFER : 0 );
  this->pfdNormal.iPixelType = PFD_TYPE_RGBA;
  this->pfdNormal.cColorBits = 32;    
  this->pfdNormal.cDepthBits = 32;
  
  pixelFormat = ChoosePixelFormat( this->hdcNormal, & this->pfdNormal );
  ok = SetPixelFormat( this->hdcNormal, pixelFormat, & this->pfdNormal );

  if ( ! ok ) {
    #if SOWIN_DEBUG && 1
    SoDebugError::postWarning( "SoWinGLWidget::createGLContext",
      "Pixelformat was not supported." );
    #endif // SOWIN_DEBUG
    return FALSE;
  }
  
  this->ctxNormal = wglCreateContext( this->hdcNormal );
  if ( ! this->ctxNormal ) {
    #if SOWIN_DEBUG && 1
    SoDebugError::postWarning( "SoWinGLWidget::createGLContext",
      "The rendering context could not be created." );
    #endif // SOWIN_DEBUG
    return FALSE;
  }
  
  // create overlay
  if ( this->glModes & SO_GL_OVERLAY ) {
    this->ctxOverlay = wglCreateLayerContext( this->hdcOverlay, 1 );
    
    // FIXME: set overlay plane. mariusbu 20010801.
  }

  // share context
  SoWinGLWidget * share = ( SoWinGLWidget * )
  SoAny::si( )->getSharedGLContext( NULL, NULL );

  if ( share != NULL )
    wglShareLists( PRIVATE( share )->ctxNormal, this->ctxNormal );
  
	SoAny::si( )->registerGLContext( ( void * ) this->owner, NULL, NULL );

  ok = wglMakeCurrent( this->hdcNormal, this->ctxNormal );

  if ( ! ok ) {
    #if SOWIN_DEBUG && 1
    SoDebugError::postWarning( "SoWinGLWidget::createGLContext",
      "The rendering context could not be made current." );
    #endif // SOWIN_DEBUG
    return FALSE;
  }

  wglMakeCurrent( NULL, NULL );

  return TRUE;
}

LRESULT
SoWinGLWidgetP::onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWinGLWidget::onCreate", "called" );
#endif // SOWIN_DEBUG

  // FIXME: add more tests. mariusbu 20010802.
label:  
  if ( ! this->createGLContext( window ) ) {
    if ( this->glModes & SO_GL_STEREO ) {
      this->glModes &= ~SO_GL_STEREO;
      goto label;
    }
    if ( this->glModes & SO_GL_OVERLAY ) {
      this->glModes &= ~SO_GL_OVERLAY;
      goto label;
    }
    if ( this->glModes & SO_GL_DOUBLE ) {
      this->glModes &= ~SO_GL_DOUBLE;
      goto label;
    }
    if ( ! ( this->glModes & SO_GL_DOUBLE ) ) {
      this->glModes |= SO_GL_DOUBLE;
      goto label;
    }
  }
  SetFocus( window );
	this->owner->widgetChanged( window );
  return 0;
}

LRESULT
SoWinGLWidgetP::onPaint( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWinGLWidget::onPaint", "called" );
#endif // SOWIN_DEBUG

  PAINTSTRUCT ps;
  this->hdcNormal = Win32::BeginPaint( window, & ps );

	BOOL ok = wglMakeCurrent( this->hdcNormal, this->ctxNormal );
	assert( ok && "The rendering context could not be made current." );

  if ( ! this->owner->realized ) {
    this->owner->realized = TRUE;
    this->owner->initGraphic( );
  }
  if ( ! this->owner->glScheduleRedraw( ) ) {
    this->owner->redraw( );
  }

  wglMakeCurrent( NULL, NULL );

  Win32::EndPaint( window, & ps );

  return 0;
}

LRESULT
SoWinGLWidgetP::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  wglMakeCurrent( NULL, NULL );
  
  SoAny::si( )->unregisterGLContext( ( void * ) this->owner );
 
  BOOL r = wglDeleteContext( this->ctxNormal );
  assert( r && "wglDeleteContext failed -- investigate" );
  this->ctxNormal = NULL;
  
  Win32::ReleaseDC( window, this->hdcNormal );
  this->hdcNormal = NULL;

  // FIXME: Overlay not supported. mariusbu 20010808.

  return 0;
}
