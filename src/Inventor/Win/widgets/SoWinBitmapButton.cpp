/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
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

#include <Inventor/lists/SbPList.h>
#include <Inventor/Win/widgets/SoWinBitmapButton.h>
#include <Inventor/Win/SoWin.h>
#include <sowindefs.h>
#include <Inventor/Win/Win32API.h>

#include <assert.h>
#include <stdio.h>


// *************************************************************************

class SoWinBitmapButtonP {
public:
  SoWinBitmapButtonP(SoWinBitmapButton * master)
  {
    this->owner = master;
    this->viewerCB = NULL;
    this->viewer = NULL;
    this->buttonWindow = NULL;
    this->depth = 0;
  }

  ~SoWinBitmapButtonP()
  {
    const int len = this->bitmapList.getLength();
    for (int i = 0; i < len; i++) { Win32::DeleteObject(this->bitmapList[i]); }
  }

  HWND buildWidget(HWND parent, RECT rect);
  HBITMAP createDIB(int width, int height, int bpp, void ** bits);
  HBITMAP parseXpm(const char ** xpm, int dibDepth = 24);
  static int axtoi(const char * str);

  HWND buttonWindow;
  SbPList bitmapList;
  int depth;

  bitmapButtonCB * viewerCB;
  SoWinFullViewer * viewer; // owner object pointer

private:
  SoWinBitmapButton * owner;
};

#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->owner)

// *************************************************************************

SoWinBitmapButton::SoWinBitmapButton(HWND parent,
                                     int x,
                                     int y,
                                     int width,
                                     int height,
                                     int depth,
                                     const char * name,
                                     void * bits)
{
  PRIVATE(this) = new SoWinBitmapButtonP(this);

  RECT rect = { x, y, width, height };
  PRIVATE(this)->buildWidget(parent, rect);

  PRIVATE(this)->depth = depth;

  if (bits != NULL) {
    this->addBitmap(width, height, depth, bits);
    this->setBitmap(0);
  }

}

SoWinBitmapButton::SoWinBitmapButton(HWND button)
{
  PRIVATE(this) = new SoWinBitmapButtonP(this);

  assert(IsWindow(button));

  char name[8];
  GetClassName(button, name, 8);
  assert(strcmp(name, "BUTTON") == 0);

  PRIVATE(this)->buttonWindow = button;
  HBITMAP bm = (HBITMAP)SendMessage(PRIVATE(this)->buttonWindow, BM_GETIMAGE,
                                    (WPARAM) IMAGE_BITMAP, 0);
  this->addBitmap(bm);
}

SoWinBitmapButton::~SoWinBitmapButton(void)
{
  delete PRIVATE(this);
}

SIZE
SoWinBitmapButton::sizeHint(void) const
{
  SIZE size = { 30, 30 };
  return size;
}

HWND
SoWinBitmapButton::getWidget(void)
{
  return PRIVATE(this)->buttonWindow;
}

int
SoWinBitmapButton::width(void)
{
  RECT rect;
  Win32::GetWindowRect(PRIVATE(this)->buttonWindow, & rect);
  return (rect.right - rect.left); //this->sizeHint().cx;
}

int
SoWinBitmapButton::height(void)
{
  RECT rect;
  Win32::GetWindowRect(PRIVATE(this)->buttonWindow, & rect);
  return (rect.bottom - rect.top); //this->sizeHint().cy;
}

void
SoWinBitmapButton::move(int x, int y)
{
  assert(IsWindow(PRIVATE(this)->buttonWindow));
  UINT flags = SWP_NOSIZE | SWP_NOZORDER;
  Win32::SetWindowPos(PRIVATE(this)->buttonWindow, NULL, x, y, 0, 0, flags);
}

void
SoWinBitmapButton::move(int x, int y, int width, int height)
{
  assert(IsWindow(PRIVATE(this)->buttonWindow));
  Win32::MoveWindow(PRIVATE(this)->buttonWindow, x, y, width, height, TRUE);
}

void
SoWinBitmapButton::size(int width, int height)
{
  assert(IsWindow(PRIVATE(this)->buttonWindow));
  UINT flags = SWP_NOMOVE | SWP_NOZORDER;// | SWP_NOREDRAW;
  Win32::SetWindowPos(PRIVATE(this)->buttonWindow, NULL, 0, 0, width, height, flags);
}

void
SoWinBitmapButton::show(void)
{
  (void)ShowWindow(PRIVATE(this)->buttonWindow, SW_SHOW);
}

void
SoWinBitmapButton::hide(void)
{
  (void)ShowWindow(PRIVATE(this)->buttonWindow, SW_HIDE);
}

void
SoWinBitmapButton::registerCallback(bitmapButtonCB * func)
{
  PRIVATE(this)->viewerCB = func;
}

void
SoWinBitmapButton::registerViewer(SoWinFullViewer * viewer)
{
  PRIVATE(this)->viewer = viewer;
}

HWND
SoWinBitmapButtonP::buildWidget(HWND parent, RECT rect)
{
  assert(IsWindow(parent));

  this->buttonWindow = Win32::CreateWindow_("BUTTON",
                                            NULL,
                                            WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS |
                                            BS_PUSHBUTTON | BS_BITMAP | BS_CENTER,
                                            rect.left, rect.top,
                                            rect.right, rect.bottom,
                                            parent,
                                            NULL,
                                            NULL,
                                            NULL);
  return this->buttonWindow;
}

void
SoWinBitmapButton::setId(long id)
{
  (void)Win32::SetWindowLong(PRIVATE(this)->buttonWindow, GWL_ID, id);
}

long
SoWinBitmapButton::getId(void)
{
  return Win32::GetWindowLong(PRIVATE(this)->buttonWindow, GWL_ID);
}

void
SoWinBitmapButton::setState(SbBool pushed)
{
 (void)SendMessage(PRIVATE(this)->buttonWindow, BM_SETSTATE, (WPARAM) pushed, 0);
}

SbBool
SoWinBitmapButton::getState(void) const
{
 return (SendMessage(PRIVATE(this)->buttonWindow, BM_GETSTATE, 0, 0) & BST_PUSHED);
}

void
SoWinBitmapButton::setEnabled(SbBool enable)
{
  Win32::EnableWindow(PRIVATE(this)->buttonWindow, enable);
}

SbBool
SoWinBitmapButton::isEnabled(void) const
{
  return (! (Win32::GetWindowLong(PRIVATE(this)->buttonWindow, GWL_STYLE) & WS_DISABLED));
}

void
SoWinBitmapButton::addBitmap(HBITMAP hbmp)
{
  PRIVATE(this)->bitmapList.append(hbmp);
}

void
SoWinBitmapButton::addBitmap(int width, int height, int bpp, void * src)
{
 void * dest;

 HBITMAP hbmp = PRIVATE(this)->createDIB(width, height, bpp, & dest);
 (void)memcpy(dest, src, width * height * (bpp / 8));
 this->addBitmap(hbmp);
}

void
SoWinBitmapButton::addBitmap(const char ** xpm)
{
  this->addBitmap(PRIVATE(this)->parseXpm(xpm, ((PRIVATE(this)->depth > 0) ? PRIVATE(this)->depth : 24)));
}

HBITMAP
SoWinBitmapButton::getBitmap(int index)
{
  return (HBITMAP) PRIVATE(this)->bitmapList[index];
}

void
SoWinBitmapButton::setBitmap(int index)
{
  assert(IsWindow(PRIVATE(this)->buttonWindow));

  (void)SendMessage(PRIVATE(this)->buttonWindow,
                    BM_SETIMAGE,
                    (WPARAM) IMAGE_BITMAP,
                    (LPARAM) this->getBitmap(index));

  Win32::InvalidateRect(PRIVATE(this)->buttonWindow, NULL, FALSE);
}

HBITMAP
SoWinBitmapButtonP::createDIB(int width, int height, int bpp, void ** bits) // 16||24||32 bpp
{
  assert(bpp > 8);

  HBITMAP bitmap = NULL;
  HDC hdc = CreateCompatibleDC(NULL);
  assert(hdc!=NULL && "CreateCompatibleDC() failed -- investigate");
  int heapspace = sizeof(BITMAPINFOHEADER);

  HANDLE heap = GetProcessHeap();
  BITMAPINFO * format = (BITMAPINFO *) HeapAlloc(heap, 0, heapspace);

  BITMAPINFOHEADER * header = (BITMAPINFOHEADER *) format;
  header->biSize = sizeof(BITMAPINFOHEADER);
  header->biWidth = width;
  header->biHeight = -height;
  header->biPlanes = 1;
  header->biBitCount = bpp;
  header->biCompression = BI_RGB;
  header->biSizeImage = 0;
  header->biXPelsPerMeter = 0;
  header->biYPelsPerMeter = 0;
  header->biClrUsed = 0;
  header->biClrImportant = 0;

  UINT flag = DIB_RGB_COLORS;
  bitmap = CreateDIBSection(hdc, format, flag, (void **) bits, NULL, 0);
  assert(* bits);

  HeapFree(heap, 0, format);
  Win32::DeleteDC(hdc);

  return bitmap;
}

// Convert from xpm to DIB (demands hex colors).
HBITMAP
SoWinBitmapButtonP::parseXpm(const char ** xpm, int dibdepth)
{
  unsigned char pixelsize = dibdepth / 8;

  int width, height, numcol, numchars;
  int nr = sscanf(xpm[0], "%d %d %d %d", &width, &height, &numcol, &numchars);
  assert((nr == 4) && "corrupt xpm?");

  // create color lookup table
  char * charlookuptable = new char[numcol * numchars];
  int * colorlookuptable = new int[numcol];

  // get colors
  int i;
  for (i = 0; i < numcol; i++) {

    int j;
    for (j = 0; j < numchars; j ++) {
      charlookuptable[(i * numchars) + j] = * (xpm[i + 1] + j);
    }

    // FIXME: make sure it is 'c '
    const char * strstart = strchr((xpm[i + 1] + numchars), 'c');

    const char * strend = strstart + 2;

    if (*strend == '#')
      colorlookuptable[i] = SoWinBitmapButtonP::axtoi(strend + 1);
    else
      colorlookuptable[i] = -1; // Parse string (color name)

  }

  // create bitmap
  void * dest;
  HBITMAP hbmp = this->createDIB(width, height, dibdepth, &dest);

  // put pixels
  for (i = 0; i < height; i++) {

    const char * line = xpm[i + 1 + numcol];

    int y = i * width * pixelsize;

    int j;
    for (j = 0; j < width; j++) {

      int x = j * pixelsize;

      // for every color
      int k;
      for (k = 0; k < numcol; k++) {

        int l;
        for (l = 0; l < numchars; l++)
          if (charlookuptable[(k * numchars) + l] != line[(j * numchars) + l])
            break;

        // if we found the char in the lookup table
        if (l >= numchars) {

          unsigned int colorvalue;
          if (colorlookuptable[k] == -1)
            colorvalue = GetSysColor(COLOR_3DFACE) & 0x00FFFFFF; // FIXME: color make param
          else
            colorvalue = colorlookuptable[k] | 0xFF000000;

          // FIXME: may not work with depth < 24
          // for each color byte in the pixel
          int m;
          for (m = 0; m < pixelsize; m++) {

            // put color byte (and only one byte)
            ((char *) dest)[y + x + m] =
              (char) ((colorvalue & (0x000000FF << (m << 3))) >> (m << 3));

          }

          // next pixel
          break;

        }

      }

    }

  }

  // cleanup
  delete charlookuptable;
  delete colorlookuptable;

  // return bitmap
  return hbmp;
}

int
SoWinBitmapButtonP::axtoi(const char * str) // convert from ASCII hex to int
{
  const char * c = str;
  int n = (strchr(c, '\0') - c);

  int x = 0;

  // convert n nibbles
  for (int i = 0; i < n; i++) {

    // numbers 0 - 9
    if ((c[i] > 0x2F) && (c[i] < 0x3A))
      x += ((c[i] - 0x30) << ((n - i - 1) * 4));

    // capital letters A - F
    if ((c[i] > 0x40) && (c[i] < 0x47))
      x += ((c[i] - 0x41 + 0x0A) << ((n - i - 1) * 4));

    // lower case letters a - f
    if ((c[i] > 0x60) && (c[i] < 0x67))
      x += ((c[i] - 0x61 + 0x0A) << ((n - i - 1) * 4));

  }

  return x;
}
