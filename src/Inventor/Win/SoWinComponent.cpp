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

SOWIN_OBJECT_ABSTRACT_SOURCE( SoWinComponent );

// *************************************************************************

// The private data for the SoWinComponent.

class SoWinComponentP {
public:
  // Constructor.
  SoWinComponentP( SoWinComponent * o ) {
    this->owner = o;

    if ( ! SoWinComponentP::sowincomplist )
      SoWinComponentP::sowincomplist = new SbPList;
    SoWinComponentP::sowincomplist->append( ( void * ) this->owner );
  }

  // Destructor.
  ~SoWinComponentP( ) {
    if ( SoWinComponentP::sowincomplist->getLength( ) == 0 ) {
      delete SoWinComponentP::sowincomplist;
      SoWinComponentP::sowincomplist = NULL;
    }
  }
  
  static LRESULT CALLBACK eventHandler( HWND window,UINT message, WPARAM wparam, LPARAM lparam );
  LRESULT onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  LRESULT onClose( HWND window, UINT message, WPARAM wparam, LPARAM lparam );  
  LRESULT onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam );

  // Variables.

  HWND parent;
  HWND widget;
  SbBool embedded, shelled;
  SbString classname, widgetname, title;
  SoWinComponentCB * closeCB;
  void * closeCBdata;
  SbPList * visibilitychangeCBs;
  SbVec2s storesize;
  SbBool fullscreen;

  SbVec2s size;
  SbVec2s pos;

  LONG style;
  LONG exstyle;

  // List of all SoWinComponent instances. Needed for the
  // SoWinComponent::getComponent() function.
  static SbPList * sowincomplist;

private:
  SoWinComponent * owner;
};

SbPList * SoWinComponentP::sowincomplist = NULL;

#define PRIVATE( o ) ( o->pimpl )

// *************************************************************************

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

///////////////////////////////////////////////////////////////////
//
//  Constructor/Destructor
//  (protected)
//

SoWinComponent::SoWinComponent( const HWND parent,
                                const char * const name,
                                const SbBool embed )
{
  this->pimpl = new SoWinComponentP( this );
  this->realized = FALSE;
  
  PRIVATE( this )->parent = parent;
  PRIVATE( this )->closeCB = NULL;
  PRIVATE( this )->closeCBdata = NULL;
  PRIVATE( this )->fullscreen = FALSE;
  PRIVATE( this )->size = SbVec2s( -1, -1 );

  if ( name ) PRIVATE( this )->widgetname = name;
  
  if ( ! IsWindow( parent ) || ! embed ) {
    PRIVATE( this )->parent = NULL;
    PRIVATE( this )->embedded = FALSE;
    PRIVATE( this )->widget = this->buildFormWidget( parent );
  } 
  else {
    PRIVATE( this )->parent = parent;
    PRIVATE( this )->embedded = TRUE;
  }
}

///////////////////////////////////////////////////////////////////
//
//  (public)
//

SoWinComponent::~SoWinComponent( void )
{
  UnregisterClass( this->getWidgetName( ), SoWin::getInstance( ) );
  delete pimpl;
}

void
SoWinComponent::show( void )
{
  ShowWindow( PRIVATE( this )->widget, SW_SHOW );
}

void
SoWinComponent::hide( void )
{
  ShowWindow( PRIVATE( this )->widget, SW_HIDE );
}

void
SoWinComponent::goFullScreen( const SbBool enable )
{
  HWND hwnd;
  
  if ( PRIVATE( this )->embedded )
    hwnd = PRIVATE( this )->parent;
  else
    hwnd = PRIVATE( this )->widget;

  if ( enable ) {
    RECT rect;
    GetWindowRect( hwnd, & rect );
    PRIVATE( this )->pos.setValue( rect.left, rect.top );
    PRIVATE( this )->size.setValue( rect.right - rect.left, rect.bottom - rect.top );
    
    PRIVATE( this )->fullscreen = TRUE;

    PRIVATE( this )->style = SetWindowLong( hwnd, GWL_STYLE, WS_POPUP );
    PRIVATE( this )->exstyle = SetWindowLong( hwnd, GWL_EXSTYLE, WS_EX_TOPMOST );

    MoveWindow( hwnd,
                0,
                0,
                GetSystemMetrics( SM_CXSCREEN ),
                GetSystemMetrics( SM_CYSCREEN ),
                FALSE );

    ShowWindow( hwnd, SW_SHOW ); // FIXME: why ? mariusbu 20010718.
  }
  else {
    PRIVATE( this )->fullscreen = FALSE;

    SetWindowLong( hwnd, GWL_STYLE, PRIVATE( this )->style );
    SetWindowLong( hwnd, GWL_EXSTYLE, PRIVATE( this )->exstyle );

    ShowWindow( hwnd, SW_SHOW ); // FIXME: why ? mariusbu 20010718.
    
    MoveWindow( hwnd,
                PRIVATE( this )->pos[0],
                PRIVATE( this )->pos[1],
                PRIVATE( this )->size[0],
                PRIVATE( this )->size[1],
                TRUE );
  }
}

SbBool
SoWinComponent::isFullScreen( void ) const
{
  return PRIVATE( this )->fullscreen;
}

SbBool
SoWinComponent::isVisible( void )
{
  return IsWindowVisible( PRIVATE( this )->widget );
}

HWND
SoWinComponent::getWidget( void ) const
{
  return PRIVATE( this )->widget;
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

  return PRIVATE( this )->widget;
  
  HWND parent = NULL;
  HWND ancestor = NULL;

  parent = GetParent( PRIVATE( this )->widget );

  while ( parent ) {
    ancestor = parent;
    parent = GetParent( ancestor );
  }

  return ancestor;
}

SbBool
SoWinComponent::isTopLevelShell( void ) const
{
  return ( PRIVATE( this )->embedded ? FALSE : TRUE );
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
  return PRIVATE( this )->parent;
}

void
SoWinComponent::setSize( const SbVec2s size )
{
  PRIVATE( this )->size = size;

  HWND hwnd = ( IsWindow( PRIVATE( this )->parent ) ?
    PRIVATE( this )->parent : PRIVATE( this )->widget );
  UINT flags = SWP_NOMOVE | SWP_NOZORDER;
  SetWindowPos( hwnd, NULL, 0, 0, size[0], size[1], flags );
}

SbVec2s
SoWinComponent::getSize( void )
{
  return PRIVATE( this )->size;
}

const char *
SoWinComponent::getWidgetName( void ) const
{
  return PRIVATE( this )->widgetname.getString( );
}

const char *
SoWinComponent::getClassName( void ) const
{
  return PRIVATE( this )->classname.getString( );
}

void
SoWinComponent::setTitle( const char * const title )
{
  if ( title ) PRIVATE( this )->title = title;
  else PRIVATE( this )->title = "";

  if ( IsWindow( PRIVATE( this )->parent ) ) {
    SetWindowText( PRIVATE( this )->parent , ( LPCTSTR ) PRIVATE( this )->title.getString( ) );
  } 
  else {
    SetWindowText( PRIVATE( this )->widget, ( LPCTSTR ) PRIVATE( this )->title.getString( ) );
  }
}

const char *
SoWinComponent::getTitle( void ) const
{
  return PRIVATE( this )->title.getLength( ) ?
    PRIVATE( this )->title.getString( ) : this->getDefaultTitle( );
}

void
SoWinComponent::setWindowCloseCallback( SoWinComponentCB * func, void * data )
{
  PRIVATE( this )->closeCB = func;
  PRIVATE( this )->closeCBdata = data; 
}

SoWinComponent *
SoWinComponent::getComponent( HWND const widget )
{
  for ( int i = 0; i < SoWinComponentP::sowincomplist->getLength( ); i++ ) {
    SoWinComponent * c = ( SoWinComponent * ) ( * SoWinComponentP::sowincomplist )[i];
    if ( c->getWidget( ) == widget ) return c;
  }
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
  PRIVATE( this )->widget = widget;
}

void
SoWinComponent::setClassName( const char * const name )
{
  if ( name )
    PRIVATE( this )->classname = name;
  else
    PRIVATE( this )->classname = "";
}
/*
void
SoWinComponent::registerWidget( HWND widget )
{
  SoWinComponent::widgets->append( widget );
}

void
SoWinComponent::unregisterWidget( HWND widget )
{
  SoWinComponent::widgets->removeItem( widget );
}
*/
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
  windowclass.lpfnWndProc = SoWinComponentP::eventHandler;
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
    rect.right = 500;
    rect.bottom = 500;
  }

  // FIXME: can this widget ever be toplevel ( not embedded ) ?
  // If so, make the window WS_VISIBLE and use CX_DEFAULTCOORD. mariusbu 20010718.

  PRIVATE( this )->style = WS_OVERLAPPEDWINDOW;
  PRIVATE( this )->exstyle = NULL;

  widget = CreateWindow( ( char * ) this->getDefaultWidgetName( ),
                         ( char * ) this->getTitle( ),
	                       PRIVATE( this )->style,
		                     0, // GetClientRect gives rect.top == rect.left == 0
                         0,
                         rect.right,
                         rect.bottom,
                         parent,
                         menu,
                         SoWin::getInstance( ),
                         PRIVATE( this ) );

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
  MessageBox( PRIVATE( this )->widget,
    "The help functionality has not been implemented.",
    "SoWin", MB_ICONEXCLAMATION | MB_OK );  
  // FIXME: function not implemented
  SOWIN_STUB( );
}

///////////////////////////////////////////////////////////////////
//
//  (private)
//

LRESULT CALLBACK
SoWinComponentP::eventHandler( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  if ( message == WM_CREATE )
  {
    CREATESTRUCT * createstruct;
    createstruct = ( CREATESTRUCT * )lparam;
    SetWindowLong( window, 0, ( LONG ) ( createstruct->lpCreateParams ) );
    return 0;
  }

  SoWinComponentP * object = ( SoWinComponentP * ) GetWindowLong( window, 0 );
  
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
SoWinComponentP::onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  this->size = SbVec2s( HIWORD(lparam), LOWORD(lparam) );
  return 0;
}

LRESULT
SoWinComponentP::onClose( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  this->owner->windowCloseAction( );
  if ( this->closeCB ) this->closeCB( this->closeCBdata, owner );
  return 0;
}

LRESULT
SoWinComponentP::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  PostQuitMessage( 0 );
  return 0;
}
