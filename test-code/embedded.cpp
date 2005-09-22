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

// Basic test example for embedding a SoWin-component (the
// examinerviewer, to be exact) into a native Win32 window.
//
// Build with: ``sowin-config --build embedded embedded.cpp''
//
// <mortene@sim.no>

#include <assert.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoSeparator.h>

LRESULT CALLBACK
mainwinproc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  if ( message == WM_DESTROY ) {
    PostQuitMessage( 0 );
    return 0;
  }
  
  if ( message == WM_SIZE ) {
    printf("size\n");
  }

  return DefWindowProc(window, message, wparam, lparam);
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        LPSTR lpCmdLine, int nShowCmd)
{
  WNDCLASS windowclass;
  windowclass.lpszClassName = "MainWindow";
  windowclass.hInstance = hInstance;
  windowclass.lpfnWndProc = mainwinproc;
  windowclass.style = CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
  windowclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
  windowclass.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass(&windowclass);

  HWND rootwin =
    CreateWindow("MainWindow", // class name
                 "Embedding SoWin component", // window name
                 WS_OVERLAPPEDWINDOW | WS_VISIBLE, // window style
                 CW_USEDEFAULT, // xpos
                 0, // ypos (ignored because of WS_VISIBLE + CWD_USEDEFAULT)
                 600, // width
                 600, // height
                 NULL, // parent
                 NULL, // menu or child-window
                 hInstance, // application instance
                 NULL);

  assert(IsWindow(rootwin) && "window creation failed");

  SoWin::init(rootwin);

  SoSeparator * s = new SoSeparator; // Scene root
  s->addChild(new SoCone);

  SoWinExaminerViewer * eviewer = new SoWinExaminerViewer(rootwin);
  eviewer->setSceneGraph(s);
  eviewer->show();

  SoWin::mainLoop();

  return 0;
}
