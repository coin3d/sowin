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
  SbBool glRealized;
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

/*!
  Protected constructor.
*/
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
  PRIVATE( this )->glRealized = FALSE;

  this->setClassName( "SoWinGLWidget" );
	
  if ( ! build ) return;
	
  PRIVATE( this )->managerWidget = this->buildWidget( parent );
  this->setBaseWidget( PRIVATE( this )->managerWidget );
} // SoWinGLWidget()

/*!
  Protected destructor.
*/
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
} // ~SoWinGLWidget()

///////////////////////////////////////////////////////////////////
//
//  (public)
//

/*!
 */
HWND
SoWinGLWidget::getNormalWindow( void )
{
  return PRIVATE( this )->normalWidget;
} // getNormalWindow()

/*!
 */
HWND
SoWinGLWidget::getOverlayWindow( void )
{
  // FIXME: overlay not supported. mariusbu 20010719.
  return PRIVATE( this )->overlayWidget;
} // getOverlayWindow()

/*!
 */
HWND
SoWinGLWidget::getNormalWidget( void )
{
  return PRIVATE( this )->normalWidget;
} // getNormalWidget()

/*!
 */
HWND
SoWinGLWidget::getOverlayWidget( void )
{
  return PRIVATE( this )->overlayWidget;
} // getOverlayWidget()

/*!
  Returns the normal device context.
*/
HDC
SoWinGLWidget::getNormalDC( void )
{
  assert( PRIVATE( this )->hdcNormal != NULL );
  return PRIVATE( this )->hdcNormal;
} // getNormalDC()

/*!
  Returns the overlay device context.
*/
HDC
SoWinGLWidget::getOverlayDC( void )
{
  assert( PRIVATE( this )->hdcOverlay != NULL );
  return PRIVATE( this )->hdcOverlay;
} // getOverlayDC()

/*!
  Returns the normal GL context.
*/
HGLRC
SoWinGLWidget::getNormalContext( void )
{
  assert( PRIVATE( this )->ctxNormal != NULL );
  return PRIVATE( this )->ctxNormal;
} // getNormalContext()

/*!
  Returns the overlay GL context.
*/
HGLRC
SoWinGLWidget::getOverlayContext( void )
{
  return PRIVATE( this )->ctxOverlay;
} // getOverlayContext()

/*!
 */
void
SoWinGLWidget::setStealFocus( SbBool doStealFocus )
{
  PRIVATE( this )->stealFocus = doStealFocus;
} // setStealFocus()

/*!
 */
void
SoWinGLWidget::setNormalVisual( PIXELFORMATDESCRIPTOR * vis )
{
  assert( vis != NULL );
  assert( PRIVATE( this )->hdcNormal != NULL );

  memcpy( ( & PRIVATE( this )->pfdNormal ), vis, sizeof( PIXELFORMATDESCRIPTOR ) );

  int format = ChoosePixelFormat( PRIVATE( this )->hdcNormal, vis );
  this->setPixelFormat( format );
} // setNormalVisual()

/*!
 */
PIXELFORMATDESCRIPTOR *
SoWinGLWidget::getNormalVisual( void )
{
  return ( & PRIVATE( this )->pfdNormal );
} // getNormalVisual()

/*!
 */
void
SoWinGLWidget::setOverlayVisual( PIXELFORMATDESCRIPTOR * vis )
{
  // FIXME: overlay not supported. mariusbu 20010719.
  assert( vis != NULL );
  assert( PRIVATE( this )->hdcNormal != NULL );
  
  memcpy( ( & PRIVATE( this )->pfdOverlay ), vis, sizeof( PIXELFORMATDESCRIPTOR ) );
  
  int format = ChoosePixelFormat( PRIVATE( this )->hdcOverlay, vis );
  this->setPixelFormat( format );
} // setOverlayVisual()

/*!
 */
PIXELFORMATDESCRIPTOR *
SoWinGLWidget::getOverlayVisual( void )
{
  return ( & PRIVATE( this )->pfdOverlay );
} // getOverlayVisual()

/*!
 */
void
SoWinGLWidget::setPixelFormat( int format )
{
  BOOL ok = SetPixelFormat( PRIVATE( this )->hdcNormal, format, & PRIVATE( this )->pfdNormal );
  assert( ok );
} // setPixelFormat()

/*!
 */
int
SoWinGLWidget::getPixelFormat( void )
{
  return GetPixelFormat( PRIVATE( this )->hdcNormal );
}

/*!
  Switch between single and double buffer mode for the OpenGL canvas.
  The default is to use a single buffer canvas.

  \sa isDoubleBuffer()
*/
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
} // setDoubleBuffer()

/*!
  Returns the status of the buffer mode.

  \sa setDoubleBuffer()
 */
SbBool
SoWinGLWidget::isDoubleBuffer( void )
{
  return ( PRIVATE( this )->glModes & SO_GL_DOUBLE ? TRUE : FALSE );
} // isDoubleBuffer()

/*!
  Specify that there should be a border around the OpenGL canvas (or not).

  \sa isBorder()
*/
void
SoWinGLWidget::setBorder( SbBool set )
{
  PRIVATE( this )->haveBorder = TRUE;
} // setBorder()

/*!
*/
int
SoWinGLWidget::getBorderSize( void )
{
  return PRIVATE( this )->borderSize;
} // getBorderSize()

/*!
*/
void
SoWinGLWidget::setBorderSize( int size )
{
  PRIVATE( this )->borderSize = size;
} // setBorderSize()

/*!
  Returns whether or not there's a border around the OpenGL canvas.

  \sa setBorder()
*/
SbBool
SoWinGLWidget::isBorder( void ) const
{
  return PRIVATE( this )->haveBorder;
} // isBorder()

/*!
  If this is set to \c TRUE, rendering will happen in the front buffer
  even if the current rendering mode is double buffered.
*/
void
SoWinGLWidget::setDrawToFrontBufferEnable( SbBool enable )
{
  PRIVATE( this )->drawToFrontBuffer = enable;
} // setDrawToFrontBufferEnable()

/*!
  \sa setDrawToFrontBufferEnable()
*/
SbBool
SoWinGLWidget::isDrawToFrontBufferEnable( void ) const
{
  return PRIVATE( this )->drawToFrontBuffer;
} // isDrawToFrontBufferEnable()

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
} // setQuadBufferStereo()

/*!
  Returns \c TRUE if quad buffer stereo is enabled for this widget.
*/
SbBool
SoWinGLWidget::isQuadBufferStereo( void ) const
{
  return ( PRIVATE( this )->glModes & SO_GL_STEREO ? TRUE : FALSE );
} // isQuadBufferStereo()

/*!
 */
void
SoWinGLWidget::setCursor( HCURSOR newCursor )
{
  assert( newCursor != NULL );
  PRIVATE( this )->currentCursor = newCursor;
  SetCursor( newCursor );
} // setCursor()

/*!
 */
HCURSOR
SoWinGLWidget::getCursor( void )
{
  return PRIVATE( this )->currentCursor;
} // getCursor()

/*!
  Should return TRUE if an overlay GL drawing area exists.
*/
SbBool
SoWinGLWidget::hasOverlayGLArea( void )
{
  return ( IsWindow( this->getOverlayWidget( ) ) ? TRUE : FALSE );
}

/*!
  Should return TRUE if a normal GL drawing area exists.
*/
SbBool
SoWinGLWidget::hasNormalGLArea( void )
{
  return ( IsWindow( this->getNormalWidget( ) ) ? TRUE : FALSE );
}

/*!
  Will be called whenever scene graph needs to be redrawn().
  If this method return FALSE, redraw() will be called immediately.

  Default method simply returns FALSE. Overload this method to
  schedule a redraw and return TRUE if you're trying to do The Right
  Thing.  
*/
SbBool
SoWinGLWidget::glScheduleRedraw( void )
{
  return FALSE;
} // glScheduleRedraw()

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
      (void)SetCapture( window );
      return 0;

    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
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

/*!
 */
void
SoWinGLWidget::redraw( void )
{
  // virtual - does nothing
}

/*!
  Renders the overlay scene graph. Default method is empty. Subclasses
  should overload this method.
*/
void
SoWinGLWidget::redrawOverlay( void )
{
  // virtual - does nothing
} // redrawOverlay()

/*!
  Any events from the native window system that goes to the OpenGL
  canvas gets piped through this method.

  It is overloaded in the subclasses to catch user interaction with
  the render canvas in the viewers, aswell as forwarding relevant
  events to the scenegraph.
*/
void
SoWinGLWidget::processEvent( MSG * msg )
{
  // Nothing is done here for the SoWinGLWidget, as the events we need
  // to handle for this superclass are caught by the method
  // SoWinGLWidget::glWidgetProc() and forwarded directly to
  // SoWinGLWidget::onPaint() etc.  The events we don't care about
  // (like mouse- and keyboard-interaction) are forwarded from
  // glWidgetProc() through this virtual method down to the
  // subclass(es).
  //                          mortene.
}

/*!
  Will be called when GL widget should initialize graphic, after
  the widget has been created. Default method enabled GL_DEPTH_TEST.
*/
void
SoWinGLWidget::initGraphic( void )
{
  glLockNormal( );
  glEnable( GL_DEPTH_TEST );
  glUnlockNormal( );
} // initGraphic()

/*!
  Will be called after the overlay widget has been created, and subclasses
  should overload this to initialize overlay stuff.

  Default method does nothing.
*/
void
SoWinGLWidget::initOverlayGraphic( void )
{
  // virtual - does nothing
} // initOverlayGraphic()

/*!
  Will be called every time the size of the GL widget changes.
*/
void
SoWinGLWidget::sizeChanged( const SbVec2s newSize )
{
  // virtual - does nothing
} // sizeChanged()

/*!
  This is the method which gets called whenever we change which OpenGL
  widget is used.

  Should be overloaded in subclasses which directly or indirectly
  store the return value from the SoWinGLWidget::getGLWidget() method.

  \sa sizeChanged()
*/
void
SoWinGLWidget::widgetChanged( HWND newWidget )
{
  // virtual
  // called whenever the widget is changed (i.e. at initialization
  // or after switching from single->double buffer)
} // widgetChanged()

/*!
  Sets the size of the GL canvas.
*/
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
} // setGLSize()

/*!
  Return the dimensions of the OpenGL canvas.
*/
SbVec2s
SoWinGLWidget::getGLSize( void ) const
{
  return PRIVATE( this )->glSize;
} // getGLSize()

/*!
  Return the aspect ratio of the OpenGL canvas.
*/
float
SoWinGLWidget::getGLAspectRatio( void ) const
{
  return ( float ) PRIVATE( this )->glSize[0] /
    ( float ) PRIVATE( this )->glSize[1];
} // getGLAspectRatio()

/*!
  \fn void SoWinGLWidget::setGlxSize( const SbVec2s size )
  This function has been renamed to the more appropriate setGLSize.
  \sa setGLSize
*/

/*!
  \fn SbVec2s SoWinGLWidget::getGlxSize( void ) const
  This function has been renamed to the more appropriate getGLSize.
  \sa getGLSize
*/

/*!
  \fn float SoWinGLWidget::getGlxAspectRatio(void) const
  This function has been renamed to the more appropriate getGLAspectRatio.
  \sa getGLAspectRatio
*/

/*!
 */
LRESULT // Used by SoWinRenderArea
SoWinGLWidget::eventHandler( HWND hwnd,
                             UINT message,
                             WPARAM wParam,
                             LPARAM lParam )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
  return 0;
} // eventHandler()

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

/*!
  Returns TRUE if the normal GL context is in RGBA mode.
  Return FALSE if color index mode is used.
*/
SbBool
SoWinGLWidget::isRGBMode( void )
{
  return ( PRIVATE( this )->glModes & SO_GL_RGB );
} // isRGBMode()

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

  this->setFocusProxy( this->getNormalWidget( ) );
  
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

/*!
  This method calls make-current on the correct context and ups the lock
  level.
*/
void
SoWinGLWidget::glLockNormal( void )
{
  assert( PRIVATE( this )->hdcNormal != NULL );
  wglMakeCurrent( PRIVATE( this )->hdcNormal, PRIVATE( this )->ctxNormal );
} // glLockNormal()

/*!
  This method drops the lock level.
*/
void
SoWinGLWidget::glUnlockNormal( void )
{
  wglMakeCurrent( NULL, NULL );
} // glUnlockNormal()

/*!
  This method calls make-current on the correct context and ups the lock
  level.
*/
void
SoWinGLWidget::glLockOverlay( void )
{
  wglMakeCurrent( PRIVATE( this )->hdcOverlay, PRIVATE( this )->ctxOverlay ); 
} // glLockOverlay()

/*!
  This method drops the lock level.
*/
void
SoWinGLWidget::glUnlockOverlay( void )
{
  wglMakeCurrent( NULL, NULL );
} // glUnlockOverlay()

/*!
 */
void
SoWinGLWidget::glSwapBuffers( void )
{
  assert( PRIVATE( this )->hdcNormal != NULL );
  Win32::SwapBuffers( PRIVATE( this )->hdcNormal );
} // glSwapBuffers()

/*!
  Flush the current GL buffer. Simply calls glFlush().
*/
void
SoWinGLWidget::glFlushBuffer( void )
{
  glFlush( );
} // glFlushBuffer()

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

  if ( ! this->glRealized ) {
    this->glRealized = TRUE;
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
