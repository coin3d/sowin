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

SOWIN_OBJECT_ABSTRACT_SOURCE(SoWinFullViewer);

SbBool SoWinFullViewer::doButtonBar = FALSE;

void
SoWinFullViewer::setDecoration( SbBool set )
{
  // FIXME: function not implemented
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
  // FIXME: function not implemented
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
  // FIXME: function not implemented
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
  // FIXME: function not implemented
  this->clientPopup = menu;
}

SbBool
SoWinFullViewer::isClientPopupMenuInstalled( void ) 
{
  return ( this->clientPopup != NULL );
}
    
HWND
SoWinFullViewer::getAppPushButtonParent( void ) const
{
  return this->appButtonForm;
}
    
void
SoWinFullViewer::addAppPushButton( HWND newButton )
{
  // FIXME: function not implemented
  this->appButtonList->append( newButton );
}

void
SoWinFullViewer::insertAppPushButton( HWND newButton, int index )
{
  // FIXME: function not implemented
  this->appButtonList->insert( newButton, index );
}

void
SoWinFullViewer::removeAppPushButton( HWND oldButton )
{
  // FIXME: function not implemented
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
                               set ? "on" : "off");
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
}

void
SoWinFullViewer::setCamera( SoCamera * camera )
{
  inherited::setCamera(camera);

  if ( this->prefmenu ) { // prefwindow
    this->setZoomSliderPosition(this->getCameraZoom());
    this->setZoomFieldString(this->getCameraZoom());

    SbBool on = camera ? TRUE : FALSE;
    /*      this->zoomSlider->setEnabled(on);
            this->zoomField->setEnabled(on);
            this->zoomrangefrom->setEnabled(on);
            this->zoomrangeto->setEnabled(on);*/
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
SoWinFullViewer::addRedrawAppButtonCallback( RedrawAppButtonCB * callback, void * data)
{
  this->customRedrawBtnCB = callback;
  this->customRedrawBtnData = data;
}

void
SoWinFullViewer::selectedPrefs( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::resetToHomePosition( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::saveHomePosition( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::viewAll( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::seekbuttonClicked( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::copyView( SbTime time )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::pasteView( SbTime time )
{
  // FIXME: function not implemented
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

  rightWheelStr = "Motion X";
  bottomWheelStr = "Motion Y";
  leftWheelStr = "Motion Z";

  //this->zoomrange = SbVec2f(1.0f, 140.0f);

  //this->prefwindow = NULL;
  //this->prefwindowtitle = "Viewer Preference Sheet";

  this->viewerWidget = NULL;
  this->renderAreaWidget = NULL;

  // FIXME: set to TRUE for testing. mariusbu 20010608.
  this->menuenabled = buildNow & SoWinFullViewer::BUILD_POPUP;
  this->decorations = ( buildNow & SoWinFullViewer::BUILD_DECORATION ) ? TRUE : FALSE;

  this->prefmenu = NULL;
  this->menutitle = "Viewer Menu";

  this->viewerButtonWidgets = new SbPList;
  this->appButtonList = new SbPList;
  this->appButtonForm = NULL;

  this->setSize( SbVec2s( 500, 400 ) ); // FIXME: make default values

  if ( buildNow ) {
    this->setClassName( "SoWinFullViewer" );
    HWND window = this->buildWidget( parent );
    this->setBaseWidget( window );
  }
}

SoWinFullViewer::~SoWinFullViewer( void )
{
  // FIXME: function not implemented
  SOWIN_STUB();
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
  return this->appButtonForm;
}

HWND
SoWinFullViewer::buildWidget( HWND parent )
{
  // FIXME: use this->buildFormWidget

  assert( IsWindow( parent ) );

  WNDCLASS windowclass;

  LPCTSTR icon = MAKEINTRESOURCE( IDI_APPLICATION );
  LPCTSTR cursor = MAKEINTRESOURCE( IDC_ARROW );
  HBRUSH brush = ( HBRUSH ) GetStockObject( COLOR_BACKGROUND );
  HMENU menu = NULL;
  LPSTR wndclassname = "SoWinFullViewer_glwidget";

  windowclass.lpszClassName = wndclassname;
  windowclass.hInstance = SoWin::getInstance( );
  windowclass.lpfnWndProc = SoWinFullViewer::mgrWindowProc;
  windowclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon( NULL, icon );
  windowclass.hCursor = LoadCursor( NULL, cursor );
  windowclass.hbrBackground = this->backgroundBrush = brush;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass( & windowclass );

  RECT rect;
  DWORD style;
  if ( IsWindow( parent ) ) {
    GetClientRect( parent, & rect );
    style = /*WS_CLIPCHILDREN | WS_CLIPSIBLINGS |*/ WS_BORDER | WS_CHILD;
  }
  else {
    rect.right = SoWin_DefaultWidth;
    rect.bottom = SoWin_DefaultHeight;
    style = /*WS_CLIPCHILDREN | WS_CLIPSIBLINGS |*/ WS_OVERLAPPEDWINDOW;
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

  ZeroMemory( & renderAreaOffset, sizeof( renderAreaOffset ) );

  if ( this->decorations ) {
    renderAreaOffset.top = 0;
    renderAreaOffset.left = 30;
    renderAreaOffset.right = -60;
    renderAreaOffset.bottom = -30;
    this->buildDecoration( this->viewerWidget );
    //this->showDecorationWidgets( TRUE );
  }

  MoveWindow( SoWin::getTopLevelWidget( ), 0, 0, 500, 400, FALSE ); // FIXME: make default values
  MoveWindow( this->renderAreaWidget,
              renderAreaOffset.left,
              renderAreaOffset.top,
              500 + renderAreaOffset.right,
              400 + renderAreaOffset.bottom,
              FALSE );

  if ( this->menuenabled )
    this->buildPopupMenu( );
  else
    _cprintf( "menu NOT enabled\n" );

  ShowWindow( this->viewerWidget, SW_SHOW );
  ShowWindow( this->renderAreaWidget, SW_SHOW );

  SoWin::addMessageHook( this->viewerWidget, WM_SIZE );

  return this->viewerWidget;
}

/*
void SoWinFullViewer::buildLeftWheel( HWND parent )
{
  // FIXME: function not implemented

  this->leftWheel = new SoWinThumbWheel( SoWinThumbWheel::Vertical,
                                         parent,
                                         5,
                                         250,
                                         this->leftWheelStr );
  this->leftWheel->registerCallback( leftWheelCB );
}
*/

void
SoWinFullViewer::buildDecoration( HWND parent )
{
  // FIXME: function not implemented
  this->buildLeftTrim( parent );
}

HWND
SoWinFullViewer::buildLeftTrim( HWND parent )
{
  this->leftWheel = new SoWinThumbWheel( SoWinThumbWheel::Vertical,
                                         parent,
                                         5,
                                         250,
                                         this->leftWheelStr );
  this->leftWheel->registerCallback( this->leftWheelCB );

  return NULL;
}

HWND
SoWinFullViewer::buildBottomTrim( HWND parent )
{
  // FIXME: function not implemented
  return NULL;
}

HWND
SoWinFullViewer::buildRightTrim( HWND parent )
{
  // FIXME: function not implemented
  return NULL;
}

HWND
SoWinFullViewer::buildZoomSlider( HWND parent )
{
  // FIXME: function not implemented
  return NULL;
}

HWND
SoWinFullViewer::buildAppButtons( HWND parent )
{
  // FIXME: function not implemented
  return NULL;
}

HWND
SoWinFullViewer::buildViewerButtons( HWND parent )
{
  // FIXME: function not implemented
  return NULL;
}

void
SoWinFullViewer::createViewerButtons( HWND parent )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::openStereoDialog( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::buildPopupMenu( void )
{
  // FIXME: function not implemented
  this->prefmenu = common->setupStandardPopupMenu( );
}

void
SoWinFullViewer::setPopupMenuString( const char * name )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::openPopupMenu( const SbVec2s position )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::destroyPopupMenu( void )
{
  // FIXME: function not implemented
}

int
SoWinFullViewer::displayPopupMenu( int x, int y, HWND owner )
{
  // FIXME: function not implemented
  //this->popupPreCallback( );
  assert( this->prefmenu != NULL );
  this->prefmenu->popUp( owner, x, y ); // FIXME: test. mariusbu 20010531.
  //this->popupPostCallback( );
  return 0;
}

HWND
SoWinFullViewer::buildFunctionsSubmenu( HWND popup )
{
  // FIXME: function not implemented
  return NULL;
}

HWND
SoWinFullViewer::buildDrawStyleSubmenu( HWND popup )
{
  // FIXME: function not implemented
  return NULL;
}

void
SoWinFullViewer::setPrefSheetString( const char * name )
{
  this->prefSheetStr = name;
}

void
SoWinFullViewer::createPrefSheet( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::createPrefSheetShellAndForm( HWND shell, HWND form )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::createDefaultPrefSheetParts( HWND widgetList[], int num, HWND form )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::layoutPartsAndMapPrefSheet( HWND widgetList[], int num, HWND form, HWND shell )
{
  // FIXME: function not implemented
}

HWND
SoWinFullViewer::createSeekPrefSheetGuts( HWND parent )
{
  // FIXME: function not implemented
  return NULL;
}

HWND
SoWinFullViewer::createSeekDistPrefSheetGuts( HWND parent )
{
  // FIXME: function not implemented
  return NULL;
}

HWND
SoWinFullViewer::createZoomPrefSheetGuts( HWND parent )
{
  // FIXME: function not implemented
  return NULL;
}

HWND
SoWinFullViewer::createClippingPrefSheetGuts( HWND parent )
{
  // FIXME: function not implemented
  return NULL;
}

HWND
SoWinFullViewer::createStereoPrefSheetGuts( HWND parent )
{
  // FIXME: function not implemented
  return NULL;
}

float
SoWinFullViewer::getLeftWheelValue( void ) const
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return 0;
}

void
SoWinFullViewer::setLeftWheelValue( const float value )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

float
SoWinFullViewer::getRightWheelValue( void ) const
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return 0;
}

void
SoWinFullViewer::setRightWheelValue( const float value )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

float
SoWinFullViewer::getBottomWheelValue( void ) const
{
  // FIXME: function not implemented
  SOWIN_STUB();
  return 0;
}

void
SoWinFullViewer::setBottomWheelValue( const float value )
{
  // FIXME: function not implemented
  SOWIN_STUB();
}

void
SoWinFullViewer::rightWheelMotion( float )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::bottomWheelMotion( float )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::leftWheelMotion( float )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::rightWheelStart( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::bottomWheelStart( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::leftWheelStart( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::rightWheelFinish( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::bottomWheelFinish( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::leftWheelFinish( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::setBottomWheelString( const char * name )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::setLeftWheelString( const char * name )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::setRightWheelString( const char * name )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::openViewerHelpCard( void )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::afterRealizeHook( void )
{
  // FIXME: function not implemented
}

HWND
SoWinFullViewer::getViewerWidget( void )
{
  return this->viewerWidget;
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
}

void
SoWinFullViewer::setCameraZoom( float zoom )
{
  // FIXME: function not implemented
}

float
SoWinFullViewer::getCameraZoom( void )
{
  // FIXME: function not implemented
  return 0.0f;
}

void
SoWinFullViewer::setZoomSliderPosition( float zoom )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::setZoomFieldString( float zoom )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::zoomSliderCB( HWND, SoWinFullViewer *, void ** )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::zoomFieldCB( HWND, SoWinFullViewer *, void ** )   // was XPointer *
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::zoomSensorCB( void *, SoSensor *)
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::visibilityChangeCB( void * pt, SbBool visible )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::rightWheelCB( SoWinFullViewer * viewer, void * * data )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::bottomWheelCB( SoWinFullViewer * viewer, void ** data )
{
  // FIXME: function not implemented
}

void
SoWinFullViewer::leftWheelCB( SoWinFullViewer * viewer, void ** data )
{
  // FIXME: function not implemented
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

    if( GetFocus( ) != object->getNormalWidget( ) )
      SetFocus( object->getNormalWidget( ) );

    POINT point = {  LOWORD( lparam ), HIWORD( lparam ) };

    switch ( message )
      {

      case WM_RBUTTONDOWN:
        ClientToScreen( window, & point );
        object->displayPopupMenu( point.x, point.y, window );
        return 0;

      case WM_SIZE:
        return object->onSize( window, message, wparam, lparam );

        /*
          case WM_PAINT:
          return object->onPaint( window, message, wparam, lparam );
        */

      case WM_DESTROY:
        return object->onDestroy( window, message, wparam, lparam );
      }
  }
  return DefWindowProc( window, message, wparam, lparam );
}

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

LRESULT
SoWinFullViewer::onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  // FIXME: function not implemented
  this->setViewing( FALSE );
  return 0;
}

LRESULT
SoWinFullViewer::onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  //HWND managerWidget = this->getManagerWidget( );
  assert( renderAreaWidget != NULL );
  MoveWindow( renderAreaWidget,//managerWidget,//
              0 + renderAreaOffset.left,
              0 + renderAreaOffset.top,
              LOWORD( lparam ) + renderAreaOffset.right,
              HIWORD( lparam ) + renderAreaOffset.bottom,
              FALSE );

  // Left trim
  if ( this->leftWheel )
  this->leftWheel->move( renderAreaOffset.left - this->leftWheel->width( ) - 2,
                         HIWORD( lparam ) + renderAreaOffset.bottom
                         - this->leftWheel->height( ) + 1 );

  // FIXME: do the rest
  return 0;
}

LRESULT
SoWinFullViewer::onPaint( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  // FIXME: function not implemented
  return 0;
}

LRESULT
SoWinFullViewer::onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
  // FIXME: function not implemented
  return 0;
}

void
SoWinFullViewer::drawDecorations( SoWinFullViewer * viewer, HWND hwnd, HDC hdc )
{
  // FIXME: function not implemented
}

