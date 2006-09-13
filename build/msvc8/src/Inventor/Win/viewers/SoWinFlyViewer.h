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

// src/Inventor/Win/viewers/SoWinFlyViewer.h.  Generated from SoGuiFlyViewer.h.in by configure.

#ifndef SOWIN_FLYVIEWER_H
#define SOWIN_FLYVIEWER_H

#include <Inventor/Win/viewers/SoWinConstrainedViewer.h>

// ************************************************************************

class SOWIN_DLL_API SoWinFlyViewer : public SoWinConstrainedViewer {
  SOWIN_OBJECT_HEADER(SoWinFlyViewer, SoWinConstrainedViewer);

public:
  SoWinFlyViewer(HWND parent = NULL,
                   const char * name = NULL, 
                   SbBool embed = TRUE, 
                   SoWinFullViewer::BuildFlag flag = BUILD_ALL,
                   SoWinViewer::Type type = BROWSER);
  ~SoWinFlyViewer();

  virtual void setViewing(SbBool enable);
  virtual void viewAll(void);
  virtual void resetToHomePosition(void);
  virtual void setCamera(SoCamera * camera);
  virtual void setCursorEnabled(SbBool enable);
  virtual void setCameraType(SoType type);

protected:
  SoWinFlyViewer(HWND parent,
                   const char * const name, 
                   SbBool embed, 
                   SoWinFullViewer::BuildFlag flag, 
                   SoWinViewer::Type type, 
                   SbBool build);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual SbBool processSoEvent(const SoEvent * const event);
  virtual void setSeekMode(SbBool enable);
  virtual void actualRedraw(void);

  virtual void rightWheelMotion(float value);

  virtual void afterRealizeHook(void);

private:
  class SoWinFlyViewerP * pimpl;
  friend class SoWinFlyViewerP;
};

// ************************************************************************

#endif // ! SOWIN_FLYVIEWER_H
