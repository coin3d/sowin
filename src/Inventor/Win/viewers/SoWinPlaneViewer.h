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

#ifndef SOWIN_PLANEVIEWER_H
#define SOWIN_PLANEVIEWER_H

class SbPlaneProjector;
class SoAnyPlaneViewer;
class SoWinPlaneViewerP;

#include <Inventor/Win/viewers/SoWinFullViewer.h>

// ************************************************************************

class SOWIN_DLL_API SoWinPlaneViewer : public SoWinFullViewer {
  
  SOWIN_OBJECT_HEADER(SoWinPlaneViewer, SoWinFullViewer);
  friend class SoAnyPlaneViewer;
  friend class SoWinPlaneViewerP;

public:
  
  SoWinPlaneViewer(
    HWND parent = NULL,
    const char * const name = NULL, 
    SbBool embed = TRUE, 
    SoWinFullViewer::BuildFlag flag = BUILD_ALL, 
    SoWinViewer::Type type = BROWSER);
  ~SoWinPlaneViewer(void);

  virtual void setViewing(SbBool enable);
  virtual void setCamera(SoCamera * camera);
  virtual void setCursorEnabled(SbBool enable);

protected:
  
  SoWinPlaneViewer(
    HWND parent,
    const char * const name, 
    SbBool embed, 
    SoWinFullViewer::BuildFlag flag, 
    SoWinViewer::Type type, 
    SbBool build);

  HWND buildWidget(HWND parent);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual SbBool processSoEvent(const SoEvent * const event);

  virtual LRESULT onCommand(HWND window,
                             UINT message,
                             WPARAM wparam,
                             LPARAM lparam);

  virtual void setSeekMode(SbBool enable);
  virtual void actualRedraw(void);

  virtual void bottomWheelMotion(float value);
  virtual void leftWheelMotion(float value);
  virtual void rightWheelMotion(float value);

  virtual void createPrefSheet(void);

  virtual void buildViewerButtonsEx(HWND parent, int x, int y, int size);  
  virtual void openViewerHelpCard(void);
  virtual void computeSeekFinalOrientation(void);

private:
  
  SoAnyPlaneViewer * common;
  SoWinPlaneViewerP * pimpl;
  
}; // class SoWinPlaneViewer

// ************************************************************************

#endif // ! SOWIN_PLANEVIEWER_H
