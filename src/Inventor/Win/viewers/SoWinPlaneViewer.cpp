/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 as published by the Free Software Foundation.  See the file
 *  LICENSE.LGPL at the root directory of the distribution for all the
 *  details.
 *
 *  If you want to use Coin SoWin for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>

#include <sowindefs.h>
#include <Inventor/Win/widgets/SoWinThumbWheel.h>
#include <Inventor/Win/widgets/SoWinBitmapButton.h>

#include <Inventor/Win/viewers/SoAnyPlaneViewer.h>
#include <Inventor/Win/viewers/SoWinPlaneViewer.h>

#include <Inventor/Win/common/pixmaps/ortho.xpm>
#include <Inventor/Win/common/pixmaps/perspective.xpm>
#include <Inventor/Win/common/pixmaps/x.xpm>
#include <Inventor/Win/common/pixmaps/y.xpm>
#include <Inventor/Win/common/pixmaps/z.xpm>

/*!
  \class SoWinPlaneViewer Inventor/Win/viewers/SoWinPlaneViewer.h
  \brief The SoWinPlaneViewer class is yet to be documented...
  \ingroup soqtviewers
*/

// ************************************************************************

SOWIN_OBJECT_SOURCE( SoWinPlaneViewer );

// ************************************************************************

#define VIEWERBUTTON_X ( VIEWERBUTTON_SEEK + 1 )
#define VIEWERBUTTON_Y ( VIEWERBUTTON_SEEK + 2 )
#define VIEWERBUTTON_Z ( VIEWERBUTTON_SEEK + 3 )
#define VIEWERBUTTON_CAMERA ( VIEWERBUTTON_SEEK + 4 )

/*!
  The public constructor.
*/

SoWinPlaneViewer::SoWinPlaneViewer(
  HWND parent,
  const char * const name, 
  SbBool embed,
  SoWinFullViewer::BuildFlag flag, 
  SoWinViewer::Type type )
: inherited( parent, name, embed, flag, type, FALSE )
, common( new SoAnyPlaneViewer( this ) )
{
  this->constructor( TRUE );
} // SoWinPlaneViewer()

// ************************************************************************

/*!
  A protected constructor.
*/

SoWinPlaneViewer::SoWinPlaneViewer(
  HWND parent,
  const char * const name, 
  SbBool embed, 
  SoWinFullViewer::BuildFlag flag, 
  SoWinViewer::Type type, 
  SbBool build )
: inherited( parent, name, embed, flag, type, FALSE )
, common( new SoAnyPlaneViewer( this ) )
{
  this->constructor( build );
} // SoWinPlaneViewer()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::constructor( // private
  SbBool build )
{
  this->mode = IDLE_MODE;

  this->projector = new SbPlaneProjector;
  SbViewVolume vv;
  vv.ortho( -1, 1, -1, 1, -1, 1 );
  this->projector->setViewVolume( vv );

  this->addVisibilityChangeCallback( SoWinPlaneViewer::visibilityCB, this );

  this->setClassName( "SoWinPlaneViewer" );
  this->setLeftWheelString( "transY" );
  this->setBottomWheelString( "transX" );

  if ( ! build ) return;

  //this->setSize( SbVec2s( 555, 515 ) );
  this->initSize.setValue( 555, 515 );
  
  HWND viewer = this->buildWidget( this->getParentWidget( ) );
  this->setBaseWidget( viewer );
} // constructor()

// ************************************************************************

/*!
  The destructor.
*/

SoWinPlaneViewer::~SoWinPlaneViewer(
  void )
{
  //delete this->pixmaps.orthogonal;
  //delete this->pixmaps.perspective;
  delete this->projector;
} // ~SoWinPlaneViewer()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::setViewing( // virtual
  SbBool enable )
{
  inherited::setViewing( enable );
} // setViewing()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::setCamera( // virtual
  SoCamera * camera )
{
  if ( camera ) {
    SoType type = camera->getTypeId();
    SbBool orthogonal =
      type.isDerivedFrom( SoOrthographicCamera::getClassTypeId( ) );
    this->setRightWheelString( orthogonal ? "Zoom" : "Dolly" );
    /*
    if ( this->buttons.camera ) {
      this->buttons.camera->setPixmap( orthogonal ?
        * ( this->pixmaps.orthogonal ) : * ( this->pixmaps.perspective ) );
    }
    */
    
    if ( this->isDoButtonBar( ) ) // may not be there if !doButtonBar
      ( ( SoWinBitmapButton * ) ( * this->viewerButtonList ) [VIEWERBUTTON_CAMERA] )->setBitmap(
        orthogonal ? 1 : 0 );
  
  }
  inherited::setCamera( camera );
} // setCamera()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::setCursorEnabled( // virtual
  SbBool enable )
{
  inherited::setCursorEnabled( enable );
} // setCursorEnabled()

// ************************************************************************

/*!
  FIXME: write doc
*/

HWND
SoWinPlaneViewer::buildWidget(
  HWND parent )
{
  HWND widget = inherited::buildWidget( parent );
  ( ( SoWinThumbWheel * )this->leftWheel )->setRangeBoundaryHandling( SoWinThumbWheel::ACCUMULATE );
  ( ( SoWinThumbWheel * )this->bottomWheel )->setRangeBoundaryHandling( SoWinThumbWheel::ACCUMULATE );
  return widget;
} // buildWidget()

// ************************************************************************

/*!
  FIXME: write doc
*/

const char *
SoWinPlaneViewer::getDefaultWidgetName( // virtual
  void ) const
{
  static const char defaultWidgetName[] = "SoWinPlaneViewer";
  return defaultWidgetName;
} // getDefaultWidgetName()

// ************************************************************************

/*!
  FIXME: write doc
*/

const char *
SoWinPlaneViewer::getDefaultTitle( // virtual
  void ) const
{
  static const char defaultTitle[] = "Plane Viewer";
  return defaultTitle;
} // getDefaultTitle()

// ************************************************************************

/*!
  FIXME: write doc
*/

const char *
SoWinPlaneViewer::getDefaultIconTitle( // virtual
  void ) const
{
  static const char defaultIconTitle[] = "Plane Viewer";
  return defaultIconTitle;
} // getDefaultIconTitle()

// ************************************************************************

/*!
  FIXME: write doc
*/

SbBool
SoWinPlaneViewer::processSoEvent( // virtual, protected
  const SoEvent * const event )
{
  if ( common->processSoEvent( event ) )
    return TRUE;

  return inherited::processSoEvent( event );
} // processSoEvent()

/*!
  This method overloaded from parent class to handle button messages
  from viewer specific buttons ( x, y, z and camera toggle ).
*/

LRESULT
SoWinPlaneViewer::onCommand( // virtual
  HWND window,
  UINT message,
  WPARAM wparam,
  LPARAM lparam )
{
	int i;
	short nc = HIWORD( wparam );// notification code
	short id = LOWORD( wparam );// item, control, or accelerator identifier
	HWND hwnd = ( HWND ) lparam;// control handle

	switch ( id ) {

    case VIEWERBUTTON_CAMERA:
      this->cameratoggleClicked( );
      return 0;

    case VIEWERBUTTON_X:
      this->xClicked( );
      return 0;

    case VIEWERBUTTON_Y:
      this->yClicked( );
      return 0;

    case VIEWERBUTTON_Z:
      this->zClicked( );
      return 0;

    default:
      return inherited::onCommand( window, message, wparam, lparam );
  }

  return 0;
} // onCommand()

//setModeFromState( keys ); 

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::setSeekMode( // virtual
  SbBool enable )
{
  inherited::setSeekMode( enable );
} // setSeekMode()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::actualRedraw( // virtual
  void )
{
  inherited::actualRedraw( );
//  common->drawRotateGraphics( );
} // actualRedraw( )

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::leftWheelMotion( // virtual
  float value )
{
  common->translateY( value - this->getLeftWheelValue( ) );
  inherited::leftWheelMotion( value );
} // leftWheelMotion()

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::bottomWheelMotion( // virtual
  float value )
{
  common->translateX( value - this->getBottomWheelValue( ) );
  inherited::bottomWheelMotion( value );
} // bottomWheelMotion()

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::rightWheelMotion( // virtual
  float value )
{
  common->zoom( this->getRightWheelValue( ) - value );
  inherited::rightWheelMotion( value );
} // rightWheelMotion()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::createPrefSheet( // virtual
  void )
{
} // createPrefSheet()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::buildViewerButtonsEx( // virtual
  HWND parent,
  int x,
  int y,
  int size )
{
	SoWinBitmapButton * button;

	button = new SoWinBitmapButton( parent, x, y, size, size, 24, "x", NULL );
	button->addBitmap( x_xpm );
	button->setBitmap( 0 );
	button->setId( VIEWERBUTTON_X );
	this->viewerButtonList->append( button );
  
	button = new SoWinBitmapButton( parent, x, y, size, size, 24, "y", NULL );
	button->addBitmap( y_xpm );
	button->setBitmap( 0 );
	button->setId( VIEWERBUTTON_Y );
	this->viewerButtonList->append( button );

  button = new SoWinBitmapButton( parent, x, y, size, size, 24, "z", NULL );
	button->addBitmap( z_xpm );
	button->setBitmap( 0 );
	button->setId( VIEWERBUTTON_Z );
	this->viewerButtonList->append( button );
  
	button = new SoWinBitmapButton( parent, x, y, size, size, 24, "perspective", NULL );
	button->addBitmap( perspective_xpm );
	button->addBitmap( ortho_xpm );
	button->setBitmap( 0 );
	button->setId( VIEWERBUTTON_CAMERA );
	this->viewerButtonList->append( button );
    
}

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::openViewerHelpCard( // virtual
  void )
{
  this->openHelpCard( "SoWinPlaneViewer.help" );
} // openViewerHelpCard( )

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::computeSeekFinalOrientation( // virtual
  void )
{
} // computeSeekFinalOrientation( )

// ************************************************************************

/*!
  \internal
*/

void
SoWinPlaneViewer::xClicked(
  void )
{
  common->viewPlaneX();
  /*
  ( ( SoWinBitmapButton * ) ( * viewerButtonList ) [VIEWERBUTTON_X] )->setState( TRUE );
  ( ( SoWinBitmapButton * ) ( * viewerButtonList ) [VIEWERBUTTON_Y] )->setState( FALSE );
  ( ( SoWinBitmapButton * ) ( * viewerButtonList ) [VIEWERBUTTON_Z] )->setState( FALSE );
  */
} // xClicked()

/*!
  \internal
*/

void
SoWinPlaneViewer::yClicked(
  void )
{
  common->viewPlaneY();
  /*
  ( ( SoWinBitmapButton * ) ( * viewerButtonList ) [VIEWERBUTTON_X] )->setState( FALSE );
  ( ( SoWinBitmapButton * ) ( * viewerButtonList ) [VIEWERBUTTON_Y] )->setState( TRUE );
  ( ( SoWinBitmapButton * ) ( * viewerButtonList ) [VIEWERBUTTON_Z] )->setState( FALSE );
  */
} // yClicked()

/*!
  \internal
*/

void
SoWinPlaneViewer::zClicked(
  void )
{
  common->viewPlaneZ();
  /*
  ( ( SoWinBitmapButton * ) ( * viewerButtonList ) [VIEWERBUTTON_X] )->setState( FALSE );
  ( ( SoWinBitmapButton * ) ( * viewerButtonList ) [VIEWERBUTTON_Y] )->setState( FALSE );
  ( ( SoWinBitmapButton * ) ( * viewerButtonList ) [VIEWERBUTTON_Z] )->setState( TRUE );
  */
} // zClicked( )

/*!
  \internal
*/

void
SoWinPlaneViewer::cameratoggleClicked(
  void )
{
  this->toggleCameraType( );
} // cameraToggleClicked( )

// ************************************************************************

/*!
  \internal
*/

void
SoWinPlaneViewer::visibilityCB( // static
  void * data,
  SbBool visible )
{
  SoWinPlaneViewer * thisp = ( SoWinPlaneViewer * ) data;

/*
  examiner viewer does this, we don't have to...
  if ( thisp->isAnimating( ) ) {
    if ( visible )
      thisp->timerTrigger->schedule( );
    else
      thisp->timerTrigger->unschedule( );
  }
*/
} // visibilityCB( )

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoWinPlaneViewer::setModeFromState( // private
  unsigned int state )
{
  _cprintf( "setModeFromState\n" );
  PlaneViewerMode mode = IDLE_MODE;

  const unsigned int maskedstate =
    state & ( MK_LBUTTON | MK_MBUTTON | MK_CONTROL );

  switch ( maskedstate ) {
  case 0:
    mode = IDLE_MODE;
    break;

  case MK_LBUTTON://LeftButton:
    mode = TRANSLATE_MODE;
    break;

  case MK_MBUTTON://MidButton:
  case ( MK_LBUTTON | MK_CONTROL ):
    mode = DOLLY_MODE;
    break;

  case MK_CONTROL://ControlButton:
    mode = ROTZ_WAIT_MODE;
    break;

  case ( MK_MBUTTON | MK_CONTROL ):
  case ( MK_LBUTTON | MK_MBUTTON | MK_CONTROL ):
    mode = ROTZ_MODE;
    break;

  default:
    SoDebugError::postWarning( "SoWinPlaneViewer::setModeFromState",
      "state not handled: %d", maskedstate );
    break;

  } // switch ( maskedstate )

  this->setMode( mode );
} // setModeFromState()

/*!
*/

void
SoWinPlaneViewer::setMode(
  PlaneViewerMode mode )
{
  // FIXME: set cursor...

  switch ( mode ) {
  case IDLE_MODE:
    while ( this->getInteractiveCount( ) )
      this->interactiveCountDec( );
    break;

  case TRANSLATE_MODE:
  case DOLLY_MODE:
  case ROTZ_MODE:
    while ( this->getInteractiveCount( ) )
      this->interactiveCountDec( );
    break;

  default:
    break;
  } // switch ( mode )

  this->mode = mode;
} // setMode()

// ************************************************************************

#if SOWIN_DEBUG
//static const char * getSoWinPlaneViewerRCSId( void ) { return rcsid; }
#endif
