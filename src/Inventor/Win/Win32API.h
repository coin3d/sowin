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

#ifndef SOWIN_WIN32API
#define SOWIN_WIN32API

// This is an internal class which wraps most of the Win32 API
// functions we use in SoWin -- to do robust checking of return values
// etc.
//
// This way, we should be able to early detect programming errors on
// our behalf, while still keeping the sourcecode nice and clean.

#include <windows.h>

class Win32 {
public:
  static void BitBlt(HDC, int, int, int, int, HDC, int, int, DWORD);
  static void EnableWindow(HWND, BOOL);
  static void GetTextExtentPoint(HDC, LPCTSTR, int, LPSIZE);
  static void MoveWindow(HWND, int, int, int, int, BOOL);
  static HGDIOBJ SelectObject(HDC, HGDIOBJ);
  static void SwapBuffers(HDC);
  static void UnregisterClass(LPCTSTR, HINSTANCE);
  static void DestroyWindow(HWND);
  static void SetWindowText(HWND, LPCTSTR);
   
private:
  static void showLastErr(void);
};

#endif // SOWIN_WIN32API
