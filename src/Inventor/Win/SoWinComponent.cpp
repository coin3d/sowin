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

  this->closeCB = NULL;
  this->closeCBData = NULL;
  this->firstRealize = TRUE;
  this->fullScreen = FALSE;
  this->size = SbVec2s( -1, -1 );

  if ( ! SoWinComponent::components )
		SoWinComponent::components = new SbPList;

	SoWinComponent::components->append( this );

  if ( name ) this->widgetName = name;
  
  if ( ! IsWindow( parent ) || ! embed ) {
    this->parent = NULL;
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
SoWinComponent::goFullScreen( const SbBool enable )
{
  // FIXME: save window position and size
  
  HWND hwnd;
  
  if ( this->embedded )
    hwnd = this->parent;
  else
    hwnd = this->widget;

  if ( enable ) {
    RECT rect;
    GetWindowRect( hwnd, & rect );
    this->pos.setValue( rect.left, rect.top );
    this->size.setValue( rect.right - rect.left, rect.bottom - rect.top );
    
    this->fullScreen = TRUE;

    this->style = SetWindowLong( hwnd, GWL_STYLE, WS_POPUP );
    this->exstyle = SetWindowLong( hwnd, GWL_EXSTYLE, WS_EX_TOPMOST );

    MoveWindow( hwnd,
                0,
                0,
                GetSystemMetrics( SM_CXSCREEN ),
                GetSystemMetrics( SM_CYSCREEN ),
                FALSE );

    ShowWindow( hwnd, SW_SHOW ); // FIXME: why ? mariusbu 20010718.
  }
  else {
    this->fullScreen = FALSE;

    SetWindowLong( hwnd, GWL_STYLE, this->style );
    SetWindowLong( hwnd, GWL_EXSTYLE, this->exstyle );

    ShowWindow( hwnd, SW_SHOW ); // FIXME: why ? mariusbu 20010718.
    
    MoveWindow( hwnd, this->pos[0], this->pos[1], this->size[0], this->size[1], TRUE );
  }
}

SbBool
SoWinComponent::isFullScreen( void ) const
{
  return this->fullScreen;
}

SbBool
SoWinComponent::isVisible( void )
{
  return IsWindowVisible( this->widget );
}

HWND
SoWinComponent::getWidget( void ) const
{
  return this->widget;
}

HWND
SoWinComponent::baseWidget( void ) const
{
  return this->getBaseWidget( );
}

HWND
SoWinComponent::getBaseWidget( void ) const
{
  // FIXME: this method should return the root in the
  // parent-children tree. Is this correct for this method ?
  // mariusbu 20010718.
  
  HWND parent = NULL;
  HWND ancestor = NULL;

  parent = GetParent( this->widget );

  while ( parent )
    {
      ancestor = parent;
      parent = GetParent( ancestor );
    }

  return ancestor;

  // return this->widget;
}

SbBool
SoWinComponent::isTopLevelShell( void ) const
{
  return ( this->embedded ? FALSE : TRUE );
}

HWND
SoWinComponent::getShellWidget( void ) const
{
  // FIXME: is this correct for this method ? mariusbu 20010718.
  return this->getBaseWidget( );
}

HWND
SoWinComponent::getParentWidget( void ) const
{
  return this->parent;
}

void
SoWinComponent::setSize( const SbVec2s size )
{
  this->size = size;

  HWND hwnd = ( IsWindow( this->parent ) ? this->parent : this->widget );
  UINT flags = SWP_NOMOVE | SWP_NOZORDER;
  SetWindowPos( hwnd, NULL, 0, 0, size[0], size[1], flags );
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
  this->closeCB = func;
  this->closeCBData = data; 
}

SoWinComponent *
SoWinComponent::getComponent( HWND const widget )
{
  // FIXME: function not implemented
  SOWIN_STUB( );
  return NULL;

  /* This code is lifted from SoQt. Not working ( methinks )! mariusbu 20010718   
  for ( int i = 0; i < SoWinComponentP::sowincomplist->getLength( ); i++ ) {
    SoWinComponent * c = ( SoWinComponent * ) ( * SoWinComponentP::sowincomplist )[i];
    if ( c->getWidget( ) == this->widget ) return c;
  }
  return NULL;
  */
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
  HBRUSH brush = ( HBRUSH ) GetStockObject( COLOR_BTNFACE );
  HMENU menu = NULL;
  HWND widget;

  windowclass.lpszClassName = ( char * ) this->getDefaultWidgetName( ); // FIXME: virtual function
  windowclass.hInstance = SoWin::getInstance( );
  windowclass.lpfnWndProc = SoWinComponent::windowProc;
  windowclass.style = CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon( SoWin::getInstance( ), icon );
  windowclass.hCursor = LoadCursor( SoWin::getInstance( ), cursor );
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

  // FIXME: can this widget ever be toplevel ( not embedded ) ?
  // If so, make the window WS_VISIBLE and use CX_DEFAULTCOORD. mariusbu 20010718.

  this->style = WS_OVERLAPPEDWINDOW;
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
  MessageBox( this->widget,
    "The help functionality has not been implemented.",
    "SoWin", MB_ICONEXCLAMATION | MB_OK );  
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

      case WM_CLOSE:
        return object->onClose( window, message, wparam, lparam );

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
SoWinComponent::onClose( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  this->windowCloseAction( );
  if ( this->closeCB ) this->closeCB( this->closeCBData, this );
  return 0;
}

LRESULT
SoWinComponent::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  PostQuitMessage( 0 );
  return 0;
}
