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
  this->doubleBufferWidget = NULL;
  this->singleBufferWidget = NULL;
  this->overlayWidget = NULL;

  this->enableDrawToFrontBuffer = FALSE;

  this->ctxNormal = NULL;
  this->ctxOverlay = NULL;
  this->ctxSingle = NULL;
  this->ctxDouble = NULL;

  this->hdcNormal = NULL;
  this->hdcOverlay = NULL;
  this->hdcSingle = NULL;
  this->hdcDouble = NULL;

  this->attribList = NULL;
  this->glModes = glModes;
  this->borderSize = 3;

  this->windowResized = FALSE;
  this->haveFocus = FALSE;

  this->parent = parent;

  if ( build ) {
    HWND glarea = this->buildWidget( parent );
    this->setBaseWidget( glarea );
  }
}

SoWinGLWidget::~SoWinGLWidget( void )
{

}

///////////////////////////////////////////////////////////////////
//
//  (public)
//

HWND
SoWinGLWidget::getNormalWindow( void )
{
  if ( this->isDoubleBuffer( ) ) {
    return this->doubleBufferWidget;
  }
  else {
    return this->singleBufferWidget;
  }
}

HWND
SoWinGLWidget::getOverlayWindow( void )
{
  return this->overlayWidget; // FIXME: overlay not supported
}

HWND
SoWinGLWidget::getNormalWidget( void )
{
  return this->getNormalWindow( );
}

HWND
SoWinGLWidget::getOverlayWidget( void )
{
  return this->getOverlayWindow( ); // FIXME: overlay not supported
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
  return this->hdcOverlay; // FIXME: overlay not supported
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
  return this->ctxOverlay; // FIXME: overlay not supported
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
  memcpy( ( & this->pfdNormal ), vis, sizeof( PIXELFORMATDESCRIPTOR ) );
}

PIXELFORMATDESCRIPTOR *
SoWinGLWidget::getNormalVisual( void )
{
  return ( & this->pfdNormal );
}

void
SoWinGLWidget::setOverlayVisual( PIXELFORMATDESCRIPTOR * vis )
{
  // Note: setOverlayVisual( ) has no effect on Win32 machines

  assert( vis != NULL );
  memcpy( ( & this->pfdOverlay ), vis, sizeof( PIXELFORMATDESCRIPTOR ) );
}

PIXELFORMATDESCRIPTOR *
SoWinGLWidget::getOverlayVisual( void )
{
  return ( & this->pfdOverlay );
}

void
SoWinGLWidget::setPixelFormat( int format )
{
  this->nPixelFormat = format;
  //BOOL ok = SetPixelFormat( this->hdcNormal, this->nPixelFormat, & pfdNormal )
  //assert( ok );
}

int
SoWinGLWidget::getPixelFormat( void )
{
  return this->nPixelFormat;
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
  // FIXME: function not implemented
  SOWIN_STUB( );
}

int
SoWinGLWidget::getBorderSize( void )
{
  return this->borderSize;
}

SbBool
SoWinGLWidget::isBorder( void ) const
{
  return ( this->borderSize != 0 );
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
}

/*!
  Returns \c TRUE if quad buffer stereo is enabled for this widget.
*/
SbBool
SoWinGLWidget::isQuadBufferStereo( void ) const
{
  // FIXME: do proper implementation. 20001123 mortene.
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
SoWinGLWidget::sizeChanged( const SbVec2s newSize ) // virtual,
{
  // virtual - does nothing
}

void
SoWinGLWidget::widgetChanged( HWND newWidget )
{
  // virtual - does nothing
  // called whenever the widget is changed (i.e. at initialization
  // or after switching from single->double buffer)
}

void
SoWinGLWidget::setGLSize( SbVec2s newSize )  // Coin spesific
{
  short width, height;
  newSize.getValue( width, height );
  if ( newSize == glSize ) return;

  this->glSize = newSize;
  this->sizeChanged( newSize );
  
  MoveWindow( this->getNormalWidget( ),
              0,
              0,
              width,
              height,
              TRUE );
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


LRESULT
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
  // Used only to draw borders

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
    rect.right = SoWin_DefaultWidth;
    rect.bottom = SoWin_DefaultHeight;
  }

  this->windowPosition.x = 0;
  this->windowPosition.y = 0;

  this->managerWidget = CreateWindow( wndclassname,
                                      wndclassname,
                                      WS_CLIPCHILDREN |
                                      WS_CLIPSIBLINGS |
                                      WS_CHILD |
                                      WS_BORDER,
                                      this->windowPosition.x,
                                      this->windowPosition.y,
                                      rect.right,
                                      rect.bottom,
                                      parent,
                                      menu,
                                      SoWin::getInstance( ),
                                      this );

  assert( IsWindow( this->managerWidget ) );

  if ( this->glModes & SO_GL_OVERLAY ) {
    this->buildOverlayGLWidget( & this->pfd ); // FIXME: overlay not supported
  }
  else {
    this->buildNormalGLWidget( & this->pfd );
  }

  this->waitForExpose = TRUE;

  SoWin::addMessageHook( this->managerWidget, WM_SIZE );
  return this->managerWidget;
}

HWND
SoWinGLWidget::getManagerWidget( void )
{
  return this->managerWidget;
}

HWND
SoWinGLWidget::getGlxMgrWidget( void )
{
  return this->getManagerWidget( );
}

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
  if ( this->overlayWidget ) {
    return ( wglSwapLayerBuffers( ( HDC ) this->hdcNormal, WGL_SWAP_MAIN_PLANE ) );
  }
  else {
    return ( SwapBuffers( ( HDC ) this->hdcNormal ) );
  }
}

SbBool
SoWinGLWidget::swapOverlayBuffers( void )
{
  return ( wglSwapLayerBuffers( ( HDC ) this->hdcOverlay, WGL_SWAP_OVERLAY1 ) );
}

DWORD
SoWinGLWidget::getThreadId( void )
{
  return this->dwThreadId;
}

void
SoWinGLWidget::setThreadId( DWORD id )
{
  this->dwThreadId = id;
}

void
SoWinGLWidget::changeCursor( HCURSOR newCursor )
{
  this->setCursor( newCursor );
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
  // FIXME: does nothing
  //wglMakeCurrent( this->hdcNormal, NULL );
}

void
SoWinGLWidget::glLockOverlay( void )
{
  // FIXME: not implemented
}

void
SoWinGLWidget::glUnlockOverlay( void )
{
  // FIXME: not implemented
}

void
SoWinGLWidget::glSwapBuffers( void )
{
  // Nothing to do...
  assert( this->hdcNormal != NULL );
  SwapBuffers( this->hdcNormal );
}

void
SoWinGLWidget::glFlushBuffer( void )
{
  glFlush( );
}

/*
float
SoWinGLWidget::getGLAspectRatio( void )
{
  short width, height;
  this->glSize.getValue( width, height );
  return ( ( float ) width / ( float ) height );
}
*/

void
SoWinGLWidget::setWindowPosition( POINT position )
{
  this->windowPosition.x = position.x;
  this->windowPosition.y = position.y;
}

///////////////////////////////////////////////////////////////////
//
//  (private)
//

void
SoWinGLWidget::buildNormalGLWidget( PIXELFORMATDESCRIPTOR * pfd )  // FIXME: pfd is ignored
{
  LPCTSTR cursor = MAKEINTRESOURCE( IDC_ARROW );
  HMENU menu = NULL;
  LPSTR wndclassname = "SoWinGLWidget_glwidget";

  WNDCLASS windowclass;
  windowclass.lpszClassName = wndclassname;
  windowclass.hInstance = SoWin::getInstance( );
  windowclass.lpfnWndProc = this->glWindowProc;
  windowclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = NULL;
  windowclass.hCursor = this->currentCursor = LoadCursor( NULL, cursor );
  windowclass.hbrBackground = NULL;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass( & windowclass );

  RECT rect;
  if ( IsWindow( parent ) ) {
    GetClientRect( parent, & rect );
  }
  else {
    rect.right = SoWin_DefaultWidth;
    rect.bottom = SoWin_DefaultHeight;
  }

  HWND normalwidget = CreateWindow( wndclassname,
                                    wndclassname,
                                    WS_CLIPCHILDREN |
                                    WS_CLIPSIBLINGS |
                                    WS_CHILD,
                                    0,
                                    0,
                                    rect.right,
                                    rect.bottom,
                                    this->managerWidget,
                                    menu,
                                    SoWin::getInstance( ),
                                    this );

  assert( IsWindow( normalwidget ) );

  this->firstRealize = TRUE;

  if ( this->glModes & SO_GL_DOUBLE ) {// ( vis->dwFlags & PFD_DOUBLEBUFFER )
    this->doubleBufferWidget = normalwidget;
  }
  else {
    this->singleBufferWidget = normalwidget;
  }
  ShowWindow( normalwidget, SW_SHOW );
}

void
SoWinGLWidget::buildOverlayGLWidget( PIXELFORMATDESCRIPTOR * pfd )
{
  // FIXME: function not implemented
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
    return object->onCreate( window, message, wparam, lparam ); // won't work
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
    
    object->processEvent( & msg );
    
    /* Steal focus from other windows
    if( ! object->haveFocus ) {
      object->haveFocus = ( BOOL ) SetFocus( window );
    }
    */
    switch ( message )
      {
      case WM_SIZE:
        return object->onSize( window, message, wparam, lparam );

      case WM_PAINT:
        object->waitForExpose = FALSE; // flips flag on first expose
        return object->onPaint( window, message, wparam, lparam );

      case WM_DESTROY:
        return object->onDestroy( window, message, wparam, lparam );

      case WM_LBUTTONDOWN:
        //case WM_MBUTTONDOWN:
        //case WM_RBUTTONDOWN:
        SetCapture( window );
        return 0;

      case WM_LBUTTONUP:
        //case WM_MBUTTONUP:
        //case WM_RBUTTONUP:
        ReleaseCapture( );
        return 0;

      case WM_KILLFOCUS:
        object->haveFocus = FALSE;
        return 0;

        //case WM_KEYDOWN:
        //return 0;
      }
  }
  return DefWindowProc( window, message, wparam, lparam );
}

LRESULT
SoWinGLWidget::onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  //CREATESTRUCT * cs = ( CREATESTRUCT * ) lparam;

  int nPixelFormat;
  BOOL ok;

  HDC hdc = GetDC( window );

  static PIXELFORMATDESCRIPTOR pfd =  // FIXME: no palette or singlebuffer support
  {
    sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
    1,                             // version number
    PFD_DRAW_TO_WINDOW |           // support window
    PFD_SUPPORT_OPENGL |           // support OpenGL
    PFD_DOUBLEBUFFER |             // double buffer
    PFD_TYPE_RGBA,                 // RGBA type
    32,                            // 32-bit colour depth
    0, 0, 0, 0, 0, 0,              // colour bits ignored
    0,                             // no alpha buffer
    0,				   // shift bit ignored
    0,				   // on accumulation buffer
    0, 0, 0, 0,			   // accum bits ignored
    32,				   // 32-bits z-buffer
    0,				   // no stencil buffer
    0,				   // no auxiliary buffer
    PFD_MAIN_PLANE,		   // main layer
    0,				   // reserved
    0, 0, 0			   // layer masks ignored
  };

  nPixelFormat = ChoosePixelFormat( hdc, & pfd );

  ok = SetPixelFormat( hdc, nPixelFormat, & pfd );
  assert( ok );

  HGLRC hrc = wglCreateContext( hdc );

#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWinGLWidget::onCreate", "called" );
#endif // SOWIN_DEBUG
	
  ok = wglMakeCurrent( hdc, hrc );
  assert( ok );

  this->hdcNormal = hdc;
  this->ctxNormal = hrc;
  this->nPixelFormat = nPixelFormat;

  wglMakeCurrent( NULL, NULL );

  memcpy( ( void * ) ( & this->pfdNormal ), & pfd, sizeof( PIXELFORMATDESCRIPTOR ) );
  if( this->glModes & SO_GL_DOUBLE ) {
    memcpy( & this->pfdDouble, & pfd, sizeof( PIXELFORMATDESCRIPTOR ) );
    this->hdcDouble = this->hdcNormal;
    this->ctxDouble = this->ctxNormal;
  } else {
    memcpy( & this->pfdSingle, & pfd, sizeof( PIXELFORMATDESCRIPTOR ) );
    this->hdcSingle = this->hdcNormal;
    this->ctxSingle = this->ctxNormal;
  }

  return 0;
}

LRESULT
SoWinGLWidget::onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{	
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo( "SoWinGLWidget::onSize", "called" );
#endif // SOWIN_DEBUG

  /*
    if(  window != this->getNormalWidget( ) )
    return 0;
  */
	
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

  if ( this->firstRealize ) {
    this->firstRealize = FALSE;
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
  wglDeleteContext( this->ctxNormal );
  ReleaseDC( window, this->hdcNormal );

  return 0;
}

SbBool
SoWinGLWidget::hasOverlayGLArea( void ) const
{
  return ( ( ( SoWinGLWidget * ) this )->getOverlayWidget( ) != NULL );
}

SbBool
SoWinGLWidget::hasNormalGLArea( void ) const
{
  return ( ( ( SoWinGLWidget * ) this )->getNormalWidget( ) != NULL );
}

SbBool
SoWinGLWidget::glScheduleRedraw( void )
{
  return FALSE;
}

