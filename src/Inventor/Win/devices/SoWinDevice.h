#ifndef  SO_WIN_DEVICE
#define  SO_WIN_DEVICE

//#include <windows.h>
//#include <Inventor/Win/SoWinDef.h>
//#include <sowindefs.h>
#include <Inventor/Win/SoWinBasic.h>

#include <Inventor/SbLinear.h>
#include <Inventor/events/SoEvent.h>

#define EventMask UINT
#define ButtonPressMask   0x01
#define ButtonReleaseMask 0x02
#define PointerMotionMask 0x04
#define ButtonMotionMask  0x08
#define KeyPressMask      0x10
#define KeyReleaseMask    0x20

//#define SoWinEventHandlerPtr callbackfunction
#define SoWinEventHandlerPtr LRESULT CALLBACK

class SoWinDevice {
public:
    SoWinDevice( void );
    ~SoWinDevice( void );
    // these functions will enable/disable this device for the passed widget.
    // the callback function f will be invoked when events occur in w.
    // data is the clientData which will be passed.
    // For enable, the window is also passed, since GL widgets can have
    // more than one window (normal, overlay, popup)
    virtual void enable(HWND widget, LRESULT CALLBACK func, void * data, HWND window = NULL) = 0;
    virtual void disable(HWND widget, LRESULT CALLBACK func, void * data) = 0;
    
    virtual const SoEvent * translateEvent(MSG * msg) = 0;

    // set the window size so that the device can correctly convert X
    // window coordinates (origin at top,left) into Inventor window
    // coordinates (origin at bottom,left).
    void setWindowSize(const SbVec2s newSize);
    const SbVec2s getWindowSize( void ) const;

protected:
    // set the window coordinate from the passed x,y value. This will flip
    // the y value to convert from X coordinates to So coordinates.
    void setEventPosition(SoEvent *event, int x, int y) const;
    
private:
    SbVec2s size;
};

#endif