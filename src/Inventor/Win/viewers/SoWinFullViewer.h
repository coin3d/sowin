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
class SoAnyPopupMenu;

// App button callback functions
typedef void AppPushButtonCB( HWND hwnd, int id, void * buttonData, void * userData );
typedef void RedrawAppPushButtonCB( LPDRAWITEMSTRUCT lpdis, void * userData );
typedef void CreateAppPushButtonCB( LPMEASUREITEMSTRUCT lpmis, void * userData );

class SOWIN_DLL_API SoWinFullViewer : public SoWinViewer {
  SOWIN_OBJECT_ABSTRACT_HEADER( SoWinFullViewer, SoWinViewer );

  friend class SoAnyFullViewer;
  friend class SoWinViewerPrefSheet;
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
		VIEWERBUTTON_SEEK,
		VIEWERBUTTON_PERSPECTIVE,
	};
    
  void setDecoration( SbBool enable );
  SbBool isDecoration( void );

  void setPopupMenuEnabled( SbBool enable );
  SbBool isPopupMenuEnabled( void );
	
  static void setDoButtonBar( SbBool enable );
  static SbBool isDoButtonBar( void );
	
  SoCallbackList popupPostCallback;   // FIXME: is this needed? mariusbu 20010611.
  SoCallbackList popupPreCallback;

  void setClientPopupMenu( HMENU menu );
  SbBool isClientPopupMenuInstalled( void );

	// App button functions
  HWND getAppPushButtonParent( void ) const;    // FIXME: is this needed? mariusbu 20010703.
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

  // SoWinStereoDialog * getStereoDialog( void );
  // void setStereoDialog( SoWinStereoDialog * newDialog );
	    
  virtual void selectedPrefs( void );
  //void resetToHomePosition( void );
  //void saveHomePosition( void );
  //void viewAll( void );

	virtual void interactbuttonClicked( void );
	virtual void viewbuttonClicked( void );
	virtual void helpbuttonClicked( void );
	virtual void homebuttonClicked( void );
	virtual void sethomebuttonClicked( void );
	virtual void viewallbuttonClicked( void );
	virtual void seekbuttonClicked( void );
	virtual void cameratoggleClicked( void );
	
  void copyView( SbTime time );
  void pasteView( SbTime time );
	
protected:
  SoWinFullViewer( HWND parent,
                   const char * name, 
                   SbBool embedded, 
                   BuildFlag flag,
                   SoWinViewer::Type type, 
                   SbBool buildNow);

  ~SoWinFullViewer( void );

  HWND buildWidget( HWND parent );

  void showDecorationWidgets( SbBool enable );
  
  virtual void buildDecoration( HWND parent );
  virtual HWND buildLeftWheel( HWND parent );
  virtual HWND buildBottomWheel( HWND parent );
  virtual HWND buildRightWheel( HWND parent );
  virtual HWND buildZoomSlider( HWND parent );

  void buildAppButtons( HWND parent );
  void buildViewerButtons( HWND parent );
  virtual void buildViewerButtonsEx( HWND parent, int x, int y, int size );
    
  virtual void openStereoDialog( void );

  virtual void buildPopupMenu( void );
  virtual void setPopupMenuString( const char * title );
  virtual void openPopupMenu( const SbVec2s position );
  virtual void destroyPopupMenu( void );  
  virtual int displayPopupMenu( int x, int y, HWND owner );
	
  void setPrefSheetString( const char * name );
  virtual void createPrefSheet( void );
	/*
	void createPrefSheetShellAndForm( HWND shell, HWND form );
  void createDefaultPrefSheetParts( HWND widgetList[], 
                                    int num,
                                    HWND form );
  void layoutPartsAndMapPrefSheet( HWND widgetList[], 
                                   int num,
                                   HWND form,
                                   HWND shell );
	
  HWND createSeekPrefSheetGuts( HWND parent );
  HWND createSeekDistPrefSheetGuts( HWND parent );
  HWND createZoomPrefSheetGuts( HWND parent );
  HWND createClippingPrefSheetGuts( HWND parent );
  HWND createStereoPrefSheetGuts( HWND parent );
  */  
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

  HWND getViewerWidget( void );

  virtual SbBool processSoEvent( const SoEvent * const event );  
  virtual LRESULT onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
	virtual LRESULT onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  virtual LRESULT onCommand( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  virtual LRESULT onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
	virtual LRESULT onDrawItem( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
	virtual LRESULT onMeasureItem( HWND window, UINT message, WPARAM wparam, LPARAM lparam );

  HWND viewerWidget;
  HWND renderAreaWidget;

  static SbBool doneButtonBar;
  static SbBool doButtonBar;
  SoFieldSensor * zoomSensor;
    
  SoWinThumbWheel * rightWheel;
  SoWinThumbWheel * bottomWheel;
  SoWinThumbWheel * leftWheel;
  SoWinThumbWheel * extraWheel;
    
  SbBool popupEnabled;

  SbVec2f zoomrange;
  SoWinViewerPrefSheet * prefsheet; // preference window
  
	SbPList * viewerButtonList;
	SbPList * appButtonList;
  
private:
    
  static void rightWheelCB ( SoWinFullViewer * viewer, void ** data );
  static void bottomWheelCB( SoWinFullViewer * viewer, void ** data );
  static void leftWheelCB  ( SoWinFullViewer * viewer, void ** data );

  void setCameraZoom( float val );
  float getCameraZoom( void );
	/*
  void setZoomSliderPosition( float zoom );
  void setZoomFieldString( float zoom );
	
  static void zoomSliderCB( HWND, SoWinFullViewer *, void ** );
  static void zoomFieldCB( HWND, SoWinFullViewer *, void ** );
  static void zoomSensorCB( void *, SoSensor *);
	
  static void visibilityChangeCB( void * p, SbBool visible );
	*/
  
  // Callback for SoWinGLWidget (new)
  static LRESULT CALLBACK glWidgetProc( HWND window, UINT message,
    WPARAM wparam, LPARAM lparam );
  
  // Callback for SoWinFullViewer
  static LRESULT CALLBACK fullViewerProc( HWND window, UINT message,
    WPARAM wparam, LPARAM lparam );

  int layoutWidgets( int cx, int cy );

	// App button callbacks
  AppPushButtonCB * appPushButtonCB;
	void * appPushButtonData;
  RedrawAppPushButtonCB * redrawAppPushButtonCB;
	void * redrawAppPushButtonData;
	CreateAppPushButtonCB * createAppPushButtonCB;
	void * createAppPushButtonData;
  
  //SoWinStereoDialog * stereoDialogBox ; // FIXME: not implemented yet
  
  SoAnyPopupMenu * prefmenu;
  SoAnyFullViewer * const common;

  SbBool menuenabled;
  SbBool decorations;
  SbBool firstBuild;
};

#endif  // SOWIN_FULLVIEWER_H














