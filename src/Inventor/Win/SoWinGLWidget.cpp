/**************************************************************************
 *
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
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
 **************************************************************************/

#if SOWIN_DEBUG
/*static const char rcsid[] =
  "$Id$";*/
#endif // SOWIN_DEBUG

#include <conio.h>

#include <Inventor/SbVec2s.h>

#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/SoWinGLWidget.h>


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
    this->managerWidget = NULL;
    this->doubleBufferWidget = NULL;
    this->singleBufferWidget = NULL;
    this->overlayWidget = NULL;

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

    this->parent = parent;

    if ( build )
    {
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

HWND SoWinGLWidget::getNormalWindow( void )
{
    if ( this->isDoubleBuffer( ) ) {
        return this->doubleBufferWidget;
    } else {
        return this->singleBufferWidget;
    }
}

HWND SoWinGLWidget::getOverlayWindow( void )
{
    assert( this->overlayWidget != NULL );
    return this->overlayWidget; // FIXME: overlay not supported
}

HWND SoWinGLWidget::getNormalWidget( void )
{
    return this->getNormalWindow( );
}

HWND SoWinGLWidget::getOverlayWidget( void )
{
    return this->getOverlayWindow( ); // FIXME: overlay not supported
}

HDC SoWinGLWidget::getNormalDC( void )
{
    assert( this->hdcNormal != NULL );
    return this->hdcNormal;
}

HDC SoWinGLWidget::getOverlayDC( void )
{
    assert( this->hdcOverlay != NULL );
    return this->hdcOverlay; // FIXME: overlay not supported
}

HGLRC SoWinGLWidget::getNormalContext( void )
{
    assert( this->ctxNormal != NULL ); 
    return this->ctxNormal;
}

HGLRC SoWinGLWidget::getOverlayContext( void )
{
    assert( this->ctxOverlay != NULL );
    return this->ctxOverlay; // FIXME: overlay not supported 
}

void SoWinGLWidget::setStealFocus( SbBool doStealFocus )
{
    this->stealFocus = doStealFocus;
}    

void SoWinGLWidget::setNormalVisual( PIXELFORMATDESCRIPTOR * vis )
{
    assert( vis != NULL );
    memcpy( ( & this->pfdNormal ), vis, sizeof( PIXELFORMATDESCRIPTOR ) );
}

PIXELFORMATDESCRIPTOR * SoWinGLWidget::getNormalVisual( void )
{
    return ( & this->pfdNormal );
}

void SoWinGLWidget::setOverlayVisual( PIXELFORMATDESCRIPTOR * vis )
{
    // Note: setOverlayVisual( ) has no effect on Win32 machines

    assert( vis != NULL );
    memcpy( ( & this->pfdOverlay ), vis, sizeof( PIXELFORMATDESCRIPTOR ) );
}

PIXELFORMATDESCRIPTOR * SoWinGLWidget::getOverlayVisual( void )
{
    return ( & this->pfdOverlay );
}

void SoWinGLWidget::setPixelFormat( int format )
{
    this->nPixelFormat = format;
    //assert( SetPixelFormat( this->hdcNormal, this->nPixelFormat, &pfdNormal ) == TRUE );
}

int SoWinGLWidget::getPixelFormat( void )
{
    return this->nPixelFormat;
}

void SoWinGLWidget::setDoubleBuffer( SbBool set )
{
    if ( set ) {
        this->glModes |= SO_GL_DOUBLE;
    } else {
        this->glModes ^= SO_GL_DOUBLE;
    }
}

SbBool SoWinGLWidget::isDoubleBuffer( void )
{
    return ( this->glModes & SO_GL_DOUBLE );
}
    
void SoWinGLWidget::setBorder( SbBool set )
{
    // FIXME: function not implemented
}

int SoWinGLWidget::getBorderSize( void )
{
    return this->borderSize;
}

SbBool SoWinGLWidget::isBorder( void ) const
{
    return ( this->borderSize != 0 );
}
    
void SoWinGLWidget::setDrawToFrontBufferEnable( SbBool enable )
{
    this->enableDrawToFrontBuffer = enable;
}

SbBool SoWinGLWidget::isDrawToFrontBufferEnable( void ) const
{
    return this->enableDrawToFrontBuffer;
}

void SoWinGLWidget::setCursor( HCURSOR newCursor )
{
    assert( newCursor != NULL );
    this->currentCursor = newCursor;
    SetCursor( newCursor );
}

HCURSOR SoWinGLWidget::getCursor( void )
{
    return this->currentCursor;
}    

///////////////////////////////////////////////////////////////////
//
//  (protected)
//
    
void SoWinGLWidget::redraw( void )
{
    // virtual - does nothing 
}

void SoWinGLWidget::redrawOverlay( void )
{
    // virtual - does nothing 
}

void SoWinGLWidget::processEvent( MSG * msg )
{
    // virtual - does nothing 
}
    
void SoWinGLWidget::initGraphic( void )
{
    // virtual - does nothing 
    // called whenever a GL window gets created
}

void SoWinGLWidget::initOverlayGraphic( void )
{
    // virtual - does nothing 
}

void SoWinGLWidget::sizeChanged( const SbVec2s newSize ) // virtual,
{
    // virtual - does nothing
}

void SoWinGLWidget::widgetChanged( HWND newWidget )
{
    // virtual - does nothing
    // called whenever the widget is changed (i.e. at initialization
    // or after switching from single->double buffer)
}
    
void SoWinGLWidget::setGlxSize( SbVec2s newSize )
{
    this->glSize = newSize;
    this->sizeChanged( newSize );
}

const SbVec2s SoWinGLWidget::getGlxSize( void ) const
{
    return this->getGLSize( );
}

const SbVec2s SoWinGLWidget::getGLSize( void ) const
{
    return this->glSize;
}
    
void SoWinGLWidget::eventHandler( HWND, SoWinGLWidget *, MSG *, BOOL *)
{
    // FIXME: function not implemented
}

void SoWinGLWidget::setStereoBuffer( SbBool set )
{
    // FIXME: function not implemented
}

SbBool SoWinGLWidget::isStereoBuffer( void )
{
    return ( this->glModes & SO_GLX_STEREO );
}

SbBool SoWinGLWidget::isRGBMode( void )
{
    return ( this->glModes & SO_GLX_RGB );
}
    
int	SoWinGLWidget::getDisplayListShareGroup( HGLRC ctx )
{
    return 0; // FIXME: nothing done yet!
}
    
HWND SoWinGLWidget::buildWidget( HWND parent )
{
    // Build managerWidget
    // Used only for borders
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

    RegisterClass( &windowclass );

    RECT rect;
    GetClientRect( parent, &rect );

    this->managerWidget = CreateWindow(
                            wndclassname,
						    wndclassname,
						    WS_CLIPCHILDREN|
                            WS_CLIPSIBLINGS|
                            WS_CHILD|
                            //WS_BORDER,
                            WS_THICKFRAME,    //makes trouble
                            //WS_DLGFRAME,
						    0,
                            0,
                            rect.right,
                            rect.bottom,
						    parent,
						    menu,
						    SoWin::getInstance(),
						    this );

    assert( IsWindow( this->managerWidget ) );
//    SoWin::addMessageCB( this->managerWindowProc );    // get messages

    if( this->glModes & SO_GL_OVERLAY ) {
        this->buildOverlayGLWidget( & this->pfd ); // FIXME: overlay not supported
    } else {
        this->buildNormalGLWidget( & this->pfd );
    }

    return this->managerWidget;
}

HWND SoWinGLWidget::getGlxMgrWidget( void )
{
    return this->managerWidget;
}

HWND SoWinGLWidget::getGLWidget( void )
{
    return this->getNormalWindow( );
}

SbBool SoWinGLWidget::makeNormalCurrent( void )
{
    return ( wglMakeCurrent( (HDC)this->hdcNormal, this->ctxNormal ) );
}

SbBool SoWinGLWidget::swapNormalBuffers( void )
{
    if ( this->overlayWidget ) {
        return ( wglSwapLayerBuffers( ( HDC ) this->hdcNormal, WGL_SWAP_MAIN_PLANE ) );
    } else {
        return ( SwapBuffers( ( HDC ) this->hdcNormal ) );
    }
}

SbBool SoWinGLWidget::swapOverlayBuffers( void )
{
    return ( wglSwapLayerBuffers( ( HDC ) this->hdcOverlay, WGL_SWAP_OVERLAY1 ) );
}

DWORD SoWinGLWidget::getThreadId( void )
{
    return this->dwThreadId;
}

void SoWinGLWidget::setThreadId( DWORD id )
{ 
    this->dwThreadId = id;
}

void SoWinGLWidget::changeCursor( HCURSOR newCursor )
{
    this->setCursor( newCursor );
}

void SoWinGLWidget::glExpose( void )
{
    if ( firstRealize ) {
        firstRealize = FALSE;
        this->glInit( );
    }
}

void SoWinGLWidget::glInit( void )
{

    this->ctxNormal = wglCreateContext( this->hdcNormal );

/*    if ( ! this->ctxNormal )
    {
        SoDebugError::postInfo( "SoWinGLWidget::glInit",
        "wglCreateContext() returned NULL" );
    }*/

    assert( this->ctxNormal != NULL );
    if ( this->isDoubleBuffer( ) )   //FIXME: don't support overlay
    {
        assert( this->hdcDouble != NULL );
        this->hdcNormal = this->hdcDouble;
        this->ctxDouble = this->ctxNormal;
    }
    else
    {
        assert( this->hdcSingle != NULL );
        this->hdcNormal = this->hdcSingle;
        this->ctxSingle = this->ctxNormal;
    }

    this->glLock( );
    glEnable( GL_DEPTH_TEST );
    this->glUnlock( );
}

void SoWinGLWidget::glReshape( int width, int height ) // virtual
{
    // virtual: function not implemented
}

void SoWinGLWidget::glRender( void ) // virtual
{
    // virtual: function not implemented
}

void SoWinGLWidget::glLock( void )
{
  assert( this->hdcNormal != NULL );
  wglMakeCurrent( this->hdcNormal, this->ctxNormal );
}

void SoWinGLWidget::glUnlock( void )
{
    // FIXME: function not implemented
    wglMakeCurrent( this->hdcNormal, NULL );
}

void SoWinGLWidget::glSwapBuffers( void )
{
    // nothing to do...
    assert( this->hdcNormal != NULL );
    SwapBuffers( this->hdcNormal );
}

void SoWinGLWidget::glFlushBuffer( void )
{
  // nothing to do...
  glFlush( );
}

float SoWinGLWidget::getGLAspectRatio( void )
{
    short width, height;
    this->glSize.getValue( width, height );
    return ( ( float ) width / ( float ) height );
}

///////////////////////////////////////////////////////////////////
//
//  (private)
//

void SoWinGLWidget::buildNormalGLWidget( PIXELFORMATDESCRIPTOR *pfd )
{
    LPCTSTR cursor = MAKEINTRESOURCE(IDC_NO);
    HMENU menu = NULL;
    LPSTR wndclassname = "SoWinGLWidget_glwidget";

    WNDCLASS windowclass;
    windowclass.lpszClassName = wndclassname;
    windowclass.hInstance = SoWin::getInstance();
    windowclass.lpfnWndProc = this->glWindowProc;
    windowclass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    windowclass.lpszMenuName = NULL;
    windowclass.hIcon = NULL;
    windowclass.hCursor = this->currentCursor = LoadCursor( NULL, cursor );
    windowclass.hbrBackground = NULL;
    windowclass.cbClsExtra = 0;
    windowclass.cbWndExtra = 4;

    RegisterClass( & windowclass );

    RECT rect;
    GetClientRect( this->managerWidget, &rect);

    HWND normalwidget = CreateWindow( wndclassname,
						              wndclassname,
						              WS_CLIPCHILDREN|
                                      WS_CLIPSIBLINGS|
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

    this->hdcNormal = GetDC( normalwidget );
    assert( this->hdcNormal != NULL );

    this->firstRealize = TRUE;

    memcpy( (void *) (& this->pfdNormal), pfd, sizeof(PIXELFORMATDESCRIPTOR) );

    this->nPixelFormat = this->ChoosePixelFormatOIV( this->hdcNormal,
                                                     pfd_cColorBits,
                                                     this->glModes,
                                                     pfd );

    assert( SetPixelFormat( this->hdcNormal, this->nPixelFormat, pfd ) == TRUE );
    
    if( this->glModes & SO_GL_DOUBLE ) {// ( vis->dwFlags & PFD_DOUBLEBUFFER )
        memcpy( & this->pfdDouble, pfd, sizeof( PIXELFORMATDESCRIPTOR ) );
        this->hdcDouble = this->hdcNormal;
        this->doubleBufferWidget = normalwidget;
    } else {
        memcpy( & this->pfdSingle, pfd, sizeof( PIXELFORMATDESCRIPTOR ) );
        this->hdcSingle = this->hdcNormal;
        this->singleBufferWidget = normalwidget;
    }

    ShowWindow( normalwidget, SW_SHOW );
//        SoWin::addProcessEventFunction( processEvent ); // TEST
}

void SoWinGLWidget::buildOverlayGLWidget( PIXELFORMATDESCRIPTOR *pfd )
{
    // FIXME: function not implemented
}

void SoWinGLWidget::destroyNormalWindows( void )
{
    // FIXME: function not implemented
}

void SoWinGLWidget::destroyGLWidget( HWND &w, HGLRC &ctx, SbBool normalWindow )
{
    // FIXME: function not implemented
}

void SoWinGLWidget::managerStructureNotifyCB( HWND, SoWinGLWidget *, MSG *, BOOL *)
{
    // FIXME: function not implemented
}

LRESULT CALLBACK SoWinGLWidget::managerWindowProc( HWND window,
                                           UINT message,
		 					               WPARAM wparam,
                                           LPARAM lparam )
{
    if ( message == WM_CREATE ) {
		CREATESTRUCT * createstruct;
		createstruct = ( CREATESTRUCT * ) lparam;
		SetWindowLong( window, 0, (LONG) ( createstruct->lpCreateParams ) );
		return 0;
	}

	SoWinGLWidget * object = ( SoWinGLWidget * ) GetWindowLong( window, 0 );
	//if ( object && ( window == object->getManagerWidget( ) ) ) {
    if ( object && object->getManagerWidget( ) ) {
        switch ( message )
        {
            case WM_SIZE:
                object->sizeChanged( SbVec2s( LOWORD( lparam ), HIWORD( lparam ) ) );
                MoveWindow( object->getNormalWidget( ),
                            0,
                            0,
                            LOWORD( lparam ),
                            HIWORD( lparam ),
                            TRUE );
                return 0;
        }
        //return 0;
		return object->dispatchMessage( window, message, wparam, lparam );
	}
	return DefWindowProc( window, message, wparam, lparam );
}

LRESULT CALLBACK SoWinGLWidget::glWindowProc( HWND window,
                                       UINT message,
		 					           WPARAM wparam,
                                       LPARAM lparam )
{
    if ( message == WM_CREATE ) {
		CREATESTRUCT * createstruct;
		createstruct = ( CREATESTRUCT * ) lparam;
		SetWindowLong( window, 0, (LONG) ( createstruct->lpCreateParams ) );
		return 0;
	}

    PAINTSTRUCT ps;

	SoWinGLWidget * object = ( SoWinGLWidget * ) GetWindowLong( window, 0 );
    //if ( object && ( window == object->getNormalWidget( ) ) ) {

    if ( object && object->getNormalWidget( ) ) {

        MSG msg;
        POINT pt;
        pt.x = LOWORD( lparam );
        pt.y = HIWORD( lparam );
        msg.hwnd = window;
        msg.lParam = lparam;
        msg.message = message;
        msg.pt = pt;
        msg.time = GetTickCount( );
        msg.wParam = wparam;
        object->processEvent( & msg );
        
        switch ( message )
        {
            case WM_SIZE:
                _cprintf( "SoWinGLWidget: WM_SIZE\n" );
                object->glReshape( LOWORD( lparam ), HIWORD( lparam ) );
                return 0;

            case WM_PAINT:
                object->hdcNormal = BeginPaint( window, & ps );
                _cprintf("SoWinGLWidget: WM_PAINT\n");
                object->glExpose( );
                object->glRender( );
                //object->OnGLPaint( window, message, wparam, lparam );
                EndPaint( window, & ps );
                return 0;

            case WM_LBUTTONDOWN:
                _cprintf( "SoWinGLWidget: WM_LBUTTONDOWN\n" );
                // call function
                return 0;

            case WM_MOUSEMOVE:
                if ( wparam & MK_LBUTTON )  // drag
                    _cprintf( "SoWinGLWidget: WM_MOUSEMOVE & MK_LBUTTON x:%d y:%d\n",
                              LOWORD( lparam ),
                              HIWORD( lparam ) );
                return 0;

            case WM_DESTROY:
                _cprintf( "SoWinGLWidget: WM_DESTROY\n" );
                //object->OnGLDestroy( window, message, wparam, lparam );
                return 0;
        }
		return object->dispatchMessage( window, message, wparam, lparam );
	}
	return DefWindowProc( window, message, wparam, lparam );
}

LRESULT
SoWinGLWidget::dispatchMessage( HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc( window, message, wparam, lparam );
}

HWND SoWinGLWidget::getManagerWidget( void )
{
    return this->managerWidget;
}
