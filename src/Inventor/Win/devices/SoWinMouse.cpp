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

#include <windows.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>

#include <Inventor/Win/devices/SoWinMouse.h>
#include <Inventor/Win/devices/SoGuiMouseP.h>
#include <Inventor/Win/devices/SoWinDeviceP.h>

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

#if 0   // FIXME: disabled until it's enabled again through autoconf test
  case WM_MOUSEWHEEL:
    if (HIWORD(message->wParam) < 0) {  // delta z = WHEEL_DELTA = 120
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON4);
    }
    else {
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON5);
    }
    break;
#endif
  default:
    this->buttonevent->setButton(SoMouseButtonEvent::ANY);
    break;
  }

  /*  if (this->locationevent) {
    this->buttonevent->setPosition(this->locationevent->getPosition());
  }
  else {*/
    PUBLIC(this)->setEventPosition(this->buttonevent, msg->pt.x, msg->pt.y);
    //}
  this->buttonevent->setShiftDown((SoWinDeviceP::modifierKeys & MK_SHIFT) ? TRUE : FALSE);
  this->buttonevent->setCtrlDown((SoWinDeviceP::modifierKeys & MK_CONTROL) ? TRUE : FALSE);
  this->buttonevent->setAltDown((SoWinDeviceP::modifierKeys & MK_ALT) ? TRUE : FALSE);
  
  return this->buttonevent;
}

// *************************************************************************
