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

#ifndef SOWIN_THUMBWHEEL_H
#define SOWIN_THUMBWHEEL_H

#include <wtypes.h>
#include <Inventor/SbBasic.h>
#include <Inventor/Win/SoWinBasic.h>

class SoAnyThumbWheel;


// *************************************************************************

class SOWIN_DLL_API SoWinThumbWheel {

public:
  enum Interaction { START, MOVE, END };
  typedef void ThumbWheelCB(Interaction type, float val, void * userdata);

  enum Orientation {
    Horizontal,
    Vertical
  };
  enum boundaryHandling {
    CLAMP,
    MODULATE,
    ACCUMULATE
  };
  enum State {
    Idle,
    Dragging,
    Disabled
  };

  SoWinThumbWheel(HWND parent = 0, long id = -1, int x = 0, int y = 0, char * name = 0);
  SoWinThumbWheel(Orientation, HWND parent = 0, long id = -1, int x = 0, int y = 0, char * name = 0);
  ~SoWinThumbWheel(void);

  void setId(long id);
  long id(void) const;
  
  void setOrientation(Orientation);
  Orientation orientation(void) const;

  void setValue(float value);
  float value(void) const;

  void setEnabled(SbBool enable);
  SbBool isEnabled(void) const;

  void setLabelText(char * text);
  void setLabelOffset(int x, int y);
  SIZE getLabelSize(void);

  void setRangeBoundaryHandling(boundaryHandling handling);
  boundaryHandling getRangeBoundaryHandling(void) const;

  HWND getWidget(void);
  SIZE sizeHint(void) const;
  int width(void);
  int height(void);
  void move(int x, int y);
  void size(int width, int height);
  void move(int x, int y, int width, int height);
  void setCallback(ThumbWheelCB * func, void * userdata);

  void show(void);
  void hide(void);

protected:

  LRESULT CALLBACK onCreate(HWND window,
                             UINT message,
                             WPARAM wparam,
                             LPARAM lparam);

  LRESULT CALLBACK onSize(HWND window,
                           UINT message,
                           WPARAM wparam,
                           LPARAM lparam);

  LRESULT CALLBACK onPaint(HWND window,
                            UINT message,
                            WPARAM wparam,
                            LPARAM lparam);

  LRESULT CALLBACK onLButtonDown(HWND window,
                                  UINT message,
                                  WPARAM wparam,
                                  LPARAM lparam);

  LRESULT CALLBACK onLButtonUp(HWND window,
                                UINT message,
                                WPARAM wparam,
                                LPARAM lparam);

  LRESULT CALLBACK onMouseMove(HWND window,
                                UINT message,
                                WPARAM wparam,
                                LPARAM lparam);

  LRESULT CALLBACK onDestroy(HWND window,
                              UINT message,
                              WPARAM wparam,
                              LPARAM lparam);

  static LRESULT CALLBACK windowProc(HWND window,
                                      UINT message,
                                      WPARAM wparam,
                                      LPARAM lparam);

private:
  
  void constructor(Orientation);
  HWND buildWidget(HWND parent, RECT rect, char * name);
  void initWheel(int diameter, int width);
  HWND createLabel(HWND parent, int x, int y, char * text);
  HBITMAP createDIB(int width, int height, int bpp, void ** bits);
  void blitBitmap(HBITMAP bitmap, HDC dc, int x,int y, int width, int height) const;
  SIZE getTextSize(HWND window, char * text);

  Orientation orient;
  State state;
  float wheelValue, tempWheelValue;
  int mouseDownPos, mouseLastPos;

  SoAnyThumbWheel * wheel;
  HBITMAP * pixmaps;
  int numPixmaps;
  int currentPixmap;

  HWND wheelWindow;
  HWND labelWindow;

  POINT labelOffset;

  ThumbWheelCB * viewerCB;
  void * userdataCB;

  static ATOM wheelWndClassAtom;
  static int wheelWidgetCounter;
};

// *************************************************************************

#endif // ! SOWIN_THUMBWHEEL_H
