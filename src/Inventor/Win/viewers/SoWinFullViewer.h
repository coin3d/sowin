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

#ifndef  SOWIN_FULLVIEWER_H
#define  SOWIN_FULLVIEWER_H

#include <Inventor/Win/viewers/SoWinViewer.h>
#include <Inventor/SbPList.h>
#include <Inventor/lists/SoCallbackList.h>

class SoFieldSensor;
class SoWinBitmapButton;
class SoWinThumbWheel;
class SoWinViewerPrefSheet;
class SoWinFullViewerP;
class SoAnyPopupMenu;

typedef void AppPushButtonCB( HWND hwnd, int id, void * buttonData, void * userData );
typedef void RedrawAppPushButtonCB( LPDRAWITEMSTRUCT lpdis, void * userData );
typedef void CreateAppPushButtonCB( LPMEASUREITEMSTRUCT lpmis, void * userData );

class SOWIN_DLL_API SoWinFullViewer : public SoWinViewer {
  SOWIN_OBJECT_ABSTRACT_HEADER( SoWinFullViewer, SoWinViewer );

  friend class SoAnyFullViewer;
  friend class SoWinViewerPrefSheet;
  friend class SoWinThumbWheel;
  friend class SoWinFullViewerP;

public:

  enum BuildFlag {
    BUILD_NONE          = 0x00, 
    BUILD_DECORATION    = 0x01, 
    BUILD_POPUP         = 0x02, 
    BUILD_ALL           = 0xff, 
  };

	enum ButtonId {
		VIEWERBUTTON_PICK,
		VIEWERBUTTON_VIEW,
		VIEWERBUTTON_HELP,
		VIEWERBUTTON_HOME,
		VIEWERBUTTON_SET_HOME,
		VIEWERBUTTON_VIEW_ALL,
		VIEWERBUTTON_SEEK
	};
    
  void setDecoration( SbBool enable );
  SbBool isDecoration( void );

  void setPopupMenuEnabled( SbBool enable );
  SbBool isPopupMenuEnabled( void );
	
  static void setDoButtonBar( SbBool enable );
  static SbBool isDoButtonBar( void );

  HWND getAppPushButtonParent( void ) const;
  void addAppPushButton( HWND newButton );
  void insertAppPushButton( HWND newButton, int index );
  void removeAppPushButton( HWND oldButton );
  int findAppPushButton( HWND oldButton );
  int lengthAppPushButton( void );
  void addAppPushButtonCallback( AppPushButtonCB * callback,
                                 void * data = NULL );
  void addRedrawAppPushButtonCallback( RedrawAppPushButtonCB * callback,
                                   void * data = NULL);
  void addCreateAppPushButtonCallback( CreateAppPushButtonCB * callback,
                                   void * data = NULL);

  HWND getRenderAreaWidget( void );
    
  virtual void setViewing( SbBool enable );
  virtual void setCamera( SoCamera * newCamera );
  virtual void hide( void );

protected:
  
  SoWinFullViewer( HWND parent,
                   const char * name, 
                   SbBool embedded, 
                   BuildFlag flag,
                   SoWinViewer::Type type, 
                   SbBool buildNow);

  ~SoWinFullViewer( void );

  HWND buildWidget( HWND parent );  
  virtual void buildDecoration( HWND parent );
  virtual HWND buildLeftWheel( HWND parent );
  virtual HWND buildBottomWheel( HWND parent );
  virtual HWND buildRightWheel( HWND parent );
  virtual HWND buildZoomSlider( HWND parent );
  virtual void buildAppButtons( HWND parent );
  virtual void buildViewerButtons( HWND parent );
  virtual void buildViewerButtonsEx( HWND parent, int x, int y, int size );
  virtual void buildPopupMenu( void );
  virtual void setPopupMenuString( const char * title );
  virtual void openPopupMenu( const SbVec2s position );
  virtual void destroyPopupMenu( void );  
  virtual int displayPopupMenu( int x, int y, HWND owner );
    
  void showDecorationWidgets( SbBool enable );
  
  void setPrefSheetString( const char * name );
  virtual void createPrefSheet( void );

  float getLeftWheelValue( void ) const;
  void setLeftWheelValue( const float value );

  float getBottomWheelValue( void ) const;
  void setBottomWheelValue( const float value );

  float getRightWheelValue( void ) const;
  void setRightWheelValue( const float value );

  virtual void rightWheelMotion( float );
  virtual void bottomWheelMotion( float );
  virtual void leftWheelMotion( float );

  virtual void rightWheelStart( void );
  virtual void bottomWheelStart( void );
  virtual void leftWheelStart( void );

  virtual void rightWheelFinish( void );
  virtual void bottomWheelFinish( void );
  virtual void leftWheelFinish( void );

  void setBottomWheelString( const char * name );
  void setLeftWheelString( const char * name );
  void setRightWheelString( const char * name );
  
  virtual void openViewerHelpCard( void );
  virtual void afterRealizeHook( void );
  
  void setCameraZoom( float val );
  float getCameraZoom( void );
  
  virtual void selectedPrefs( void );

  virtual SbBool processSoEvent( const SoEvent * const event );  

  static LRESULT CALLBACK glWidgetProc( HWND window, UINT message,
    WPARAM wparam, LPARAM lparam );
  
  static LRESULT CALLBACK vwrWidgetProc( HWND window, UINT message,
    WPARAM wparam, LPARAM lparam );

  virtual LRESULT onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
	virtual LRESULT onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  virtual LRESULT onCommand( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  virtual LRESULT onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
	virtual LRESULT onDrawItem( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
	virtual LRESULT onMeasureItem( HWND window, UINT message, WPARAM wparam, LPARAM lparam );

 	void seekbuttonClicked( void );
  
  SoFieldSensor * zoomSensor;
    
  SoWinThumbWheel * rightWheel;
  SoWinThumbWheel * bottomWheel;
  SoWinThumbWheel * leftWheel;

  SbVec2f zoomrange;
  SoWinViewerPrefSheet * prefsheet;
  
	SbPList * viewerButtonList;
	SbPList * appButtonList;

  SbVec2s initSize;

  HWND viewerWidget;
  HWND renderAreaWidget;
  
private:

  SoWinFullViewerP * pimpl;
  SoAnyFullViewer * const common;
  SoAnyPopupMenu * prefmenu;
  
};

#endif  // SOWIN_FULLVIEWER_H














