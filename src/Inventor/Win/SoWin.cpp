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

// *************************************************************************

// Class documentation in common/SoGuiCommon.cpp.in.

/*!
  \mainpage

  %SoWin is a C++ GUI toolkit for using Coin with the Microsoft
  Windows Win32 API.  It can also be used on top of Open Inventor from
  SGI and TGS.  The API is based on the InventorXt API originally from
  SGI.

  The corresponding documentation for Coin is located 
  <a href="http://doc.coin3d.org/Coin/">here</a>.
*/

// *************************************************************************

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
  
  static LRESULT onDestroy(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  static LRESULT onQuit(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
  
  static HINSTANCE Instance;
  static HWND mainWidget;
  static char * appName;
  static char * className;

  static SbBool useParentEventHandler;
  static WNDPROC parentEventHandler;

private:
  SoWin * owner;
  
};

  // Variables.

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

  SoWin::registerWindowClass(classname);
 
  SIZE size = { 500, 500 };
  HWND toplevel = SoWin::createWindow((char *) appname, (char *) classname, size, NULL);
  SoWinP::useParentEventHandler = FALSE;
  
  SoWin::init( toplevel );
  
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

  SoDebugError::setHandlerCallback(SoWin::errorHandlerCB, NULL);

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
    //    wcl.hInstance = SoWin::getInstance();
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
    (void)Win32::SetWindowLong(toplevelwidget, GWL_WNDPROC, (long) SoWin::eventHandler);
  }
}

/*!
  This is the event dispatch loop. It doesn't return until
  \a PostQuitMessage() is called (which is also done automatically by
  Windows whenever the user closes an application's main widget).
*/
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
    else if (SoWinP::idleSensorActive)
      SoWin::doIdleTasks();
    else // !idleSensorActive
      WaitMessage();
  }

  SoWin::done();
}

/*!
  This function will make the main event loop finish looping.

  NOTE: exitMainLoop() is not part of the original SGI InventorXt API.
*/
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
 */
BOOL
SoWin::dispatchEvent(MSG * msg)
{
  TranslateMessage(msg);
  DispatchMessage(msg);
  return TRUE;
}

/*!
  This method is provided for easier porting/compatibility with the
  Open Inventor SoXt component classes. It will call ShowWindow() with the
  argument SW_SHOW on the provided \a widget window handle.

  \sa hide()
*/
void
SoWin::show(HWND const widget)
{
  (void)ShowWindow(widget, SW_SHOW);
}

/*!
  This method is provided for easier porting/compatibility with the
  Open Inventor SoXt component classes. It will call ShowWindow() with the
  argument SW_HIDE on the provided \a widget window handle.

  \sa show()
*/
void
SoWin::hide(HWND const widget)
{
  (void)ShowWindow(widget, SW_HIDE);
}

/*!
  This method is provided for easier porting of applications based on the
  Open Inventor SoXt component classes. It will call SetWindowPos() on the
  provided \a widget window handle.

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
  Open Inventor SoXt component classes. It will call GetWindowExtEx() on the
  provided \a widget window handle's device context (returning an SbVec2s).

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

/*!
  Returns a pointer to the HWND which is the main widget for the
  application. When this widget gets closed, SoWin::mainLoop() will
  return (unless the close event is caught by the user).

  \sa getShellWidget()
*/
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
                               const char * const title,
                               const char * const string1,
                               const char * const string2)
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
 */
HWND
SoWin::createWindow(char * title, char * className, SIZE size, HWND parent, HMENU menu)
{
  DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
  DWORD exstyle = NULL;

  HWND widget = Win32::CreateWindowEx_(exstyle,
                                       className,
                                       title,
                                       style,
                                       CW_USEDEFAULT,
                                       CW_USEDEFAULT,
                                       size.cx,
                                       size.cy,
                                       parent,
                                       menu,
                                       SoWin::getInstance(),
                                       NULL);
  return widget;
}

/*!
 */
SbBool
SoWin::nextEvent(int appContext, MSG * msg)
{
  return GetMessage(msg, NULL, 0, 0);
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

/*!
 */
void
SoWin::setInstance(HINSTANCE instance)
{
  SoWinP::Instance = instance;
}

/*!
 */
HINSTANCE
SoWin::getInstance(void)
{
  return SoWinP::Instance;
}

/*!
 */
void
SoWin::errorHandlerCB(const SoError * error, void * data)
{
  // Normally, errors, warnings and info goes to a dialog box..
#if 1
  SbString debugstring = error->getDebugString();

  MessageBox(NULL,
              (LPCTSTR) debugstring.getString(),
              "SoError",
              MB_OK | MB_ICONERROR);
#else
  // ..but during development it might be better to pipe it to the
  // console, so keep this #if/#else/#endif wrapper for convenience.

  (void)printf("%s\n", error->getDebugString().getString());
#endif
}

/*!
 */
void
SoWin::doIdleTasks(void)
{
  SoDB::getSensorManager()->processTimerQueue();
  SoDB::getSensorManager()->processDelayQueue(TRUE); // isidle = TRUE
  SoGuiP::sensorQueueChanged(NULL);
}

///////////////////////////////////////////////////////////////////
//
//  (protected)
//

/*!
 */
void
SoWin::registerWindowClass(const char * const className)
{
  WNDCLASS windowclass;

  LPCTSTR icon = MAKEINTRESOURCE(IDI_APPLICATION);
  HBRUSH brush = (HBRUSH) GetSysColorBrush(COLOR_BTNFACE);

  windowclass.lpszClassName = className;
  windowclass.hInstance = SoWin::getInstance();
  windowclass.lpfnWndProc = SoWin::eventHandler;
  windowclass.style = CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon(SoWin::getInstance(), icon);
  windowclass.hCursor = Win32::LoadCursor(NULL, IDC_ARROW);
  windowclass.hbrBackground = brush;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass(& windowclass);
}

/*!
 */
void
SoWin::unRegisterWindowClass(const char * const className)
{
  Win32::UnregisterClass(className, SoWin::getInstance());
}

/*!
 */
LRESULT CALLBACK
SoWin::eventHandler(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  LRESULT retval = 0;
  BOOL handled = FALSE;
  
  switch(message)
    {

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

/*!
 */
void CALLBACK
SoWinP::timerSensorCB(HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo("SoWin::timerSensorCB", "called");
#endif // SOWIN_DEBUG
  SoDB::getSensorManager()->processTimerQueue();
  SoGuiP::sensorQueueChanged(NULL);
}

/*!
 */
void CALLBACK
SoWinP::delaySensorCB(HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo("SoWin::delaySensorCB", "called");
#endif // SOWIN_DEBUG
  SoDB::getSensorManager()->processDelayQueue(FALSE);
  SoGuiP::sensorQueueChanged(NULL);
}

/*!
 */
void CALLBACK
SoWinP::idleSensorCB(HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo("SoWin::idleSensorCB", "called");
#endif // SOWIN_DEBUG
  SoWin::doIdleTasks();
}

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

/*!
 */
LRESULT
SoWinP::onDestroy(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  PostQuitMessage(0);
  return 0;
}

/*!
 */
LRESULT
SoWinP::onQuit(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  if (SoWinP::idleSensorActive) KillTimer(NULL, SoWinP::idleSensorId);
  if (SoWinP::timerSensorActive) KillTimer(NULL, SoWinP::timerSensorId);
  if (SoWinP::delaySensorActive) KillTimer(NULL, SoWinP::delaySensorId);

  SoWin::unRegisterWindowClass(SoWinP::className);

  return 0;
}
