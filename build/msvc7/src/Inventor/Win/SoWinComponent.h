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

#ifndef SOWIN_COMPONENT_H
#define SOWIN_COMPONENT_H

#include <Inventor/SbLinear.h>
#include <Inventor/Win/SoWinObject.h>

#ifdef __COIN_SOQT__
class QWidget;
#endif // __COIN_SOQT__
#ifdef __COIN_SOXT__
#include <X11/Intrinsic.h>
#endif // __COIN_SOXT__
#ifdef __COIN_SOGTK__
#include <gtk/gtk.h>
#endif // __COIN_SOGTK__
#ifdef __COIN_SOWIN__
#include <windows.h>
#endif // __COIN_SOWIN__


class SoWinComponent;
class SoWinCursor;

typedef void SoWinComponentCB(void * user, SoWinComponent * component);
typedef void SoWinComponentVisibilityCB(void * user, SbBool visible);

// *************************************************************************

class SOWIN_DLL_API SoWinComponent : public SoWinObject {
  SOWIN_OBJECT_ABSTRACT_HEADER(SoWinComponent, SoWinObject);

public:
  virtual ~SoWinComponent();

  virtual void show(void);
  virtual void hide(void);

  virtual void setComponentCursor(const SoWinCursor & cursor);
  static void setWidgetCursor(HWND w, const SoWinCursor & cursor);

  SbBool isFullScreen(void) const;
  SbBool setFullScreen(const SbBool onoff);

  SbBool isVisible(void);
  SbBool isTopLevelShell(void) const;

  HWND getWidget(void) const;
  HWND getBaseWidget(void) const;
  HWND getShellWidget(void) const;
  HWND getParentWidget(void) const;

  void setSize(const SbVec2s size);
  SbVec2s getSize(void) const;

  void setTitle(const char * const title);
  const char * getTitle(void) const;
  void setIconTitle(const char * const title);
  const char * getIconTitle(void) const;

  const char * getWidgetName(void) const;
  const char * getClassName(void) const;

  void setWindowCloseCallback(SoWinComponentCB * const func,
                              void * const user = NULL);
  static SoWinComponent * getComponent(HWND widget);

  static void initClasses(void);

protected:
  SoWinComponent(HWND const parent = NULL,
                   const char * const name = NULL,
                   const SbBool embed = TRUE);

  virtual void afterRealizeHook(void);

  // About the wrapping below: this variable was added after SoQt 1.0,
  // and before SoXt 1.1. To be able to release SoQt 1.1 from this
  // same branch, sizeof(SoQtComponent) needs to be the same as for
  // SoQt 1.0, which means we can't add this variable for SoQt.
#ifndef __COIN_SOQT__
  SbBool firstRealize;
#endif // __COIN_SOQT__

  void setClassName(const char * const name);
  void setBaseWidget(HWND widget);

  void registerWidget(HWND widget);
  void unregisterWidget(HWND widget);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual void sizeChanged(const SbVec2s & size);

  void addVisibilityChangeCallback(SoWinComponentVisibilityCB * const func,
                                   void * const user = NULL);
  void removeVisibilityChangeCallback(SoWinComponentVisibilityCB * const func,
                                      void * const user = NULL);

private:
  class SoWinComponentP * pimpl;
  friend class SoGuiComponentP;
  friend class SoWinComponentP;

  // FIXME!: audit and remove as much as possible of the remaining
  // toolkit specific parts below. 20020117 mortene.

#ifdef __COIN_SOXT__
public:
  Display * getDisplay(void);
  void fitSize(const SbVec2s size);
  // FIXME: I guess these should really be part of the common
  // API. 20011012 mortene.
  void addWindowCloseCallback(SoXtComponentCB * callback, void * closure = NULL);
  void removeWindowCloseCallback(SoXtComponentCB * callback, void * closure = NULL);

protected:
  // FIXME: I guess this should perhaps be part of the common API?
  // 20011012 mortene.
  void invokeVisibilityChangeCallbacks(const SbBool enable) const;
  void invokeWindowCloseCallbacks(void) const;
  virtual void windowCloseAction(void);

private:
  // FIXME: get rid of this? 20011012 mortene.
  static void event_handler(Widget, XtPointer, XEvent *, Boolean *);
#endif // __COIN_SOXT__

#ifdef __COIN_SOGTK__
protected:
  virtual SbBool eventFilter(GtkWidget * object, GdkEvent * event);
private:
  static gint eventHandler(GtkWidget * object, GdkEvent * event, gpointer closure);
#endif // __COIN_SOGTK__
};

// *************************************************************************

#endif // ! SOWIN_COMPONENT_H
