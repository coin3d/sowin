/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

//  $Id$

#ifndef SOWIN_POPUPMENU_H
#define SOWIN_POPUPMENU_H

#include <Inventor/Win/SoWinBasic.h>

#include <Inventor/Win/widgets/SoAnyPopupMenu.h>

// *************************************************************************

struct MenuRecord;
struct ItemRecord;

class SoWinPopupMenu : public SoAnyPopupMenu
{
  typedef SoAnyPopupMenu inherited;

public:
  SoWinPopupMenu( void );
  ~SoWinPopupMenu( void );

  virtual int newMenu( char * name, int menuid = -1 );
  virtual int getMenu( char * name );
  virtual void setMenuTitle( int id, char * title );
  virtual char * getMenuTitle( int id );

  virtual int newMenuItem( char * name, int itemid = -1 );
  virtual int getMenuItem( char * name );
  virtual void setMenuItemTitle( int itemid, char * title );
  virtual char * getMenuItemTitle( int itemid );
  virtual void setMenuItemEnabled( int itemid, SbBool enabled );
  virtual SbBool getMenuItemEnabled( int itemid );
  virtual SbBool getMenuItemMarked( int itemid );

  virtual void addMenu( int menuid, int submenuid, int pos = -1 );
  virtual void addMenuItem( int menuid, int itemid, int pos = -1 );
  virtual void addSeparator( int menuid, int pos = -1 );
  virtual void removeMenu( int menuid );
  virtual void removeMenuItem( int itemid );

  virtual void popUp( HWND inside, int x, int y );

  virtual void itemActivation( int itemid );    // call this on WM_COMMAND

protected:
  virtual void _setMenuItemMarked( int itemid, SbBool marked );
  MenuRecord * getMenuRecord( int menuid );
  ItemRecord * getItemRecord( int itemid );
  MenuRecord * createMenuRecord( char * name );
  ItemRecord * createItemRecord( char * name );

private:
  SbPList * menus;
  SbPList * items;

};  // class SoWinPopupMenu

// *************************************************************************

#endif // ! SOWIN_POPUPMENU_H
