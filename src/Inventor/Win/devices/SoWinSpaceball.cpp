#include <windows.h>

#if SOWIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOWIN_DEBUG

#include <Inventor/misc/SoBasic.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>

#include <sowindefs.h>
#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinSpaceball.h>


SoWinSpaceball::SoWinSpaceball( UINT mask )
{
    // FIXME: function not implemented
}

SoWinSpaceball::~SoWinSpaceball( void )
{
    // FIXME: function not implemented
}
    
void
SoWinSpaceball::enable( HWND, SoWinEventHandler * , void *, HWND )
{
    // FIXME: function not implemented
}

void
SoWinSpaceball::disable( HWND, SoWinEventHandler * , void * )
{
    // FIXME: function not implemented
}

const SoEvent * SoWinSpaceball::translateEvent( MSG * msg )
{
    // FIXME: function not implemented
    return ( SoEvent * ) NULL;
}
  
void SoWinSpaceball::setRotationScaleFactor( float factor )
{
    this->rotScale = factor;
}

float SoWinSpaceball::getRotationScaleFactor( void ) const
{
    return rotScale;
}

void SoWinSpaceball::setTranslationScaleFactor( float factor )
{
    this->transScale = factor;
}

float SoWinSpaceball::getTranslationScaleFactor( void ) const
{
    return this->transScale;
}

SbBool SoWinSpaceball::exists( void )
{
    // FIXME: function not implemented
    return FALSE;
}
 
void SoWinSpaceball::setFocusToWindow( SbBool flag )
{
    // FIXME: function not implemented
}

SbBool SoWinSpaceball::isFocusToWindow( void ) const
{
    // FIXME: function not implemented
    return 0;
}