/**************************************************************************
 *
 *  This file is part of the Coin SoWin GUI binding library.
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

#if SOWIN_DEBUG
static const char rcsid[] =
  "$Id$";
#endif // SOWIN_DEBUG

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#if SOWIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOWIN_DEBUG

#include <sowindefs.h>
#include <Inventor/Win/widgets/SoWinThumbWheel.h>

#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/Win/viewers/SoAnyExaminerViewer.h>

/*!
  \class SoWinExaminerViewer SoWinExaminerViewer.h Inventor/Win/viewers/SoWinExaminerViewer.h
  \brief The SoWinExaminerViewer class is a full-fledged model viewer
  with functionality for rotation, pan, zoom, etc.
  \ingroup sowinviewers

  TODO: more doc
  ...overview of what this class provides over parent class...
  ...keyboard combinations...mousebutton combinations...explain pan,
  rotate, zoom, dolly, seek...explain the fact that we're moving the
  camera, not the scene...
  ...viewer modes (examine vs interact) w/ explanation of what they are
  useful for...
  ...screenshot...
  ...example code...

  \sa SoWinWalkViewer, SoWinFlyViewer, SoWinPlaneViewer, SoWinCollisionViewer
*/

/*¡
  SoWinExaminerViewer is missing the class description documentation.
*/

// *************************************************************************

SOWIN_OBJECT_SOURCE(SoWinExaminerViewer);

// *************************************************************************

/*!
  Constructor.  See parent class for explanation of arguments.
  Calling this constructor will make sure the examiner viewer widget
  will be built immediately.
*/

SoWinExaminerViewer::SoWinExaminerViewer(
  HWND parent,
  const char * name,
  SbBool embed,
  SoWinFullViewer::BuildFlag flag,
  SoWinViewer::Type type )
: inherited( parent, name, embed, flag, type, FALSE )
, common( new SoAnyExaminerViewer( this ) )
{
  this->constructor( TRUE );
} // SoWinExaminerViewer()

// *************************************************************************

/*!
  Constructor. See parent class for explanation of arguments.
*/

SoWinExaminerViewer::SoWinExaminerViewer(
  HWND parent,
  const char * name,
  SbBool embed,
  SoWinFullViewer::BuildFlag flag,
  SoWinViewer::Type type,
  SbBool build)
: inherited( parent, name, embed, flag, type, FALSE )
, common( new SoAnyExaminerViewer( this ) )
{
  this->constructor( build );
} // SoWinExaminerViewer()

// *************************************************************************

/*!
  \internal

  This contains the real constructor code (the two constructors are only
  entry points for this method).
*/

void
SoWinExaminerViewer::constructor(
  SbBool build )
{
//    this->defaultcursor = NULL;
//    this->rotatecursor = NULL;
//    this->pancursor = NULL;
//    this->zoomcursor = NULL;

//    this->orthopixmap = new QPixmap((const char **)ortho_xpm);
//    this->perspectivepixmap = new QPixmap((const char **)perspective_xpm);
//    assert(this->orthopixmap->size() == this->perspectivepixmap->size());

//    this->spindetecttimer = NULL;
  this->setClassName("SoWinExaminerViewer");

//    this->addVisibilityChangeCallback(SoWinExaminerViewer::visibilityCB, this);

  this->setPopupMenuString("Examiner Viewer");
  this->setPrefSheetString("Examiner Viewer Preference Sheet");
  this->setLeftWheelString("Rotx");
  this->setBottomWheelString("Roty");

  if ( build ) {
    HWND widget = this->buildWidget( this->getParentWidget() );
    this->setBaseWidget( widget );
  }
} // constructor()

// *************************************************************************

/*!
  Destructor.
*/

SoWinExaminerViewer::~SoWinExaminerViewer(
  void )
{
//    // Cursors.
//    delete this->zoomcursor;
//    delete this->pancursor;
//    delete this->rotatecursor;
//    delete this->defaultcursor;

//    // Button pixmaps.
//    delete this->orthopixmap;
//    delete this->perspectivepixmap;

//    // Variables used in the spin animation code.
//    delete this->spindetecttimer;

  delete this->common;
} // ~SoWinExaminerViewer()

// *************************************************************************

/*!
  This method overloaded from parent class to make sure the mouse
  pointer cursor is updated.
*/

void
SoWinExaminerViewer::setViewing( // virtual
  SbBool enable )
{
  this->common->setMode( enable ?
                         SoAnyExaminerViewer::EXAMINE :
                         SoAnyExaminerViewer::INTERACT );
  inherited::setViewing( enable );
} // setViewing()

// *************************************************************************

/*!
  This method overloaded from parent class to toggle the camera type
  selection button pixmap and string of the zoom/dolly thumbwheel.
*/

void
SoWinExaminerViewer::setCamera( // virtual
  SoCamera * newCamera )
{
  if (newCamera) {
    SoType camtype = newCamera->getTypeId();
    SbBool orthotype =
      camtype.isDerivedFrom(SoOrthographicCamera::getClassTypeId());

    this->setRightWheelString(orthotype ? "Zoom" : "Dolly");
//      if (this->cameratogglebutton) {
//        this->cameratogglebutton->setPixmap(orthotype ?
//                                            * (this->orthopixmap) :
//                                            * (this->perspectivepixmap));
//      }
  }

  inherited::setCamera(newCamera);
} // setCamera()

// *************************************************************************

/*!
  Decide whether or not the mouse pointer cursor should be visible in the
  rendering canvas.
*/

void
SoWinExaminerViewer::setCursorEnabled( // virtual, protected
  SbBool enable )
{
  inherited::setCursorEnabled( enable );
  this->setCursorRepresentation( this->common->currentmode );
} // setcursorEnabled()

/*!
  FIXME: write doc
*/

void
SoWinExaminerViewer::resetToHomePosition(
  void )
{
  inherited::resetToHomePosition();
} // resetToHomePosition()

/*!
  FIXME: write doc
*/

void
SoWinExaminerViewer::viewAll( // virtual
  void )
{
  inherited::viewAll();
} // viewAll()

// *************************************************************************

/*!
  Overloaded to provide the examiner viewer functionality on the left
  thumbwheel (x axis rotation).
*/

void
SoWinExaminerViewer::leftWheelMotion(
  float value )
{
  if ( common->isAnimating() )
    common->stopAnimating();

	inherited::leftWheelMotion(
		common->rotXWheelMotion( value, this->getLeftWheelValue() ) );
} // leftWheelMotion()

/*!
  Overloaded to provide the examiner viewer functionality on the bottom
  thumbwheel (y axis rotation).
*/

void
SoWinExaminerViewer::bottomWheelMotion(
  float value )
{
  if ( common->isAnimating() )
    common->stopAnimating();

  inherited::bottomWheelMotion(
		common->rotYWheelMotion( value, this->getBottomWheelValue() ) );
} // bottomWheelMotion()

/*!
  Overloaded to provide the examiner viewer functionality on the left
  thumbwheel (dolly/zoom).
*/

void
SoWinExaminerViewer::rightWheelMotion(
  float value )
{
	common->zoom( this->getRightWheelValue() - value );
	inherited::rightWheelMotion( value );
} // rightWheelMotion()

// *************************************************************************

/*!
  Overloaded to provide name of class.
*/

const char *
SoWinExaminerViewer::getDefaultWidgetName( // virtual
  void ) const
{
  static const char defaultWidgetName[] = "SoWinExaminerViewer";
  return defaultWidgetName;
} // getDefaultWidgetName()

// *************************************************************************

/*!
  Overloaded to provide ``title'' of class.
*/

const char *
SoWinExaminerViewer::getDefaultTitle(void) const
{
  static const char defaultTitle[] = "Examiner Viewer";
  return defaultTitle;
} // getDefaultTitle()

// *************************************************************************

/*!
  Overloaded to provide ``title'' of class.
*/

const char *
SoWinExaminerViewer::getDefaultIconTitle(void) const
{
  static const char defaultIconTitle[] = "Examiner Viewer";
  return defaultIconTitle;
} // getDefaultIconTitle()

// *************************************************************************

/*!
  Pops up the examiner viewer help card.
*/

void
SoWinExaminerViewer::openViewerHelpCard(void)
{
  this->openHelpCard("SoWinExaminerViewer.help");
} // openViewerHelpCard()

// *************************************************************************

/*!
*/

SbBool
SoWinExaminerViewer::processSoEvent(
  const SoEvent * const event )
{
  if ( common->processSoEvent(event) )
    return TRUE;

  return inherited::processSoEvent(event);
} // processSoEvent()

// *************************************************************************

/*!
  Overload this method to make sure any animations are stopped before
  we go into seek mode.
*/

void
SoWinExaminerViewer::setSeekMode(SbBool on)
{
#if SOWIN_DEBUG
  if (on == this->isSeekMode()) {
    SoDebugError::postWarning("SoWinExaminerViewer::setSeekMode",
                              "seek mode already %sset", on ? "" : "un");
    return;
  }
#endif // SOWIN_DEBUG

  if (common->isAnimating()) common->stopAnimating();
  inherited::setSeekMode(on);
  this->common->setMode(on ?
                        SoAnyExaminerViewer::WAITING_FOR_SEEK :
                        SoAnyExaminerViewer::EXAMINE);
} // setSeekMode()

// *************************************************************************

/*!
  Overload this method to be able to draw the axis cross if selected
  in the preferences sheet.
*/

void
SoWinExaminerViewer::actualRedraw(void)
{
  common->actualRedraw();
  inherited::actualRedraw();
  if ( common->isFeedbackVisible() )
    common->drawAxisCross();
  if ( common->isAnimating() )
    this->scheduleRedraw();
} // actualRedraw()

// *************************************************************************

/*!
  \internal

  Set cursor graphics according to mode.
*/

void
SoWinExaminerViewer::setCursorRepresentation( int mode )
{
//    HWND w = this->getRenderAreaWidget();
//    assert(w);

//    if (!this->defaultcursor) {
//      this->defaultcursor = new QCursor(w->cursor());

//      // For Win on MSWin, it is necessary to mask the bitmaps "manually"
//      // before setting up the QBitmaps for the cursors. It doesn't seem
//      // to matter any way under X11. Sounds like a Win bug to me, which
//      // seems strange -- as this issue has been present for at least a
//      // couple of years. 20000630 mortene.
//      {
//        unsigned char * bitmaps[] = {
//          so_win_rotate_bitmap, so_win_rotate_mask_bitmap,
//          so_win_zoom_bitmap, so_win_zoom_mask_bitmap,
//          so_win_pan_bitmap, so_win_pan_mask_bitmap
//        };
//        unsigned int bitmapsizes[] = {
//          (so_win_rotate_width + 7) / 8 * so_win_rotate_height,
//          (so_win_zoom_width + 7) / 8 * so_win_zoom_height,
//          (so_win_pan_width + 7) / 8 * so_win_pan_height,
//        };

//        for ( unsigned int i = 0;
//              i < (sizeof(bitmapsizes) / sizeof(unsigned int)); i++) {
//          for ( unsigned int j = 0; j < bitmapsizes[i]; j++)
//            bitmaps[i*2][j] &= bitmaps[i*2+1][j];
//        }
//      }

//      QBitmap zoomBtm(so_win_zoom_width, so_win_zoom_height,
//                      (uchar*)so_win_zoom_bitmap, FALSE);
//      QBitmap zoomMask(so_win_zoom_width, so_win_zoom_height,
//                       (uchar*)so_win_zoom_mask_bitmap, FALSE);
//      QBitmap panBtm(so_win_pan_width, so_win_pan_height,
//                     (uchar*)so_win_pan_bitmap, FALSE);
//      QBitmap panMask(so_win_pan_width, so_win_pan_height,
//                      (uchar*)so_win_pan_mask_bitmap, FALSE);

//      QBitmap rotateBtm(so_win_rotate_width, so_win_rotate_height,
//                        (uchar*)so_win_rotate_bitmap, FALSE);
//      QBitmap rotateMask(so_win_rotate_width, so_win_rotate_height,
//                         (uchar*)so_win_rotate_mask_bitmap, FALSE);

//      this->zoomcursor = new QCursor(zoomBtm, zoomMask,
//                                     so_win_zoom_x_hot, so_win_zoom_y_hot);
//      this->pancursor = new QCursor(panBtm, panMask,
//                                    so_win_pan_x_hot, so_win_pan_y_hot);
//      this->rotatecursor = new QCursor(rotateBtm, rotateMask,
//                                       so_win_rotate_x_hot, so_win_rotate_y_hot);
//    }



//    if (!this->isCursorEnabled()) {
//      w->setCursor(blankCursor);
//      return;
//    }

//    switch (mode) {
//    case SoAnyExaminerViewer::INTERACT:
//      w->setCursor(arrowCursor);
//      break;

//    case SoAnyExaminerViewer::EXAMINE:
//    case SoAnyExaminerViewer::DRAGGING:
//      w->setCursor(* this->rotatecursor);
//      break;

//    case SoAnyExaminerViewer::ZOOMING:
//      w->setCursor(* this->zoomcursor);
//      break;

//    case SoAnyExaminerViewer::WAITING_FOR_SEEK:
//      w->setCursor(crossCursor);
//      break;

//    case SoAnyExaminerViewer::WAITING_FOR_PAN:
//    case SoAnyExaminerViewer::PANNING:
//      w->setCursor(* this->pancursor);
//      break;

//    default: assert(0); break;
//    }
} // setCursorRepresentation()

// *************************************************************************

void
SoWinExaminerViewer::setAnimationEnabled(
  const SbBool enable )
{
  common->setAnimationEnabled( enable );
  // FIXME: set spinanimtoggle state
} // setAnimationEnabled()

SbBool
SoWinExaminerViewer::isAnimationEnabled(
  void ) const
{
  return common->isAnimationEnabled();
} // isAnimationEnabled()

void
SoWinExaminerViewer::stopAnimating(
  void )
{
  common->stopAnimating();
} // stopAnimating()

SbBool
SoWinExaminerViewer::isAnimating(
  void ) const
{
  return common->isAnimating();
} // isAnimating()

void
SoWinExaminerViewer::setFeedbackVisibility(
  const SbBool enable )
{
  common->setFeedbackVisibility( enable );
} // setFeedbackVisibility()

SbBool
SoWinExaminerViewer::isFeedbackVisible(
  void ) const
{
  return common->isFeedbackVisible();
} // isFeedbackVisible()

void
SoWinExaminerViewer::setFeedbackSize(
   const int size )
{
  common->setFeedbackSize( size );
} // setFeedbackSize()

int
SoWinExaminerViewer::getFeedbackSize(
  void ) const
{
  return common->getFeedbackSize();
} // getFeedbackSize()

// *************************************************************************

/*!
*/

void
SoWinExaminerViewer::afterRealizeHook( // virtual
  void )
{
  this->setCursorRepresentation( this->common->currentmode );
  inherited::afterRealizeHook();
} // afterRealizeHook()

// *************************************************************************

#if SOWIN_DEBUG
static const char * getSoWinExaminerViewerRCSID(void) { return rcsid; }
#endif




