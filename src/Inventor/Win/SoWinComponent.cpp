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
    
    if ( ! SoWinComponentP::sowinfullscreenlist )
      SoWinComponentP::sowinfullscreenlist = new SbPList;
    
  }

  // Destructor.
  ~SoWinComponentP( ) {

    if ( SoWinComponentP::sowincomplist ) {
      if ( SoWinComponentP::sowincomplist->getLength( ) == 0 ) {
        delete SoWinComponentP::sowincomplist;
        SoWinComponentP::sowincomplist = NULL;
      }
    }

    if ( SoWinComponentP::sowinfullscreenlist ) {
      if ( SoWinComponentP::sowinfullscreenlist->getLength( ) == 0 ) {
        delete SoWinComponentP::sowinfullscreenlist;
        SoWinComponentP::sowinfullscreenlist = NULL;
      }
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

  // List of all SoWinComponent instances. Needed for the
  // SoWinComponent::getComponent() function.
  static SbPList * sowincomplist;

  struct fullscreenData {
    HWND widget;
    SbVec2s pos;
    SbVec2s size;
    LONG style;
    LONG exstyle;
  };
  static SbPList * sowinfullscreenlist;

private:
  SoWinComponent * owner;
};

SbPList * SoWinComponentP::sowincomplist = NULL;
SbPList * SoWinComponentP::sowinfullscreenlist = NULL;

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
 
  if ( name ) PRIVATE( this )->widgetname = name;
  
  if ( ! IsWindow( parent ) || ! embed ) {
    PRIVATE( this )->parent = NULL;
    PRIVATE( this )->embedded = FALSE;
    PRIVATE( this )->widget = this->buildFormWidget( parent );
  } 
  else {
    PRIVATE( this )->parent = parent;
    PRIVATE( this )->embedded = TRUE;
    PRIVATE( this )->widget = NULL;
  }
}

///////////////////////////////////////////////////////////////////
//
//  (public)
//

SoWinComponent::~SoWinComponent( void )
{
  if ( IsWindow( PRIVATE( this )->widget ) )
    DestroyWindow( PRIVATE( this )->widget );
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
  HWND hwnd = this->getShellWidget( );

  SoWinComponentP::fullscreenData * data = NULL;

  if ( enable ) {

    if ( this->isFullScreen( ) )
      return;

    data = new SoWinComponentP::fullscreenData;
    
    RECT rect;

    // Save size and position
    GetWindowRect( hwnd, & rect );
    data->pos.setValue( rect.left, rect.top );
    data->size.setValue( rect.right - rect.left, rect.bottom - rect.top );

    // Go fullscreen
    data->style = SetWindowLong( hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE );
    data->exstyle = SetWindowLong( hwnd, GWL_EXSTYLE, WS_EX_TOPMOST );
    data->widget = hwnd;

    MoveWindow( hwnd,
                0,
                0,
                GetSystemMetrics( SM_CXSCREEN ),
                GetSystemMetrics( SM_CYSCREEN ),
                TRUE );
    
    // Add to list of fullscreen windows
    SoWinComponentP::sowinfullscreenlist->append( data );
  }
  else {

    if ( ! this->isFullScreen( ) )
      return;

    // Find in list of fullscreen windows
    SoWinComponentP::fullscreenData * d = NULL;
    int i;
    for ( i = 0; i < SoWinComponentP::sowinfullscreenlist->getLength( ); i++ ) {
      d = ( SoWinComponentP::fullscreenData * ) SoWinComponentP::sowinfullscreenlist->get( i );
      if ( d->widget == hwnd ) {
        data = d;
        break;
      }
    }
    if ( ! data ) return;

    // Go normal
    SetWindowLong( hwnd, GWL_STYLE, data->style );
    SetWindowLong( hwnd, GWL_EXSTYLE, data->exstyle );

    MoveWindow( hwnd,
                data->pos[0],
                data->pos[1],
                data->size[0],
                data->size[1],
                TRUE );
    
    // Remove from list of fullscreen windows
    SoWinComponentP::sowinfullscreenlist->remove( i );
    delete data;
  }
}

SbBool
SoWinComponent::isFullScreen( void ) const
{
  // Check fullscreen list for shell widget
  HWND hwnd = this->getShellWidget( );
  SoWinComponentP::fullscreenData * d = NULL;
  for ( int i = 0; i < SoWinComponentP::sowinfullscreenlist->getLength( ); i++ ) {
    d = ( SoWinComponentP::fullscreenData * ) SoWinComponentP::sowinfullscreenlist->get( i );
    if ( d->widget == hwnd )
      return TRUE;
  }
  return FALSE;
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
  // parent-children tree. Is this correct ? mariusbu 20010718.

  HWND hwnd = PRIVATE( this )->widget;
 
  while( IsWindow( GetParent( hwnd ) ) )
    hwnd = GetParent( hwnd );

  return hwnd;
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
  //PRIVATE( this )->size = size;
  
  UINT flags = SWP_NOMOVE | SWP_NOZORDER;
  SetWindowPos( this->getShellWidget( ), NULL, 0, 0, size[0], size[1], flags );
}

SbVec2s
SoWinComponent::getSize( void )
{
  RECT rect;
  GetWindowRect( this->getShellWidget( ), & rect );
  return SbVec2s( rect.right - rect.left, rect.bottom - rect.top );
  //return PRIVATE( this )->size;
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
  HWND widget;

  windowclass.lpszClassName = ( char * ) this->getDefaultWidgetName( );
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

  // When this method is called, the component is *not* embedded. mariusbu 20010727.
  widget = CreateWindow( ( char * ) this->getDefaultWidgetName( ),
                         ( char * ) this->getTitle( ),
                         WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		                     CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         500,
                         500,
                         parent,
                         NULL,
                         SoWin::getInstance( ),
                         PRIVATE( this ) );

  assert( IsWindow( widget ) );
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
  //this->size = SbVec2s( HIWORD(lparam), LOWORD(lparam) );
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
