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

#ifndef SOWIN_EXAMINERVIEWER_H
#define SOWIN_EXAMINERVIEWER_H

#include <Inventor/SbLinear.h>
#include <Inventor/Win/viewers/SoWinFullViewer.h>

class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;

class SoWinThumbWheel;

// *************************************************************************

class SOWIN_DLL_API SoWinExaminerViewer : public SoWinFullViewer {
  SOWIN_OBJECT_HEADER(SoWinExaminerViewer, SoWinFullViewer);

public:
  SoWinExaminerViewer(HWND parent = NULL,
                        const char * name = NULL,
                        SbBool embed = TRUE,
                        SoWinFullViewer::BuildFlag flag = BUILD_ALL,
                        SoWinViewer::Type type = BROWSER);
  ~SoWinExaminerViewer();

  void setAnimationEnabled(const SbBool enable);
  SbBool isAnimationEnabled(void) const;

  void stopAnimating(void);
  SbBool isAnimating(void) const;

  void setFeedbackVisibility(const SbBool enable);
  SbBool isFeedbackVisible(void) const;

  void setFeedbackSize(const int size);
  int getFeedbackSize(void) const;

  virtual void setViewing(SbBool enable);
  virtual void setCamera(SoCamera * camera);
  virtual void setCursorEnabled(SbBool enable);

protected:
  SoWinExaminerViewer(HWND parent,
                        const char * name,
                        SbBool embed,
                        SoWinFullViewer::BuildFlag flag,
                        SoWinViewer::Type type,
                        SbBool build);

  virtual void leftWheelMotion(float val);
  virtual void bottomWheelMotion(float val);
  virtual void rightWheelMotion(float val);

  virtual void createViewerButtons(HWND parent, SbPList * buttonlist);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual SbBool processSoEvent(const SoEvent * const event);
  virtual void setSeekMode(SbBool enable);
  virtual void actualRedraw(void);

  virtual void afterRealizeHook(void);

private:
  class SoWinExaminerViewerP * pimpl;

  friend class SoGuiExaminerViewerP;
  friend class SoWinExaminerViewerP;
};

#endif // ! SOWIN_EXAMINERVIEWER_H
