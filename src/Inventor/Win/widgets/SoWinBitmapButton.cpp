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

static const char rcsid[] =
"$Id$";

#include <Inventor/lists/SbPList.h>
#include <Inventor/Win/widgets/SoWinBitmapButton.h>
#include <Inventor/Win/SoWin.h>
#include <sowindefs.h>
#include <Inventor/Win/Win32API.h>

#include <assert.h>
#include <stdio.h>

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
  RECT rect = { x, y, width, height };

  this->constructor();
  this->buildWidget(parent, rect);

  this->depth = depth;

  if(bits != NULL) {
    this->addBitmap(width, height, depth, bits);
    this->setBitmap(0);
  }

} // SoWinBitmapButton()

SoWinBitmapButton::SoWinBitmapButton(HWND button)
{
 assert(IsWindow(button));

 char name[8];
 GetClassName(button, name, 8);
 assert(strcmp(name, "BUTTON") == 0);

 this->constructor();
 this->buttonWindow = button;
 this->addBitmap((HBITMAP) (
  SendMessage(this->buttonWindow, BM_GETIMAGE, (WPARAM) IMAGE_BITMAP, 0)
 ));
} // SoWinBitmapButton()

SoWinBitmapButton::~SoWinBitmapButton(void)
{
 // FIXME: cleanup resources
 this->destructor();
} // ~SoWinBitmapButton()

SIZE
SoWinBitmapButton::sizeHint(void) const
{
  SIZE size = { 30, 30 };
  return size;
} // sizeHint()

HWND
SoWinBitmapButton::getWidget(void)
{
  return this->buttonWindow;
}

int
SoWinBitmapButton::width(void)
{
  RECT rect;
  Win32::GetWindowRect(this->buttonWindow, & rect);
  return (rect.right - rect.left); //this->sizeHint().cx;
}

int
SoWinBitmapButton::height(void)
{
  RECT rect;
  Win32::GetWindowRect(this->buttonWindow, & rect);
  return (rect.bottom - rect.top); //this->sizeHint().cy;
}

void
SoWinBitmapButton::move(int x, int y)
{
  assert(IsWindow(this->buttonWindow));
  UINT flags = SWP_NOSIZE | SWP_NOZORDER;
  Win32::SetWindowPos(this->buttonWindow, NULL, x, y, 0, 0, flags);
}

void
SoWinBitmapButton::move(int x, int y, int width, int height)
{
  assert(IsWindow(this->buttonWindow));
  Win32::MoveWindow(this->buttonWindow, x, y, width, height, TRUE);
}

void
SoWinBitmapButton::size(int width, int height)
{
  assert(IsWindow(this->buttonWindow));
  UINT flags = SWP_NOMOVE | SWP_NOZORDER;// | SWP_NOREDRAW;
  Win32::SetWindowPos(this->buttonWindow, NULL, 0, 0, width, height, flags);
}

void
SoWinBitmapButton::show(void)
{
  (void)ShowWindow(this->buttonWindow, SW_SHOW);
}

void
SoWinBitmapButton::hide(void)
{
  (void)ShowWindow(this->buttonWindow, SW_HIDE);
}

void
SoWinBitmapButton::registerCallback(bitmapButtonCB * func)
{
  this->viewerCB = func;
}

void
SoWinBitmapButton::registerViewer(SoWinFullViewer * viewer)
{
  this->viewer = viewer;
}

void
SoWinBitmapButton::constructor(void)
{
  this->buttonWindow = NULL;
  this->viewerCB = NULL;
  this->viewer = NULL;
  this->bitmapList = new SbPList;
  this->depth = 0;
} // constructor()

void
SoWinBitmapButton::destructor(void)
{
  for (int i = this->bitmapList->getLength(); i >= 0; i--) {
    Win32::DeleteObject(this->bitmapList->get(i));
    this->bitmapList->remove(i);
  }
  delete this->bitmapList;
} // destructor()

HWND
SoWinBitmapButton::buildWidget(HWND parent, RECT rect)
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
                                            SoWin::getInstance(),
                                            NULL);

  return this->buttonWindow;
}

void
SoWinBitmapButton::setId(long id)
{
  (void)Win32::SetWindowLong(this->buttonWindow, GWL_ID, id);
}

long
SoWinBitmapButton::getId(void)
{
  return Win32::GetWindowLong(this->buttonWindow, GWL_ID);
}

void
SoWinBitmapButton::setState(SbBool pushed)
{
 (void)SendMessage(this->buttonWindow, BM_SETSTATE, (WPARAM) pushed, 0);
} // setState()

SbBool
SoWinBitmapButton::getState(void) const
{
 return (SendMessage(this->buttonWindow, BM_GETSTATE, 0, 0) & BST_PUSHED);
} // setState()

void
SoWinBitmapButton::setEnabled(SbBool enable)
{
  Win32::EnableWindow(this->buttonWindow, enable);
} // setEnabled()

SbBool
SoWinBitmapButton::isEnabled(void) const
{
  return (! (Win32::GetWindowLong(buttonWindow, GWL_STYLE) & WS_DISABLED));
} // isEnabled()

void
SoWinBitmapButton::addBitmap(HBITMAP hbmp)
{
 this->bitmapList->append(hbmp);
} // addBitmap()

void
SoWinBitmapButton::addBitmap(int width, int height, int bpp, void * src)
{
 void * dest;

 HBITMAP hbmp = this->createDIB(width, height, bpp, & dest);

 memcpy(dest, src, width * height * (bpp / 8));

 this->addBitmap(hbmp);

} // addBitmap()

void
SoWinBitmapButton::addBitmap(char ** xpm)
{
 this->addBitmap(this->parseXpm(xpm, ((this->depth > 0) ? this->depth : 24)));
} // addBitmap()

HBITMAP
SoWinBitmapButton::getBitmap(int index)
{
 return (HBITMAP) (* this->bitmapList)[index];
} // getBitmap()

void
SoWinBitmapButton::setBitmap(int index)
{
  assert(IsWindow(this->buttonWindow));

  (void)SendMessage(this->buttonWindow,
                     BM_SETIMAGE,
                     (WPARAM) IMAGE_BITMAP,
                     (LPARAM) this->getBitmap(index));

  Win32::InvalidateRect(this->buttonWindow, NULL, FALSE);
} // setBitmap()
/*
HBITMAP
SoWinBitmapButton::getCurrentBitmap(void) const
{
 assert(IsWindow(this->buttonWindow));

 return (HBITMAP) (SendMessage(this->buttonWindow, BM_GETIMAGE, (WPARAM) IMAGE_BITMAP, 0));
} // getCurrentBitmap()
*/
HBITMAP
SoWinBitmapButton::createDIB(int width, int height, int bpp, void ** bits) // 16||24||32 bpp
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
SoWinBitmapButton::parseXpm(char ** xpm, int dibdepth)
{
  unsigned char pixelsize = dibdepth / 8;

  // get width
  char * strstart = xpm[0];
  char * strend = strchr(strstart, ' ');
  assert(strend);
  *strend = '\0';
  int width = atoi(strstart);
  *strend = ' ';

  // get height
  strstart = strend + 1;
  strend = strchr(strstart, ' ');
  assert(strend);
  *strend = '\0';
  int height = atoi(strstart);
  *strend = ' ';

  // get number of colors
  strstart = strend + 1;
  strend = strchr(strstart, ' ');
  assert(strend);
  *strend = '\0';
  int numcol = atoi(strstart);
  *strend = ' ';

  // get number of chars per pixel
  strstart = strend + 1;
  strend = strchr(strstart, ' ');
  if (!strend) strend = strchr(strstart, '\0');
  assert(strend);
  *strend = '\0';
  int numchars = atoi(strstart);
  // * strend = ' '; FIXME

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
    strstart = strchr((xpm[i + 1] + numchars), 'c');

    strend = strstart + 2;

    if (*strend == '#')
      colorlookuptable[i] = axtoi(strend + 1);
    else
      colorlookuptable[i] = -1; // Parse string (color name)

  }

  // create bitmap
  void * dest;
  HBITMAP hbmp = this->createDIB(width, height, dibdepth, &dest);

  // put pixels
  for (i = 0; i < height; i++) {

    char * line = xpm[i + 1 + numcol];

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
SoWinBitmapButton::axtoi(char * str) // convert from ASCII hex to int
{
  char * c = str;
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
