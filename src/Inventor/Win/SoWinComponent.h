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

#ifndef SOWIN_COMPONENT_H
#define SOWIN_COMPONENT_H

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SoLists.h>
#include <Inventor/Win/SoWinObject.h>
#include <wtypes.h>

class SoWinComponent;
class SoWinComponentP;

typedef void SoWinComponentCB( void * user, SoWinComponent * component );
typedef void SoWinComponentVisibilityCB( void * user, SbBool visible );

// *************************************************************************

class SOWIN_DLL_API SoWinComponent : SoWinObject {

  SOWIN_OBJECT_ABSTRACT_HEADER( SoWinComponent, SoWinObject );
  friend class SoWinComponentP;
  
public:
  
  virtual ~SoWinComponent( void );

  virtual void show( void );
  virtual void hide( void );
  
  SbBool isFullScreen( void ) const;
  SbBool setFullScreen( const SbBool enable );

  SbBool isVisible( void );
  HWND getWidget( void ) const;
  HWND baseWidget( void ) const;
  HWND getBaseWidget( void ) const;
  SbBool isTopLevelShell( void ) const;
  HWND getShellWidget( void ) const;
  HWND getParentWidget( void ) const;

  void setSize( const SbVec2s size );
  SbVec2s getSize( void );

  void setTitle( const char * const title );
  const char * getTitle( void ) const;
  
  void setIconTitle( const char * const title ) { this->setTitle( title ); };
  const char * getIconTitle( void ) const { return this->getTitle( ); };

  void setWindowCloseCallback( SoWinComponentCB * func, void * data = NULL );

  static SoWinComponent * getComponent( HWND widget );

  const char * getWidgetName( void ) const;
  const char * getClassName( void ) const;
  
  static void initClasses( void );
  
  HWND setFocusProxy( HWND widget );
  HWND getFocusProxy( void );
  
protected:

  SoWinComponent( const HWND parent = NULL,
                  const char * const name = NULL,
                  const SbBool embed = TRUE );

  void setBaseWidget( HWND widget );
  void setClassName( const char * const name );

  HWND buildFormWidget( HWND parent );

  virtual void sizeChanged( const SbVec2s newSize );
  virtual const char * getDefaultWidgetName( void ) const;
  virtual const char * getDefaultTitle( void ) const;
  virtual const char * getDefaultIconTitle( void ) const { return this->getDefaultTitle( ); };

  virtual void windowCloseAction( void );
  virtual void afterRealizeHook( void );

  void addVisibilityChangeCallback( SoWinComponentVisibilityCB * func, void * user = NULL );
  void removeVisibilityChangeCallback( SoWinComponentVisibilityCB * func, void * user = NULL );

  void openHelpCard( const char * name );

  void setResize( SbBool set );
  SbBool getResize( void );

  SbBool realized;
  
private:

  SoWinComponentP * pimpl;

}; // class SoWinComponent

// *************************************************************************

#endif // !SOWIN_COMPONENT_H
