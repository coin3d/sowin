#ifndef SOWINDEF_H
#define SOWINDEF_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

// Misc defines done for compile-level compatibility with the original
// InventorWin. These are typically a redefine of a typename from
// X11/Xt to the similar type on Win32.
//
// (Why anyone would want to use X11 types in Win32-dependent code is
// beyond me. Anyway, there are a lot more of these than the ones
// below, I've just added those which have so far been requested.)
//
// -mortene

#define Widget HWND
#define XAnyEvent MSG
#define XtPointer PVOID

// These I don't understand at all -- why the heck define a misspelled
// type name into the correct one? There's seriously a limit to how
// far one should take "programmer convenience"...   -mortene.
#define Hinst HINSTANCE
#define Hwnd HWND

#endif // ! SOWINDEF_H
