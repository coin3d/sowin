#ifndef SOWINFULLVIEWERP_H
#define SOWINFULLVIEWERP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#ifndef SOWIN_INTERNAL
#error this is a private header file
#endif /* !SOWIN_INTERNAL */

#include <Inventor/Win/viewers/SoGuiFullViewerP.h>
#include <Inventor/Win/SoWinCursor.h>
#include <Inventor/Win/widgets/SoWinThumbWheel.h>

class SbStorage;

// ************************************************************************

// This class contains private data and methods used within the
// SoWinFullViewer class.

class SoWinFullViewerP : public SoGuiFullViewerP
{
public:
  SoWinFullViewerP(SoWinFullViewer * publ);
  ~SoWinFullViewerP();

  enum ButtonId {
    VIEWERBUTTON_PICK,
    VIEWERBUTTON_VIEW,
    VIEWERBUTTON_HOME,
    VIEWERBUTTON_SET_HOME,
    VIEWERBUTTON_VIEW_ALL,
    VIEWERBUTTON_SEEK
  };

  class SoWinBitmapButton * viewerButton(int idx);
  HWND appButton(int idx);

  static void setThumbWheelValue(void * wheel, float val);

  static void leftWheelCB(SoWinThumbWheel::Interaction type, float val,
                          void * userdata);
  static void bottomWheelCB(SoWinThumbWheel::Interaction type, float val,
                            void * userdata);
  static void rightWheelCB(SoWinThumbWheel::Interaction type, float val,
                           void * userdata);

  static void interactbuttonProc(SoWinBitmapButton * b, void * userdata);
  static void examinebuttonProc(SoWinBitmapButton * b, void * userdata);
  static void homebuttonProc(SoWinBitmapButton * b, void * userdata);
  static void sethomebuttonProc(SoWinBitmapButton * b, void * userdata);
  static void viewallbuttonProc(SoWinBitmapButton * b, void * userdata);

  static void seekbuttonProc(SoWinBitmapButton * b, void * userdata);
  void seekbuttonClicked(void);

  void showDecorationWidgets(SbBool onOff);

  HWND buildLeftWheel(HWND parent);
  HWND buildBottomWheel(HWND parent);
  HWND buildRightWheel(HWND parent);
  
  int layoutWidgets(int cx, int cy);
  static LRESULT CALLBACK systemEventHook(int code, WPARAM wparam, LPARAM lparam);

  static SbStorage * hookhandle;
  static int nrinstances;
  
  static SbDict * parentHWNDmappings;

  SbBool menuenabled;
  SbBool decorations;

  SoWinCursor cursor;

  HWND viewerwidget;
  HWND renderareawidget;

  SbPList lefttrimbuttons, righttrimbuttons;

  SoWinThumbWheel * leftthumbwheel, * bottomthumbwheel, * rightthumbwheel;
};

// ************************************************************************

#endif // ! SOWINFULLVIEWERP_H
