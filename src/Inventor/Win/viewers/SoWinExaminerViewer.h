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

// $Id$

#ifndef SOWIN_EXAMINERVIEWER_H
#define SOWIN_EXAMINERVIEWER_H

#include <Inventor/Win/viewers/SoWinFullViewer.h>

class SoWinThumbWheel;
class SoAnyExaminerViewer;
class SoWinExaminerViewerP;

// *************************************************************************

class SOWIN_DLL_API SoWinExaminerViewer : public SoWinFullViewer {
  
  SOWIN_OBJECT_HEADER(SoWinExaminerViewer, SoWinFullViewer);
  friend class SoAnyExaminerViewer;
  friend class SoWinExaminerViewerP;
  
public:
  
  SoWinExaminerViewer(
    HWND parent = NULL,
    const char * name = NULL,
    SbBool embed = TRUE,
    SoWinFullViewer::BuildFlag flag = BUILD_ALL,
    SoWinViewer::Type type = BROWSER );
  ~SoWinExaminerViewer( void );

  void setAnimationEnabled( const SbBool enable );
  SbBool isAnimationEnabled( void ) const;

  void stopAnimating( void );
  SbBool isAnimating( void ) const;

  void setFeedbackVisibility( const SbBool enable );
  SbBool isFeedbackVisible( void ) const;

  void setFeedbackSize( const int size );
  int getFeedbackSize( void ) const;

  virtual void setViewing( SbBool enable );
  virtual void setCamera( SoCamera * camera );
  virtual void setCursorEnabled( SbBool enable );
  virtual void resetToHomePosition( void );
  virtual void viewAll( void );

protected:
  
  SoWinExaminerViewer(
    HWND parent,
    const char * name,
    SbBool embed,
    SoWinFullViewer::BuildFlag flag,
    SoWinViewer::Type type,
    SbBool build );

  virtual void leftWheelMotion( float val );
  virtual void bottomWheelMotion( float val );
  virtual void rightWheelMotion( float val );

  virtual const char * getDefaultWidgetName( void ) const;
  virtual const char * getDefaultTitle( void ) const;
  virtual const char * getDefaultIconTitle( void ) const;

  virtual void openViewerHelpCard( void );
  virtual SbBool processSoEvent( const SoEvent * const event );
  virtual LRESULT onCommand( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  virtual void setSeekMode( SbBool enable );
  virtual void actualRedraw( void );
  virtual void afterRealizeHook( void );
  virtual void createPrefSheet( void );
  virtual void buildViewerButtonsEx( HWND parent, int x, int y, int size );

  void setCursorRepresentation( int mode ); // Used by SoAnyExaminerViewer. mariusbu 20010724.
  
private:

  SoAnyExaminerViewer * const common;
  SoWinExaminerViewerP * const pimpl;
  
}; // class SoWinExaminerViewer

// *************************************************************************

#endif // ! SOWIN_EXAMINERVIEWER_H
