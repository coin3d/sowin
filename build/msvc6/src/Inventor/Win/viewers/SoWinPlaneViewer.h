/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SOWINPLANEVIEWER_H
#define SOWINPLANEVIEWER_H

#include <Inventor/Win/viewers/SoWinFullViewer.h>

// ************************************************************************

class SOWIN_DLL_API SoWinPlaneViewer : public SoWinFullViewer {
  SOWIN_OBJECT_HEADER(SoWinPlaneViewer, SoWinFullViewer);

public:
  SoWinPlaneViewer(HWND parent = NULL,
                     const char * const name = NULL, 
                     SbBool embed = TRUE, 
                     SoWinFullViewer::BuildFlag flag = BUILD_ALL, 
                     SoWinViewer::Type type = BROWSER);
  ~SoWinPlaneViewer();

  virtual void setViewing(SbBool enable);
  virtual void setCamera(SoCamera * camera);
  virtual void setCursorEnabled(SbBool enable);

protected:
  SoWinPlaneViewer(HWND parent,
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
  virtual void setSeekMode(SbBool enable);
  virtual void actualRedraw(void);

  virtual void bottomWheelStart(void);
  virtual void bottomWheelMotion(float value);
  virtual void bottomWheelFinish(void);

  virtual void leftWheelStart(void);
  virtual void leftWheelMotion(float value);
  virtual void leftWheelFinish(void);

  virtual void rightWheelStart(void);
  virtual void rightWheelMotion(float value);
  virtual void rightWheelFinish(void);

  virtual void createViewerButtons(HWND parent, SbPList * buttons);

  virtual void afterRealizeHook(void);

private:
  class SoWinPlaneViewerP * pimpl;

  friend class SoGuiPlaneViewerP;
  friend class SoWinPlaneViewerP;
};

#endif // !SOWINPLANEVIEWER_H
