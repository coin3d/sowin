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

#include <windows.h>

#include <Inventor/SoLists.h>
#include <Inventor/errors/SoDebugError.h>

#include <sowindefs.h>
#include <Inventor/Win/widgets/SoWinPopupMenu.h>

/*!
  \class SoWinPopupMenu Inventor/Win/widgets/SoWinPopupMenu.h
  \brief The SoWinPopupMenu class implements a common interface for popup
  menu management for all the Coin GUI toolkit libraries.
*/

// *************************************************************************

struct MenuRecord {
  int menuid;
  char * name;
  char * title;
  HMENU menu;
  HMENU parent;
}; // struct MenuRecord

struct ItemRecord {
  int itemid;
  int flags;
  char * name;
  char * title;
  HMENU parent;
}; // struct ItemRecord

#define ITEM_TOGGLE       0x0001
#define ITEM_MARKED       0x0002
#define ITEM_SEPARATOR    0x0004
#define ITEM_ENABLED      0x0008

// *************************************************************************

SoWinPopupMenu::SoWinPopupMenu( void )
{
  this->menus = new SbPList;
  this->items = new SbPList;

  this->notify = FALSE;
  this->selectedItem = -1;
} // SoWinPopupMenu()

SoWinPopupMenu::~SoWinPopupMenu( void )
{
  const int numMenus = this->menus->getLength();
  HMENU popup = NULL;
  int i;
  for ( i = 0; i < numMenus; i++ ) {
    MenuRecord * rec = ( MenuRecord * ) ( * this->menus )[i];
    if ( rec->menuid == 0 ) popup = rec->menu;
    delete [] rec->name;
    delete [] rec->title;
    if ( rec->parent == NULL ) delete rec->menu; // menu not attached
    delete rec;
  }

  const int numItems = this->items->getLength( );
  for ( i = 0; i < numItems; i++ ) {
    ItemRecord * rec = ( ItemRecord * ) ( * this->items )[i];
    delete [] rec->name;
    delete [] rec->title;
    delete rec;
  }

  // delete root popup menu
  delete popup;
} // ~SoWinPopupMenu()

// *************************************************************************

int
SoWinPopupMenu::newMenu( char * name, int menuid )
{
  int id = menuid;
  if ( id == -1 ) {
    id = 1;
    while ( this->getMenuRecord( id ) != NULL ) id++;
  } else {
    if ( this->getMenuRecord( id ) != NULL ) {
#if SOWIN_DEBUG
      SoDebugError::postInfo( "SoWinPopupMenu::NewMenu",
                              "requested menuid already taken" );
#endif // SOWIN_DEBUG
      return -1;
    }
  }
  // id contains ok ID
  MenuRecord * rec = createMenuRecord( name );
  rec->menuid = id;
  this->menus->append( ( void * ) rec );
  return id;
} // newMenu()

int
SoWinPopupMenu::getMenu( char * name )
{
  const int numMenus = this->menus->getLength();
  int i;
  for ( i = 0; i < numMenus; i++ )
    if ( strcmp( ( ( MenuRecord * ) ( * this->menus )[i] )->name, name ) == 0 )
      return ( ( MenuRecord * ) ( * this->menus )[i] )->menuid;
  return -1;
} // getMenu()

void
SoWinPopupMenu::setMenuTitle( int menuid, char * title )
{
  MenuRecord * rec = this->getMenuRecord( menuid );
  if ( rec == NULL ) {
    SoDebugError::postWarning( "SoWinPopupMenu::setMenuTitle",
                               "no such menu (%d.title = \"%s\")", menuid, title );
    return;
  }
  delete [] rec->title;
  rec->title = strcpy( new char [strlen(title)+1], title );

  if ( rec->parent )
    ModifyMenu( rec->parent, rec->menuid, MF_BYPOSITION | MF_STRING, rec->menuid, rec->title );
  //rec->parent->changeItem( rec->title, rec->menuid );

} // setMenuTitle()

char *
SoWinPopupMenu::getMenuTitle( int menuid )
{
  MenuRecord * rec = this->getMenuRecord( menuid );
  if ( rec == NULL )
    return NULL;
  return rec->title;
} // getMenuTitle()

// *************************************************************************

int
SoWinPopupMenu::newMenuItem( char * name, int itemid )
{
  int id = itemid;
  if ( id == -1 ) {
    id = 1;
    while ( this->getItemRecord( itemid ) != NULL ) id++;
  } else {
    if ( this->getItemRecord( itemid ) != NULL ) {
#if SOWIN_DEBUG
      SoDebugError::postInfo( "SoWinPopupMenu::newMenuItem",
                              "requested itemid already taken" );
#endif // SOWIN_DEBUG
      return -1;
    }
  }
  ItemRecord * rec = createItemRecord( name );
  rec->itemid = id;
  this->items->append( rec );
  return id;
} // newMenuItem()

int
SoWinPopupMenu::getMenuItem( char * name )
{
  const int numItems = this->items->getLength( );
  int i;
  for ( i = 0; i < numItems; i++ )
    if ( strcmp( ( ( ItemRecord * ) ( * this->items)[i] )->name, name ) == 0 )
      return ( ( ItemRecord * ) ( * this->items)[i] )->itemid;
  return -1;
} // getMenuItem()

void
SoWinPopupMenu::setMenuItemTitle( int itemid, char * title )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL )
    return;
  delete [] rec->title;
  rec->title = strcpy( new char [strlen(title)+1], title );

  if ( rec->parent )
    ModifyMenu( rec->parent, rec->itemid, MF_BYCOMMAND | MF_STRING, rec->itemid, rec->title );
} // setMenuItemTitle()

char *
SoWinPopupMenu::getMenuItemTitle( int itemid )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL ) return NULL;
  return rec->title;
} // getMenuItemTitle()

void
SoWinPopupMenu::setMenuItemEnabled( int itemid, SbBool enabled )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL )
    return;
  
	if ( enabled )
		rec->flags |= ITEM_ENABLED;
	else
		rec->flags &= ~ITEM_ENABLED;

	EnableMenuItem( rec->parent, rec->itemid, MF_BYCOMMAND | ( enabled ? MF_ENABLED : MF_GRAYED ) );
} // setMenuItemEnabled()

SbBool
SoWinPopupMenu::getMenuItemEnabled( int itemid )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  /*
  if ( rec == NULL )
    return FALSE;
  */
  assert( rec != NULL );
  assert( IsMenu( rec->parent ) );

  //MENUITEMINFO  menuiteminfo;
  //memset( ( void * ) & menuiteminfo, 0, sizeof( menuiteminfo ) );
  //GetMenuItemInfo( rec->parent, rec->itemid, TRUE, & menuiteminfo );
  //return ( menuiteminfo.fState & MFS_ENABLED ) ? TRUE : FALSE;
	
	return ( rec->flags & ITEM_ENABLED ? TRUE : FALSE );
} // getMenuItemEnabled()

void
SoWinPopupMenu::_setMenuItemMarked( int itemid, SbBool marked )
{
  ItemRecord * rec = this->getItemRecord( itemid );

  assert( rec != NULL );
  assert( IsMenu( rec->parent ) );

  rec->flags |= ITEM_TOGGLE;

  MENUITEMINFO info;
  
  info.cbSize = sizeof( MENUITEMINFO );
  info.fMask = MIIM_STATE;
  
  if ( marked ) {
    rec->flags |= ITEM_MARKED;
    info.fState = MFS_CHECKED;
  }
  else {
    rec->flags &= ~ITEM_MARKED;    
    info.fState = MFS_UNCHECKED;
  }
  
  SetMenuItemInfo( rec->parent, rec->itemid, FALSE, & info );

} // setMenuItemMarked()

SbBool
SoWinPopupMenu::getMenuItemMarked( int itemid )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  assert( rec != NULL );
  assert( rec->parent != NULL );
  
  MENUITEMINFO info;

  info.cbSize = sizeof( MENUITEMINFO );
  info.fMask = MIIM_STATE;
  
  GetMenuItemInfo( rec->parent, rec->itemid, FALSE, & info );

  return ( info.fState & MFS_CHECKED ? TRUE : FALSE );
} // getMenuItemMarked()

// *************************************************************************

void
SoWinPopupMenu::addMenu( int menuid, int submenuid, int pos )
{
  MenuRecord * super = this->getMenuRecord( menuid );
  MenuRecord * sub = this->getMenuRecord( submenuid );
  if ( super == NULL || sub == NULL ) {
#if SOWIN_DEBUG
    SoDebugError::postInfo( "SoWinPopupMenu::addMenu",
                            "no such menu (super = 0x%08x, sub = 0x%08x)", super, sub );
#endif // SOWIN_DEBUG
    return;
  }

  MENUITEMINFO menuiteminfo;
  memset( ( void * ) & menuiteminfo, 0, sizeof( menuiteminfo ) );
  menuiteminfo.cbSize = sizeof( menuiteminfo );
  menuiteminfo.fMask = MIIM_SUBMENU | MIIM_TYPE;
  menuiteminfo.fType = MFT_STRING;
  menuiteminfo.hSubMenu = sub->menu;
  menuiteminfo.dwTypeData = sub->title;
  menuiteminfo.cch = strlen( sub->title );

  if ( pos == -1 )
    InsertMenuItem( super->menu, sub->menuid, FALSE, & menuiteminfo );
  else
    InsertMenuItem( super->menu, pos, TRUE, & menuiteminfo );
  sub->parent = super->menu;
} // addMenu()

void
SoWinPopupMenu::addMenuItem( int menuid, int itemid, int pos )
{
  MenuRecord * menu = this->getMenuRecord( menuid );
  ItemRecord * item = this->getItemRecord( itemid );
  if ( menu == NULL || item == NULL ) {
#if SOWIN_DEBUG
    SoDebugError::postInfo( "SoWinPopupMenu::addMenuItem",
                            "no such item (menu = 0x%08x, item = 0x%08x)", menu, item );
#endif // SOWIN_DEBUG
    return;
  }

  InsertMenu( menu->menu, pos, MF_BYPOSITION | MF_STRING, item->itemid, item->title );

  item->parent = menu->menu;
  if ( item->flags & ITEM_MARKED )
    CheckMenuItem( item->parent, item->itemid, MF_BYCOMMAND | MF_CHECKED );
} // addMenuItem()

void
SoWinPopupMenu::addSeparator( int menuid, int pos )
{
  MenuRecord * menu = this->getMenuRecord( menuid );
  if ( menu == NULL ) {
    SoDebugError::postWarning( "SoWinPopupMenu::addSeparator",
                               "no such menu (%d)", menuid );
    return;
  }
  ItemRecord * rec = createItemRecord( "separator" );
	
  InsertMenu( menu->menu, pos, MF_BYPOSITION | MF_SEPARATOR, pos, NULL );
  rec->flags |= ITEM_SEPARATOR;
  this->items->append( rec );
} // addSeparator()

void
SoWinPopupMenu::removeMenu( int menuid )
{
  MenuRecord * rec = this->getMenuRecord( menuid );
  if ( rec == NULL ) {
#if SOWIN_DEBUG
    SoDebugError::postInfo( "SoWinPopupMenu::removeMenu", "no such menu" );
#endif // SOWIN_DEBUG
    return;
  }
  if ( rec->menuid == 0 ) {
#if SOWIN_DEBUG
    SoDebugError::postInfo( "SoWinPopupMenu::removeMenu", "can't remove root" );
#endif // SOWIN_DEBUG
    return;
  }
  if ( rec->parent == NULL ) {
#if SOWIN_DEBUG
    SoDebugError::postInfo( "SoWinPopupMenu::removeMenu", "menu not attached" );
#endif // SOWIN_DEBUG
    return;
  }
  ::RemoveMenu( rec->menu, rec->menuid, MF_BYCOMMAND );
  rec->parent = NULL;
} // removeMenu()

void
SoWinPopupMenu::removeMenuItem( int itemid )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL ) {
#if SOWIN_DEBUG
    SoDebugError::postInfo( "SoWinPopupMenu::removeMenuItem", "no such item" );
#endif // SOWIN_DEBUG
    return;
  }
  if ( rec->parent == NULL ) {
#if SOWIN_DEBUG
    SoDebugError::postInfo( "SoWinPopupMenu::removeMenuItem", "item not attached" );
#endif // SOWIN_DEBUG
    return;
  }
  ::RemoveMenu( rec->parent, rec->itemid, MF_BYCOMMAND );
  rec->parent = NULL;
} // removeMenuItem()

// *************************************************************************

void
SoWinPopupMenu::popUp( HWND inside, int x, int y )
{
  MenuRecord * menurec = this->getMenuRecord( 0 );
  this->selectedItem = TrackPopupMenu( menurec->menu,
                                       TPM_LEFTALIGN |
                                       TPM_TOPALIGN |
                                       TPM_RIGHTBUTTON |
                                       TPM_RETURNCMD |
                                       ( this->notify ? 0 : TPM_NONOTIFY ),
                                       x,
                                       y,
                                       0,
                                       inside,
                                       NULL );

  if ( this->selectedItem == 0 )
    return;
  
  ItemRecord * itemrec = this->getItemRecord( this->selectedItem );
  assert( itemrec != NULL );
  
} // popUp()

int
SoWinPopupMenu::getSelectedItem( void )
{
	return ( this->selectedItem );
} // getSelectedItem()

void
SoWinPopupMenu::setNotify( SbBool enable )
{
	this->notify = enable;
} // setNotify()

// *************************************************************************

MenuRecord *
SoWinPopupMenu::getMenuRecord( int menuid )
{
  const int numMenus = this->menus->getLength( );
  int i;
  for ( i = 0; i < numMenus; i++ )
    if ( ( ( MenuRecord *) ( * this->menus)[i] )->menuid == menuid )
      return ( MenuRecord * ) ( * this->menus )[i];
  return ( MenuRecord * ) NULL;
} // getMenuRecord()

ItemRecord *
SoWinPopupMenu::getItemRecord( int itemid )
{
  const int numItems = this->items->getLength( );
  int i;
	
  for ( i = 0; i < numItems; i++ )
    if ( ( ( ItemRecord * ) ( * this->items)[i] )->itemid == itemid )
      return ( ItemRecord * ) ( * this->items)[i];

  return ( ItemRecord * ) NULL;
} // getItemRecord()

// *************************************************************************

MenuRecord *
SoWinPopupMenu::createMenuRecord( char * name )
{
  MenuRecord * rec = new MenuRecord;
  rec->menuid = -1;
  rec->name = strcpy( new char [strlen( name ) + 1], name );
  rec->title = strcpy( new char [strlen( name ) + 1], name );
  rec->menu = CreatePopupMenu( );
  rec->parent = NULL;
  return rec;
} // create()

ItemRecord *
SoWinPopupMenu::createItemRecord( char * name )
{
  ItemRecord * rec = new ItemRecord;
  rec->itemid = -1;
  rec->flags = 0;
  rec->name = strcpy( new char [strlen( name ) + 1], name );
  rec->title = strcpy( new char [strlen( name ) + 1], name );
  rec->parent = NULL;
  return rec;
} // create()

// *************************************************************************

void
SoWinPopupMenu::itemActivation( int itemid )
{
  inherited::invokeMenuSelection( itemid );
} // menuSelection()

// *************************************************************************
