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

#include <assert.h>
#include <string.h>
#include <windows.h>
#include <GL/gl.h>

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SoLists.h>
#include <Inventor/errors/SoDebugError.h>

#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoWinComponent.h>
#include <Inventor/Win/SoWinGLWidget.h>
#include <Inventor/Win/SoWinRenderArea.h>
#include <Inventor/Win/viewers/SoWinViewer.h>
#include <Inventor/Win/viewers/SoWinFullViewer.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <sowindefs.h> // SOWIN_STUB

// *************************************************************************

SOWIN_OBJECT_ABSTRACT_SOURCE(SoWinComponent);

void
SoWinComponent::initClasses( void )
{
  SoWinComponent::initClass( );
  SoWinGLWidget::initClass( );
  SoWinRenderArea::initClass( );
  SoWinViewer::initClass( );
  SoWinFullViewer::initClass( );
  SoWinExaminerViewer::initClass( );
} // initClasses()

// *************************************************************************

// static variables
SbPList * SoWinComponent::widgets = NULL;
SbPList * SoWinComponent::components = NULL;

// *************************************************************************

///////////////////////////////////////////////////////////////////
//
//  Constructor/Destructor
//  (protected)
//

SoWinComponent::SoWinComponent( const HWND parent,
                                const char * const name,
                                const SbBool embed )
{
  this->constructorParent = parent;

  this->firstRealize = TRUE;
  this->size = SbVec2s( -1, -1 );

  if ( ! SoWinComponent::components )
		SoWinComponent::components = new SbPList;

	SoWinComponent::components->append( this );

  if ( name ) this->widgetName = name;
  
  if ( ( parent == ( HWND ) NULL ) || ! embed ) {
    this->embedded = FALSE;
    this->widget = this->buildFormWidget( parent );
  } 
  else {
    this->parent = parent;
    this->embedded = TRUE;
  }
  /*if ( parent ) {
        if ( parent == SoWin::getTopLevelWidget( ) )
        this->embedded = FALSE;
  }*/
}

///////////////////////////////////////////////////////////////////
//
//  (public)
//

SoWinComponent::~SoWinComponent( void )
{
  UnregisterClass( this->getWidgetName( ), SoWin::getInstance( ) );
}

void
SoWinComponent::show( void )
{
  ShowWindow( this->widget, SW_SHOW );
}

void
SoWinComponent::hide( void )
{
  ShowWindow( this->widget, SW_HIDE );
}

void
SoWinComponent::goFullScreen( SbBool enable )
{
  HWND hwnd;
  if ( this->embedded )
    hwnd = this->parent;
  else
    hwnd = this->widget;

  if ( enable ) {
    this->style = GetWindowLong( hwnd, GWL_STYLE );
    this->exstyle = GetWindowLong( hwnd, GWL_EXSTYLE );

    SetWindowLong( hwnd, GWL_STYLE, WS_POPUP );
    SetWindowLong( hwnd, GWL_EXSTYLE, WS_EX_TOPMOST );
    MoveWindow( hwnd,
                0,
                0,
                GetSystemMetrics( SM_CXSCREEN ),
                GetSystemMetrics( SM_CYSCREEN ),
                TRUE );
  }
  else {
    SetWindowLong( hwnd, GWL_STYLE, this->style );
    SetWindowLong( hwnd, GWL_EXSTYLE, this->exstyle );
    UpdateWindow( hwnd ); // FIXME: save old size?
    /*
    short width, height;
    this->size.getValue( width, height );

    RECT rect;
    GetWindowRect( this->widget, & rect );
    MoveWindow( this->widget, rect.left, rect.top, width, height, TRUE );
    */
  }
}

SbBool
SoWinComponent::isVisible( void )
{
  return IsWindowVisible( widget );
}

HWND
SoWinComponent::getWidget( void ) const
{
  return this->getBaseWidget( );
}

HWND
SoWinComponent::baseWidget( void ) const
{
  return this->getBaseWidget( );
}

HWND
SoWinComponent::getBaseWidget( void ) const
{
  return this->widget;
}

SbBool
SoWinComponent::isTopLevelShell( void ) const
{
  // FIXME: function not implemented
  SOWIN_STUB( );
  return FALSE;
}

HWND
SoWinComponent::getShellWidget( void ) const
{
  // FIXME: function not implemented
  SOWIN_STUB( );
  return NULL; // this->getMDIAncestor( ( HWND ) this->baseWidget );
}

HWND
SoWinComponent::getParentWidget( void ) const
{
  return this->parent;
}

int *
SoWinComponent::getDisplay( void )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
  return NULL;
}

void
SoWinComponent::setSize( const SbVec2s size )
{
  this->size = size;

  short width, height;
  this->size.getValue( width, height );

  RECT rect;
  GetWindowRect( this->widget, & rect );
  MoveWindow( this->widget, rect.left, rect.top, width, height, TRUE );
}

SbVec2s
SoWinComponent::getSize( void )
{
  return this->size;
}

const char *
SoWinComponent::getWidgetName( void ) const
{
  return this->widgetName.getString( );
}

const char *
SoWinComponent::getClassName( void ) const
{
  return this->widgetClass.getString( );
}

void
SoWinComponent::setTitle( const char * const title )
{
  if ( title ) this->title = title;
  else this->title = "";

  if ( this->parent ) {
    SetWindowText( this->parent , ( LPCTSTR ) this->title.getString( ) );
  } 
  else {
    SetWindowText( this->widget, ( LPCTSTR ) this->title.getString( ) );
  }
}

const char *
SoWinComponent::getTitle( void ) const
{
  return this->title.getLength( ) ?
    this->title.getString( ) : this->getDefaultTitle( );
}

void
SoWinComponent::setIconTitle( const char * const title )
{
  if (title) this->iconTitle = title;
  else this->iconTitle = "";
}

const char *
SoWinComponent::getIconTitle( void ) const
{
  return this->iconTitle.getLength( ) ? 
    this->iconTitle.getString( ) : this->getDefaultIconTitle( );
}

void
SoWinComponent::setWindowCloseCallback( SoWinComponentCB * func, void * data )
{
  /*    this->windowCloseFunc = func;
        this->windowCloseData = data; */
  // FIXME: function not implemented
  SOWIN_STUB( );
}

SoWinComponent *
SoWinComponent::getComponent( HWND const widget )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
  return NULL;
}

///////////////////////////////////////////////////////////////////
//
//  (protected)
//

void
SoWinComponent::setBaseWidget( HWND widget )
{
  assert( IsWindow( widget ) );
  this->widget = widget;
}

void
SoWinComponent::setClassName( const char * const name )
{
  if ( name ) this->widgetClass = name;
  else this->widgetClass = "";
}

void
SoWinComponent::registerWidget( HWND widget )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
}

void
SoWinComponent::unregisterWidget( HWND widget )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
}

HWND
SoWinComponent::buildFormWidget( HWND parent )
{
  WNDCLASS windowclass;

  LPCTSTR icon = MAKEINTRESOURCE( IDI_APPLICATION );
  LPCTSTR cursor = MAKEINTRESOURCE( IDC_ARROW );
  HBRUSH brush = ( HBRUSH ) GetStockObject( COLOR_BACKGROUND );
  HMENU menu = NULL;
  HWND widget;

  windowclass.lpszClassName = ( char * ) this->getDefaultWidgetName( ); // FIXME: virtual function
  windowclass.hInstance = SoWin::getInstance( );
  windowclass.lpfnWndProc = SoWinComponent::windowProc;
  windowclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon( NULL, icon );
  windowclass.hCursor = LoadCursor( NULL, cursor );
  windowclass.hbrBackground = brush;
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

  this->style = /*WS_CLIPCHILDREN | WS_CLIPSIBLINGS |*/ WS_OVERLAPPEDWINDOW;
  this->exstyle = NULL;

  widget = CreateWindow( ( char * ) this->getDefaultWidgetName( ),
                         ( char * ) this->getTitle( ),
	                 this->style,
	                 0, // GetClientRect gives rect.top == rect.left == 0
                         0,
                         rect.right,
                         rect.bottom,
                         parent,
                         menu,
                         SoWin::getInstance( ),
                         this );

  return widget;
}

const char *
SoWinComponent::getDefaultWidgetName( void ) const
{
  static const char defaultWidgetTitle[] = "Win Component";
  return defaultWidgetTitle;
}

const char *
SoWinComponent::getDefaultTitle( void ) const
{
  static const char defaultTitle[] = "Win Component";
  return defaultTitle;
}

const char *
SoWinComponent::getDefaultIconTitle( void ) const
{
  static const char defaultIconTitle[] = "Win Component";
  return defaultIconTitle;
}

void
SoWinComponent::windowCloseAction( void )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
}

void
SoWinComponent::afterRealizeHook( void )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
}

void
SoWinComponent::addVisibilityChangeCallback( SoWinComponentVisibilityCB * func, void * user )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
}

void
SoWinComponent::removeVisibilityChangeCallback( SoWinComponentVisibilityCB * func, void * user )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
}

void
SoWinComponent::openHelpCard( const char * name )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
}

void
SoWinComponent::setResize( SbBool set )
{
  this->resizeBaseWidget = set;
}

SbBool
SoWinComponent::getResize( void )
{
  return this->resizeBaseWidget;
}

HPALETTE
SoWinComponent::_setupColorPalette( HDC )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
  return NULL;
}

void
SoWinComponent::unSubclassDialog( HWND hWnd )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
}

void
SoWinComponent::subclassDialog( HWND hWnd )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
}

void
SoWinComponent::drawDialogIcon( HWND hWnd )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
}

LRESULT CALLBACK
SoWinComponent::dlgWndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
  return 0;
}

HWND
SoWinComponent::getMDIAncestor( HWND hwnd )
{
  assert( IsWindow( hwnd ) );

  // FIXME: ???

  HWND parent = NULL;
  HWND ancestor = NULL;

  parent = GetParent( hwnd );

  while ( parent )
    {
      ancestor = parent;
      parent = GetParent( ancestor );
    }

  return ancestor;
}

int
SoWinComponent::ChoosePixelFormatOIV( HDC hdc,
                                      int pixelType,
                                      int glModes,
                                      PIXELFORMATDESCRIPTOR * pfd )
{
  assert( hdc != NULL );
  assert( pfd != NULL );

  memset( pfd, 0, sizeof( PIXELFORMATDESCRIPTOR ) );

  pfd->nSize = sizeof( PIXELFORMATDESCRIPTOR );
  pfd->nVersion = 1;
  pfd->dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_SWAP_LAYER_BUFFERS;
  if ( glModes & GL_DOUBLEBUFFER ) {
    pfd->dwFlags |= PFD_DOUBLEBUFFER;
  }
  pfd->iPixelType = pixelType;
  pfd->cColorBits = pfd_cColorBits;
  pfd->cDepthBits = pfd_cDepthBits;
  pfd->iLayerType = PFD_MAIN_PLANE;  // FIXME: no support for overlay

  int pixelformat = ChoosePixelFormat( hdc, pfd );
  assert( pixelformat != 0 );

  return pixelformat;
}

///////////////////////////////////////////////////////////////////
//
//  (private)
//

LRESULT CALLBACK
SoWinComponent::windowProc( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  if ( message == WM_CREATE )
  {
    CREATESTRUCT * createstruct;
    createstruct = ( CREATESTRUCT * )lparam;
    SetWindowLong( window, 0, ( LONG ) ( createstruct->lpCreateParams ) );
    return 0;
  }

  SoWinComponent * object = ( SoWinComponent * ) GetWindowLong( window, 0 );
  if ( object ) {
    switch ( message )
      {
      case WM_SIZE:
        return object->onSize( window, message, wparam, lparam );

      case WM_PAINT:
        return object->onPaint( window, message, wparam, lparam );

      case WM_DESTROY:
        return object->onDestroy( window, message, wparam, lparam );
      }
  }
  return DefWindowProc( window, message, wparam, lparam );
}

LRESULT
SoWinComponent::onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  this->size = SbVec2s( HIWORD(lparam), LOWORD(lparam) );
  return 0;
}

LRESULT
SoWinComponent::onPaint( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
  return 0;
}

LRESULT
SoWinComponent::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  this->windowCloseAction( );
  PostQuitMessage( 0 );
  return 0;
}
