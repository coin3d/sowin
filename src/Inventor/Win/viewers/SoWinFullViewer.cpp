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

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/errors/SoDebugError.h>

#include <sowindefs.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/widgets/SoWinThumbWheel.h>
#include <Inventor/Win/widgets/SoAnyPopupMenu.h>
#include <Inventor/Win/viewers/SoAnyFullViewer.h>
#include <Inventor/Win/viewers/SoWinFullViewer.h>

// Button icons.
#include <Inventor/Win/common/pixmaps/pick.xpm>
#include <Inventor/Win/common/pixmaps/view.xpm>
#include <Inventor/Win/common/pixmaps/help.xpm>
#include <Inventor/Win/common/pixmaps/home.xpm>
#include <Inventor/Win/common/pixmaps/set_home.xpm>
#include <Inventor/Win/common/pixmaps/view_all.xpm>
#include <Inventor/Win/common/pixmaps/seek.xpm>

SbBool SoWinFullViewer::doButtonBar = FALSE;

void SoWinFullViewer::setDecoration(SbBool set)
{
    // FIXME: function not implemented
}

SbBool SoWinFullViewer::isDecoration( void )
{
    return this->decorationFlag;
}

void SoWinFullViewer::setPopupMenuEnabled( SbBool set )
{
    // FIXME: function not implemented
}

SbBool SoWinFullViewer::isPopupMenuEnabled( void )
{
    return this->popupEnabled;
}

void SoWinFullViewer::setDoButtonBar( SbBool set )
{
    // FIXME: function not implemented
}

SbBool SoWinFullViewer::isDoButtonBar( void )
{
    return SoWinFullViewer::doButtonBar;
}

void SoWinFullViewer::setClientPopupMenu( HMENU menu )
{
    // FIXME: function not implemented
}

SbBool SoWinFullViewer::isClientPopupMenuInstalled( void ) 
{
    return ( this->hClientPopup != NULL );
}
    
HWND SoWinFullViewer::getAppPushButtonParent( void ) const
{
    return this->appButtonForm;
}
    
void SoWinFullViewer::addAppPushButton( HWND newButton )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::insertAppPushButton( HWND newButton, int index )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::removeAppPushButton( HWND oldButton )
{
    // FIXME: function not implemented
}

int SoWinFullViewer::findAppPushButton( HWND oldButton )
{
    return this->appButtonList->find( oldButton );
}

int SoWinFullViewer::lengthAppPushButton( void )
{
    return this->appButtonList->getLength( );
}

HWND SoWinFullViewer::getRenderAreaWidget( void )
{
    return this->raWidget;
}

void SoWinFullViewer::setViewing( SbBool set )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::setCamera( SoCamera * camera )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::hide( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::setHeadlight( SbBool set )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::setDrawStyle( SoWinViewer::DrawType type, SoWinViewer::DrawStyle style )                               
{
    // FIXME: function not implemented
}

void SoWinFullViewer::setBufferingType( SoWinViewer::BufferType type )
{
    // FIXME: function not implemented
}
/*
SoWinStereoDialog * SoWinFullViewer::getStereoDialog( void )
{
    return this->stereoDialogBox;
}

void SoWinFullViewer::setStereoDialog( SoWinStereoDialog * newDialog )
{
    this->stereoDialogBox = newDialog;
}
*/
void SoWinFullViewer::addPushAppButtonCallback( PushAppButtonCB * callback, void * data )
{
    this->customPushBtnCB = callback;
    this->customPushBtnData = data ;
}

void SoWinFullViewer::addRedrawAppButtonCallback( RedrawAppButtonCB * callback, void * data)
{
    this->customRedrawBtnCB = callback;
    this->customRedrawBtnData = data;
}

SoWinFullViewer::SoWinFullViewer( HWND parent,
                                  const char * name, 
                                  SbBool embedded, 
                                  BuildFlag flag,
                                  SoWinViewer::Type type, 
                                  SbBool buildNow) : 
SoWinViewer(parent, name, embedded, type, buildNow )
{
    // FIXME: function not implemented
}

SoWinFullViewer::~SoWinFullViewer( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::pushButtonCB( HWND, int id, void * )
{

}

void SoWinFullViewer::pushAppButtonCB( HWND hwnd, int id, void * data )
{
    if ( this->customPushBtnCB )
        this->customPushBtnCB( hwnd, id, data, customPushBtnData );
}

void SoWinFullViewer::redrawAppButtonCB( LPDRAWITEMSTRUCT lpdis )
{
        if ( this-> customRedrawBtnCB )
            this->customRedrawBtnCB( lpdis, customRedrawBtnData );
}
    
HWND SoWinFullViewer::getButtonWidget( void ) const
{
    return this->appButtonForm;
}

HWND SoWinFullViewer::buildWidget( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

void SoWinFullViewer::buildLeftWheel( HWND parent )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::buildDecoration( HWND parent )
{
    // FIXME: function not implemented
}

HWND SoWinFullViewer::buildLeftTrim( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

HWND SoWinFullViewer::buildBottomTrim( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

HWND SoWinFullViewer::buildRightTrim( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

HWND SoWinFullViewer::buildZoomSlider( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

HWND SoWinFullViewer::buildAppButtons( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

HWND SoWinFullViewer::buildViewerButtons( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

void SoWinFullViewer::createViewerButtons( HWND parent )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::buildPopupMenu( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::openStereoDialog( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::openPopupMenu( const SbVec2s position )
{

}

void SoWinFullViewer::destroyPopupMenu( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::setPopupMenuString( const char * name )
{
    // FIXME: function not implemented
}

HWND SoWinFullViewer::buildFunctionsSubmenu( HWND popup )
{
    // FIXME: function not implemented
    return NULL;
}

HWND SoWinFullViewer::buildDrawStyleSubmenu( HWND popup )
{
    // FIXME: function not implemented
    return NULL;
}

int SoWinFullViewer::displayPopupMenu( int x, int y, HWND owner )
{
    // FIXME: function not implemented
    return 0;
}

void SoWinFullViewer::setPrefSheetString( const char * name )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::createPrefSheet( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::createPrefSheetShellAndForm( HWND shell, HWND form )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::createDefaultPrefSheetParts( HWND widgetList[], int num, HWND form )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::layoutPartsAndMapPrefSheet( HWND widgetList[], int num, HWND form, HWND shell )
{
    // FIXME: function not implemented
}

HWND SoWinFullViewer::createSeekPrefSheetGuts( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

HWND SoWinFullViewer::createSeekDistPrefSheetGuts( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

HWND SoWinFullViewer::createZoomPrefSheetGuts( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

HWND SoWinFullViewer::createClippingPrefSheetGuts( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

HWND SoWinFullViewer::createStereoPrefSheetGuts( HWND parent )
{
    // FIXME: function not implemented
    return NULL;
}

void SoWinFullViewer::rightWheelMotion( float )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::bottomWheelMotion( float )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::leftWheelMotion( float )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::rightWheelStart( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::bottomWheelStart( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::leftWheelStart( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::rightWheelFinish( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::bottomWheelFinish( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::leftWheelFinish( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::setBottomWheelString( const char * name )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::setLeftWheelString( const char * name )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::setRightWheelString( const char * name )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::openViewerHelpCard( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::afterRealizeHook( void )
{
    // FIXME: function not implemented
}

// private:
void SoWinFullViewer::doAppButtonLayout( int start )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::setCameraZoom( float zoom )
{
    // FIXME: function not implemented
}

float SoWinFullViewer::getCameraZoom( void )
{
    // FIXME: function not implemented
    return 0.0f;
}

void SoWinFullViewer::setZoomSliderPosition( float zoom )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::setZoomFieldString( float zoom )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::zoomSliderCB( HWND, SoWinFullViewer *, void * * )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::zoomFieldCB( HWND, SoWinFullViewer *, void * * )   // was XPointer *
{
    // FIXME: function not implemented
}

void SoWinFullViewer::zoomSensorCB( void *, SoSensor *)
{
    // FIXME: function not implemented
}

void SoWinFullViewer::visibilityChangeCB( void * pt, SbBool visible )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::rightWheelCB ( SoWinFullViewer * viewer, void * * data )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::bottomWheelCB( SoWinFullViewer * viewer, void * * data )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::leftWheelCB  ( SoWinFullViewer * viewer, void * * data )
{
    // FIXME: function not implemented
}

LRESULT CALLBACK SoWinFullViewer::mgrWindowProc( HWND hwnd,                                                 UINT message,
		 					                     WPARAM wParam,
                                                 LPARAM lParam )
{
    // FIXME: function not implemented
    return 0;
}
LRESULT CALLBACK SoWinFullViewer::btnWindowProc( HWND hwnd,                                                 UINT message,
		 					                     WPARAM wParam,
                                                 LPARAM lParam )
{
    // FIXME: function not implemented
    return 0;
}

LRESULT CALLBACK SoWinFullViewer::appBtnWindowProc( HWND hwnd,
                                                    UINT message,
	  	 					                        WPARAM wParam,
                                                    LPARAM lParam )
{
    // FIXME: function not implemented
    return 0;
}

LRESULT CALLBACK SoWinFullViewer::txtWindowProc( HWND hwnd,
                                                 UINT message,
		 					                     WPARAM wParam,
                                                 LPARAM lParam )
{
    // FIXME: function not implemented
    return 0;
}

void SoWinFullViewer::drawDecorations( SoWinFullViewer * viewer, HWND hwnd, HDC hdc )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::selectedPrefs( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::resetToHomePosition( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::saveHomePosition( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::viewAll( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::seekbuttonClicked( void )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::copyView( SbTime time )
{
    // FIXME: function not implemented
}

void SoWinFullViewer::pasteView( SbTime time )
{
    // FIXME: function not implemented
}

