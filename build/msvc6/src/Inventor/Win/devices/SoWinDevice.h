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

#ifndef SOWIN_DEVICE_H
#define SOWIN_DEVICE_H

// *************************************************************************
//
// Toolkit-specific typedef and include(s). Put these before any Coin
// and/or SoWin includes, in case there are any dependency bugs in
// the underlying native toolkit set of include files versus the
// compiler environment's include files.

#include <Inventor/Win/SoWinBasic.h> // Contains __COIN_SOWIN__ define.

#ifdef __COIN_SOQT__
#include <qevent.h>
typedef void SoWinEventHandler(HWND, void *, MSG *, bool *);
#endif // __COIN_SOQT__
#ifdef __COIN_SOXT__
#include <X11/Intrinsic.h>
typedef void SoWinEventHandler(HWND, XtPointer, XEvent *, Boolean *);
#endif // __COIN_SOXT__
#ifdef __COIN_SOGTK__
#include <gtk/gtk.h>
typedef gint SoWinEventHandler(HWND, MSG *, gpointer);
#endif // __COIN_SOGTK__
#ifdef __COIN_SOWIN__
#include <windows.h>
typedef LRESULT SoWinEventHandler(HWND, UINT, WPARAM, LPARAM);
#endif // __COIN_SOWIN__

// *************************************************************************

#include <Inventor/SbLinear.h>
#include <Inventor/Win/SoWinObject.h>

class SoEvent;

// *************************************************************************

class SOWIN_DLL_API SoWinDevice : public SoWinObject {
  SOWIN_OBJECT_ABSTRACT_HEADER(SoWinDevice, SoWinObject);

public:
  virtual ~SoWinDevice();

  virtual void enable(HWND w, SoWinEventHandler * handler, void * closure) = 0;
  virtual void disable(HWND w, SoWinEventHandler * handler, void * closure) = 0;

  virtual const SoEvent * translateEvent(MSG * event) = 0;

  void setWindowSize(const SbVec2s size);
  SbVec2s getWindowSize(void) const;

  static void initClasses(void);

protected:
  SoWinDevice(void);

  void setEventPosition(SoEvent * event, int x, int y) const;
  static SbVec2s getLastEventPosition(void);

  void addEventHandler(HWND, SoWinEventHandler *, void *);
  void removeEventHandler(HWND, SoWinEventHandler *, void *);
  void invokeHandlers(MSG * event);

private:
  class SoWinDeviceP * pimpl;
  friend class SoWinDeviceP;
};

// *************************************************************************

#endif // !SOWIN_DEVICE_H
