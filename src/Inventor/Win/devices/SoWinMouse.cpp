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

#include <windows.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>

#include <Inventor/Win/devices/SoWinMouse.h>
#include <Inventor/Win/devices/SoGuiMouseP.h>
#include <Inventor/Win/devices/SoWinDeviceP.h>

// Small hack to get WM_MOUSEWHEEL define value. Should be harmless to
// do in this manner, and we avoid having to set up the define
// _WIN32_WINDOWS >= 0x0400 before including <windows.h> (there are
// indications in comp.os.ms-windows.programmer discussions that the
// _WIN32_WINDOWS define could have peculiar / unwanted sideeffects).

#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020a
#endif // WM_MOUSEWHEEL

#define PRIVATE(obj) ((obj)->pimpl)
#define PUBLIC(obj) ((obj)->pub)

// *************************************************************************

class SoWinMouseP : public SoGuiMouseP {
public:
  SoWinMouseP(SoWinMouse * p) : SoGuiMouseP(p) { }

  SoLocation2Event * makeLocationEvent(MSG * msg);
  SoMouseButtonEvent * makeButtonEvent(MSG * msg, SoButtonEvent::State state);
};

// *************************************************************************

SoWinMouse::SoWinMouse(int events)
{
  PRIVATE(this) = new SoWinMouseP(this);
  PRIVATE(this)->eventmask = events;
}

SoWinMouse::~SoWinMouse(void)
{
  delete PRIVATE(this);
}

// *************************************************************************

void
SoWinMouse::enable(HWND, SoWinEventHandler * , void *)
{
  // Win32 has no way of enabling the mouse. mariusbu 20010823.
  // Do nothing.

  // FIXME: should still try to add some magic here so Win32 events
  // are actually enabled or disabled for the widget handle in
  // question, or the semantics won't really match what the client
  // code expects. 20020625 mortene.
}

void
SoWinMouse::disable(HWND, SoWinEventHandler * , void *)
{
  // Win32 has no way of disabling the mouse. mariusbu 20010823.
  // Do nothing.

  // FIXME: should still try to add some magic here so Win32 events
  // are actually enabled or disabled for the widget handle in
  // question, or the semantics won't really match what the client
  // code expects. 20020625 mortene.
}

// *************************************************************************

const SoEvent *
SoWinMouse::translateEvent(MSG * msg)
{
  SoEvent * soevent = (SoEvent *) NULL;
  SoButtonEvent::State state = SoButtonEvent::UNKNOWN;

  switch (msg->message) {

  case WM_LBUTTONDOWN:
  case WM_MBUTTONDOWN:
  case WM_RBUTTONDOWN:
  case WM_MOUSEWHEEL:
    if (! (PRIVATE(this)->eventmask & SoWinMouse::BUTTON_PRESS)) break;
    state = SoButtonEvent::DOWN;
    soevent = PRIVATE(this)->makeButtonEvent(msg, state);
    break;

  case WM_LBUTTONUP:
  case WM_MBUTTONUP:
  case WM_RBUTTONUP:
    if (! (PRIVATE(this)->eventmask & SoWinMouse::BUTTON_RELEASE)) break;
    state = SoButtonEvent::UP;
    soevent = PRIVATE(this)->makeButtonEvent(msg, state);
    break;

  case WM_MOUSEMOVE:
    if (! (PRIVATE(this)->eventmask & SoWinMouse::POINTER_MOTION)) break;
    soevent = PRIVATE(this)->makeLocationEvent(msg);
    break;

    // FIXME: implement BUTTON_MOTION filtering. mariusbu.


  case WM_SETFOCUS:
  case WM_KILLFOCUS:

    // should we make location-events for these?
    do {
      // FIXME: not implemented
    } while (FALSE);
    break;

    // events we should ignore:
  default:
    break;

  }

  if (soevent) {
    long msec = GetTickCount();
    soevent->setTime(SbTime((msec / 1000), (msec % 1000) * 1000));
  }

  return (SoEvent *) soevent;
}

// *************************************************************************

SoLocation2Event *
SoWinMouseP::makeLocationEvent(MSG * msg)
{
  static POINT prevPos = { 0xFFFF, 0xFFFF };
  if ((msg->pt.x == prevPos.x) && (msg->pt.y == prevPos.y)) {
    return NULL;
  }
  else {
    prevPos = msg->pt;
  }

  if (this->locationevent == NULL)
    this->locationevent = new SoLocation2Event;

  PUBLIC(this)->setEventPosition(this->locationevent, msg->pt.x, msg->pt.y);

  this->locationevent->setShiftDown((SoWinDeviceP::modifierKeys & MK_SHIFT) ? TRUE : FALSE);
  this->locationevent->setCtrlDown((SoWinDeviceP::modifierKeys & MK_CONTROL) ? TRUE : FALSE);
  this->locationevent->setAltDown((SoWinDeviceP::modifierKeys & MK_ALT) ? TRUE : FALSE);

  return this->locationevent;
}

SoMouseButtonEvent *
SoWinMouseP::makeButtonEvent(MSG * msg, SoButtonEvent::State state)
{
  if (this->buttonevent == NULL)
    this->buttonevent = new SoMouseButtonEvent;

  this->buttonevent->setState(state);

  switch (msg->message) {

  case WM_LBUTTONDOWN: // left button
  case WM_LBUTTONUP:
    this->buttonevent->setButton(SoMouseButtonEvent::BUTTON1);
    break;

  case WM_MBUTTONDOWN: // midbutton
  case WM_MBUTTONUP:
    this->buttonevent->setButton(SoMouseButtonEvent::BUTTON3);
    break;

  case WM_RBUTTONDOWN: // right button
  case WM_RBUTTONUP:
    this->buttonevent->setButton(SoMouseButtonEvent::BUTTON2);
    break;

  case WM_MOUSEWHEEL:
    if (((int16_t)HIWORD(msg->wParam)) < 0) {  // HIWORD(wParam) == deltaZ
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON4);
    }
    else {
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON5);
    }
    break;

  default:
    this->buttonevent->setButton(SoMouseButtonEvent::ANY);
    break;
  }

  if ( msg->message == WM_MOUSEWHEEL ) {
    SbVec2s pos = PUBLIC(this)->getLastEventPosition();
    PUBLIC(this)->setEventPosition(this->buttonevent, pos[0], pos[1]);
  } else {
    PUBLIC(this)->setEventPosition(this->buttonevent, msg->pt.x, msg->pt.y);
  }

  this->buttonevent->setShiftDown((SoWinDeviceP::modifierKeys & MK_SHIFT) ? TRUE : FALSE);
  this->buttonevent->setCtrlDown((SoWinDeviceP::modifierKeys & MK_CONTROL) ? TRUE : FALSE);
  this->buttonevent->setAltDown((SoWinDeviceP::modifierKeys & MK_ALT) ? TRUE : FALSE);

  return this->buttonevent;
}

// *************************************************************************

#undef PRIVATE
#undef PUBLIC
