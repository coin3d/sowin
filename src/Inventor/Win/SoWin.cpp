/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2004 by Systems in Motion.  All rights reserved.
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

// The mainpage documentation below is heavily based on the one for
// SoQt in SoQt.cpp.

/*!
  \mainpage

  The %SoWin library is a C++ GUI toolkit that binds together the
  \COIN rendering library with the user interface parts of the
  MSWindows Win32 API, thereby providing application programmers a
  convenient method of using the \COIN library from MSWindows
  development environments.

  By using the combination of \COIN and %SoWin for your 3D
  applications, you have a complete framework for writing software for
  Microsoft Windows operating systems.

  %SoWin, like \COIN, provides the programmer with a high-level
  application programmer's interface (API) in C++. The library
  primarily includes a class-hierarchy of viewer components of varying
  functionality and complexity, with various modes for the end-user to
  control the 3D-scene camera interaction.

  For a small, completely stand-alone usage example on how to
  initialize the library and set up a viewer instance window, see the
  following code:

  \code
  #include <Inventor/Win/SoWin.h>
  #include <Inventor/Win/viewers/SoWinExaminerViewer.h>
  #include <Inventor/nodes/SoBaseColor.h>
  #include <Inventor/nodes/SoCone.h>
  #include <Inventor/nodes/SoSeparator.h>
  
  int
  main(int argc, char ** argv)
  {
    // Initializes SoWin library (and implicitly also the Coin
    // library). Returns a top-level / shell window to use.
    HWND mainwin = SoWin::init(argc, argv, argv[0]);
  
    // Make a dead simple scene graph by using the Coin library, only
    // containing a single yellow cone under the scenegraph root.
    SoSeparator * root = new SoSeparator;
    root->ref();

    SoBaseColor * col = new SoBaseColor;
    col->rgb = SbColor(1, 1, 0);
    root->addChild(col);

    root->addChild(new SoCone);
  
    // Use one of the convenient SoWin viewer classes.
    SoWinExaminerViewer * eviewer = new SoWinExaminerViewer(mainwin);
    eviewer->setSceneGraph(root);
    eviewer->show();
  
    // Pop up the main window.
    SoWin::show(mainwin);
    // Loop until exit.
    SoWin::mainLoop();

    // Clean up resources.
    delete eviewer;
    root->unref();

    return 0;
  }
  \endcode

  As compiled and run, this example provides the end-user with a full
  fledged 3D viewer. The viewer automatically contains mouse
  interaction handling logic to let the end-user "examine" the
  3D-model / scene (since this is the SoWinExaminerViewer class), plus
  toolbar controls on the right-side decorations border for often used
  controls:

  <center>
  <img src="http://doc.coin3d.org/images/SoLibs/general/sogui-class-example.png">
  </center>

  The %SoWin library contains several such high-level classes as the
  SoWinExaminerViewer used in the above example. These are primarily
  used for doing Rapid Application Development (RAD) of new concepts
  and ideas for your 3D system.  The "real" application will typically
  use one of the lower-complexity classes higher up in the inheritance
  hierarchy, such as the SoWinRenderArea, which provides the
  application programmer with full control over the user interface
  components and general layout to present for the end-user, as
  suitable for the specific application needs.

  This is how the %SoWin library fits in with the other system
  components:

  <center>
  <img src="http://doc.coin3d.org/images/SoLibs/mainpage/sowin-boxology.png">
  </center>

  As can be seen from the above figure, %SoWin builds on Systems in
  Motion's \COIN library for the 3D graphics, and the standard
  Microsoft Windows Win32 API for the 2D user interface components.

  The additional functionality provided by %SoWin over \COIN is:

  <ul>

  <li>The most convenient management of OpenGL context types, such as
  singlebuffered versus doublebuffered rendering, the use of overlay
  planes, stereo rendering, etc. This is handled through the
  SoWinGLWidget class and through the SoWinRenderArea class (which
  contains the main binding into the \COIN library's main data
  structures).</li>

  <li>The translation of native Win32 interaction device events (from
  e.g. the mouse or the keyboard) into the \COIN library's event
  types. The translation is done by the SoWinDevice classes,
  controlled by the SoWinRenderArea.

  These "generic" \COIN events are then passed into the 3D scenegraph
  for further processing, for instance by \COIN's 3D user interaction
  components -- like this "trackball manipulator" attached to a simple
  cone:

  <center>
  <img src="http://doc.coin3d.org/images/Coin/draggers/trackball-cone.png">
  </center>
  </li>

  <li>Some abstract viewer classes, like the SoWinViewer and
  SoWinFullViewer, which provides additional services on top of the
  SoWinRenderArea for assisting the application programmer in
  convenient handling of cameras and lightsources in the 3D scene (by
  the SoWinViewer), plus adding the basic, common user interface
  components (by the SoWinFullViewer).</li>

  <li>A set of high-level viewer classes, as has been presented by the
  SoWinExaminerViewer in the above source code example. There are
  currently three different non-abstract viewer classes to choose
  from: the SoWinExaminerViewer (a plain model viewer), the
  SoWinFlyViewer (for fly-throughs in larger 3D scenes) and the
  SoWinPlaneViewer (for CAD-style viewing and interaction along the 3
  principal axes).</li>

  </ul>

  For those who are using the implementation of the Inventor API from
  SGI, we would like to point out that %SoWin can also be used on top
  of that library instead of the \COIN library from Systems in Motion.

  The %SoWin API is based on and closely matches the InventorXt
  library API, originally developed by SGI. This should make it
  straigthforward to port simple InventorXt code over to %SoWin, for
  instance to gain greater portability.

  For more information about the Coin3D family of libraries, including
  licensing information, please visit the Coin3D web site 
  <http://www.coin3d.org>.

  \sa The documentation for the \COIN library: <http://doc.coin3d.org/Coin>.
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
#include <Inventor/Win/nodes/SoGuiNodes.h>
#include <Inventor/Win/engines/SoGuiEngines.h>

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

  SoGuiNodes::initClasses();
  SoGuiEngines::initClasses();

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
