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

// *************************************************************************

// Class documentation in common/SoGuiCommon.cpp.in.

/*!
  \mainpage

  %SoWin is a C++ GUI toolkit for using Coin with the Microsoft
  Windows Win32 API.  It can also be used on top of Open Inventor from
  SGI and TGS.  The API is based on the InventorXt API originally from
  SGI.

  FIXME: improve documentation, with usage examples etc. 20030411 mortene.

  The corresponding documentation for Coin is located 
  <a href="http://doc.coin3d.org/Coin/">here</a>.
*/

// *************************************************************************

#include <limits.h>
#include <Inventor/SbTime.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodekits/SoNodeKit.h>

#include <Inventor/Win/Win32API.h>
#include <sowindefs.h> // SOWIN_STUB
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoGuiP.h>
#include <Inventor/Win/devices/SoWinDevice.h>
#include <Inventor/Win/SoWinComponent.h>
#include <Inventor/Win/SoAny.h>

// The private data for the SoWin class.

class SoWinP {
  
public:

  static BOOL CALLBACK sizeChildProc(HWND window, LPARAM lparam);
  static void errorHandlerCB(const SoError * error, void * data);
  static LRESULT CALLBACK eventHandler(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  static SbBool pipeErrorMessagesToConsole(void);

  static int timerSensorId;
  static SbBool timerSensorActive;
  static void CALLBACK timerSensorCB(HWND window,
                                      UINT message,
                                      UINT idevent,
                                      DWORD dwtime);

  static int delaySensorId;
  static SbBool delaySensorActive;
  static void CALLBACK delaySensorCB(HWND window,
                                      UINT message,
                                      UINT idevent,
                                      DWORD dwtime);

  static int idleSensorId;
  static SbBool idleSensorActive;
  static void CALLBACK idleSensorCB(HWND window,
                                     UINT message,
                                     UINT idevent,
                                     DWORD dwtime);
  static void doIdleTasks(void);
  
  static LRESULT onDestroy(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  static LRESULT onQuit(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  
  static HINSTANCE Instance;
  static HWND mainWidget;
  static char * appName;
  static char * className;

  static SbBool useParentEventHandler;
  static WNDPROC parentEventHandler;

  static int DEBUG_LISTMODULES;

private:
  SoWin * owner;
  
};

// *************************************************************************

HINSTANCE SoWinP::Instance = NULL;
HWND SoWinP::mainWidget = NULL;
char * SoWinP::appName = NULL;
char * SoWinP::className = NULL;
int SoWinP::timerSensorId = 0;
SbBool SoWinP::timerSensorActive = FALSE;
int SoWinP::delaySensorId = 0;
SbBool SoWinP::delaySensorActive = FALSE;
int SoWinP::idleSensorId = 0;
SbBool SoWinP::idleSensorActive = FALSE;
WNDPROC SoWinP::parentEventHandler = NULL;
SbBool SoWinP::useParentEventHandler = TRUE;

#define ENVVAR_NOT_INITED INT_MAX

int SoWinP::DEBUG_LISTMODULES = ENVVAR_NOT_INITED;

// *************************************************************************

// init()-method documented in common/SoGuiCommon.cpp.in.
HWND
SoWin::init(int & argc, char ** argv,
            const char * appname, const char * classname)
{
  if (appname)
    SoWinP::appName = strcpy(new char [ strlen(appname) + 1 ], appname);
  if (classname)
    SoWinP::className = strcpy(new char [ strlen(classname) + 1 ], classname);

  {
    WNDCLASS windowclass;
    LPCTSTR icon = MAKEINTRESOURCE(IDI_APPLICATION);
    HBRUSH brush = (HBRUSH) GetSysColorBrush(COLOR_BTNFACE);
    windowclass.lpszClassName = classname;
    windowclass.hInstance = NULL;
    windowclass.lpfnWndProc = SoWinP::eventHandler;
    windowclass.style = CS_OWNDC;
    windowclass.lpszMenuName = NULL;
    windowclass.hIcon = LoadIcon(NULL, icon);
    windowclass.hCursor = Win32::LoadCursor(NULL, IDC_ARROW);
    windowclass.hbrBackground = brush;
    windowclass.cbClsExtra = 0;
    windowclass.cbWndExtra = 4;
    (void)Win32::RegisterClass(&windowclass);
  }
 
  SIZE size = { 500, 500 };
  HWND toplevel =
    Win32::CreateWindowEx_(NULL, // exstyle
                           classname,
                           appname,
                           WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, // style
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           size.cx,
                           size.cy,
                           NULL, // parent
                           NULL, // menu
                           NULL,
                           NULL);

  SoWinP::useParentEventHandler = FALSE;
  
  SoWin::init(toplevel);
  
  return toplevel;
}


// init()-method documented in common/SoGuiCommon.cpp.in.
void
SoWin::init(HWND toplevelwidget)
{
  SoDB::init();
  SoNodeKit::init();
  SoInteraction::init();
  SoWinObject::init();

  SoDebugError::setHandlerCallback(SoWinP::errorHandlerCB, NULL);

  // This should prove helpful for debugging the pervasive problem
  // under Win32 with loading multiple instances of the same library.
  if (SoWinP::DEBUG_LISTMODULES == ENVVAR_NOT_INITED) {
    const char * env = SoAny::si()->getenv("SOGUI_DEBUG_LISTMODULES");
    SoWinP::DEBUG_LISTMODULES = env ? atoi(env) : 0;
    if (SoWinP::DEBUG_LISTMODULES) { SoAny::listWin32ProcessModules(); }
  }

  SoDB::getSensorManager()->setChangedCallback(SoGuiP::sensorQueueChanged, NULL);
  if (IsWindow(toplevelwidget)) 
    SoWinP::mainWidget = toplevelwidget;

  if (SoWinP::useParentEventHandler) {
    // FIXME: this GetWindowLong() call fails with "invalid handle" if
    // we try to run this example program:
    //
    // --8<--- [snip] ------8<--- [snip] ------8<--- [snip] ----
    //
    //  #include <stdlib.h> // exit()
    //  #include <Inventor/Win/SoWin.h>
    //  #include <Inventor/Win/SoWinRenderArea.h>
    //  #include <Inventor/nodes/SoSeparator.h>
    //  #include <Inventor/nodes/SoPerspectiveCamera.h>
    //  #include <Inventor/nodes/SoDirectionalLight.h>
    //  #include <Inventor/nodes/SoMaterial.h>
    //  #include <Inventor/nodes/SoSphere.h>
    //
    //  // Dummy message handler for 2nd window
    //  LRESULT CALLBACK
    //  WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    //  {
    //    switch(message) {
    //    case WM_DESTROY:
    //      PostQuitMessage(0);
    //      break;
    //    default:
    //      return DefWindowProc(hwnd, message, wParam, lParam);
    //    }
    //    return 0;
    //  }
    //
    //
    //  int
    //  main(int argc, char ** argv)
    //  {
    //    WNDCLASSEX wcl;
    //    wcl.cbSize = sizeof(WNDCLASSEX);
    //    wcl.hInstance = NULL;
    //    wcl.lpszClassName = "My Window";
    //    wcl.lpfnWndProc = WindowFunc;
    //    wcl.style = 0;
    //    wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    //    wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
    //    wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
    //    wcl.lpszMenuName = NULL;
    //    wcl.cbClsExtra = 0;
    //    wcl.cbWndExtra = 0;
    //    wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    //    if (!RegisterClassEx(&wcl)) { exit(1); }
    //    HWND appwin = CreateWindow("AppWindow",
    //                               "AppWindow", // title
    //                               WS_OVERLAPPEDWINDOW,
    //                               CW_USEDEFAULT,
    //                               CW_USEDEFAULT,
    //                               CW_USEDEFAULT,
    //                               CW_USEDEFAULT,
    //                               HWND_DESKTOP,
    //                               NULL,
    //                               (HINSTANCE)NULL,
    //                               NULL);
    //
    //
    //    SoWin::init(appwin);
    //
    //    // Create a scene cointaining a sphere
    //    SoSeparator * root = new SoSeparator;
    //    root->ref(); // increment the root's reference counter
    //
    //    SoPerspectiveCamera * camera = new SoPerspectiveCamera;
    //    SoDirectionalLight * light = new SoDirectionalLight;
    //    SoMaterial * material = new SoMaterial;
    //    SoSphere * sphere = new SoSphere;
    //
    //    root->addChild(camera); // add camera node to the scene graph
    //    root->addChild(light); // add directional light to the scene
    //    root->addChild(material);// add material (with default settings)
    //    root->addChild(sphere); // add sphere node to the scene graph
    //
    //    // Create a renderingarea which will be used to display the
    //    // scene graph in the window.
    //    SoWinRenderArea * renderarea = new SoWinRenderArea(appwin);
    //
    //    // Make the camera able to see the whole scene
    //    camera->viewAll(root, renderarea->getViewportRegion());
    //
    //    // Display the scene in our renderarea and change the title
    //    renderarea->setSceneGraph(root);
    //    renderarea->setTitle("Sphere");
    //    renderarea->show();
    //
    //    SoWin::show(appwin); // display the main window
    //    SoWin::mainLoop(); // main Coin event loop
    //    delete renderarea; // free up the resources occupied by the renderarea
    //
    //    root->unref(); // decrement the root's reference counter
    //    return 0;
    //  }
    // 
    // --8<--- [snip] ------8<--- [snip] ------8<--- [snip] ----
    //
    // (BTW, after fixing this bug, store away the sourcecode example
    // above as an example on how to set up an SoWin renderarea within
    // a "stand-alone" application window.)
    //
    // 20020521 mortene.
    SoWinP::parentEventHandler = (WNDPROC) Win32::GetWindowLong(toplevelwidget, GWL_WNDPROC);
    (void)Win32::SetWindowLong(toplevelwidget, GWL_WNDPROC, (long) SoWinP::eventHandler);
  }
}

// documented in common/SoGuiCommon.cpp.in
void
SoWin::mainLoop(void)
{
  MSG msg;
  while (TRUE) {
    if (GetQueueStatus(QS_ALLINPUT) != 0) { // if messagequeue != empty
      if (GetMessage(& msg, NULL, 0, 0)) { // if msg != WM_QUIT
        TranslateMessage(& msg);
        DispatchMessage(& msg);
      }
      else break; // msg == WM_QUIT
    }
    else if (SoWinP::idleSensorActive) {
      SoWinP::doIdleTasks();
    }
    else {
      WaitMessage();
    }
  }

  SoWin::done();
}

// documented in common/SoGuiCommon.cpp.in
void
SoWin::exitMainLoop(void)
{
  PostQuitMessage(0);
}

// documented in common/SoGuiCommon.cpp.in
void
SoWin::done(void)
{
  // FIXME: should clean up all resources stlil dangling
  // about. 20020624 mortene.
}

/*!
  This method is provided for easier porting/compatibility with the
  Open Inventor SoXt component classes. It will call ShowWindow() with
  the argument SW_SHOW on the provided \a widget window handle.

  \sa hide()
*/
void
SoWin::show(HWND const widget)
{
  (void)ShowWindow(widget, SW_SHOW);
}

/*!
  This method is provided for easier porting/compatibility with the
  Open Inventor SoXt component classes. It will call ShowWindow() with
  the argument SW_HIDE on the provided \a widget window handle.

  \sa show()
*/
void
SoWin::hide(HWND const widget)
{
  (void)ShowWindow(widget, SW_HIDE);
}

/*!
  This method is provided for easier porting of applications based on
  the Open Inventor SoXt component classes. It will call
  SetWindowPos() on the provided \a widget window handle.

  \sa getWidgetSize()
*/
void
SoWin::setWidgetSize(HWND widget, const SbVec2s size)
{
  UINT flags = SWP_NOMOVE | SWP_NOZORDER;
  Win32::SetWindowPos(widget, NULL, 0, 0, size[0], size[1], flags);
}

/*!
  This method is provided for easier porting/compatibility with the
  Open Inventor SoXt component classes. It will call GetWindowExtEx()
  on the provided \a widget window handle's device context (returning
  an SbVec2s).

  \sa setWidgetSize()
*/
SbVec2s
SoWin::getWidgetSize(HWND widget)
{
  HDC hdc = GetDC(widget);

  SIZE size;
  if (! GetWindowExtEx(hdc, & size)) {
    size.cx = -1;
    size.cy = -1;
  }
  return SbVec2s((short) size.cx, (short) size.cy);
}

// Documented in common/SoGuiCommon.cpp.in.
HWND
SoWin::getTopLevelWidget(void)
{
  return SoWinP::mainWidget;
}

// Documented in common/SoGuiCommon.cpp.in.
//
// Just a simple wrap-around for the Win32 API MessageBox() call,
// provided for easier porting from applications using the Open
// Inventor SoXt component classes.
void
SoWin::createSimpleErrorDialog(HWND const widget,
                               const char * title,
                               const char * string1,
                               const char * string2)
{
  
  SbString t(title ? title : "");
  SbString errstr(string1 ? string1 : "");

  if (string2) {
    errstr += '\n';
    errstr += string2;
  }

  MessageBox(widget, errstr.getString(), t.getString(), MB_OK | MB_ICONERROR | MB_TASKMODAL);
}

/*!
  Returns a pointer to the HWND which is the top level widget for the
  given HWND \a hwnd.

  \sa getTopLevelWidget()
*/
HWND
SoWin::getShellWidget(HWND hwnd)
{
  LONG style;
  HWND parent = hwnd;
  
  do {
    hwnd = parent;
    style = Win32::GetWindowLong(hwnd, GWL_STYLE);
    // FIXME: this check seems bogus. 20020521 mortene.
    if (style & WS_OVERLAPPEDWINDOW) break;
    parent = GetParent(hwnd);
  } while(IsWindow(parent));
  
  return hwnd;
}

// Return value of SOWIN_MSGS_TO_CONSOLE environment variable.
SbBool
SoWinP::pipeErrorMessagesToConsole(void)
{
  static const char * conmsgs = SoAny::si()->getenv("SOWIN_MSGS_TO_CONSOLE");
  int val = conmsgs ? atoi(conmsgs) : 0;
  return val > 0;
}

void
SoWinP::errorHandlerCB(const SoError * error, void * data)
{
  // Normally, errors, warnings and info goes to a dialog box in
  // SoWin, but during development it might be better to pipe it to
  // the console.
  if (SoWinP::pipeErrorMessagesToConsole()) {
    (void)printf("%s\n", error->getDebugString().getString());
  }
  else {
    SbString debugstring = error->getDebugString();
    MessageBox(NULL, (LPCTSTR) debugstring.getString(), "SoError", MB_OK | MB_ICONERROR);
  }
}

LRESULT CALLBACK
SoWinP::eventHandler(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  LRESULT retval = 0;
  BOOL handled = FALSE;
  
  switch (message) {
  case WM_DESTROY:
    if (! SoWinP::useParentEventHandler) {
      retval = SoWinP::onDestroy(window, message, wparam, lparam);
      handled = TRUE;
    }
    break;
            
  case WM_QUIT:
    retval = SoWinP::onQuit(window, message, wparam, lparam);
    handled = TRUE;
    break;
  }

  if (SoWinP::useParentEventHandler && SoWinP::parentEventHandler)
    return SoWinP::parentEventHandler(window, message, wparam, lparam);

  if (handled)
    return retval;
    
  return DefWindowProc(window, message, wparam, lparam);
}

///////////////////////////////////////////////////////////////////
//
//  (private)
//

void CALLBACK
SoWinP::timerSensorCB(HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo("SoWin::timerSensorCB", "called");
#endif // SOWIN_DEBUG
  SoDB::getSensorManager()->processTimerQueue();
  SoGuiP::sensorQueueChanged(NULL);
}

void CALLBACK
SoWinP::delaySensorCB(HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo("SoWin::delaySensorCB", "called");
#endif // SOWIN_DEBUG
  SoDB::getSensorManager()->processDelayQueue(FALSE);
  SoGuiP::sensorQueueChanged(NULL);
}

// Process of all Inventor sensors scheduled for execution when the
// system is idle.
void
SoWinP::doIdleTasks(void)
{
  SoDB::getSensorManager()->processTimerQueue();
  SoDB::getSensorManager()->processDelayQueue(TRUE); // isidle = TRUE
  SoGuiP::sensorQueueChanged(NULL);
}

void CALLBACK
SoWinP::idleSensorCB(HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo("SoWin::idleSensorCB", "called");
#endif // SOWIN_DEBUG

  SoWinP::doIdleTasks();
}

LRESULT
SoWinP::onDestroy(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  PostQuitMessage(0);
  return 0;
}

LRESULT
SoWinP::onQuit(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  if (SoWinP::idleSensorActive) KillTimer(NULL, SoWinP::idleSensorId);
  if (SoWinP::timerSensorActive) KillTimer(NULL, SoWinP::timerSensorId);
  if (SoWinP::delaySensorActive) KillTimer(NULL, SoWinP::delaySensorId);

  Win32::UnregisterClass(SoWinP::className, NULL);

  return 0;
}

#ifndef DOXYGEN_SKIP_THIS

// This function gets called whenever something has happened to any of
// the sensor queues. It starts or reschedules a timer which will
// trigger when a sensor is ripe for plucking.
void
SoGuiP::sensorQueueChanged(void * cbdata)
{
  SoSensorManager * sensormanager = SoDB::getSensorManager();

  SbTime timevalue;
  if (sensormanager->isTimerSensorPending(timevalue)) {
    SbTime interval = timevalue - SbTime::getTimeOfDay();

    if (interval.getValue() < 0.0) interval.setValue(0.0);
    if (SoWinP::timerSensorActive) KillTimer(NULL, SoWinP::timerSensorId);
    
    SoWinP::timerSensorId = SetTimer(SoWinP::mainWidget,
                                      1,
                                      interval.getMsecValue(),
                                      (TIMERPROC)SoWinP::timerSensorCB);

    SoWinP::timerSensorActive = TRUE;
  }
  else if (SoWinP::timerSensorActive) {
    KillTimer(NULL, SoWinP::timerSensorId);
    SoWinP::timerSensorActive = FALSE;
  }

  if (sensormanager->isDelaySensorPending()) {
        
    if (! SoWinP::idleSensorActive) {
      SoWinP::idleSensorId = SetTimer(SoWinP::mainWidget,
                                       2,
                                       0,
                                       (TIMERPROC)SoWinP::idleSensorCB);
      SoWinP::idleSensorActive = TRUE;
    }

    if (! SoWinP::delaySensorActive) {
      unsigned long timeout = SoDB::getDelaySensorTimeout().getMsecValue();
      SoWinP::delaySensorId = SetTimer(SoWinP::mainWidget,
                                        3,
                                        timeout,
                                        (TIMERPROC)SoWinP::delaySensorCB);
      SoWinP::delaySensorActive = TRUE;
    }
  }
  else {
                             
    if (SoWinP::idleSensorActive) {
      KillTimer(NULL, SoWinP::idleSensorId);
      SoWinP::idleSensorActive = FALSE;
    }

    if (SoWinP::delaySensorActive) {
      KillTimer(NULL, SoWinP::delaySensorId);
      SoWinP::delaySensorActive = FALSE;
    }
  }
}

#endif // !DOXYGEN_SKIP_THIS
