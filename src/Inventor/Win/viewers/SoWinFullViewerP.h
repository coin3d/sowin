/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef SOWINFULLVIEWERP_H
#define SOWINFULLVIEWERP_H

#include <SoGuiFullViewerP.h>
#include <Inventor/Win/SoWinCursor.h>

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
    VIEWERBUTTON_HELP,
    VIEWERBUTTON_HOME,
    VIEWERBUTTON_SET_HOME,
    VIEWERBUTTON_VIEW_ALL,
    VIEWERBUTTON_SEEK
  };

  class SoWinBitmapButton * viewerButton(int idx);
  HWND appButton(int idx);

  static void setThumbWheelValue(void * wheel, float val);

  static void rightWheelCB(SoWinFullViewer * viewer, void ** data);
  static void bottomWheelCB(SoWinFullViewer * viewer, void ** data);
  static void leftWheelCB(SoWinFullViewer * viewer, void ** data);

  void interactbuttonClicked(void);
  void viewbuttonClicked(void);
  void helpbuttonClicked(void);
  void homebuttonClicked(void);
  void sethomebuttonClicked(void);
  void viewallbuttonClicked(void);

  virtual void selectedPrefs(void);
  void seekbuttonClicked(void);

  void showDecorationWidgets(SbBool onOff);

  HWND buildLeftWheel(HWND parent);
  HWND buildBottomWheel(HWND parent);
  HWND buildRightWheel(HWND parent);
  
  int layoutWidgets(int cx, int cy);
  static LRESULT CALLBACK systemEventHook(int code, WPARAM wparam, LPARAM lparam);

  static HHOOK hookhandle;
  static int nrinstances;
  
  // App button callbacks
  AppPushButtonCB * appPushButtonCB;
  void * appPushButtonData;
  RedrawAppPushButtonCB * redrawAppPushButtonCB;
  void * redrawAppPushButtonData;
  CreateAppPushButtonCB * createAppPushButtonCB;
  void * createAppPushButtonData;

  static SbDict * parentHWNDmappings;

  SbBool menuenabled;
  SbBool decorations;

  static SbBool doneButtonBar;
  static SbBool doButtonBar;

  SoWinCursor cursor;
};

// ************************************************************************

#endif // ! SOWINFULLVIEWERP_H