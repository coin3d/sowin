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

#ifndef SOWIN_WALKVIEWER_H
#define SOWIN_WALKVIEWER_H

#include <Inventor/Win/viewers/SoWinConstrainedViewer.h>

// ************************************************************************

class SOWIN_DLL_API SoWinWalkViewer : public SoWinConstrainedViewer {
  SOWIN_OBJECT_HEADER(SoWinWalkViewer, SoWinConstrainedViewer);

public:
  SoWinWalkViewer(
    HWND parent = NULL,
    const char * name = NULL,
    SbBool embed = TRUE,
    SoWinFullViewer::BuildFlag flag = BUILD_ALL,
    SoWinViewer::Type type = BROWSER);
  ~SoWinWalkViewer(void);

  virtual void setViewing(SbBool enable);
  virtual void setCamera(SoCamera * camera);
  virtual void setCursorEnabled(SbBool enable);

  virtual void setCameraType(SoType type);

protected:
  SoWinWalkViewer(
    HWND parent,
    const char * name,
    SbBool embed,
    SoWinFullViewer::BuildFlag flag,
    SoWinViewer::Type type,
    SbBool build);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual void processEvent(MSG * event);
  virtual void setSeekMode(SbBool enable);
  virtual void actualRedraw(void);

  virtual void rightWheelMotion(float value);

  virtual HWND buildLeftTrim(HWND parent);

  virtual void createPrefSheet(void);
  virtual void openViewerHelpCard(void);

}; // class SoWinWalkViewer

// ************************************************************************

#endif // ! SOWIN_WALKVIEWER_H
