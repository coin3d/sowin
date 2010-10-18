#ifndef SOWIN_SPACENAVDEVICE_H
#define SOWIN_SPACENAVDEVICE_H
/**************************************************************************\
 *
 *  This file is part of the SIM Voleon visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using SIM Voleon with software that can not be combined with
 *  the GNU GPL, and for taking advantage of the additional benefits
 *  of our support services, please contact Kongsberg Oil & Gas
 *  Technologies about acquiring a SIM Voleon Professional Edition
 *  License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/Win/devices/SoWinDevice.h>

class SOWIN_DLL_API SoWinSpacenavDevice : public SoWinDevice {
  SOWIN_OBJECT_HEADER(SoWinSpacenavDevice, SoWinDevice);

 public:
  SoWinSpacenavDevice();
  virtual ~SoWinSpacenavDevice();

  virtual void enable(HWND w, SoWinEventHandler * handler, void * closure);
  virtual void disable(HWND w, SoWinEventHandler * handler, void * closure);
  virtual const SoEvent * translateEvent(MSG * event);

 private:
  class SoWinSpacenavDeviceP * pimpl;
  friend class SoWinSpacenavDeviceP;
};


#endif // !SOWIN_SPACENAVDEVICE_H
