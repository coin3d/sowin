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

#include <Win32API.h>
#include <stdio.h>
#include <assert.h>

void
Win32::showLastErr(void)
{
  LPTSTR buffer;

  DWORD lasterr = GetLastError();

  BOOL result =
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  lasterr,
                  0,
                  (LPTSTR)&buffer,
                  0,
                  NULL);

  if (result) {
    // Don't use fprintf(), as compiling in stdout or stderr file
    // descriptor pointer values is problematic when SoWin is built as
    // a DLL.
    (void)printf("\n*** GetLastError()==%d => %s\n", lasterr, buffer);
    (void)LocalFree(buffer);
  }
}

void
Win32::MoveWindow(HWND hWnd,      // handle to window
                  int X,          // horizontal position
                  int Y,          // vertical position
                  int nWidth,     // width
                  int nHeight,    // height
                  BOOL bRepaint   // repaint flag
                  )
{
  BOOL r = ::MoveWindow( hWnd, X, Y, nWidth, nHeight, bRepaint);
  if (!r) { Win32::showLastErr(); }
  assert( r && "MoveWindow() failed -- investigate");
}

void
Win32::EnableWindow(HWND hWnd,     // handle to window
                    BOOL bEnable   // flag for enabling or disabling input
                    )
{
  BOOL enabled = ::IsWindowEnabled(hWnd);
  if (enabled && bEnable) { return; }
  if (!enabled && !bEnable) { return; }

  BOOL r = ::EnableWindow( hWnd, bEnable );
  BOOL fail = (!r && bEnable) || (r && !bEnable);
  if (fail) { Win32::showLastErr(); }
  assert( !fail && "EnableWindow() failed -- investigate" );
}

void
Win32::GetTextExtentPoint(HDC hdc,           // handle to device context
                          LPCTSTR lpString,  // pointer to text string
                          int cbString,      // number of characters in string
                          LPSIZE lpSize      // pointer to structure for string size
                          )
{
  BOOL r = ::GetTextExtentPoint( hdc, lpString, cbString, lpSize );
  if (!r) { Win32::showLastErr(); }
  assert( r && "GetTextExtentPoint() failed -- investigate");
}
  
void
Win32::BitBlt(HDC hdcDest, // handle to destination device context
              int nXDest,  // x-coordinate of destination rectangle's upper-left corner
              int nYDest,  // y-coordinate of destination rectangle's upper-left corner
              int nWidth,  // width of destination rectangle
              int nHeight, // height of destination rectangle
              HDC hdcSrc,  // handle to source device context
              int nXSrc,   // x-coordinate of source rectangle's upper-left corner
              int nYSrc,   // y-coordinate of source rectangle's upper-left corner
              DWORD dwRop  // raster operation code
              )
{
  BOOL r = ::BitBlt( hdcDest, nXDest, nYDest, nWidth, nHeight,
                     hdcSrc, nXSrc, nYSrc, dwRop );
  if (!r) { Win32::showLastErr(); }
  assert( r && "BitBlt() failed -- investigate");
}

HGDIOBJ
Win32::SelectObject(HDC hdc,          // handle to device context
                    HGDIOBJ hgdiobj   // handle to object
                    )
{
  HGDIOBJ o = ::SelectObject( hdc, hgdiobj );
  BOOL fail = ((o == NULL) || (o == (HGDIOBJ)GDI_ERROR));
  assert( !fail && "SelectObject() failed -- investigate");
  return o;
}


void
Win32::SwapBuffers(HDC hdc  // device context whose buffers get swapped
                   )
{
  BOOL r = ::SwapBuffers(hdc);
  if (!r) { Win32::showLastErr(); }
  assert( r && "SwapBuffers() failed -- investigate");
}

void
Win32::UnregisterClass(LPCTSTR lpClassName,  // address of class name string
                       HINSTANCE hInstance   // handle of application instance
                       )
{
  BOOL r = ::UnregisterClass(lpClassName, hInstance);
  if (!r) { Win32::showLastErr(); }
  assert( r && "UnregisterClass() failed -- investigate");
}

void
Win32::DestroyWindow(HWND hWnd)      // handle to window or control
{
  BOOL r = ::DestroyWindow(hWnd);
  if (!r) { Win32::showLastErr(); }
  assert( r && "DestroyWindow() failed -- investigate");
}

void
Win32::SetWindowText(HWND hWnd,       // handle to window or control
                     LPCTSTR lpString)// address of string
{
  BOOL r = ::SetWindowText( hWnd, lpString );
  if (!r) { Win32::showLastErr(); }
  assert( r && "SetWindowText() failed -- investigate" );
}

void
Win32::InvalidateRect(HWND hWnd,     // handle of window with changed update region
           CONST RECT *lpRect,       // address of rectangle coordinates
           BOOL bErase)              // erase-background flag
{
  BOOL r = ::InvalidateRect(hWnd, lpRect, bErase);
  if (!r) { Win32::showLastErr(); }
  assert( r && "InvalidateRect() failed -- investigate" );
}

void
Win32::GetWindowRect(HWND hWnd,      // handle to window
                     LPRECT lpRect)  // address of structure for window coordinates
{
  BOOL r = ::GetWindowRect(hWnd, lpRect);
  if (!r) { Win32::showLastErr(); }  
  assert( r && "GetWindowRect() failed -- investigate" );
}

void
Win32::GetClientRect(HWND hWnd,      // handle to window
                     LPRECT lpRect)  // address of structure for window coordinates
{
  BOOL r = ::GetClientRect(hWnd, lpRect);
  if (!r) { Win32::showLastErr(); }  
  assert( r && "GetClientRect() failed -- investigate" );
}

LONG
Win32::SetWindowLong(HWND hWnd,       // handle of window
                     int nIndex,      // offset of value to set
                     LONG dwNewLong)  // new value
{
  SetLastError(0);
  LONG l = ::SetWindowLong(hWnd, nIndex, dwNewLong);
  BOOL failed = l==0 && ::GetLastError()!=0;
  if ( failed ) { Win32::showLastErr(); }  
  assert( !failed && "SetWindowLong() failed -- investigate" );
  return l;
}

LONG
Win32::GetWindowLong(HWND hWnd,       // handle of window
                     int nIndex)      // offset of value to set
{
  SetLastError(0);
  LONG l = ::GetWindowLong(hWnd, nIndex);
  BOOL failed = l==0 && ::GetLastError()!=0;
  if ( failed ) { Win32::showLastErr(); }  
  assert( !failed && "GetWindowLong() failed -- investigate" );
  return l;
}

void
Win32::SetWindowPos(HWND hWnd,    // handle to window
                    HWND hWndInsertAfter,  // placement-order handle
                    int X,                 // horizontal position
                    int Y,                 // vertical position
                    int cx,                // width
                    int cy,                // height
                    UINT uFlags)           // window-positioning flags

{
  BOOL r = ::SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
  if (!r) { Win32::showLastErr(); }  
  assert( r && "SetWindowPos() failed -- investigate" );
}

HHOOK
Win32::SetWindowsHookEx(int idHook,        // type of hook to install
                        HOOKPROC lpfn,     // address of hook procedure
                        HINSTANCE hMod,    // handle to application instance
                        DWORD dwThreadId)   // identity of thread to install hook for
{
  HHOOK h = ::SetWindowsHookEx(idHook, lpfn, hMod, dwThreadId );
  if (!h) { Win32::showLastErr(); }
  assert( h && "SetWindowsHookEx() failed -- investigate" );
  return h;
}
