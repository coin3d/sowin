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

#ifndef SOWIN_DEVICE_H
#define SOWIN_DEVICE_H

#include <Inventor/SbLinear.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/Win/SoWinObject.h>
#include <wtypes.h>

#define ButtonPressMask   0x01
#define ButtonReleaseMask 0x02
#define PointerMotionMask 0x04
#define ButtonMotionMask  0x08
#define KeyPressMask      0x10
#define KeyReleaseMask    0x20

#ifndef MK_ALT
#define MK_ALT 0x02
#endif


// typedef void SoWinEventHandler(HWND, void *, MSG *, SbBool *);
typedef LRESULT SoWinEventHandler(HWND, UINT, WPARAM, LPARAM);

typedef void (*SoWinEventHandlerPtr)(HWND, void *, MSG *, SbBool *);

class SOWIN_DLL_API SoWinDevice : public SoWinObject {
  SOWIN_OBJECT_ABSTRACT_HEADER(SoWinDevice, SoWinObject);

public:
  SoWinDevice(void);
  ~SoWinDevice(void);

  virtual void enable(HWND widget, SoWinEventHandler * callbackproc, void * data, HWND window = NULL) = 0;
  virtual void disable(HWND widget, SoWinEventHandler * callbackproc, void * data) = 0;
    
  virtual const SoEvent * translateEvent(MSG * msg) = 0;

  void setWindowSize(const SbVec2s newSize);
  const SbVec2s getWindowSize(void) const;

  static void initClasses(void);

protected:
  // set the window coordinate from the passed x,y value. This will flip
  // the y value to convert from X coordinates to So coordinates.
  void setEventPosition(SoEvent * event, int x, int y) const;
  static long modifierKeys;
    
private:
  SbVec2s size;
};

#endif // !SOWIN_DEVICE_H
