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

#ifndef  SOWIN_VIEWERPREFSHEET_H
#define  SOWIN_VIEWERPREFSHEET_H

class SoWinThumbWheel;
class SoWinFullViewer;
class SoWinExaminerViewer;

class SOWIN_DLL_API SoWinViewerPrefSheet {
  
public:
  SoWinViewerPrefSheet(void);
  ~SoWinViewerPrefSheet(void);
  void create(HWND parent = NULL);
  void size(void);
  void destroy(void);
  void show(SbBool show);
  HWND getWidget(void);
  void setTitle(const char * title);

  void createSeekWidgets(SoWinFullViewer * viewer);
  void createZoomWidgets(SoWinFullViewer * viewer);
  void createClippingWidgets(SoWinFullViewer * viewer);
  void createSpinWidgets(SoWinExaminerViewer * viewer);
  
protected:
  
  enum widgetId {
    
    SEEK_TIME_EDIT,
    SEEK_TO_PT_RADIO,
    SEEK_TO_OBJ_RADIO,
    SEEK_DIST_WHEEL,
    SEEK_DIST_EDIT,
    SEEK_DIST_PCT_RADIO,
    SEEK_DIST_ABS_RADIO,
    ZOOM_SLIDER,
    ZOOM_EDIT,
    ZOOM_RANGE_FROM_EDIT,
    ZOOM_RANGE_TO_EDIT,
    CLIPPING_AUTO_CHECK,
    CLIPPING_NEAR_WHEEL,
    CLIPPING_NEAR_EDIT,
    CLIPPING_FAR_WHEEL,
    CLIPPING_FAR_EDIT,
    SPIN_ENABLE_CHECK,
    SPIN_AXES_CHECK,
    SPIN_AXES_WHEEL,
    SPIN_AXES_EDIT
    
  };

  void constructor(void);

  void createMainWidget(HWND parent);

  void initSeekWidgets(SoWinFullViewer * viewer);
  void initZoomWidgets(SoWinFullViewer * viewer);
  void initClippingWidgets(SoWinFullViewer * viewer);
  void initSpinWidgets(SoWinExaminerViewer * viewer);

  void destroyMainWidget(void);
  void destroySeekWidgets(void);
  void destroyZoomWidgets(void);  
  void destroyClippingWidgets(void);
  void destroySpinWidgets(void);

  HWND createLabelWidget(HWND parent, const char * text = NULL, int x = 0, int y = 0);
  HWND createEditWidget(HWND parent, long id, int width = 64, int x = 0, int y = 0);
  HWND createRadioWidget(HWND parent, long id, const char * text = NULL, int x = 0, int y = 0);
  HWND createSliderWidget(HWND parent, long id, int width = 64, int x = 0, int y = 0);
  HWND createCheckWidget(HWND parent, long id, const char * text = NULL, int x = 0, int y = 0);
  
  void setSliderValue(HWND slider, int value);
  int getSliderValue(HWND slider);
  void setSliderRange(HWND slider, int min, int max);
  SIZE getSliderRange(HWND slider);
  void setChecked(HWND hwnd, BOOL check);
  void setEnabled(HWND hwnd, BOOL enable);
  
  SIZE getTextSize(HWND window, const char * text);
  int getFontHeight(HWND window);

  void setEditValue(HWND edit, float value);
  float getEditValue(HWND edit);
  
  // Event handlers

  static LRESULT CALLBACK processEvent(HWND window,
                                        UINT message,
                                        WPARAM wparam,
                                        LPARAM lparam);

  LRESULT onCreate(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  LRESULT onDestroy(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  LRESULT onCommand(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  LRESULT onScroll(HWND window, UINT message, WPARAM wparam, LPARAM lparam);  
  LRESULT onThumbWheel(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  
private:
 
  int lineHeight;
  int x, y;
  SbString className;
  SbString title;
  
  HWND mainWidget;
  
  HWND seekWidgets[10];
  SoWinThumbWheel * seekDistWheel;

  HWND zoomWidgets[7];

  HWND clippingWidgets[5];
  SoWinThumbWheel * nearPlaneWheel;
  SoWinThumbWheel * farPlaneWheel;

  HWND spinWidgets[4];
  SoWinThumbWheel * axesSizeWheel;

  SoWinFullViewer * seekViewer;
  SoWinFullViewer * zoomViewer;
  SoWinFullViewer * clippingViewer;
  SoWinExaminerViewer * spinViewer;

  static ATOM wndClassAtom;
  static int wndCounter;
  
};

#endif  // SOWIN_VIEWERPREFSHEET_H



