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

#include <Inventor/Win/Win32API.h>
#include <stdio.h>
#include <assert.h>
#include <tchar.h>
#include <strsafe.h>

// Returns the string and error code describing the cause of an
// internal Win32 API error.
SbString
Win32::getWin32Err(DWORD & lasterr)
{
  LPTSTR buffer;
  BOOL result;

  lasterr = ::GetLastError();
  result = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  lasterr,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPTSTR)&buffer,
                  0,
                  NULL);

  SbString s;
  if (result)
    s = buffer;
  else
    s.sprintf("*WIN32 ERROR* FormatMessage() failed! "
              "GetLastError() returned %lu [0x%lX]", lasterr, lasterr);

  if (result) { (void)::LocalFree(buffer); }
  return s;
 }

void
Win32::showLastErr(void)
{
  DWORD lasterr;
  SbString s = Win32::getWin32Err(lasterr);

  // Don't use fprintf(), as compiling in stdout or stderr file
  // descriptor pointer values is problematic when SoWin is built as a
  // DLL.
#ifndef NDEBUG
  (void)printf("\n*** GetLastError()==%d => %s\n", lasterr, s.getString());
#endif // NDEBUG
}

HWND
Win32::CreateWindow_(LPCTSTR lpClassName,  // pointer to registered class name
                     LPCTSTR lpWindowName, // pointer to window name
                     DWORD dwStyle,        // window style
                     int x,                // horizontal position of window
                     int y,                // vertical position of window
                     int nWidth,           // window width
                     int nHeight,          // window height
                     HWND hWndParent,      // handle to parent or owner window
                     HMENU hMenu,          // handle to menu or child-window identifier
                     HANDLE hInstance,     // handle to application instance
                     LPVOID lpParam        // pointer to window-creation data
                     )
{
  HWND hwnd = ::CreateWindow(lpClassName, lpWindowName, dwStyle, x, y,
                             nWidth, nHeight, hWndParent, hMenu,
                             // FIXME: ugly cast, get rid of it. 20020315 mortene.
                             (HINSTANCE__ *)hInstance, lpParam);
  if (hwnd == NULL) { Win32::showLastErr(); }
  assert((hwnd != NULL) && ::IsWindow(hwnd) && "CreateWindow() failed -- investigate");
  return hwnd;
}

HWND
Win32::CreateWindowEx_(DWORD dwExStyle,      // extended window style
                       LPCTSTR lpClassName,  // pointer to registered class name
                       LPCTSTR lpWindowName, // pointer to window name
                       DWORD dwStyle,        // window style
                       int x,                // horizontal position of window
                       int y,                // vertical position of window
                       int nWidth,           // window width
                       int nHeight,          // window height
                       HWND hWndParent,      // handle to parent or owner window
                       HMENU hMenu,          // handle to menu or child-window identifier
                       HANDLE hInstance,     // handle to application instance
                       LPVOID lpParam        // pointer to window-creation data
                       )
{
  HWND hwnd = ::CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle,
                               x, y, nWidth, nHeight, hWndParent, hMenu,
                               // FIXME: ugly cast, get rid of it. 20020315 mortene.
                               (HINSTANCE__ *)hInstance, lpParam);
  if (hwnd == NULL) { Win32::showLastErr(); }
  assert((hwnd != NULL) && ::IsWindow(hwnd) && "CreateWindowEx() failed -- investigate");
  return hwnd;
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
  BOOL r = ::MoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
  if (!r) { Win32::showLastErr(); }
  assert(r && "MoveWindow() failed -- investigate");
}

void
Win32::EnableWindow(HWND hWnd,     // handle to window
                    BOOL bEnable   // flag for enabling or disabling input
                   )
{
  BOOL enabled = ::IsWindowEnabled(hWnd);
  if (enabled && bEnable) { return; }
  if (!enabled && !bEnable) { return; }

  BOOL r = ::EnableWindow(hWnd, bEnable);
  BOOL fail = (!r && bEnable) || (r && !bEnable);
  if (fail) { Win32::showLastErr(); }
  assert(!fail && "EnableWindow() failed -- investigate");
}

void
Win32::GetTextExtentPoint(HDC hdc,           // handle to device context
                          LPCTSTR lpString,  // pointer to text string
                          int cbString,      // number of characters in string
                          LPSIZE lpSize      // pointer to structure for string size
                         )
{
  BOOL r = ::GetTextExtentPoint(hdc, lpString, cbString, lpSize);
  if (!r) { Win32::showLastErr(); }
  assert(r && "GetTextExtentPoint() failed -- investigate");
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
  BOOL r = ::BitBlt(hdcDest, nXDest, nYDest, nWidth, nHeight,
                     hdcSrc, nXSrc, nYSrc, dwRop);
  if (!r) { Win32::showLastErr(); }
  assert(r && "BitBlt() failed -- investigate");
}

HGDIOBJ
Win32::SelectObject(HDC hdc,          // handle to device context
                    HGDIOBJ hgdiobj   // handle to object
                   )
{
  HGDIOBJ o = ::SelectObject(hdc, hgdiobj);
  BOOL fail = ((o == NULL) || (o == HGDI_ERROR));
  assert(!fail && "SelectObject() failed -- investigate");
  return o;
}

void
Win32::DeleteObject(HGDIOBJ hObject   // handle to graphic object
                   )
{
  BOOL r = ::DeleteObject(hObject);
  if (!r) { Win32::showLastErr(); }
  assert(r && "DeleteObject() failed -- investigate");
}

HDC
Win32::GetDC(HWND hWnd   // handle to a window
            )
{
  HDC hdc = ::GetDC(hWnd);
  if (!hdc) { Win32::showLastErr(); }
  assert(hdc && "GetDC() failed -- investigate");
  return hdc;
}

void
Win32::DeleteDC(HDC hdc   // handle to device context
               )
{
  BOOL r = ::DeleteDC(hdc);
  if (!r) { Win32::showLastErr(); }
  assert(r && "DeleteDC() failed -- investigate");
}

void
Win32::ReleaseDC(HWND hWnd,  // handle to window
                 HDC hDC     // handle to device context
                )
{
  int r = ::ReleaseDC(hWnd, hDC);
  if (!r) { Win32::showLastErr(); }
  assert(r && "ReleaseDC() failed -- investigate");
}

HDC
Win32::BeginPaint(HWND hwnd,  // handle to window
                  LPPAINTSTRUCT lpPaint // pointer to structure for paint information
                 )
{
  HDC hdc = ::BeginPaint(hwnd, lpPaint);
  if (!hdc) { Win32::showLastErr(); }
  assert(hdc && "BeginPaint() failed -- investigate");
  return hdc;
}

void
Win32::EndPaint(HWND hWnd,  // handle to window
                CONST PAINTSTRUCT *lpPaint // pointer to structure for paint data
               )
{
  BOOL r = ::EndPaint(hWnd, lpPaint);
  if (!r) { Win32::showLastErr(); }
  assert(r && "EndPaint() failed -- investigate");
}
void
Win32::SwapBuffers(HDC hdc  // device context whose buffers get swapped
                  )
{
  BOOL r = ::SwapBuffers(hdc);
  if (!r) { Win32::showLastErr(); }
  assert(r && "SwapBuffers() failed -- investigate");
}

ATOM
Win32::RegisterClass(CONST WNDCLASS *lpWndClass   // address of structure with class
                                                  // data
                    )
{
  ATOM a = ::RegisterClass(lpWndClass);
  if (!a) { Win32::showLastErr(); }
  assert(a && "RegisterClass() failed -- investigate");
  return a;
}

void
Win32::UnregisterClass(LPCTSTR lpClassName,  // address of class name string
                       HINSTANCE hInstance   // handle of application instance
                      )
{
  BOOL r = ::UnregisterClass(lpClassName, hInstance);
  if (!r) { Win32::showLastErr(); }
  assert(r && "UnregisterClass() failed -- investigate");
}

void
Win32::DestroyWindow(HWND hWnd      // handle to window or control
                    )
{
  BOOL r = ::DestroyWindow(hWnd);
  if (!r) { Win32::showLastErr(); }
  assert(r && "DestroyWindow() failed -- investigate");
}

void
Win32::SetWindowText(HWND hWnd,       // handle to window or control
                     LPCTSTR lpString // address of string
                    )
{
  BOOL r = ::SetWindowText(hWnd, lpString);
  if (!r) { Win32::showLastErr(); }
  assert(r && "SetWindowText() failed -- investigate");
}

void
Win32::InvalidateRect(HWND hWnd,          // handle of window with changed update region
                      CONST RECT *lpRect, // address of rectangle coordinates
                      BOOL bErase         // erase-background flag
                     )
{
  BOOL r = ::InvalidateRect(hWnd, lpRect, bErase);
  if (!r) { Win32::showLastErr(); }
  assert(r && "InvalidateRect() failed -- investigate");
}

void
Win32::GetWindowRect(HWND hWnd,      // handle to window
                     LPRECT lpRect   // address of structure for window coordinates
                    )
{
  BOOL r = ::GetWindowRect(hWnd, lpRect);
  if (!r) { Win32::showLastErr(); }
  assert(r && "GetWindowRect() failed -- investigate");
}

void
Win32::GetClientRect(HWND hWnd,      // handle to window
                     LPRECT lpRect   // address of structure for window coordinates
                    )
{
  BOOL r = ::GetClientRect(hWnd, lpRect);
  if (!r) { Win32::showLastErr(); }
  assert(r && "GetClientRect() failed -- investigate");
}

// *************************************************************************

LONG_PTR
Win32::SetWindowLongPtr(HWND hWnd,       // handle of window
                        int nIndex,      // offset of value to set
                        LONG_PTR dwNewLong   // new value
                        )
{
  SetLastError(0);

#if HAVE_SETWINDOWLONGPTR // (MSVC 6 SDK doesn't have SetWindowLongPtr())
  LONG_PTR l = ::SetWindowLongPtr(hWnd, nIndex, dwNewLong);
#else // ! HAVE_SETWINDOWLONGPTR
  LONG_PTR l = ::SetWindowLong(hWnd, nIndex, dwNewLong);
#endif // ! HAVE_SETWINDOWLONGPTR

  BOOL failed = l==0 && ::GetLastError()!=0;
  if (failed) { Win32::showLastErr(); }
  assert(!failed && "SetWindowLongPtr() failed -- investigate");
  return l;
}

LONG_PTR
Win32::GetWindowLongPtr(HWND hWnd,       // handle of window
                        int nIndex       // offset of value to set
                        )
{
  SetLastError(0);

#if HAVE_SETWINDOWLONGPTR // (MSVC 6 SDK doesn't have Set/GetWindowLongPtr())
  LONG_PTR l = ::GetWindowLongPtr(hWnd, nIndex);
#else // ! HAVE_SETWINDOWLONGPTR
  LONG_PTR l = ::GetWindowLong(hWnd, nIndex);
#endif // ! HAVE_SETWINDOWLONGPTR

  BOOL failed = l==0 && ::GetLastError()!=0;
  if (failed) { Win32::showLastErr(); }
  assert(!failed && "GetWindowLongPtr() failed -- investigate");
  return l;
}

ULONG_PTR
Win32::SetClassLongPtr(HWND hWnd,       // handle of window
                       int nIndex,      // offset of value to set
                       LONG_PTR dwNewLong   // new value
                       )
{
  SetLastError(0);

#if HAVE_SETCLASSLONGPTR // (MingW doesn't have SetClassLongPtr())
  ULONG_PTR l = ::SetClassLongPtr(hWnd, nIndex, dwNewLong);
#else // ! HAVE_SETCLASSLONGPTR
  ULONG_PTR l = ::SetClassLong(hWnd, nIndex, dwNewLong);
#endif // ! HAVE_SETCLASSLONGPTR

  BOOL failed = l==0 && ::GetLastError()!=0;
  if (failed) { Win32::showLastErr(); }
  assert(!failed && "SetClassLongPtr() failed -- investigate");
  return l;
}

ULONG_PTR
Win32::GetClassLongPtr(HWND hWnd,       // handle of window
                       int nIndex       // offset of value to set
                       )
{
  SetLastError(0);

#if HAVE_SETCLASSLONGPTR // (MingW doesn't have Set/GetClassLongPtr())
  ULONG_PTR l = ::GetClassLongPtr(hWnd, nIndex);
#else // ! HAVE_SETCLASSLONGPTR
  ULONG_PTR l = ::GetClassLong(hWnd, nIndex);
#endif // ! HAVE_SETCLASSLONGPTR

  BOOL failed = l==0 && ::GetLastError()!=0;
  if (failed) { Win32::showLastErr(); }
  assert(!failed && "GetClassLongPtr() failed -- investigate");
  return l;
}

// *************************************************************************

void
Win32::SetWindowPos(HWND hWnd,             // handle to window
                    HWND hWndInsertAfter,  // placement-order handle
                    int X,                 // horizontal position
                    int Y,                 // vertical position
                    int cx,                // width
                    int cy,                // height
                    UINT uFlags            // window-positioning flags
                   )

{
  BOOL r = ::SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
  if (!r) { Win32::showLastErr(); }
  assert(r && "SetWindowPos() failed -- investigate");
}

HHOOK
Win32::SetWindowsHookEx(int idHook,        // type of hook to install
                        HOOKPROC lpfn,     // address of hook procedure
                        HINSTANCE hMod,    // handle to application instance
                        DWORD dwThreadId   // identity of thread to install hook for
                       )
{
  HHOOK h = ::SetWindowsHookEx(idHook, lpfn, hMod, dwThreadId);
  if (!h) { Win32::showLastErr(); }
  assert(h && "SetWindowsHookEx() failed -- investigate");
  return h;
}

void
Win32::UnhookWindowsHookEx(HHOOK hhk // handle to hook procedure to remove
                           )
{
  BOOL r = ::UnhookWindowsHookEx(hhk);
  if (!r) { Win32::showLastErr(); }
  assert(r && "UnhookWindowsHookEx() failed -- investigate");
}

void
Win32::ModifyMenu(HMENU hMnu,       // handle to menu
                  UINT uPosition,   // menu item to modify
                  UINT uFlags,      // menu item flags
                  UINT uIDNewItem,  // menu item identifier or handle to drop-down
                                    // menu or submenu
                  LPCTSTR lpNewItem // menu item content
                 )
{
  BOOL r = ::ModifyMenu(hMnu, uPosition, uFlags, uIDNewItem, lpNewItem);
  if (!r) { Win32::showLastErr(); }
  assert(r && "ModifyMenu() failed -- investigate");
}

void
Win32::EnableMenuItem(HMENU hMenu,         // handle to menu
                      UINT uIDEnableItem,  // menu item to enable, disable, or gray
                      UINT uEnable         // menu item flags
                     )
{
  BOOL r = ::EnableMenuItem(hMenu, uIDEnableItem, uEnable);
  BOOL failed = r == 0xFFFFFFFF;
  if (failed) { Win32::showLastErr(); }
  assert(!failed && "EnableMenuItem() failed -- investigate");
}

void
Win32::GetMenuItemInfo(HMENU hMenu,
                       UINT uItem,
                       BOOL fByPosition,
                       LPMENUITEMINFO lpmii
                      )
{
  BOOL r = ::GetMenuItemInfo(hMenu, uItem, fByPosition, lpmii);
  if (!r) { Win32::showLastErr(); }
  assert(r && "GetMenuItemInfo() failed -- investigate");
}

void
Win32::SetMenuItemInfo(HMENU hMenu,
                       UINT uItem,
                       BOOL fByPosition,
                       LPMENUITEMINFO lpmii
                      )
{
  BOOL r = ::SetMenuItemInfo(hMenu, uItem, fByPosition, lpmii);
  if (!r) { Win32::showLastErr(); }
  assert(r && "SetMenuItemInfo() failed -- investigate");
}

void
Win32::InsertMenuItem(HMENU hMenu,
                      UINT uItem,
                      BOOL fByPosition,
                      LPMENUITEMINFO lpmii
                     )
{
  BOOL r = ::InsertMenuItem(hMenu, uItem, fByPosition, lpmii);
  if (!r) { Win32::showLastErr(); }
  assert(r && "InsertMenuItem() failed -- investigate");
}

void
Win32::InsertMenu(HMENU hMenu,      // handle to menu
                  UINT uPosition,   // menu item that new menu item precedes
                  UINT uFlags,      // menu item flags
                  UINT uIDNewItem,  // menu item identifier or handle to drop-down
                                    // menu or submenu
                  LPCTSTR lpNewItem // menu item content
)
{
  BOOL r = ::InsertMenu(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem);
  if (!r) { Win32::showLastErr(); }
  assert(r && "InsertMenu() failed -- investigate");
}

void
Win32::RemoveMenu(HMENU hMenu,     // handle to menu
                  UINT uPosition,  // menu item identifier or position
                  UINT uFlags      // menu item flag
                  )
{
  BOOL r = ::RemoveMenu(hMenu, uPosition, uFlags);
  if (!r) { Win32::showLastErr(); }
  assert(r && "RemoveMenu() failed -- investigate");
}

DWORD
Win32::CheckMenuItem(HMENU hmenu,        // handle to menu
                     UINT uIDCheckItem,  // menu item to check or uncheck
                     UINT uCheck         // menu item flags
                     )
{
  DWORD r = ::CheckMenuItem(hmenu, uIDCheckItem, uCheck);
  if (r==0xFFFFFFFF) { Win32::showLastErr(); }
  assert(r!=0xFFFFFFFF && "CheckMenuItem() failed -- investigate");
  return r;
}

HCURSOR
Win32::CreateCursor(HINSTANCE hInst,         // handle to application instance
                    int xHotSpot,            // horizontal position of hot spot
                    int yHotSpot,            // vertical position of hot spot
                    int nWidth,              // cursor width
                    int nHeight,             // cursor height
                    CONST VOID *pvANDPlane,  // pointer to AND bitmask array
                    CONST VOID *pvXORPlane   // pointer to XOR bitmask array
                    )
{
  HCURSOR r = ::CreateCursor(hInst, xHotSpot, yHotSpot, nWidth, nHeight,
                             pvANDPlane, pvXORPlane);
  if (r == NULL) { Win32::showLastErr(); }
  assert(r != NULL && "CreateCursor() failed -- investigate");
  return r;
}

HCURSOR
Win32::LoadCursor(HINSTANCE hInstance,  // handle to application instance
                  LPCTSTR lpCursorName  // name string or cursor resource identifier
                  )
{
  HCURSOR r = ::LoadCursor(hInstance, lpCursorName);
  if (r == NULL) { Win32::showLastErr(); }
  assert(r != NULL && "LoadCursor() failed -- investigate");
  return r;
}

void
Win32::ClientToScreen(HWND hWnd,       // window handle for source coordinates
                      LPPOINT lpPoint  // pointer to structure containing screen coordinates
                      )
{
  BOOL r = ::ClientToScreen(hWnd, lpPoint);
  if (r == 0) { Win32::showLastErr(); }
  assert(r && "ClientToScreen() failed -- investigate");
}

HMENU
Win32::CreatePopupMenu(VOID)
{
  HMENU m = ::CreatePopupMenu();
  if (m == NULL) { Win32::showLastErr(); }
  assert(m && "CreatePopupMenu() failed -- investigate");
  return m;
}

void
Win32::DestroyMenu(HMENU hMenu)
{
  BOOL r = ::DestroyMenu(hMenu);
  if (!r) { Win32::showLastErr(); }
  assert(r && "DestroyMenu() failed -- investigate");
}

HWND
Win32::SetFocus(HWND hWnd)
{
  HWND h = ::SetFocus(hWnd);
  BOOL failed = h==NULL && ::GetLastError()!=0;
  if (failed) { Win32::showLastErr(); }
  assert(!failed && "SetFocus() failed -- investigate");
  return h;
}

UINT_PTR
Win32::SetTimer(HWND hWnd,
                UINT_PTR nIDEvent,
                UINT uElapse,
                TIMERPROC lpTimerFunc)
{
  UINT_PTR id = ::SetTimer(hWnd, nIDEvent, uElapse, lpTimerFunc);
  if (id == 0) { Win32::showLastErr(); }
  assert(id != 0 && "SetTimer() failed -- investigate");
  return id;
}

void
Win32::KillTimer(HWND hWnd, UINT_PTR uIDEvent)
{
  BOOL ret = ::KillTimer(hWnd, uIDEvent);
  if (ret == 0) { Win32::showLastErr(); }
  assert(ret != 0 && "KillTimer() failed -- investigate");
}

std::string
Win32::GetOSDisplayString()
{
   typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
   typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);

   static const unsigned int BUFSIZE=256;

   TCHAR pszOS[BUFSIZE];
   OSVERSIONINFOEX osvi;
   SYSTEM_INFO si;
   PGNSI pGNSI;
   PGPI pGPI;
   BOOL bOsVersionInfoEx;
   DWORD dwType;

   ZeroMemory(&si, sizeof(SYSTEM_INFO));
   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

   if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
      return "";


   std::string retVal;
   // Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.

   pGNSI = (PGNSI) GetProcAddress(
      GetModuleHandle(TEXT("kernel32.dll")),
      "GetNativeSystemInfo");
   if(NULL != pGNSI)
      pGNSI(&si);
   else GetSystemInfo(&si);

   if ( VER_PLATFORM_WIN32_NT==osvi.dwPlatformId &&
        osvi.dwMajorVersion > 4 )
   {
      StringCchCopy(pszOS, BUFSIZE, TEXT("Microsoft "));

      // Test for the specific product.

      if ( osvi.dwMajorVersion == 6 )
      {
         if( osvi.dwMinorVersion == 0 )
         {
            if( osvi.wProductType == VER_NT_WORKSTATION )
                StringCchCat(pszOS, BUFSIZE, TEXT("Windows Vista "));
            else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2008 " ));
         }

         if ( osvi.dwMinorVersion == 1 )
         {
            if( osvi.wProductType == VER_NT_WORKSTATION )
                StringCchCat(pszOS, BUFSIZE, TEXT("Windows 7 "));
            else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2008 R2 " ));
         }

         pGPI = (PGPI) GetProcAddress(
            GetModuleHandle(TEXT("kernel32.dll")),
            "GetProductInfo");

         pGPI( osvi.dwMajorVersion, osvi.dwMinorVersion, 0, 0, &dwType);

         switch( dwType )
         {
            case PRODUCT_ULTIMATE:
               StringCchCat(pszOS, BUFSIZE, TEXT("Ultimate Edition" ));
               break;
#ifdef PRODUCT_PROFESSIONAL
            case PRODUCT_PROFESSIONAL:
               StringCchCat(pszOS, BUFSIZE, TEXT("Professional" ));
               break;
#endif //PRODUCT_PROFESSIONAL
            case PRODUCT_HOME_PREMIUM:
               StringCchCat(pszOS, BUFSIZE, TEXT("Home Premium Edition" ));
               break;
            case PRODUCT_HOME_BASIC:
               StringCchCat(pszOS, BUFSIZE, TEXT("Home Basic Edition" ));
               break;
            case PRODUCT_ENTERPRISE:
               StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition" ));
               break;
            case PRODUCT_BUSINESS:
               StringCchCat(pszOS, BUFSIZE, TEXT("Business Edition" ));
               break;
            case PRODUCT_STARTER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Starter Edition" ));
               break;
            case PRODUCT_CLUSTER_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Cluster Server Edition" ));
               break;
            case PRODUCT_DATACENTER_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Datacenter Edition" ));
               break;
            case PRODUCT_DATACENTER_SERVER_CORE:
               StringCchCat(pszOS, BUFSIZE, TEXT("Datacenter Edition (core installation)" ));
               break;
            case PRODUCT_ENTERPRISE_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition" ));
               break;
            case PRODUCT_ENTERPRISE_SERVER_CORE:
               StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition (core installation)" ));
               break;
            case PRODUCT_ENTERPRISE_SERVER_IA64:
               StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition for Itanium-based Systems" ));
               break;
            case PRODUCT_SMALLBUSINESS_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Small Business Server" ));
               break;
            case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
               StringCchCat(pszOS, BUFSIZE, TEXT("Small Business Server Premium Edition" ));
               break;
            case PRODUCT_STANDARD_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Standard Edition" ));
               break;
            case PRODUCT_STANDARD_SERVER_CORE:
               StringCchCat(pszOS, BUFSIZE, TEXT("Standard Edition (core installation)" ));
               break;
            case PRODUCT_WEB_SERVER:
               StringCchCat(pszOS, BUFSIZE, TEXT("Web Server Edition" ));
               break;
         }
      }

      if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
      {
         if( GetSystemMetrics(SM_SERVERR2) )
            StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Server 2003 R2, "));
         else if ( osvi.wSuiteMask & VER_SUITE_STORAGE_SERVER )
            StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Storage Server 2003"));
#ifdef VER_SUITE_WH_SERVER
         else if ( osvi.wSuiteMask & VER_SUITE_WH_SERVER )
            StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Home Server"));
#endif //VER_SUITE_WH_SERVER
         else if( osvi.wProductType == VER_NT_WORKSTATION &&
                  si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
         {
            StringCchCat(pszOS, BUFSIZE, TEXT( "Windows XP Professional x64 Edition"));
         }
         else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2003, "));

         // Test for the server type.
         if ( osvi.wProductType != VER_NT_WORKSTATION )
         {
            if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_IA64 )
            {
                if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Edition for Itanium-based Systems" ));
                else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise Edition for Itanium-based Systems" ));
            }

            else if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
            {
                if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter x64 Edition" ));
                else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise x64 Edition" ));
                else StringCchCat(pszOS, BUFSIZE, TEXT( "Standard x64 Edition" ));
            }

            else
            {
                if ( osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Compute Cluster Edition" ));
                else if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Edition" ));
                else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise Edition" ));
                else if ( osvi.wSuiteMask & VER_SUITE_BLADE )
                   StringCchCat(pszOS, BUFSIZE, TEXT( "Web Edition" ));
                else StringCchCat(pszOS, BUFSIZE, TEXT( "Standard Edition" ));
            }
         }
      }

      if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
      {
         StringCchCat(pszOS, BUFSIZE, TEXT("Windows XP "));
         if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
            StringCchCat(pszOS, BUFSIZE, TEXT( "Home Edition" ));
         else StringCchCat(pszOS, BUFSIZE, TEXT( "Professional" ));
      }

      if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
      {
         StringCchCat(pszOS, BUFSIZE, TEXT("Windows 2000 "));

         if ( osvi.wProductType == VER_NT_WORKSTATION )
         {
            StringCchCat(pszOS, BUFSIZE, TEXT( "Professional" ));
         }
         else
         {
            if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
               StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Server" ));
            else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
               StringCchCat(pszOS, BUFSIZE, TEXT( "Advanced Server" ));
            else StringCchCat(pszOS, BUFSIZE, TEXT( "Server" ));
         }
      }

       // Include service pack (if any) and build number.

      if( _tcslen(osvi.szCSDVersion) > 0 )
      {
          StringCchCat(pszOS, BUFSIZE, TEXT(" ") );
          StringCchCat(pszOS, BUFSIZE, osvi.szCSDVersion);
      }

      TCHAR buf[80];

      StringCchPrintf( buf, 80, TEXT(" (build %d)"), osvi.dwBuildNumber);
      StringCchCat(pszOS, BUFSIZE, buf);

      if ( osvi.dwMajorVersion >= 6 )
      {
         if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
            StringCchCat(pszOS, BUFSIZE, TEXT( ", 64-bit" ));
         else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
            StringCchCat(pszOS, BUFSIZE, TEXT(", 32-bit"));
      }

      return pszOS;
   }

   else
   {
      printf( "This version of Windows is unknown to the build system.\n");
      return "UNKNOWN Windows";
   }
}
