/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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
\**************************************************************************/

#ifndef  SO_WIN_FULL_VIEWER
#define  SO_WIN_FULL_VIEWER

#include <Inventor/Win/viewers/SoWinViewer.h>
#include <Inventor/SbPList.h>
#include <Inventor/lists/SoCallbackList.h>

class  SoFieldSensor;
class  SoWinBitmapButton;
class  SoWinThumbWheel;

typedef void PushAppButtonCB( HWND hwnd, int id, void * pushData, void * userData );
typedef void RedrawAppButtonCB( LPDRAWITEMSTRUCT lpdis, void * userData );


class SoWinFullViewer : public SoWinViewer {
    typedef SoWinViewer inherited;
    friend class SoAnyFullViewer;
public:

    enum BuildFlag {
        BUILD_NONE          = 0x00, 
        BUILD_DECORATION    = 0x01, 
        BUILD_POPUP         = 0x02, 
        BUILD_ALL           = 0xff, 
    };
    
    void setDecoration(SbBool set);
    SbBool isDecoration( void );

    void setPopupMenuEnabled( SbBool set );
    SbBool isPopupMenuEnabled( void );

    static void setDoButtonBar( SbBool set );
    static SbBool isDoButtonBar( void );

	SoCallbackList popupPostCallback;
	SoCallbackList popupPreCallback;

	void setClientPopupMenu( HMENU menu );
	SbBool isClientPopupMenuInstalled( void );
    
    HWND getAppPushButtonParent( void ) const;
    void addAppPushButton( HWND newButton );
    void insertAppPushButton( HWND newButton, int index );
    void removeAppPushButton( HWND oldButton );
    int findAppPushButton( HWND oldButton );
    int lengthAppPushButton( void );
    HWND getRenderAreaWidget( void );
    
    virtual void setViewing( SbBool set );
    virtual void setCamera( SoCamera * camera );
    virtual void hide( void );
    virtual void setHeadlight( SbBool set );
    virtual void setDrawStyle( SoWinViewer::DrawType type,
                               SoWinViewer::DrawStyle style );
    virtual void setBufferingType(SoWinViewer::BufferType type);

//    SoWinStereoDialog * getStereoDialog( void );
//    void setStereoDialog( SoWinStereoDialog * newDialog );

    HMENU rootPopup;
    HMENU mainPopup;
    HMENU funcPopup;
    HMENU drawPopup;
    HMENU prefPopup;

    UINT curPopupDrawItem;
    UINT curPopupMoveItem;
    UINT curPopupBufferItem;

	HMENU hClientPopup;

    void addPushAppButtonCallback( PushAppButtonCB * callback,
                                   void * data = NULL );
    void addRedrawAppButtonCallback( RedrawAppButtonCB * callback,
                                     void * data = NULL);
        
    void selectedPrefs( void );
    void resetToHomePosition( void );
    void saveHomePosition( void );
    void viewAll( void );
    void seekbuttonClicked( void );
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
    
    SbBool decorationFlag;
    HWND mgrWidget; // form which manages all other widgets
    HWND raWidget;  // render area HWND
    HWND leftTrimForm;
    HWND bottomTrimForm;
    HWND rightTrimForm;

    static SbBool doButtonBar;
    
    HWND zoomForm;
    HWND zoomField;
    HWND zoomSlider;
    SoFieldSensor * zoomSensor;
    
    SoWinThumbWheel * rightWheel;
    SoWinThumbWheel * bottomWheel;
    SoWinThumbWheel * leftWheel;
    SoWinThumbWheel * extraWheel;

    HWND extraTrimForm;
    float extraWheelVal;
    char * extraWheelStr;
    int extraLabelHeight;
    HWND extraWheelLabel;

    HWND vwrButtonForm;

    HBRUSH backgroundBrush;

    char * rightWheelStr;
    char * bottomWheelStr;
    char * leftWheelStr;
    float rightWheelVal;
    float bottomWheelVal;
    float leftWheelVal;
    HWND rightWheelLabel;
    HWND bottomWheelLabel;
    HWND leftWheelLabel;
    
    SbPList * viewerButtonWidgets;

    int numFullVwrButtons;
    virtual void pushButtonCB( HWND, int id, void * );
    virtual void pushAppButtonCB( HWND hwnd, int id, void * data );
    virtual void redrawAppButtonCB( LPDRAWITEMSTRUCT lpdis );
 
    HWND getButtonWidget( void ) const;
    
    SbBool popupEnabled;
    HWND popupWidget;
    HWND * popupToggleWidgets;
    HWND * drawStyleWidgets;
    HWND bufferStyleWidgets[3];
    char * popupTitle;

    HWND buildWidget( HWND parent );
    void buildLeftWheel( HWND parent );
    
    virtual void buildDecoration( HWND parent );
    virtual HWND buildLeftTrim( HWND parent );
    virtual HWND buildBottomTrim( HWND parent );
    virtual HWND buildRightTrim( HWND parent );
    virtual HWND buildZoomSlider( HWND parent );
    HWND buildAppButtons( HWND parent );
    HWND buildViewerButtons( HWND parent );
    virtual void createViewerButtons( HWND parent );
    
    virtual void buildPopupMenu( void );
	virtual void openStereoDialog( void );
    void setPopupMenuString( const char * title );
    void openPopupMenu( const SbVec2s position );
    virtual void destroyPopupMenu( void );
    HWND buildFunctionsSubmenu( HWND popup );
    HWND buildDrawStyleSubmenu( HWND popup );

    virtual int displayPopupMenu( int x, int y, HWND owner );

    void setPrefSheetString( const char * name );
    virtual void createPrefSheet( void );
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

private:
    SbString menutitle;
    SoAnyPopupMenu * prefmenu;
    SbBool menuenabled;

    SbBool firstBuild;

    HWND appButtonForm;
    SbPList * appButtonList;
    void doAppButtonLayout( int start );

//	SoWinStereoDialog * stereoDialogBox ;
    
    SbVec2f zoomSldRange;
    void setCameraZoom( float zoom );
    float getCameraZoom( void );
    void setZoomSliderPosition( float zoom );
    void setZoomFieldString( float zoom );

    static void zoomSliderCB( HWND, SoWinFullViewer *, void ** );
    static void zoomFieldCB( HWND, SoWinFullViewer *, void ** );   // was XPointer *
    static void zoomSensorCB( void *, SoSensor *);
    
    SoWinBitmapButton * buttonList[10];

    HWND prefSheetShellWidget;
    char * prefSheetStr;

    int seekDistWheelVal;
    HWND seekDistField;
    
    HWND clipWheelForm;
    int clipNearWheelVal, clipFarWheelVal;
    HWND clipNearField, clipFarField;
    
    HWND stereoWheelForm;
    HWND stereoField;
    HWND stereoLabel;
    int stereoWheelVal;

    static void visibilityChangeCB( void * pt, SbBool visible );
    
    static void rightWheelCB ( SoWinFullViewer * viewer, void ** data );
    static void bottomWheelCB( SoWinFullViewer * viewer, void ** data );
    static void leftWheelCB  ( SoWinFullViewer * viewer, void ** data );

    // Window proc for SoWinFullViewer "manager HWND" windows
    static LRESULT CALLBACK mgrWindowProc( HWND hwnd, UINT message,
		 					               WPARAM wParam, LPARAM lParam );

    // Window proc for SoWinFullViewer "button container" windows
    static LRESULT CALLBACK btnWindowProc( HWND hwnd, UINT message,
		 					               WPARAM wParam, LPARAM lParam );

    // Window proc for SoWinFullViewer "application button container" windows
    static LRESULT CALLBACK appBtnWindowProc( HWND hwnd, UINT message,
		 					               WPARAM wParam, LPARAM lParam );

    // Window proc for SoWinFullViewer text entry window (zoomfield)
    static LRESULT CALLBACK txtWindowProc( HWND hwnd, UINT message,
		 					               WPARAM wParam, LPARAM lParam );

    PushAppButtonCB * customPushBtnCB ;
    RedrawAppButtonCB * customRedrawBtnCB ;
    void * customPushBtnData, * customRedrawBtnData ;

    WNDPROC origBtnWndProc;
    WNDPROC origAppBtnWndProc;
    WNDPROC origTxtWndProc;

    static void drawDecorations( SoWinFullViewer * viewer, HWND hwnd, HDC hdc );
};

#endif  // SO_WIN_FULL_VIEWER 
