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

static const char rcsid[] =
"$Id$";

#include <Inventor/errors/SoDebugError.h>

#include <sowindefs.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinFullViewer.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/Win/viewers/SoAnyExaminerViewer.h>
#include <Inventor/Win/widgets/SoWinThumbWheel.h>
#include <Inventor/Win/widgets/SoWinViewerPrefSheet.h>
#include <Inventor/Win/Win32API.h>

#define AXES_SIZE_FROM_WHEEL(value) (value * 10)
#define AXES_SIZE_TO_WHEEL(value) (value / 10)

ATOM SoWinViewerPrefSheet::wndClassAtom = NULL;
int SoWinViewerPrefSheet::wndCounter = 0;

SoWinViewerPrefSheet::SoWinViewerPrefSheet(void)
{
  this->constructor();
}

SoWinViewerPrefSheet::~SoWinViewerPrefSheet(void)
{
    this->destroy();
}

void SoWinViewerPrefSheet::create(HWND parent)
{
  if (IsWindow(this->mainWidget)) {
    HWND r = SetActiveWindow(this->mainWidget);
    assert((r != NULL) && "SetActiveWindow() failed -- investigate");
    return;
  }

  this->x = 10;
  this->y = 10;
  
  this->createMainWidget(parent);
  this->lineHeight = this->getFontHeight(this->mainWidget) + 10;
}

void SoWinViewerPrefSheet::size(void)
{ 
  RECT rect;
  Win32::GetClientRect(this->mainWidget, & rect);
  int height = rect.bottom;
  
  Win32::GetWindowRect(this->mainWidget, & rect);

  Win32::MoveWindow(this->mainWidget,
                     rect.left,
                     rect.top,
                     // FIXME no adjustment to width yet
                     (rect.right - rect.left),
                     (rect.bottom - rect.top) + ((this->y + 10)  - height),
                     TRUE);
}

void SoWinViewerPrefSheet::destroy(void)
{
  if (IsWindow (this->mainWidget))
    this->destroyMainWidget();
  if (this->seekViewer)
    this->destroySeekWidgets();
  if (this->zoomViewer)
    this->destroyZoomWidgets();
  if (this->clippingViewer)
    this->destroyClippingWidgets();
  if (this->spinViewer)
    this->destroySpinWidgets();
  this->x = this->y = 0;
}

void SoWinViewerPrefSheet::show(SbBool show)
{
  // FIXME: update all widgets (init)
  (void)ShowWindow(this->mainWidget, (show ? SW_SHOW : SW_HIDE));
  if (show) {
    (void)SetActiveWindow(this->mainWidget);
  }
}

HWND SoWinViewerPrefSheet::getWidget(void)
{
  return this->mainWidget;
}

void SoWinViewerPrefSheet::setTitle(const char * title)
{
  if (this->mainWidget) {
    Win32::SetWindowText(this->mainWidget, title);
  }
  this->title = title;
}

void SoWinViewerPrefSheet::createSeekWidgets(SoWinFullViewer * viewer)
{
  assert(IsWindow(this->mainWidget));

  if (this->seekViewer)// already created, destroy first
    return;
  
  this->seekViewer = viewer;
  
  this->seekWidgets[0] = this->createLabelWidget(this->mainWidget, "Seek animation time:", this->x, this->y);
  this->seekWidgets[1] = this->createEditWidget(this->mainWidget, SEEK_TIME_EDIT, 64, this->x + 175, this->y);
  this->seekWidgets[2] = this->createLabelWidget(this->mainWidget, "seconds", this->x + 245, this->y);
  this->y += this->lineHeight;
  
  this->seekWidgets[3] = this->createLabelWidget(this->mainWidget, "Seek to:", this->x, this->y);
  this->seekWidgets[4] = this->createRadioWidget(this->mainWidget, SEEK_TO_PT_RADIO, "point",
                                                  this->x + 90, this->y);
  this->seekWidgets[5] = this->createRadioWidget(this->mainWidget, SEEK_TO_OBJ_RADIO, "object",
                                                  this->x + 190, this->y);
  this->y += this->lineHeight;

  this->seekWidgets[6] = this->createLabelWidget(this->mainWidget, "Seek distance:", this->x, this->y);
  this->seekDistWheel = new SoWinThumbWheel(SoWinThumbWheel::Horizontal, this->mainWidget, SEEK_DIST_WHEEL,
                                             this->x + 140, this->y);
  this->seekWidgets[7] = this->createEditWidget(this->mainWidget, SEEK_DIST_EDIT, 64, this->x + 270, this->y);
  this->y += this->lineHeight;

  this->seekWidgets[8] = this->createRadioWidget(this->mainWidget, SEEK_DIST_PCT_RADIO, "percentage",
                                                  this->x, this->y);
  this->seekWidgets[9] = this->createRadioWidget(this->mainWidget, SEEK_DIST_ABS_RADIO, "absolute",
                                                  this->x + 100, this->y);
  this->y += this->lineHeight;

  this->initSeekWidgets(viewer);
}

void SoWinViewerPrefSheet::createZoomWidgets(SoWinFullViewer * viewer)
{
  assert(IsWindow(this->mainWidget));
  
  if (this->zoomViewer)// already created, destroy first
    return;

  this->zoomViewer = viewer;

  this->zoomWidgets[0] = this->createLabelWidget(this->mainWidget, "Camera zoom:", this->x, this->y);
  this->zoomWidgets[1] = this->createSliderWidget(this->mainWidget, ZOOM_SLIDER, 118, this->x + 140, this->y);
  this->zoomWidgets[2] = this->createEditWidget(this->mainWidget, ZOOM_EDIT, 64, this->x + 270, this->y);
  this->y += this->lineHeight;

  this->zoomWidgets[3] = this->createLabelWidget(this->mainWidget, "Zoom slider ranges from:", this->x, this->y);
  this->zoomWidgets[4] = this->createEditWidget(this->mainWidget, ZOOM_RANGE_FROM_EDIT, 64, this->x + 175, this->y);
  this->zoomWidgets[5] = this->createLabelWidget(this->mainWidget, "to:", this->x + 245, this->y);
  this->zoomWidgets[6] = this->createEditWidget(this->mainWidget, ZOOM_RANGE_TO_EDIT, 64, this->x + 270, this->y);
  this->y += this->lineHeight;

  this->initZoomWidgets(viewer);
}

void SoWinViewerPrefSheet::createClippingWidgets(SoWinFullViewer * viewer)
{
  assert(IsWindow(this->mainWidget));
  
  if (this->clippingViewer)// already created, destroy first
    return;

  this->clippingViewer = viewer;

  this->clippingWidgets[0] = this->createCheckWidget(this->mainWidget, CLIPPING_AUTO_CHECK, "Auto clipping planes",
                                                      this->x, this->y);
  this->y += this->lineHeight;

  this->clippingWidgets[1] = this->createLabelWidget(this->mainWidget, "Near plane:", this->x, this->y);
  this->nearPlaneWheel = new SoWinThumbWheel(SoWinThumbWheel::Horizontal, this->mainWidget, CLIPPING_NEAR_WHEEL,
                                              this->x + 140, this->y);
  this->clippingWidgets[2] = this->createEditWidget(this->mainWidget, CLIPPING_NEAR_EDIT, 64, this->x + 270, this->y);
  this->y += this->lineHeight;
  
  this->clippingWidgets[3] = this->createLabelWidget(this->mainWidget, "Far plane:", this->x, this->y);
  this->farPlaneWheel = new SoWinThumbWheel(SoWinThumbWheel::Horizontal, this->mainWidget, CLIPPING_FAR_WHEEL,
                                             this->x + 140, this->y);
  this->clippingWidgets[4] = this->createEditWidget(this->mainWidget, CLIPPING_FAR_EDIT, 64,
                                                     this->x + 270, this->y);
  this->y += this->lineHeight;

  this->initClippingWidgets(viewer);
}

void SoWinViewerPrefSheet::createSpinWidgets(SoWinExaminerViewer * viewer)
{
  assert(IsWindow(this->mainWidget));
  
  if (this->spinViewer)// already created, destroy first
    return;

  this->spinViewer = viewer;

  this->spinWidgets[0] = this->createCheckWidget(this->mainWidget, SPIN_ENABLE_CHECK, "Enable spin animation",
                                                  this->x, this->y);
  this->y += this->lineHeight;

  this->spinWidgets[1] = this->createCheckWidget(this->mainWidget, SPIN_AXES_CHECK, "Show point of rotation axes",
                                                  this->x, this->y);
  this->y += this->lineHeight;
  
  this->spinWidgets[2] = this->createLabelWidget(this->mainWidget, "Axes size:", this->x, this->y);
  this->axesSizeWheel = new SoWinThumbWheel(SoWinThumbWheel::Horizontal, this->mainWidget, SPIN_AXES_WHEEL,
                                             this->x + 140, this->y);
  this->spinWidgets[3] = this->createEditWidget(this->mainWidget, SPIN_AXES_EDIT, 64, this->x + 270, this->y);
  this->y += this->lineHeight;

  this->initSpinWidgets(viewer);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//  (protected)
//

void SoWinViewerPrefSheet::constructor(void)
{
  this->lineHeight = 0;
  this->className = "SoWinViewerPrefSheet";
  this->mainWidget = NULL;
  this->title = NULL;

  this->seekViewer = NULL;
  this->zoomViewer = NULL;
  this->clippingViewer = NULL;
  this->spinViewer = NULL;  
}

void SoWinViewerPrefSheet::createMainWidget(HWND parent)
{
  
  LPSTR wndclassname = (LPSTR) this->className.getString();
  HMENU menu = NULL;

  if (! SoWinViewerPrefSheet::wndClassAtom) {

    WNDCLASS windowclass;
    LPCTSTR icon = MAKEINTRESOURCE(IDI_APPLICATION);
    LPCTSTR cursor = MAKEINTRESOURCE(IDC_ARROW);
    HBRUSH brush = (HBRUSH) GetSysColorBrush(COLOR_BTNFACE);

    windowclass.lpszClassName = wndclassname;
    windowclass.hInstance = SoWin::getInstance();
    windowclass.lpfnWndProc = SoWinViewerPrefSheet::processEvent;
    windowclass.style = CS_OWNDC;
    windowclass.lpszMenuName = NULL;
    windowclass.hIcon = LoadIcon(NULL, icon);
    windowclass.hCursor = LoadCursor(SoWin::getInstance(), cursor);
    windowclass.hbrBackground = brush;
    windowclass.cbClsExtra = 0;
    windowclass.cbWndExtra = 4;

    SoWinViewerPrefSheet::wndClassAtom = Win32::RegisterClass(& windowclass);
    
  }

  SoWinViewerPrefSheet::wndCounter++;
  
  DWORD style = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE;

  this->mainWidget = CreateWindowEx(NULL,
                                     wndclassname,
                                     this->title.getString(),
                                     style,
                                     CW_USEDEFAULT,
                                     CW_USEDEFAULT,
                                     370,
                                     400,
                                     parent,
                                     menu,
                                     SoWin::getInstance(),
                                     this);
  
  assert(IsWindow(this->mainWidget));
  (void)SetActiveWindow(this->mainWidget);
}

void SoWinViewerPrefSheet::initSeekWidgets(SoWinFullViewer * viewer)
{
  this->setEditValue(this->seekWidgets[1], viewer->getSeekTime());

  this->setChecked(this->seekWidgets[4], viewer->isDetailSeek());
  this->setChecked(this->seekWidgets[5], ! viewer->isDetailSeek());

  float distance =  viewer->getSeekDistance();
  this->setEditValue(this->seekWidgets[7], distance);
    
  this->seekDistWheel->setRangeBoundaryHandling(SoWinThumbWheel::ACCUMULATE);
  this->seekDistWheel->setValue(distance);

  this->setChecked(this->seekWidgets[8], viewer->isSeekValuePercentage());
  this->setChecked(this->seekWidgets[9], ! viewer->isSeekValuePercentage());
}

void SoWinViewerPrefSheet::initZoomWidgets(SoWinFullViewer * viewer)
{
  float zoom = viewer->getCameraZoom();

  this->setSliderRange(this->zoomWidgets[1],
    (int) viewer->zoomrange[0],
    (int) viewer->zoomrange[1]);

  this->setSliderValue(this->zoomWidgets[1], (int) zoom);
  this->setEditValue(this->zoomWidgets[2], zoom);
  
  this->setEditValue(this->zoomWidgets[4], viewer->zoomrange[0]);
  this->setEditValue(this->zoomWidgets[6], viewer->zoomrange[1]);  
}

void SoWinViewerPrefSheet::initClippingWidgets(SoWinFullViewer * viewer)
{
  BOOL autoCl =  viewer->isAutoClipping();
  this->setChecked(this->clippingWidgets[0], autoCl);
  
  SoCamera * cam = viewer->getCamera();
  if(! cam) return;
  
  float nearDist = cam->nearDistance.getValue();
  float farDist = cam->farDistance.getValue();

  this->nearPlaneWheel->setRangeBoundaryHandling(SoWinThumbWheel::ACCUMULATE);
  this->nearPlaneWheel->setValue(nearDist);
  
  this->setEditValue(this->clippingWidgets[2], nearDist);

  this->farPlaneWheel->setRangeBoundaryHandling(SoWinThumbWheel::ACCUMULATE);  
  this->farPlaneWheel->setValue(farDist);
  
  this->setEditValue(this->clippingWidgets[4], farDist);      
  
  //enableClippingWidgets(autoCl); // NB! checkbox is always enabled
  if (autoCl) {
    this->nearPlaneWheel->setEnabled(FALSE);
    this->farPlaneWheel->setEnabled(FALSE);
    for (int i = 1; i < 5; i++)
      this->setEnabled(this->clippingWidgets[i], FALSE);
  }
}

void SoWinViewerPrefSheet::initSpinWidgets(SoWinExaminerViewer * viewer)
{
  BOOL anim = viewer->isAnimationEnabled();
  this->setChecked(this->spinWidgets[0], anim);

  BOOL visible = viewer->isFeedbackVisible();
  this->setChecked(this->spinWidgets[1], visible);

  float size = viewer->getFeedbackSize();
  this->axesSizeWheel->setRangeBoundaryHandling(SoWinThumbWheel::ACCUMULATE);
  this->axesSizeWheel->setValue(AXES_SIZE_TO_WHEEL(size));
  this->setEditValue(this->spinWidgets[3], size);
  
  //enableSpinWidgets(anim); // NB! checkbox is always enabled
  if (! anim)
    setEnabled(this->spinWidgets[1], FALSE);
  
  if (! (visible && anim)) {
    setEnabled(this->spinWidgets[2], FALSE);
    setEnabled(this->spinWidgets[3], FALSE);
    this->axesSizeWheel->setEnabled(FALSE);
  }
}

void SoWinViewerPrefSheet::destroyMainWidget(void)
{
  Win32::DestroyWindow(this->mainWidget);
  SoWinViewerPrefSheet::wndCounter--;
  
  if (SoWinViewerPrefSheet::wndCounter <= 0 && SoWinViewerPrefSheet::wndClassAtom) {
    Win32::UnregisterClass(this->className.getString(), SoWin::getInstance());
    SoWinViewerPrefSheet::wndClassAtom = NULL;
  }
  
  this->mainWidget = NULL;
}

void SoWinViewerPrefSheet::destroySeekWidgets(void)
{
  for (int i = 0; i < 10; i++) {
    if (IsWindow(this->seekWidgets[i])) {
      Win32::DestroyWindow(this->seekWidgets[i]);
    }
  }
  if (this->seekDistWheel)
    delete this->seekDistWheel;
  this->seekViewer = NULL;
}

void SoWinViewerPrefSheet::destroyZoomWidgets(void)
{
  for (int i = 0; i < 7; i++) {
    if (IsWindow(this->zoomWidgets[i])) {
      Win32::DestroyWindow(this->zoomWidgets[i]);
    }
  }
  this->zoomViewer = NULL;
}

void SoWinViewerPrefSheet::destroyClippingWidgets(void)
{
  for (int i = 0; i < 5; i++) {
    if (IsWindow(this->clippingWidgets[i])) {
      Win32::DestroyWindow(this->clippingWidgets[i]);
    }
  }
  if (this->nearPlaneWheel)
    delete nearPlaneWheel;
  if (this->farPlaneWheel)
    delete farPlaneWheel;
  this->clippingViewer = NULL;
}

void SoWinViewerPrefSheet::destroySpinWidgets(void)
{
  for (int i = 0; i < 4; i++) {
    if (IsWindow(this->spinWidgets[i])) {
      Win32::DestroyWindow(this->spinWidgets[i]);
    }
  }

  if (this->axesSizeWheel)
    delete this->axesSizeWheel;
  this->spinViewer = NULL;
}

HWND SoWinViewerPrefSheet::createLabelWidget(HWND parent, const char * text, int x, int y)
{
  assert(IsWindow(parent));
  SIZE textSize = this->getTextSize(parent, text); // FIXME: assumes the same font as parent
  HWND hwnd = CreateWindowEx(NULL,
                              "STATIC",
                              (text ? text : ""),
                              WS_VISIBLE | WS_CHILD | SS_LEFT,
                              x, y,
                              textSize.cx, textSize.cy,
                              parent,
                              NULL,
                              SoWin::getInstance(),
                              NULL);
  assert(IsWindow(hwnd));
  return hwnd;  
}

HWND SoWinViewerPrefSheet::createEditWidget(HWND parent, long id, int width, int x, int y)
{
  assert(IsWindow(parent));
  HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                              "EDIT",
                              "",
                              WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
                              x, y,
                              width, this->getFontHeight(parent) + 4,
                              parent,
                              NULL,
                              SoWin::getInstance(),
                            NULL);
  assert(IsWindow(hwnd));

  (void)Win32::SetWindowLong(hwnd, GWL_ID, id); 

  return hwnd;
}

HWND SoWinViewerPrefSheet::createRadioWidget(HWND parent, long id, const char * text, int x, int y)
{
  assert(IsWindow(parent));
  SIZE textSize = this->getTextSize(parent, text); // FIXME: assumes the same font as parent  
  HWND hwnd = CreateWindowEx(NULL,
                              "BUTTON",
                              (text ? text : ""),
                              WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON | BS_LEFT,
                              x, y,
                              30 + textSize.cx, textSize.cy,
                              parent,
                              NULL,
                              SoWin::getInstance(),
                              NULL);
  assert(IsWindow(hwnd));

  (void)Win32::SetWindowLong(hwnd, GWL_ID, id);
  return hwnd;
}

HWND SoWinViewerPrefSheet::createSliderWidget(HWND parent, long id, int width, int x, int y)
{
  assert(IsWindow(parent));
  HWND hwnd = CreateWindowEx(NULL,
                              "SCROLLBAR",
                              "",
                              WS_CHILD | WS_VISIBLE | SBS_HORZ,
                              x, y,
                              width, this->getFontHeight(parent) + 2,
                              parent,
                              NULL,
                              SoWin::getInstance(),
                              NULL);
  assert(IsWindow(hwnd));

  (void)Win32::SetWindowLong(hwnd, GWL_ID, id);
  return hwnd;  
}

HWND SoWinViewerPrefSheet::createCheckWidget(HWND parent, long id, const char * text, int x, int y)
{
  assert(IsWindow(parent));
  SIZE textSize = this->getTextSize(parent, text); // FIXME: assumes the same font as parent  
  HWND hwnd = CreateWindowEx(NULL,
                              "BUTTON",
                              (text ? text : ""),
                              WS_VISIBLE | WS_CHILD | BS_CHECKBOX | BS_LEFT,
                              x, y,
                              30 + textSize.cx, textSize.cy,
                              parent,
                              NULL,
                              SoWin::getInstance(),
                              NULL);
  assert(IsWindow(hwnd));

  (void)Win32::SetWindowLong(hwnd, GWL_ID, id);
  return hwnd;  
}

SIZE SoWinViewerPrefSheet::getTextSize(HWND window, const char * text)
{
  assert(IsWindow(window));
  
  int len = strlen(text);
  HDC hdc = GetDC(window);

  SIZE size;
  Win32::GetTextExtentPoint(hdc, text, len, & size);
  return size;
}

int SoWinViewerPrefSheet::getFontHeight(HWND window)
{
  return this->getTextSize(window, "Ig").cy;
}

// Slider funcs

void SoWinViewerPrefSheet::setSliderValue(HWND slider, int value)
{
  SCROLLINFO scrollInfo;
  ZeroMemory(& scrollInfo, sizeof(SCROLLINFO));
  scrollInfo.cbSize = sizeof(SCROLLINFO);
  scrollInfo.fMask = SIF_POS;
  scrollInfo.nPos = value;
 
  SetScrollInfo(slider,
                 SB_CTL,
                 /*(this->orient == Horizontal) SB_HORZ : SB_VERT)*/
                 //SB_HORZ,
                 & scrollInfo,
                 TRUE); // FIXME: redraw needed?
}

int SoWinViewerPrefSheet::getSliderValue(HWND slider)
{
  SCROLLINFO scrollInfo;
  ZeroMemory(& scrollInfo, sizeof(SCROLLINFO));
  scrollInfo.cbSize = sizeof(SCROLLINFO);
  scrollInfo.fMask = SIF_POS;

  GetScrollInfo(slider,
                 SB_CTL,
                 /*(this->orient == Horizontal) SB_HORZ : SB_VERT)*/
                 //SB_HORZ,
                 & scrollInfo);

  return (scrollInfo.nPos);
}

void SoWinViewerPrefSheet::setSliderRange(HWND slider, int min, int max)
{
  SCROLLINFO scrollInfo;
  ZeroMemory(& scrollInfo, sizeof(SCROLLINFO));
  scrollInfo.cbSize = sizeof(SCROLLINFO);
  scrollInfo.fMask = SIF_RANGE | SIF_PAGE;
  scrollInfo.nMin = min;
  scrollInfo.nMax = max;
  scrollInfo.nPage = 1;//((max - min + 1) + min);
 
  SetScrollInfo(slider, SB_CTL, & scrollInfo, TRUE);
}

SIZE SoWinViewerPrefSheet::getSliderRange(HWND slider)
{
  SCROLLINFO scrollInfo;
  ZeroMemory(& scrollInfo, sizeof(SCROLLINFO));
  scrollInfo.cbSize = sizeof(SCROLLINFO);
  scrollInfo.fMask = SIF_RANGE;

  GetScrollInfo(slider,
                 SB_CTL,
                 /*(this->orient == Horizontal) SB_HORZ : SB_VERT),*/
                 //SB_HORZ,
                 & scrollInfo);
  
  SIZE range = { scrollInfo.nMin, scrollInfo.nMax }; 
  return range;
}

void SoWinViewerPrefSheet::setChecked(HWND hwnd, BOOL check)
{  
  (void)SendMessage(hwnd, BM_SETCHECK, (WPARAM) (check ? BST_CHECKED : BST_UNCHECKED), 0);
}

void SoWinViewerPrefSheet::setEnabled(HWND hwnd, BOOL enable)
{
  Win32::EnableWindow(hwnd, enable);
}

void SoWinViewerPrefSheet::setEditValue(HWND edit, float value)
{
  const int BUFSIZE = 32;
  char str[BUFSIZE];
  int l = sprintf(str, "%.3f", value);
  assert((l < BUFSIZE-1) && "buffer too small");

  Win32::SetWindowText(edit, str);
}

float SoWinViewerPrefSheet::getEditValue(HWND edit)
{
  const int BUFSIZE = 32;
  char str[BUFSIZE];
  SetLastError(0);
  int l = GetWindowText(edit, str, BUFSIZE);
  assert(! (l==0 && GetLastError()!= 0) && "GetWindowText() failed -- investigate");
  assert((l < BUFSIZE-1) && "buffer too small");
  return (float) atof(str);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//  (Event handlers)
//

LRESULT CALLBACK
SoWinViewerPrefSheet::processEvent(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  if (message == WM_CREATE) {
    CREATESTRUCT * createstruct;
    createstruct = (CREATESTRUCT *) lparam;

    (void)Win32::SetWindowLong(window, 0, (LONG) (createstruct->lpCreateParams));
    
    SoWinViewerPrefSheet * object = (SoWinViewerPrefSheet *)(createstruct->lpCreateParams);
    return object->onCreate(window, message, wparam, lparam);
  }

  SoWinViewerPrefSheet * object = (SoWinViewerPrefSheet *) Win32::GetWindowLong(window, 0);

  if (object && IsWindow(object->mainWidget)) {

    switch (message)
      {
      case WM_DESTROY:
        return object->onDestroy(window, message, wparam, lparam);
      case WM_COMMAND:
        return object->onCommand(window, message, wparam, lparam);
      case WM_HSCROLL:
        return object->onScroll(window, message, wparam, lparam);  
      case WM_THUMBWHEEL:
        return object->onThumbWheel(window, message, wparam, lparam);  
      }
  }
  return DefWindowProc(window, message, wparam, lparam);
}

LRESULT SoWinViewerPrefSheet::onCreate(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  HWND r = SetActiveWindow(window);
  assert((r != NULL) && "SetActiveWindow() failed -- investigate");
  SetFocus(window);
  ReleaseCapture();
  return 0;
}

LRESULT SoWinViewerPrefSheet::onDestroy(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  this->destroy();
  return 0;
}

LRESULT SoWinViewerPrefSheet::onCommand(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  WORD nc = HIWORD(wparam);
  WORD id = LOWORD(wparam);
  HWND ctrl = (HWND) lparam;

  switch (id) {
    
    case SEEK_TIME_EDIT:
      if (nc == EN_CHANGE) {
        this->seekViewer->setSeekTime(this->getEditValue(ctrl));
      }
      break;
      
    case SEEK_TO_PT_RADIO:
      if (! this->seekViewer->isDetailSeek()) {
        this->seekViewer->setDetailSeek(TRUE);
        this->setChecked(this->seekWidgets[4], TRUE);
        this->setChecked(this->seekWidgets[5], FALSE);
      }
      break;
      
    case SEEK_TO_OBJ_RADIO:
      if (this->seekViewer->isDetailSeek()) {
        this->seekViewer->setDetailSeek(FALSE);
        this->setChecked(this->seekWidgets[4], FALSE);
        this->setChecked(this->seekWidgets[5], TRUE);
      }      
      break;
      
    case SEEK_DIST_EDIT:
      if (nc == EN_CHANGE) {
        float value =  this->getEditValue(ctrl);
        if (value <= .0) value = .0001; // .0 not allowed
        this->seekViewer->setSeekDistance(value);
        this->seekDistWheel->setValue(value);
      }
      break;
      
    case SEEK_DIST_PCT_RADIO:
      if (! this->seekViewer->isSeekValuePercentage()) {
        this->seekViewer->setSeekValueAsPercentage(TRUE);
        this->setChecked(this->seekWidgets[8], TRUE);
        this->setChecked(this->seekWidgets[9], FALSE);
      }
      break;
      
    case SEEK_DIST_ABS_RADIO:
      if (this->seekViewer->isSeekValuePercentage()) {
        this->seekViewer->setSeekValueAsPercentage(FALSE);
        this->setChecked(this->seekWidgets[8], FALSE);
        this->setChecked(this->seekWidgets[9], TRUE);
      }
      break;
      
    case ZOOM_EDIT:
      if (nc == EN_CHANGE) {
        float value =  this->getEditValue(ctrl);
        if (value < zoomViewer->zoomrange[0]) {
          value = zoomViewer->zoomrange[0];
          this->setEditValue(ctrl, value);
        }
        if (value > zoomViewer->zoomrange[1]) {
          value = zoomViewer->zoomrange[1];
          this->setEditValue(ctrl, value);
        }
        this->zoomViewer->setCameraZoom(value);
        this->setSliderValue(this->zoomWidgets[1], (int) value);
      }
      break;
      
    case ZOOM_RANGE_FROM_EDIT:
      if (nc == EN_CHANGE) {
        float value =  this->getEditValue(ctrl);
        if (value < 0.0) {
          this->setEditValue(ctrl, 0.0);
          break;
        }
        this->zoomViewer->zoomrange[0] = value;
        if (zoomViewer->getCameraZoom() < value)
          this->setEditValue(this->zoomWidgets[2], value); // will cause new message        
        this->setSliderRange(this->zoomWidgets[1],
                              (int) zoomViewer->zoomrange[0],
                              (int) zoomViewer->zoomrange[1]);
      }
      break;
      
    case ZOOM_RANGE_TO_EDIT:
      if (nc == EN_CHANGE) {
        float value =  this->getEditValue(ctrl);
        if (value >= 180.0) {
          this->setEditValue(ctrl, 179.999);
          break;
        }
        this->zoomViewer->zoomrange[1] = value;
        if (zoomViewer->getCameraZoom() > value)
          this->setEditValue(this->zoomWidgets[2], value); // will cause new message
        this->setSliderRange(this->zoomWidgets[1],
                              (int) zoomViewer->zoomrange[0],
                              (int) zoomViewer->zoomrange[1]);
      }
      break;
      
    case CLIPPING_AUTO_CHECK:
      {
        BOOL autoCl = this->clippingViewer->isAutoClipping();
        this->clippingViewer->setAutoClipping(! autoCl);
        this->setChecked(this->clippingWidgets[0], ! autoCl);
        this->nearPlaneWheel->setEnabled(autoCl);
        this->farPlaneWheel->setEnabled(autoCl);
        
        this->setEditValue(this->clippingWidgets[2],
                            clippingViewer->getCamera()->nearDistance.getValue());
        this->setEditValue(this->clippingWidgets[4],
                            clippingViewer->getCamera()->farDistance.getValue());
                
        for (int i = 1; i < 5; i++)
          this->setEnabled(this->clippingWidgets[i], autoCl);
        
      }
      break;
      
    case CLIPPING_NEAR_EDIT:
      if (nc == EN_CHANGE) {
        float value =  this->getEditValue(ctrl);
        float farDist = this->clippingViewer->getCamera()->farDistance.getValue();
        if (value >= farDist) {
          value = farDist - .0001; // FIXME: sprintf is rounding up value (se setEditValue)
          this->setEditValue(ctrl, value);
        }
        this->clippingViewer->getCamera()->nearDistance.setValue(value);
        this->nearPlaneWheel->setValue(value);
      }
      break;
      
    case CLIPPING_FAR_EDIT:
      if (nc == EN_CHANGE) {
        float value =  this->getEditValue(ctrl);
        float nearDist = this->clippingViewer->getCamera()->nearDistance.getValue();
        if (value <= nearDist) {
          value = nearDist + .0001; // FIXME: sprintf is rounding up value (se setEditValue)
          this->setEditValue(ctrl, value);
        }
        this->clippingViewer->getCamera()->farDistance.setValue(value);
        this->farPlaneWheel->setValue(value);
      }
      break;
      
    case SPIN_ENABLE_CHECK:
      {
        BOOL anim = this->spinViewer->isAnimationEnabled();
        BOOL visible = this->spinViewer->isFeedbackVisible();
        
        this->spinViewer->setAnimationEnabled(! anim);
        this->setChecked(this->spinWidgets[0], ! anim);
        
      }
      break;
      
    case SPIN_AXES_CHECK:
      {
        BOOL visible = this->spinViewer->isFeedbackVisible();
        this->spinViewer->setFeedbackVisibility(! visible);
        this->setChecked(this->spinWidgets[1], ! visible);

        setEnabled(this->spinWidgets[2], ! visible);
        setEnabled(this->spinWidgets[3], ! visible);
        this->axesSizeWheel->setEnabled(! visible);
      }
      break;
      
    case SPIN_AXES_EDIT:
      if (nc == EN_CHANGE) {
        float value =  this->getEditValue(ctrl);
        if (value <= 1.) {
          value = 1.;
          this->setEditValue(ctrl, value);
        }
        this->spinViewer->setFeedbackSize(value);
        this->axesSizeWheel->setValue(AXES_SIZE_TO_WHEEL(value));
      }
      break;
      
  }
  
  return 0;
}

LRESULT SoWinViewerPrefSheet::onScroll(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  int scrollCode = (int) LOWORD(wparam);
  short pos = (short) HIWORD(wparam); 
  HWND scrollBar = (HWND) lparam;

  switch (scrollCode) {
    case SB_PAGELEFT:
    case SB_LINELEFT:
      pos = (short) this->getSliderValue(scrollBar);
      this->setEditValue(this->zoomWidgets[2], (float) pos - 1);
      return 0;

    case SB_PAGERIGHT:
    case SB_LINERIGHT:
      pos = (short) this->getSliderValue(scrollBar);
      this->setEditValue(this->zoomWidgets[2], (float) pos + 1);
      return 0;

    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      this->setEditValue(this->zoomWidgets[2], (float) pos);
      return 0;
  }
  
  return 0;
}

LRESULT SoWinViewerPrefSheet::onThumbWheel(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  
  switch(wparam) {

    case SEEK_DIST_WHEEL:
      this->setEditValue(this->seekWidgets[7], * (float *) lparam);
      break;
      
    case CLIPPING_NEAR_WHEEL:
      this->setEditValue(this->clippingWidgets[2], * (float *) lparam);
      break;

    case CLIPPING_FAR_WHEEL:
      this->setEditValue(this->clippingWidgets[4], * (float *) lparam);
      break;

    case SPIN_AXES_WHEEL:
      this->setEditValue(this->spinWidgets[3], AXES_SIZE_FROM_WHEEL(* (float *) lparam));
      break;
      
  }
  
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//  (private)
//
