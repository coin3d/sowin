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

#if SOWIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#include <conio.h>
#endif // SOWIN_DEBUG

SOWIN_OBJECT_ABSTRACT_SOURCE(SoWinGLWidget);

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
  : SoWinComponent( parent, name, embed ),
    waitForExpose( TRUE )
{
  this->managerWidget = NULL;
  this->normalWidget = NULL;
  this->overlayWidget = NULL;

  this->enableDrawToFrontBuffer = FALSE;

  this->ctxNormal = NULL;
  this->ctxOverlay = NULL;

  this->hdcNormal = NULL;
  this->hdcOverlay = NULL;

  this->glModes = glModes;
  this->borderSize = 3;
  this->haveBorder = FALSE;
  this->currentCursor = NULL;

  this->haveFocus = FALSE;
  this->stealFocus = FALSE;

  this->parent = parent;

  if ( build ) {
    this->managerWidget = this->buildWidget( parent );
    this->setBaseWidget( this->managerWidget );
  }
}

SoWinGLWidget::~SoWinGLWidget( void )
{
  UnregisterClass( "SoWinGLWidget_glwidget", SoWin::getInstance( ) );
  UnregisterClass( "SoWinGLWidget_managerwidget", SoWin::getInstance( ) );
}

///////////////////////////////////////////////////////////////////
//
//  (public)
//

HWND
SoWinGLWidget::getNormalWindow( void )
{
  return this->normalWidget;
}

HWND
SoWinGLWidget::getOverlayWindow( void )
{
  // FIXME: overlay not supported. mariusbu 20010719.
  return this->overlayWidget;
}

HWND
SoWinGLWidget::getNormalWidget( void )
{
  return this->getNormalWindow( );
}

HWND
SoWinGLWidget::getOverlayWidget( void )
{
  return this->getOverlayWindow( );
}

HDC
SoWinGLWidget::getNormalDC( void )
{
  assert( this->hdcNormal != NULL );
  return this->hdcNormal;
}

HDC
SoWinGLWidget::getOverlayDC( void )
{
  assert( this->hdcOverlay != NULL );
  return this->hdcOverlay;
}

HGLRC
SoWinGLWidget::getNormalContext( void )
{
  assert( this->ctxNormal != NULL );
  return this->ctxNormal;
}

HGLRC
SoWinGLWidget::getOverlayContext( void )
{
  return this->ctxOverlay;
}

void
SoWinGLWidget::setStealFocus( SbBool doStealFocus )
{
  this->stealFocus = doStealFocus;
}

void
SoWinGLWidget::setNormalVisual( PIXELFORMATDESCRIPTOR * vis )
{
  assert( vis != NULL );
  assert( this->hdcNormal != NULL );

  memcpy( ( & this->pfdNormal ), vis, sizeof( PIXELFORMATDESCRIPTOR ) );

  int format = ChoosePixelFormat( this->hdcNormal, vis );
  this->setPixelFormat( format );
}

PIXELFORMATDESCRIPTOR *
SoWinGLWidget::getNormalVisual( void )
{
  return ( & this->pfdNormal );
}

void
SoWinGLWidget::setOverlayVisual( PIXELFORMATDESCRIPTOR * vis )
{
  // FIXME: overlay not supported. mariusbu 20010719.
  assert( vis != NULL );
  //assert( this->hdcNormal != NULL );
  
  memcpy( ( & this->pfdOverlay ), vis, sizeof( PIXELFORMATDESCRIPTOR ) );
  
  //int format = ChoosePixelFormat( this->hdcOverlay, vis );
  //this->setPixelFormat( format );
}

PIXELFORMATDESCRIPTOR *
SoWinGLWidget::getOverlayVisual( void )
{
  return ( & this->pfdOverlay );
}

void
SoWinGLWidget::setPixelFormat( int format )
{
  BOOL ok = SetPixelFormat( this->hdcNormal, format, & pfdNormal );
  assert( ok );
}

int
SoWinGLWidget::getPixelFormat( void )
{
  return GetPixelFormat( this->hdcNormal );
}

void
SoWinGLWidget::setDoubleBuffer( SbBool set )
{
  if ( set ) {
    this->glModes |= SO_GL_DOUBLE;
  }
  else {
    this->glModes ^= SO_GL_DOUBLE;
  }
}

SbBool
SoWinGLWidget::isDoubleBuffer( void )
{
  return ( this->glModes & SO_GL_DOUBLE );
}

void
SoWinGLWidget::setBorder( SbBool set )
{
  this->haveBorder = TRUE;
  // FIXME: SetWindowLong() or paint border? mariusbu 20010719.
}

int
SoWinGLWidget::getBorderSize( void )
{
  return this->borderSize;
}

SbBool
SoWinGLWidget::isBorder( void ) const
{
  return this->haveBorder;
}

void
SoWinGLWidget::setDrawToFrontBufferEnable( SbBool enable )
{
  this->enableDrawToFrontBuffer = enable;
}

SbBool
SoWinGLWidget::isDrawToFrontBufferEnable( void ) const
{
  return this->enableDrawToFrontBuffer;
}

/*!
  Enables or disables quad buffer stereo.
*/
void
SoWinGLWidget::setQuadBufferStereo( const SbBool enable )
{
  // FIXME: do proper implementation. 20001123 mortene.
  // FIXME: function not implemented
  SOWIN_STUB();
}

/*!
  Returns \c TRUE if quad buffer stereo is enabled for this widget.
*/
SbBool
SoWinGLWidget::isQuadBufferStereo( void ) const
{
  // FIXME: do proper implementation. 20001123 mortene.
  // FIXME: function not implemented
  // SOWIN_STUB();
  return FALSE;
}

void
SoWinGLWidget::setCursor( HCURSOR newCursor )
{
  assert( newCursor != NULL );
  this->currentCursor = newCursor;
  SetCursor( newCursor );
}

HCURSOR
SoWinGLWidget::getCursor( void )
{
  return this->currentCursor;
}

void
SoWinGLWidget::processExternalEvent( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  MSG msg;
  POINT pt = { LOWORD( lparam ), HIWORD( lparam ) };
  msg.hwnd = window;
  msg.lParam = lparam;
  msg.message = message;
  msg.pt = pt;
  msg.time = GetTickCount( );
  msg.wParam = wparam;

  this->processEvent( & msg );
}

///////////////////////////////////////////////////////////////////
//
//  (protected)
//

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
  this->createGLContext( this->getNormalWidget( ) );
}

void
SoWinGLWidget::setGLSize( SbVec2s newSize )
{
  short width, height;
  newSize.getValue( width, height );
  if ( newSize == glSize ) return;

  this->glSize = newSize;
  this->sizeChanged( newSize );

  UINT flags = SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW;
  SetWindowPos( this->getNormalWidget( ), NULL, 0, 0, width, height, flags );
}

SbVec2s
SoWinGLWidget::getGLSize( void ) const
{
  return this->glSize;
}

float
SoWinGLWidget::getGLAspectRatio( void ) const
{
  return ( float ) this->glSize[0] / ( float ) this->glSize[1];
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
  return ( this->glModes & SO_GLX_RGB );
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

  WNDCLASS windowclass;
  HMENU menu = NULL;
  HWND widget = NULL;
  LPSTR wndclassname = "SoWinGLWidget_managerwidget";

  windowclass.lpszClassName = wndclassname;
  windowclass.hInstance = SoWin::getInstance( );
  windowclass.lpfnWndProc = this->managerWindowProc;
  windowclass.style = NULL;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = NULL;
  windowclass.hCursor = NULL;
  windowclass.hbrBackground = NULL;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass( & windowclass );

  RECT rect;
  if ( IsWindow( parent ) ) {
    GetClientRect( parent, & rect );
  }
  else {
    rect.left = 0;
    rect.top = 0;
    rect.right = 500;
    rect.bottom = 500;
  }

  HWND managerwidget = CreateWindow( wndclassname,
                                     wndclassname,
                                     WS_CLIPCHILDREN |
                                     WS_CLIPSIBLINGS |
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

  // FIXME: make param in build*GLWidget  
  this->managerWidget = managerwidget;

  if ( this->glModes & SO_GL_OVERLAY )
    this->buildOverlayGLWidget( & this->pfdOverlay );

  this->buildNormalGLWidget( & this->pfdNormal );

  this->waitForExpose = TRUE;
  
  return managerwidget;
}

HWND
SoWinGLWidget::getManagerWidget( void )
{
  return this->managerWidget;
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
  return this->getNormalWindow( );
}

SbBool
SoWinGLWidget::makeNormalCurrent( void )
{
  return ( wglMakeCurrent( ( HDC ) this->hdcNormal, this->ctxNormal ) );
}

SbBool
SoWinGLWidget::swapNormalBuffers( void )
{
  if ( ! ( this->glModes & SO_GL_DOUBLE ) )
    return FALSE;
  
  return ( SwapBuffers( ( HDC ) this->hdcNormal ) );
}

SbBool
SoWinGLWidget::swapOverlayBuffers( void )
{
  return ( wglSwapLayerBuffers( ( HDC ) this->hdcOverlay, WGL_SWAP_OVERLAY1 ) );
}

void
SoWinGLWidget::glLockNormal( void )
{
  assert( this->hdcNormal != NULL );
  wglMakeCurrent( this->hdcNormal, this->ctxNormal );
}

void
SoWinGLWidget::glUnlockNormal( void )
{
  wglMakeCurrent( this->hdcNormal, NULL );
}

void
SoWinGLWidget::glLockOverlay( void )
{
  // FIXME: not implemented
  // FIXME: overlay not supported. mariusbu 20010719.
}

void
SoWinGLWidget::glUnlockOverlay( void )
{
  // FIXME: not implemented
  // FIXME: overlay not supported. mariusbu 20010719.  
}

void
SoWinGLWidget::glSwapBuffers( void )
{
  assert( this->hdcNormal != NULL );
  SwapBuffers( this->hdcNormal );
}

void
SoWinGLWidget::glFlushBuffer( void )
{
  glFlush( );
}
/*
void
SoWinGLWidget::setWindowPosition( POINT position )
{
  UINT flags = SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW;
  SetWindowPos( this->getNormalWidget( ),
    NULL, position.x, position.y, 0, 0, flags );
}
*/
///////////////////////////////////////////////////////////////////
//
//  (private)
//

void
SoWinGLWidget::buildNormalGLWidget( PIXELFORMATDESCRIPTOR * pfd )  // FIXME: pfd is ignored
{
  HMENU menu = NULL;
  LPSTR wndclassname = "SoWinGLWidget_glwidget";

  WNDCLASS windowclass;
  windowclass.lpszClassName = wndclassname;
  windowclass.hInstance = SoWin::getInstance( );
  windowclass.lpfnWndProc = this->glWindowProc;
  windowclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_SAVEBITS;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = NULL;
  windowclass.hCursor =  NULL;
  windowclass.hbrBackground = NULL;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass( & windowclass );
	
	this->currentCursor = LoadCursor( SoWin::getInstance( ), IDC_ARROW );
	
  RECT rect;
  if ( IsWindow( parent ) ) {
    GetClientRect( parent, & rect );
  }
  else {
    rect.left = 0;
    rect.top = 0;
    rect.right = 500;
    rect.bottom = 500;
  }

  if ( this->haveBorder ) {
    rect.left += this->borderSize;
    rect.top += this->borderSize;
    rect.right -= this->borderSize;
    rect.bottom -= this->borderSize;
  }

  HWND normalwidget = CreateWindowEx( NULL,
                                      wndclassname,
                                      wndclassname,
                                      WS_CLIPCHILDREN |
                                      WS_CLIPSIBLINGS |
                                      WS_CHILD,
                                      rect.left,
                                      rect.top,
                                      rect.right,
                                      rect.bottom,
                                      this->managerWidget,
                                      menu,
                                      SoWin::getInstance( ),
                                      this );

  assert( IsWindow( normalwidget ) );

  this->realized = FALSE;
  this->normalWidget = normalwidget;

  ShowWindow( normalwidget, SW_SHOW );
}

void
SoWinGLWidget::buildOverlayGLWidget( PIXELFORMATDESCRIPTOR * pfd )
{
  // FIXME: function not implemented
  // FIXME: overlay not supported. mariusbu 20010719.
  SOWIN_STUB( );
}

LRESULT CALLBACK
SoWinGLWidget::managerWindowProc( HWND window,
                                  UINT message,
                                  WPARAM wparam,
                                  LPARAM lparam )
{
  if ( message == WM_CREATE ) {
    CREATESTRUCT * createstruct;
    createstruct = ( CREATESTRUCT * ) lparam;
    SetWindowLong( window, 0, ( LONG ) ( createstruct->lpCreateParams ) );
    return 0;
  }

  SoWinGLWidget * object = ( SoWinGLWidget * ) GetWindowLong( window, 0 );

  if ( object && window == object->getManagerWidget( ) ) {
    switch ( message )
      {
      case WM_SIZE:
        object->setGLSize( SbVec2s( LOWORD( lparam ), HIWORD( lparam ) ) );
        return 0;
      }
  }
  return DefWindowProc( window, message, wparam, lparam );
}

LRESULT CALLBACK
SoWinGLWidget::glWindowProc( HWND window,
                             UINT message,
                             WPARAM wparam,
                             LPARAM lparam )
{
  if ( message == WM_CREATE ) {
    CREATESTRUCT * createstruct;
    createstruct = ( CREATESTRUCT * ) lparam;
    SetWindowLong( window, 0, ( LONG ) ( createstruct->lpCreateParams ) );

    SoWinGLWidget * object = ( SoWinGLWidget * )( createstruct->lpCreateParams );
    return object->onCreate( window, message, wparam, lparam );
  }

  SoWinGLWidget * object = ( SoWinGLWidget * ) GetWindowLong( window, 0 );

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
    if( ( ( ! object->haveFocus ) && object->stealFocus ) ||
      ( message == WM_LBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_RBUTTONDOWN ) ) {
      object->haveFocus = ( BOOL ) SetFocus( window );
    }

    object->processEvent( & msg );
    
    switch ( message )
      {
      case WM_SIZE:
        return object->onSize( window, message, wparam, lparam );

      case WM_PAINT:
        object->waitForExpose = FALSE; // flip flag on first expose
        return object->onPaint( window, message, wparam, lparam );

      case WM_DESTROY:
        return object->onDestroy( window, message, wparam, lparam );

      case WM_LBUTTONDOWN:
      case WM_MBUTTONDOWN:
      case WM_RBUTTONDOWN:
        SetCapture( window );
        return 0;

      case WM_LBUTTONUP:
      case WM_MBUTTONUP:
      case WM_RBUTTONUP:
        ReleaseCapture( );
        return 0;

      case WM_KILLFOCUS:
        object->haveFocus = FALSE;
        return 0;

			case WM_SETCURSOR:
				SetCursor( object->getCursor( ) );
				return 0;
 
      }
  }
  return DefWindowProc( window, message, wparam, lparam );
}

BOOL
SoWinGLWidget::createGLContext( HWND window )
{
  int pixelFormat;
  BOOL ok;
  
  wglMakeCurrent( NULL, NULL );
  wglDeleteContext( this->ctxNormal );
  DeleteDC( this->hdcNormal );

  HDC hdc = GetDC( window );
  
  memset( & this->pfdNormal, 0, sizeof( PIXELFORMATDESCRIPTOR ) );
  this->pfdNormal.nSize = sizeof( PIXELFORMATDESCRIPTOR );
  this->pfdNormal.nVersion = 1;
  this->pfdNormal.dwFlags = PFD_DRAW_TO_WINDOW |
                            PFD_SUPPORT_OPENGL |
                            PFD_SWAP_LAYER_BUFFERS |
                            // PFD_STEREO |
                            ( this->glModes & SO_GL_DOUBLE ?
                            PFD_DOUBLEBUFFER : 0 );
  this->pfdNormal.iPixelType = PFD_TYPE_RGBA; // PFD_TYPE_COLORINDEX
  this->pfdNormal.cColorBits = 32;    
  this->pfdNormal.cDepthBits = 32;
  
  pixelFormat = ChoosePixelFormat( hdc, & this->pfdNormal );
  ok = SetPixelFormat( hdc, pixelFormat, & this->pfdNormal );
  assert( ok );

  SoWinGLWidget * share = ( SoWinGLWidget * )
		SoAny::si( )->getSharedGLContext( NULL, NULL );

  HGLRC hrc = wglCreateContext( hdc );
  // FIXME: implement overlay layer support. mariusbu 20010719.
  //wglCreateLayerContext( )

	if ( share != NULL )
    wglShareLists( share->ctxNormal, hrc );

	SoAny::si( )->registerGLContext( ( void * ) this, NULL, NULL );

  ok = wglMakeCurrent( hdc, hrc );
  assert( ok );

  this->hdcNormal = hdc;
  this->ctxNormal = hrc;

  wglMakeCurrent( NULL, NULL );

  return TRUE;
}

LRESULT
SoWinGLWidget::onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWinGLWidget::onCreate", "called" );
#endif // SOWIN_DEBUG
  this->createGLContext( window );
  SetFocus( window );
  return 0;
}

LRESULT
SoWinGLWidget::onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{	
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWinGLWidget::onSize", "called" );
#endif // SOWIN_DEBUG
	
  BOOL ok = wglMakeCurrent( this->hdcNormal, this->ctxNormal );
  assert( ok );

  this->setGLSize( SbVec2s( LOWORD( lparam ), HIWORD( lparam ) ) );

  ok = wglMakeCurrent( NULL, NULL );
  assert( ok );

  return 0;
}

LRESULT
SoWinGLWidget::onPaint( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWinGLWidget::onPaint", "called" );
#endif // SOWIN_DEBUG

  PAINTSTRUCT ps;
  this->hdcNormal = BeginPaint( window, & ps );

  wglMakeCurrent( this->hdcNormal, this->ctxNormal );

  if ( ! this->realized ) {
    this->realized = TRUE;
    this->initGraphic( );
  }
  if ( ! this->glScheduleRedraw( ) ) {
    this->redraw( );
  }

  wglMakeCurrent( this->hdcNormal, NULL );

  EndPaint( window, & ps );

  return 0;
}

LRESULT
SoWinGLWidget::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
	SoAny::si( )->unregisterGLContext( ( void * ) this );
	
  wglDeleteContext( this->ctxNormal );
  ReleaseDC( window, this->hdcNormal );

  return 0;
}

SbBool
SoWinGLWidget::hasOverlayGLArea( void ) const
{
  return ( IsWindow( ( ( SoWinGLWidget * ) this )->getOverlayWidget( ) ) );
}

SbBool
SoWinGLWidget::hasNormalGLArea( void ) const
{
  return ( IsWindow( ( ( SoWinGLWidget * ) this )->getNormalWidget( ) ) );
}

SbBool
SoWinGLWidget::glScheduleRedraw( void )
{
  return FALSE;
}
