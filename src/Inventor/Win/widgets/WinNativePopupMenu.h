#ifndef SOWIN_WINNATIVEPOPUPMENU_H
#define SOWIN_WINNATIVEPOPUPMENU_H

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
  ~WinNativePopupMenu(void);

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
