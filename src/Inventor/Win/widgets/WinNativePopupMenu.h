#ifndef SOWIN_WINNATIVEPOPUPMENU_H
#define SOWIN_WINNATIVEPOPUPMENU_H

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

#ifndef SOWIN_INTERNAL
#error this is a private header file
#endif /* !SOWIN_INTERNAL */

#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/widgets/SoWinPopupMenu.h>

// *************************************************************************

struct MenuRecord;
struct ItemRecord;

class SOWIN_DLL_API WinNativePopupMenu : public SoWinPopupMenu {
  typedef SoWinPopupMenu inherited;

public:
  WinNativePopupMenu(void);
  virtual ~WinNativePopupMenu(void);

  virtual int newMenu(const char * name, int menuid = -1);
  virtual int getMenu(const char * name);
  virtual void setMenuTitle(int id, const char * title);
  virtual const char * getMenuTitle(int id);

  virtual int newMenuItem(const char * name, int itemid = -1);
  virtual int getMenuItem(const char * name);
  virtual void setMenuItemTitle(int itemid, const char * title);
  virtual const char * getMenuItemTitle(int itemid);
  virtual void setMenuItemEnabled(int itemid, SbBool enabled);
  virtual SbBool getMenuItemEnabled(int itemid);
  virtual SbBool getMenuItemMarked(int itemid);

  virtual void addMenu(int menuid, int submenuid, int pos = -1);
  virtual void addMenuItem(int menuid, int itemid, int pos = -1);
  virtual void addSeparator(int menuid, int pos = -1);
  virtual void removeMenu(int menuid);
  virtual void removeMenuItem(int itemid);

  virtual void popUp(HWND inside, int x, int y);

  virtual int getSelectedItem(void);

  void setNotify(SbBool enable);

protected:
  virtual void _setMenuItemMarked(int itemid, SbBool marked);
  MenuRecord * getMenuRecord(int menuid);
  ItemRecord * getItemRecord(int itemid);
  MenuRecord * createMenuRecord(const char * name);
  ItemRecord * createItemRecord(const char * name);

private:
  SbPList * menus;
  SbPList * items;
  SbBool notify;

  int selectedItem;
};  // class WinNativePopupMenu

// *************************************************************************

#endif // ! SOWIN_WINNATIVEPOPUPMENU_H
