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

typedef void SoWinComponentCB( void * user, SoWinComponent * component );
typedef void SoWinComponentVisibilityCB( void * user, SbBool visible );

// *************************************************************************

// default values when choosing pixelformat (ogl)
const char pfd_cDepthBits = 32;
const char pfd_cColorBits = 32;

class SOWIN_DLL_API SoWinComponent : SoWinObject
{
  SOWIN_OBJECT_ABSTRACT_HEADER( SoWinComponent, SoWinObject );

public:

  virtual ~SoWinComponent( void );

  virtual void show( void );
  virtual void hide( void );
  void goFullScreen( SbBool enable );
  SbBool isFullScreen( void );
  SbBool isVisible( void );

  HWND getWidget( void ) const;
  HWND baseWidget( void ) const;
  HWND getBaseWidget( void ) const;

  SbBool isTopLevelShell( void ) const;
  HWND getShellWidget( void ) const;

  HWND getParentWidget( void ) const;

  inline int * getDisplay( void );

  void setSize( const SbVec2s size );
  SbVec2s getSize( void );

  const char * getWidgetName( void ) const;
  const char * getClassName( void ) const;

  void setTitle( const char * const title );
  const char * getTitle( void ) const;

  void setIconTitle( const char * const title );
  const char * getIconTitle( void ) const;

  void setWindowCloseCallback( SoWinComponentCB * func, void * data = NULL );

  static SoWinComponent * getComponent( HWND widget );

  SbString helpFileName;
  UINT helpContextID;

  static void initClasses( void );

protected:

  SoWinComponent( const HWND parent = NULL,
                  const char * const name = NULL,
                  const SbBool embed = TRUE );

  void setBaseWidget( HWND widget );
  void setClassName( const char * const name );

  void registerWidget( HWND widget );
  void unregisterWidget( HWND widget );

  HWND buildFormWidget( HWND parent );

  virtual const char * getDefaultWidgetName( void ) const;
  virtual const char * getDefaultTitle( void ) const;
  virtual const char * getDefaultIconTitle( void ) const;

  virtual void windowCloseAction( void );
  virtual void afterRealizeHook( void );

  void addVisibilityChangeCallback( SoWinComponentVisibilityCB * func, void * user = NULL );
  void removeVisibilityChangeCallback( SoWinComponentVisibilityCB * func, void * user = NULL );

  void openHelpCard( const char * name );

  void setResize( SbBool set );
  SbBool getResize( void );

  static HPALETTE _setupColorPalette( HDC );

  void unSubclassDialog( HWND hWnd );
  void subclassDialog( HWND hWnd );
  void drawDialogIcon( HWND hWnd );

  static LRESULT CALLBACK dlgWndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
  static HWND getMDIAncestor( HWND hwnd );

  static int ChoosePixelFormatOIV(HDC hdc,int pixelType,int glModes, PIXELFORMATDESCRIPTOR *pfd);

  SbBool m_nParentIsMDI;
  HICON hDlgIcon ;
  SbBool firstRealize;

private:

  static LRESULT CALLBACK windowProc(HWND window,UINT message, WPARAM wparam,LPARAM lparam);

  LRESULT onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  LRESULT onPaint( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  LRESULT onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam );

  //  static LRESULT CALLBACK componentWndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
  //  static LRESULT CALLBACK formWindowProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );

  HWND parent;
  HWND widget;
  HWND constructorParent;
  LONG style; // windowstyle
  LONG exstyle; // extended windowstyle
  SbBool fullScreen;

  SbString widgetName;
  SbString widgetClass;
  SbString title;
  SbString iconTitle;

  SbVec2s size;
  SbVec2s pos;

  SbBool embedded;
  SbBool resizeBaseWidget;

  static SbPList * widgets;
  static SbPList * components;

  SoWinComponentCB * windowCloseFunc;
  SoWinComponentCB * windowCloseData;
}; // class SoWinComponent

// *************************************************************************

#endif // !SOWIN_COMPONENT_H
