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

#ifndef SOWIN_INPUTFOCUS_H
#define SOWIN_INPUTFOCUS_H

#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinDevice.h>

#define sowinEnterWindowMask 0x01
#define sowinLeaveWindowMask 0x02

#define SO_WIN_ALL_FOCUS_EVENTS (sowinEnterWindowMask | sowinLeaveWindowMask)

class SOWIN_DLL_EXPORT SoWinInputFocus : public SoWinDevice {
    typedef SoWinDevice inherited;

public:
    SoWinInputFocus(UINT mask = SO_WIN_ALL_FOCUS_EVENTS);
    virtual ~SoWinInputFocus(void);

    virtual void enable( HWND window, SoWinEventHandler * handler, void * closure );
    virtual void disable( HWND window, SoWinEventHandler * handler, void * closure );

    virtual const SoEvent * translateEvent( MSG * event );

private:
    UINT mask;
}; // class SoWinInputFocus

#endif // ! SOWIN_INPUTFOCUS_H
