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

#include <Inventor/SbTime.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodekits/SoNodeKit.h>

#include <Inventor/Win/Win32API.h>
#include <sowindefs.h> // SOWIN_STUB
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/devices/SoWinDevice.h>
#include <Inventor/Win/SoWinComponent.h>
#include <Inventor/Win/SoAny.h>

// The private data for the SoWin class.

class SoWinP {
  
public:

  static BOOL CALLBACK sizeChildProc(HWND window, LPARAM lparam);
  static void sensorQueueChanged(void * cbdata);

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

// documented in common/SoGuiObject.cpp.in
void
SoWinObject::init(void)
{
  SoWinObject::initClass();
  SoWinDevice::initClasses();
  SoWinComponent::initClasses();
} // init()

///////////////////////////////////////////////////////////////////
//
//  (public)
//

/*!
  \fn HWND SoWin::init(const char * const appName, const char * const className)

  This method is provided for easier porting/compatibility with the
  Open Inventor SoXt component classes. It just adds dummy \a argc and
  \a argv arguments and calls the SoWin::init() method below.
*/
HWND
SoWin::internal_init(const char * const appName, const char * const className)
{
  int argc = 1;
  char * argv[] = { (char *) appName, NULL };
  return SoWin::internal_init(argc, argv, appName, className);
} // internal_init()


/*!
  \fn HWND SoWin::init(int argc, char ** argv, const char * const appName, const char * const className)

  Initializes the SoWin component toolkit library, as well as the Open Inventor
  library.

  Calls \a SoDB::init(), \a SoNodeKit::init() and \a SoInteraction::init(), and
  returns a  main widget for you
*/

HWND
SoWin::internal_init(int argc,
                     char ** argv,
                     const char * const appName,
                     const char * const className)
{
  if (appName)
    SoWinP::appName = strcpy(new char [ strlen(appName) + 1 ], appName);
  if (className)
    SoWinP::className = strcpy(new char [ strlen(className) + 1 ], className);

  SoWin::registerWindowClass(className);
 
  SIZE size = { 500, 500 };
  HWND toplevel = SoWin::createWindow((char *) appName, (char *) className, size, NULL);
  SoWinP::useParentEventHandler = FALSE;
  
  SoWin::internal_init( toplevel );
  
  return toplevel;
} // internal_init()


/*!
  \fn SoWin::init(HWND const topLevelWidget)

  Calls \a SoDB::init(), \a SoNodeKit::init() and \a SoInteraction::init().
  Assumes you are creating your main widget.
  \a topLevelWidget should be your application's main widget.
*/
void
SoWin::internal_init(HWND const topLevelWidget)
{
  SoDB::init();
  SoNodeKit::init();
  SoInteraction::init();
  SoWinObject::init();

  SoDebugError::setHandlerCallback(SoWin::errorHandlerCB, NULL);

  SoDB::getSensorManager()->setChangedCallback(SoWinP::sensorQueueChanged, NULL);
  if (IsWindow(topLevelWidget)) 
    SoWinP::mainWidget = topLevelWidget;

  if (SoWinP::useParentEventHandler) {
    SoWinP::parentEventHandler = (WNDPROC) Win32::GetWindowLong(topLevelWidget, GWL_WNDPROC);
    (void)Win32::SetWindowLong(topLevelWidget, GWL_WNDPROC, (long) SoWin::eventHandler);
  }
} // internal_init()

/*!
 */
void
SoWin::internal_init(void)
{
  SoWin::internal_init("SoWin", "SoWin");
} // internal_init()

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
} // mainLoop()

/*!
  This function will make the main event loop finish looping.

  NOTE: exitMainLoop() is not part of the original SGI InventorXt API.
*/
void
SoWin::exitMainLoop(void)
{
  PostQuitMessage(0);
} // exitMainLoop()

/*!
 */
BOOL
SoWin::dispatchEvent(MSG * msg)
{
  TranslateMessage(msg);
  DispatchMessage(msg);
  return TRUE;
} // dispatchEvent()

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
} // show()

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
} // hide()

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
} // setWidgetSize()

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
} // getWidgetSize()

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
} // getTopLevelWidget()

/*!
  This will pop up an error dialog. It's just a simple wrap-around for
  the Win32 API MessageBox() call, provided for easier porting from
  applications using the Open Inventor SoXt component classes, aswell
  as being a convenient way for the application programmer or from
  SoWin components to throw up an obtrusive application-global error
  dialog.

  If \a widget is \c NULL, the dialog will be modal for the whole
  application (all windows will be blocked for input). If not, only
  the window for the given \a widget will be blocked.

  \a dialogTitle is the title of the dialog box. \a errorStr1 and \a
  errorStr2 contains the text which will be shown in the dialog box.

  There will only be a single "Ok" button for the user to press.
*/
void
SoWin::createSimpleErrorDialog(HWND const widget, const char * const dialogTitle, const char * const errorStr1, const char * const errorStr2)
{
  
  SbString title(dialogTitle ? dialogTitle : "");
  SbString errstr(errorStr1 ? errorStr1 : "");

  if (errorStr2) {
    errstr += '\n';
    errstr += errorStr2;
  }

  MessageBox(widget, errstr.getString(), title.getString(), MB_OK | MB_ICONERROR | MB_TASKMODAL);
} // createSimpleErrorDialog()

/*!
 */
HWND
SoWin::createWindow(char * title, char * className, SIZE size, HWND parent, HMENU menu)
{
  DWORD style, exstyle;
  LPVOID params = NULL;

  style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
  exstyle = NULL;

  HWND widget = CreateWindowEx(exstyle,
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
                                params);
  return widget;
} // createWindow()

/*!
 */
SbBool
SoWin::nextEvent(int appContext, MSG * msg)
{
  return GetMessage(msg, NULL, 0, 0);
} // nextEvent()

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
    if (style & WS_OVERLAPPEDWINDOW) break;
    parent = GetParent(hwnd);
  } while(IsWindow(parent));
  
  return hwnd;
} // getShellWidget()

/*!
 */
void
SoWin::setInstance(HINSTANCE instance)
{
  SoWinP::Instance = instance;
} // setInstance()

/*!
 */
HINSTANCE
SoWin::getInstance(void)
{
  return SoWinP::Instance;
} // getInstance()

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
} // errorHandlerCB()

/*!
 */
void
SoWin::doIdleTasks(void)
{
  SoDB::getSensorManager()->processTimerQueue();
  SoDB::getSensorManager()->processDelayQueue(TRUE); // isidle = TRUE
  SoWinP::sensorQueueChanged(NULL);
} // doIdleTasks()

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
  LPCTSTR cursor = MAKEINTRESOURCE(IDC_ARROW);
  HBRUSH brush = (HBRUSH) GetSysColorBrush(COLOR_BTNFACE);

  windowclass.lpszClassName = className;
  windowclass.hInstance = SoWin::getInstance();
  windowclass.lpfnWndProc = SoWin::eventHandler;
  windowclass.style = CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon(SoWin::getInstance(), icon);
  windowclass.hCursor = LoadCursor(SoWin::getInstance(), cursor);
  windowclass.hbrBackground = brush;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass(& windowclass);
} // registerWindowClass()

/*!
 */
void
SoWin::unRegisterWindowClass(const char * const className)
{
  Win32::UnregisterClass(className, SoWin::getInstance());
} // unRegisterWindowClass(

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
} // eventHandler()

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
  SoWinP::sensorQueueChanged(NULL);
} // timerSensorCB()

/*!
 */
void CALLBACK
SoWinP::delaySensorCB(HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo("SoWin::delaySensorCB", "called");
#endif // SOWIN_DEBUG
  SoDB::getSensorManager()->processDelayQueue(FALSE);
  SoWinP::sensorQueueChanged(NULL);
} // delaySensorCB()

/*!
 */
void CALLBACK
SoWinP::idleSensorCB(HWND window, UINT message, UINT idevent, DWORD dwtime)
{
#if SOWIN_DEBUG && 0
  SoDebugError::postInfo("SoWin::idleSensorCB", "called");
#endif // SOWIN_DEBUG
  SoWin::doIdleTasks();
} // idleSensorCB()

/*!
  \internal

  This function gets called whenever something has happened to any of
  the sensor queues. It starts or reschedules a timer which will trigger
  when a sensor is ripe for plucking.
*/
void
SoWinP::sensorQueueChanged(void * cbdata)
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
                                      SoWinP::timerSensorCB);

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
                                       SoWinP::idleSensorCB);
      SoWinP::idleSensorActive = TRUE;
    }

    if (! SoWinP::delaySensorActive) {
      unsigned long timeout = SoDB::getDelaySensorTimeout().getMsecValue();
      SoWinP::delaySensorId = SetTimer(SoWinP::mainWidget,
                                        3,
                                        timeout,
                                        SoWinP::delaySensorCB);
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
} // sensorQueueChanged()

/*!
 */
LRESULT
SoWinP::onDestroy(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  PostQuitMessage(0);
  return 0;
} // onDestroy()

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
} // onQuit()


SbBool
SoWin::isDebugLibrary(void)
{
  return SOWIN_DEBUG != 0 ? TRUE : FALSE;
} // isDebugLibrary()

SbBool
SoWin::isCompatible(unsigned int major, unsigned int minor)
{
  if ( major != SOWIN_MAJOR_VERSION )
    return FALSE;
  if ( minor > SOWIN_MINOR_VERSION )
    return FALSE;
  return TRUE;
} // isCompatible()

SoWinABIType
SoWin::getABIType(void)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef COIN_MAKE_DLL
  return SOWIN_DLL_ABI;
#else
  return SOWIN_LIB_ABI;
#endif
#endif
  return SOWIN_UNKNOWN_ABI;
} // getABIType()

void
SoWin::abort(SoWinABIError error)
{
  SIZE size = { 500, 200 };
  switch ( error ) {
  case SOWIN_LINKTIME_MISMATCH:
    SoWin::createSimpleErrorDialog(
      SoWin::createWindow("SoWin", "Fatal Error", size, NULL),
      "Fatal Error",
      "Detected linktime mismatch error.");
    break;
  case SOWIN_LINKSTYLE_MISMATCH:
    SoWin::createSimpleErrorDialog(
      SoWin::createWindow("SoWin", "Fatal Error", size, NULL),
      "Fatal Error",
      "Detected linkstyle mismatch error (DLL vs. LIB).");
    break;
  case SOWIN_RUNTIME_MISMATCH:
    SoWin::createSimpleErrorDialog(
      SoWin::createWindow("SoWin", "Fatal Error", size, NULL),
      "Fatal Error",
      "Detected runtime mismatch error (versioning and ABI compatibility).");
    break;
  default:
    SoWin::createSimpleErrorDialog(
      SoWin::createWindow("SoWin", "Fatal Error", size, NULL),
      "Fatal Error",
      "SoWin doesn't even know about the error :(");
    break;
  }
  exit(-1);
} // abort()
