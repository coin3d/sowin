#ifndef SOWINFULLVIEWERP_H
#define SOWINFULLVIEWERP_H

/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and / or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use this library in software that is incompatible
 *  with the GNU GPL, and / or you would like to take advantage of the
 *  additional benefits with regard to our support services, please
 *  contact Systems in Motion about acquiring a Coin Professional
 *  Edition License.  See <URL:http://www.coin3d.org> for more
 *  information.
 *
 *  Systems in Motion, Abels gate 5, Teknobyen, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef SOWIN_INTERNAL
#error this is a private header file
#endif /* !SOWIN_INTERNAL */

#include <Inventor/Win/viewers/SoGuiFullViewerP.h>
#include <Inventor/Win/SoWinCursor.h>
#include <Inventor/Win/widgets/SoWinThumbWheel.h>

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

  void interactbuttonClicked(void);
  void viewbuttonClicked(void);
  void homebuttonClicked(void);
  void sethomebuttonClicked(void);
  void viewallbuttonClicked(void);

  void seekbuttonClicked(void);

  void showDecorationWidgets(SbBool onOff);

  HWND buildLeftWheel(HWND parent);
  HWND buildBottomWheel(HWND parent);
  HWND buildRightWheel(HWND parent);
  
  int layoutWidgets(int cx, int cy);
  static LRESULT CALLBACK systemEventHook(int code, WPARAM wparam, LPARAM lparam);

  static HHOOK hookhandle;
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
