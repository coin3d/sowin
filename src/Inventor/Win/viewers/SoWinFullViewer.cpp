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

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/errors/SoDebugError.h>

#include <sowindefs.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/widgets/SoWinThumbWheel.h>
#include <Inventor/Win/widgets/SoWinBitmapButton.h>
#include <Inventor/Win/widgets/SoAnyPopupMenu.h>
#include <Inventor/Win/widgets/SoWinPopupMenu.h>
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
#include <Inventor/Win/common/pixmaps/perspective.xpm>
#include <Inventor/Win/common/pixmaps/ortho.xpm>

#define VIEWERBUTTON( id ) ( ( SoWinBitmapButton * ) ( * viewerButtonList )[id] )
const int DECORATION_SIZE = 30;
const int DECORATION_BUFFER = 5;

SOWIN_OBJECT_ABSTRACT_SOURCE( SoWinFullViewer );

SbBool SoWinFullViewer::doButtonBar = FALSE;

void
SoWinFullViewer::setDecoration( SbBool set )
{
  this->decorations = set;
}

SbBool
SoWinFullViewer::isDecoration( void )
{
  return this->decorations;
}

void
SoWinFullViewer::setPopupMenuEnabled( SbBool set )
{
  this->popupEnabled = set;
}

SbBool
SoWinFullViewer::isPopupMenuEnabled( void )
{
  return this->popupEnabled;
}

void
SoWinFullViewer::setDoButtonBar( SbBool set )
{
  SoWinFullViewer::doButtonBar = set;
}

SbBool
SoWinFullViewer::isDoButtonBar( void )
{
  return SoWinFullViewer::doButtonBar;
}

void
SoWinFullViewer::setClientPopupMenu( HMENU menu )
{
  // FIXME: use SoWinPopupMenu * ?
  // this->clientPopup = menu;
  // FIXME: function not implemented
  SOWIN_STUB();
}

SbBool
SoWinFullViewer::isClientPopupMenuInstalled( void ) 
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return FALSE; //( this->clientPopup != NULL );
}
    
HWND
SoWinFullViewer::getAppPushButtonParent( void ) const
{
	return this->viewerWidget;
}
    
void
SoWinFullViewer::addAppPushButton( HWND newButton )
{
  this->appButtonList->append( newButton );
}

void
SoWinFullViewer::insertAppPushButton( HWND newButton, int index )
{
  this->appButtonList->insert( newButton, index );
}

void
SoWinFullViewer::removeAppPushButton( HWND oldButton )
{
  int index = this->appButtonList->find( oldButton );
  this->appButtonList->remove( index );
}

int
SoWinFullViewer::findAppPushButton( HWND oldButton )
{
  return this->appButtonList->find( oldButton );
}

int
SoWinFullViewer::lengthAppPushButton( void )
{
  return this->appButtonList->getLength( );
}

HWND
SoWinFullViewer::getRenderAreaWidget( void )
{
  return this->renderAreaWidget;
}

void
SoWinFullViewer::setViewing( SbBool set )
{
  if ( ( set && this->isViewing( ) ) || ( ! set && ! this->isViewing( ) ) ) {
#if SOWIN_DEBUG && 1 // debug
    SoDebugError::postWarning( "SoWinFullViewer::setViewing, view mode already ",
                               set ? "on" : "off" );
#endif // debug
    return;
  }

  inherited::setViewing( set );

  // FIXME:
  /*
    VIEWERBUTTON( EXAMINE_BUTTON )->setOn( set );
    VIEWERBUTTON( INTERACT_BUTTON )->setOn( set ? FALSE : TRUE);
    VIEWERBUTTON( SEEK_BUTTON )->setEnabled( set );
  */
	VIEWERBUTTON( VIEWERBUTTON_VIEW )->setState( set );
	VIEWERBUTTON( VIEWERBUTTON_PICK )->setState( set ? FALSE : TRUE );
	VIEWERBUTTON( VIEWERBUTTON_SEEK )->setEnabled( set );
}

void
SoWinFullViewer::setCamera( SoCamera * camera )
{
  inherited::setCamera( camera );

  if ( this->prefmenu ) { // prefwindow
    this->setZoomSliderPosition( this->getCameraZoom( ) );
    this->setZoomFieldString( this->getCameraZoom( ) );

    SbBool on = camera ? TRUE : FALSE;
    /*  this->zoomSlider->setEnabled( on );
        this->zoomField->setEnabled( on );
        this->zoomrangefrom->setEnabled( on );
        this->zoomrangeto->setEnabled( on );*/
  }
}

void
SoWinFullViewer::hide( void )
{
  ShowWindow( this->viewerWidget, SW_HIDE );
}

/*
SoWinStereoDialog *
SoWinFullViewer::getStereoDialog( void )
{
    return this->stereoDialogBox;
}

void
SoWinFullViewer::setStereoDialog( SoWinStereoDialog * newDialog )
{
    this->stereoDialogBox = newDialog;
}
*/

void
SoWinFullViewer::addPushAppButtonCallback( PushAppButtonCB * callback, void * data )
{
  this->customPushBtnCB = callback;
  this->customPushBtnData = data ;
}

void
SoWinFullViewer::addRedrawAppButtonCallback( RedrawAppButtonCB * callback, void * data )
{
  this->customRedrawBtnCB = callback;
  this->customRedrawBtnData = data;
}

void
SoWinFullViewer::selectedPrefs( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}
/*
void
SoWinFullViewer::resetToHomePosition( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::saveHomePosition( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::viewAll( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}
*/
void
SoWinFullViewer::seekbuttonClicked( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::copyView( SbTime time )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::pasteView( SbTime time )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

///////////////////////////////////////////////////////////////////
//
//  (protected)
//
// 

SoWinFullViewer::SoWinFullViewer( HWND parent,
                                  const char * name, 
                                  SbBool embedded, 
                                  BuildFlag flag,
                                  SoWinViewer::Type type, 
                                  SbBool buildNow) : 
  inherited(parent, name, embedded, type, buildNow ),
  common( new SoAnyFullViewer( this ) )   // FIXME: warning
{
  //this->zoomrange = SbVec2f(1.0f, 140.0f);

  //this->prefwindow = NULL;
  //this->prefwindowtitle = "Viewer Preference Sheet";

  this->viewerWidget = NULL;
  this->renderAreaWidget = NULL;

  this->menuenabled = ( flag & SoWinFullViewer::BUILD_POPUP ) ? TRUE : FALSE;
  this->decorations = ( flag & SoWinFullViewer::BUILD_DECORATION ) ? TRUE : FALSE;

  this->prefmenu = NULL;

	this->leftWheel = NULL;
  this->bottomWheel = NULL;
  this->rightWheel = NULL;
  this->extraWheel = NULL; // Is this needed? mariusbu 20010611.

  this->viewerButtonList = new SbPList;
  this->appButtonList = new SbPList;

  this->setSize( SbVec2s( 500, 420 ) ); // FIXME: make default values

  if ( buildNow ) {
    this->setClassName( "SoWinFullViewer" );
    HWND window = this->buildWidget( parent );
    this->setBaseWidget( window );
  }
}

SoWinFullViewer::~SoWinFullViewer( void )
{
	// FIXME: remember to dealocate resources
}

void
SoWinFullViewer::pushButtonCB( HWND, int id, void * )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::pushAppButtonCB( HWND hwnd, int id, void * data )
{
  if ( this->customPushBtnCB )
    this->customPushBtnCB( hwnd, id, data, customPushBtnData );
}

void
SoWinFullViewer::redrawAppButtonCB( LPDRAWITEMSTRUCT lpdis )
{
  if ( this->customRedrawBtnCB )
    this->customRedrawBtnCB( lpdis, customRedrawBtnData );
}
    
HWND
SoWinFullViewer::getButtonWidget( void ) const
{
	return this->viewerWidget;
}

HWND
SoWinFullViewer::buildWidget( HWND parent )
{
  assert( IsWindow( parent ) );

  WNDCLASS windowclass;

  LPCTSTR icon = MAKEINTRESOURCE( IDI_APPLICATION );
  LPCTSTR cursor = MAKEINTRESOURCE( IDC_ARROW );
  HMENU menu = NULL;
  LPSTR wndclassname = "SoWinFullViewer_widget";

  windowclass.lpszClassName = wndclassname;
  windowclass.hInstance = SoWin::getInstance( );
  windowclass.lpfnWndProc = SoWinFullViewer::mgrWindowProc;
  windowclass.style = CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon( NULL, icon );
  windowclass.hCursor = LoadCursor( NULL, cursor );
  windowclass.hbrBackground = NULL;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass( & windowclass );

  RECT rect;
  DWORD style;
  if ( IsWindow( parent ) ) {
    GetClientRect( parent, & rect );
    style = WS_CHILD;
  }
  else {
    rect.right = 500;
    rect.bottom = 420;
    style = WS_OVERLAPPEDWINDOW;
  }

  this->viewerWidget = CreateWindow( wndclassname,
                                     wndclassname,
                                     style,
                                     0,
                                     0,
                                     rect.right,
                                     rect.bottom,
                                     parent,
                                     menu,
                                     SoWin::getInstance( ),
                                     this );
  assert( IsWindow( this->viewerWidget ) );

  this->renderAreaWidget = inherited::buildWidget( this->viewerWidget );
  assert( IsWindow( this->renderAreaWidget ) );

	MoveWindow( SoWin::getTopLevelWidget( ), 0, 0, 500, 420, FALSE ); // FIXME: make default values

  if ( this->menuenabled )
    this->buildPopupMenu( );

  ShowWindow( this->viewerWidget, SW_SHOW );
  ShowWindow( this->renderAreaWidget, SW_SHOW );

  SoWin::addMessageHook( this->viewerWidget, WM_SIZE );

	if ( this->decorations )
			this->buildDecoration( this->viewerWidget );

  return this->viewerWidget;
}

void
SoWinFullViewer::buildDecoration( HWND parent )
{
  this->buildLeftWheel( parent );
  this->buildBottomWheel( parent );
  this->buildRightWheel( parent );
	//this->buildZoomSlider( parent );
	//if ( SoWinFullViewer::doButtonBar )
	this->buildViewerButtons( parent );
	this->buildAppButtons( parent );
}

HWND
SoWinFullViewer::buildLeftWheel( HWND parent )
{
  // Create coords are not needed - the widget is moved into place (see onSize)
  this->leftWheel = new SoWinThumbWheel( SoWinThumbWheel::Vertical,
                                         parent,
		                                     0,
                                         0,
                                         "RotX" );
  this->leftWheel->registerCallback( this->leftWheelCB );
	this->leftWheel->registerViewer( this );
	this->leftWheel->setRangeBoundaryHandling( SoWinThumbWheel::MODULATE );
	this->leftWheel->setLabelOffset( -9, 12 );
	
  return leftWheel->getWidget( );
}

HWND
SoWinFullViewer::buildBottomWheel( HWND parent )
{
	// Create coords are not needed - the widget is moved into place (see onSize)
  this->bottomWheel = new SoWinThumbWheel( SoWinThumbWheel::Horizontal,
		                                       parent,
		                                       0,
                                           0,
                                           "RotY" );
  this->bottomWheel->registerCallback( this->bottomWheelCB );
	this->bottomWheel->registerViewer( this );
	this->bottomWheel->setRangeBoundaryHandling( SoWinThumbWheel::MODULATE );
	this->bottomWheel->setLabelOffset( -5, -3 );
	
  return this->bottomWheel->getWidget( );
}

HWND
SoWinFullViewer::buildRightWheel( HWND parent )
{
	// Create coords are not needed - the widget is moved into place (see onSize)
  this->rightWheel = new SoWinThumbWheel( SoWinThumbWheel::Vertical,
                                          parent,
		                                      0,
                                          0,
                                          "Dolly" );
  this->rightWheel->registerCallback( this->rightWheelCB );
	this->rightWheel->registerViewer( this );
	this->rightWheel->setRangeBoundaryHandling( SoWinThumbWheel::ACCUMULATE );
	this->rightWheel->setLabelOffset( -15, 12 );

	return this->rightWheel->getWidget( );
}

HWND
SoWinFullViewer::buildZoomSlider( HWND parent )
{
  // FIXME: function not implemented
  // SOWIN_STUB();
  // return NULL;
	/*
	this->zoomSlider = CreateWindow( "SCROLLBAR", "Zoom", WS_CHILD | WS_VISIBLE, 300, 350,
		100, 18, parent, NULL, SoWin::getInstance( ), NULL );
	*/	
	return this->zoomSlider;
}

void
SoWinFullViewer::buildAppButtons( HWND parent )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::buildViewerButtons( HWND parent )
{
	// Create coords are not needed - the widget is moved into place (see onSize)
	// Set id's so they can be used as indices in the list later ( ie. viewerButtonList[id] )
	
	SoWinBitmapButton * button;

	button = new SoWinBitmapButton( parent, 0, 0, DECORATION_SIZE, DECORATION_SIZE, 24, "pick", NULL );
	button->addBitmap( pick_xpm );
	button->setBitmap( 0 ); // use first ( and only ) bitmap
	button->setId( VIEWERBUTTON_PICK );
	viewerButtonList->append( button );
	button->setState( this->isViewing( ) ? FALSE : TRUE );

	button = new SoWinBitmapButton( parent, 0, 0, DECORATION_SIZE, DECORATION_SIZE, 24, "view", NULL );
	button->addBitmap( view_xpm );
	button->setBitmap( 0 ); // use first ( and only ) bitmap
	button->setId( VIEWERBUTTON_VIEW );
	viewerButtonList->append( button );
	button->setState( this->isViewing( ) );
	
	button = new SoWinBitmapButton( parent, 0, 0, DECORATION_SIZE, DECORATION_SIZE, 24, "help", NULL );
	button->addBitmap( help_xpm );
	button->setBitmap( 0 ); // use first ( and only ) bitmap
	button->setId( VIEWERBUTTON_HELP );
	viewerButtonList->append( button );

	button = new SoWinBitmapButton( parent, 0, 0, DECORATION_SIZE, DECORATION_SIZE, 24, "home", NULL );
	button->addBitmap( home_xpm );
	button->setBitmap( 0 ); // use first ( and only ) bitmap
	button->setId( VIEWERBUTTON_HOME );
	viewerButtonList->append( button );
	
	button = new SoWinBitmapButton( parent, 0, 0, DECORATION_SIZE, DECORATION_SIZE, 24, "set_home", NULL );
	button->addBitmap( set_home_xpm );
	button->setBitmap( 0 );
	button->setId( VIEWERBUTTON_SET_HOME );
	viewerButtonList->append( button );
	
	button = new SoWinBitmapButton( parent, 0, 0, DECORATION_SIZE, DECORATION_SIZE, 24, "view_all", NULL );
	button->addBitmap( view_all_xpm );
	button->setBitmap( 0 ); // use first ( and only ) bitmap
	button->setId( VIEWERBUTTON_VIEW_ALL );
	viewerButtonList->append( button );
	
	button = new SoWinBitmapButton( parent, 0, 0, DECORATION_SIZE, DECORATION_SIZE, 24, "seek", NULL );
	button->addBitmap( seek_xpm );
	button->setBitmap( 0 ); // use first ( and only ) bitmap
	button->setId( VIEWERBUTTON_SEEK );
	viewerButtonList->append( button );
	
	button = new SoWinBitmapButton( parent, 0, 0, DECORATION_SIZE, DECORATION_SIZE, 24, "perspective", NULL );
	button->addBitmap( perspective_xpm ); // FIXME: ortho
	button->addBitmap( ortho_xpm );
	button->setBitmap( 0 ); // use first ( of two ) bitmap
	button->setId( VIEWERBUTTON_PERSPECTIVE );
	viewerButtonList->append( button );
}
/*
void
SoWinFullViewer::createViewerButtons( HWND parent )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}
*/
void
SoWinFullViewer::openStereoDialog( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::buildPopupMenu( void )
{
  this->prefmenu = common->setupStandardPopupMenu( );
}

void
SoWinFullViewer::setPopupMenuString( const char * name )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::openPopupMenu( const SbVec2s position )
{
  short x, y;
  position.getValue( x, y );

  // Get the right coords
  RECT clientRect;
  POINT point;
  GetClientRect( this->renderAreaWidget, & clientRect );
  point.y = clientRect.bottom - y;
  point.x = x;
  ClientToScreen( this->renderAreaWidget, & point );

	// Popup
	assert( this->prefmenu != NULL );
	this->common->prepareMenu( this->prefmenu );
  this->displayPopupMenu( point.x, point.y, this->viewerWidget );
}

void
SoWinFullViewer::destroyPopupMenu( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

int
SoWinFullViewer::displayPopupMenu( int x, int y, HWND owner )
{
  //this->popupPreCallback( );
  assert( this->prefmenu != NULL );
  this->prefmenu->popUp( owner, x, y );
	int selectedItem =  ( ( SoWinPopupMenu * ) this->prefmenu )->getSelectedItem( );
	if ( selectedItem != 0 ) // No item selected ( user aborted )
		this->common->menuSelection( selectedItem );
  //this->popupPostCallback( );
  return 0;
}
/* FIXME: not needed? mariusbu 20010611.
HMENU
SoWinFullViewer::buildFunctionsSubmenu( HMENU popup )
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return NULL;
}

HMENU
SoWinFullViewer::buildDrawStyleSubmenu( HMENU popup )
{
  // FIXME: function not implemented
  return NULL;
}
*/
void
SoWinFullViewer::setPrefSheetString( const char * name )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::createPrefSheet( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::createPrefSheetShellAndForm( HWND shell, HWND form )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::createDefaultPrefSheetParts( HWND widgetList[], int num, HWND form )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::layoutPartsAndMapPrefSheet( HWND widgetList[], int num, HWND form, HWND shell )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

HWND
SoWinFullViewer::createSeekPrefSheetGuts( HWND parent )
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return NULL;
}

HWND
SoWinFullViewer::createSeekDistPrefSheetGuts( HWND parent )
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return NULL;
}

HWND
SoWinFullViewer::createZoomPrefSheetGuts( HWND parent )
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return NULL;
}

HWND
SoWinFullViewer::createClippingPrefSheetGuts( HWND parent )
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return NULL;
}

HWND
SoWinFullViewer::createStereoPrefSheetGuts( HWND parent )
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return NULL;
}

float
SoWinFullViewer::getLeftWheelValue( void ) const
{
	return this->leftWheel->value( );
}

void
SoWinFullViewer::setLeftWheelValue( const float value )
{
	this->leftWheel->setValue( value );
}

float
SoWinFullViewer::getBottomWheelValue( void ) const
{
	return this->bottomWheel->value( );
}

void
SoWinFullViewer::setBottomWheelValue( const float value )
{
	this->bottomWheel->setValue( value );
}

float
SoWinFullViewer::getRightWheelValue( void ) const
{
	return this->rightWheel->value( );
}

void
SoWinFullViewer::setRightWheelValue( const float value )
{
	this->rightWheel->setValue( value );
}

void
SoWinFullViewer::rightWheelFinish( void )
{
  this->interactiveCountDec( );
}

void
SoWinFullViewer::bottomWheelStart( void )
{
	this->interactiveCountInc( );
}

void
SoWinFullViewer::leftWheelStart( void )
{
	this->interactiveCountInc( );
}

void
SoWinFullViewer::leftWheelMotion( float value )
{
	this->leftWheel->setValue( value );
}

void
SoWinFullViewer::leftWheelFinish( void )
{
	this->interactiveCountDec( );
}

void
SoWinFullViewer::bottomWheelMotion( float value )
{
	this->bottomWheel->setValue( value );
}

void
SoWinFullViewer::bottomWheelFinish( void )
{
  this->interactiveCountDec( );
}

void
SoWinFullViewer::rightWheelStart( void )
{
	this->interactiveCountInc( );
}

void
SoWinFullViewer::rightWheelMotion( float value )
{
	this->rightWheel->setValue( value );
}

void
SoWinFullViewer::setLeftWheelString( const char * name )
{
	if( this->leftWheel )
		this->leftWheel->setLabelText( ( char * ) name );
}

void
SoWinFullViewer::setBottomWheelString( const char * name )
{
	if( this->bottomWheel )
		this->bottomWheel->setLabelText( ( char * ) name );
}

void
SoWinFullViewer::setRightWheelString( const char * name )
{
	if( this->rightWheel )
		this->rightWheel->setLabelText( ( char * ) name );
}

void
SoWinFullViewer::openViewerHelpCard( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::afterRealizeHook( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

HWND
SoWinFullViewer::getViewerWidget( void )
{
  return this->viewerWidget;
}

SbBool
SoWinFullViewer::processSoEvent( const SoEvent * const event )
{
  if ( common->processSoEvent( event ) ||
       inherited::processSoEvent( event ) )
    return TRUE;
  return FALSE;
}

///////////////////////////////////////////////////////////////////
//
//  (private)
//
//

void
SoWinFullViewer::doAppButtonLayout( int start )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::setCameraZoom( float zoom )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

float
SoWinFullViewer::getCameraZoom( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return 0.0f;
}

void
SoWinFullViewer::setZoomSliderPosition( float zoom )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::setZoomFieldString( float zoom )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::zoomSliderCB( HWND, SoWinFullViewer *, void ** )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::zoomFieldCB( HWND, SoWinFullViewer *, void ** )   // was XPointer *
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::zoomSensorCB( void *, SoSensor *)
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::visibilityChangeCB( void * pt, SbBool visible )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::leftWheelCB( SoWinFullViewer * viewer, void ** data )
{
  // FIXME: not pretty
	
	if ( data == NULL ) {
		viewer->leftWheelStart( );
		return;
	}
	
	if ( ( int ) data == -1 ) {
		viewer->leftWheelFinish( );
		return;
	}

	viewer->leftWheelMotion( ** ( float ** ) data );
}

void
SoWinFullViewer::bottomWheelCB( SoWinFullViewer * viewer, void ** data )
{
	// FIXME: not pretty
	
	if ( data == NULL ) {
		viewer->bottomWheelStart( );
		return;
	}
	
	if ( ( int ) data == -1 ) {
		viewer->bottomWheelFinish( );
		return;
	}

	viewer->bottomWheelMotion( ** ( float ** ) data );
}

void
SoWinFullViewer::rightWheelCB( SoWinFullViewer * viewer, void ** data )
{
	// FIXME: not pretty
	
	if ( data == NULL ) {
		viewer->rightWheelStart( );
		return;
	}
	
	if ( ( int ) data == -1 ) {
		viewer->rightWheelFinish( );
		return;
	}
	
	viewer->rightWheelMotion( ** ( float ** ) data );
}

LRESULT CALLBACK
SoWinFullViewer::mgrWindowProc( HWND window,
                                UINT message,
                                WPARAM wparam,
                                LPARAM lparam )
{
  if ( message == WM_CREATE ) {
    CREATESTRUCT * createstruct;
    createstruct = ( CREATESTRUCT * ) lparam;
    SetWindowLong( window, 0, (LONG) ( createstruct->lpCreateParams ) );
    SoWinFullViewer * object = ( SoWinFullViewer * ) GetWindowLong( window, 0 );
    return object->onCreate( window, message, wparam, lparam );
  }

  SoWinFullViewer * object = ( SoWinFullViewer * ) GetWindowLong( window, 0 );

  if ( object && window == object->getViewerWidget( ) ) {
		/*
    if( GetFocus( ) != object->getNormalWidget( ) )
      SetFocus( object->getNormalWidget( ) );
		*/
    POINT point = {  LOWORD( lparam ), HIWORD( lparam ) };

    switch ( message )
      {

      case WM_SIZE:
        return object->onSize( window, message, wparam, lparam );

        /*
          case WM_PAINT:
          return object->onPaint( window, message, wparam, lparam );
        */

      case WM_DESTROY:
        return object->onDestroy( window, message, wparam, lparam );
				
			case WM_LBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_RBUTTONDOWN:
				SetCapture( window );
				return 0;

			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			case WM_RBUTTONUP:
				ReleaseCapture( );
				return 0;
				
			case WM_COMMAND:
			  return object->onCommand( window, message, wparam, lparam );
      }
  }
  return DefWindowProc( window, message, wparam, lparam );
}
/*
LRESULT CALLBACK
SoWinFullViewer::btnWindowProc( HWND window,
                                UINT message,
                                WPARAM wparam,
                                LPARAM lparam )
{
  // FIXME: function not implemented
  return DefWindowProc( window, message, wparam, lparam );
}

LRESULT CALLBACK
SoWinFullViewer::appBtnWindowProc( HWND window,
                                   UINT message,
                                   WPARAM wparam,
                                   LPARAM lparam )
{
  // FIXME: function not implemented
  return DefWindowProc( window, message, wparam, lparam );
}

LRESULT CALLBACK
SoWinFullViewer::txtWindowProc( HWND window,
                                UINT message,
                                WPARAM wparam,
                                LPARAM lparam )
{
  // FIXME: function not implemented
  return DefWindowProc( window, message, wparam, lparam );
}
*/
LRESULT
SoWinFullViewer::onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  // FIXME: function not implemented
	if ( ! this->isViewing( ) ) this->setViewing( TRUE );
  return 0;
}

LRESULT
SoWinFullViewer::onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
	int i, x, y, width, height, bottom, right, top, numButtons;

	// RenderArea
	assert( IsWindow( this->renderAreaWidget ) );
	
	if ( this->isFullScreen( ) ) {
			MoveWindow( this->renderAreaWidget, 0, 0, LOWORD( lparam ), HIWORD( lparam ), FALSE );
			return 0; 
	}
	else {
		MoveWindow( this->renderAreaWidget, DECORATION_SIZE, 0,
			LOWORD( lparam ) - ( 2 * DECORATION_SIZE ), HIWORD( lparam ) - DECORATION_SIZE, FALSE );
	}
	
  // Viewer buttons
	numButtons = viewerButtonList->getLength( );

	for( i = 0; i < numButtons; i++ )
		( ( SoWinBitmapButton * )( * viewerButtonList )[i] )->move(
			LOWORD( lparam ) - DECORATION_SIZE, DECORATION_SIZE * i );

	bottom = ( HIWORD( lparam ) - ( DECORATION_SIZE + DECORATION_BUFFER ) );
	right = ( LOWORD( lparam ) - ( DECORATION_SIZE + DECORATION_BUFFER ) );
	
	// Left wheel
  if ( this->leftWheel ) {

		x = ( DECORATION_SIZE / 2 ) - ( this->leftWheel->sizeHint( ).cx / 2 ) - 1;
		width = this->leftWheel->sizeHint( ).cx;

		top = DECORATION_BUFFER;
		
		// if area is large enough for original height
		if ( ( bottom - top ) > this->leftWheel->sizeHint( ).cy ) {

			height = this->leftWheel->sizeHint( ).cy;

			y = bottom - height;

		} // else we must use all available space
		else {

			y = top;

			height = bottom - top;
			
		}
		
		this->leftWheel->move( x, y, width, height );
	}
	
  // Bottom wheel
	if ( this->bottomWheel ) {

		x = DECORATION_SIZE + 42;
		y = ( HIWORD( lparam ) - DECORATION_SIZE ) +
			( ( DECORATION_SIZE / 2 ) - ( this->bottomWheel->sizeHint( ).cy / 2 ) + 1 );
		
		height = this->bottomWheel->sizeHint( ).cy;
		
		if ( right < ( x + this->bottomWheel->sizeHint( ).cx ) ) {

			width = right - x;
			
		}
		else {

			width =  this->bottomWheel->sizeHint( ).cx;
			
		}	

		this->bottomWheel->move( x, y, width, height );
			
	}
	
  // Right wheel
  if ( this->rightWheel ) {
		
		x = ( LOWORD( lparam ) - DECORATION_SIZE ) +
			( ( DECORATION_SIZE / 2 ) - ( this->rightWheel->sizeHint( ).cx / 2 ) + 1 );
		
		width = this->rightWheel->sizeHint( ).cx;

		top = numButtons * DECORATION_SIZE + DECORATION_BUFFER;
		
		// if area is large enough for original height
		if ( ( bottom - top ) > this->rightWheel->sizeHint( ).cy ) {

			height = this->rightWheel->sizeHint( ).cy;

			y = bottom - height;

		} // else we must use all available space
		else {

			y = top;

			height = bottom - top;
			
		}
		
		this->rightWheel->move( x, y, width, height );
	}
	
	/*
	// Slider
	MoveWindow( this->zoomSlider,
		LOWORD( lparam ) - ( 170 + DECORATION_SIZE ),
		HIWORD( lparam ) + DECORATION_SIZE + 6,
		150, 18, FALSE );
	*/
  return 0;
}

LRESULT
SoWinFullViewer::onCommand( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
	short nc = HIWORD( wparam );// notification code
	short id = LOWORD( wparam );// item, control, or accelerator identifier
	HWND hwnd = ( HWND ) lparam;// handle of control
	
	switch( id ) {
		
		case VIEWERBUTTON_PICK:
			VIEWERBUTTON( VIEWERBUTTON_PICK )->setState( TRUE );
			VIEWERBUTTON( VIEWERBUTTON_VIEW )->setState( FALSE );
			if ( this->isViewing( ) )
			  this->setViewing( FALSE );
			break;
			
		case VIEWERBUTTON_VIEW:
			VIEWERBUTTON( VIEWERBUTTON_VIEW )->setState( TRUE );
			VIEWERBUTTON( VIEWERBUTTON_PICK )->setState( FALSE );
			if ( ! this->isViewing( ) )
			  this->setViewing( TRUE );
			break;
			
		case VIEWERBUTTON_HELP:
			this->openViewerHelpCard( );
			break;
			
		case VIEWERBUTTON_HOME:
			this->resetToHomePosition( );
			break;
			
		case VIEWERBUTTON_SET_HOME:
			this->saveHomePosition( );
			break;
			
		case VIEWERBUTTON_VIEW_ALL:
			this->viewAll( );
			break;
			
		case VIEWERBUTTON_SEEK:
			this->setSeekMode( this->isSeekMode( ) ? FALSE : TRUE );
			break;
			
		case VIEWERBUTTON_PERSPECTIVE:
			// FIXME
			break;
			
	}

	return 0;
}

LRESULT // FIXME: is not called
SoWinFullViewer::onPaint( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
	// FIXME: function not implemented
  SOWIN_STUB();
	return 0;
}

LRESULT
SoWinFullViewer::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return 0;
}

void // FIXME: is not used
SoWinFullViewer::drawDecorations( SoWinFullViewer * viewer, HWND hwnd, HDC hdc )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}
