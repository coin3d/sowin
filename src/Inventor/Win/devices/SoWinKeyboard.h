#ifndef  SO_WIN_KEYBOARD
#define  SO_WIN_KEYBOARD

//#include <Inventor/Win/SoWinBeginStrict.h>


#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/devices/SoWinDevice.h>
#include <Inventor/events/SoKeyboardEvent.h>

class SoWinKeyboard : public SoWinDevice {

    enum KeyboardEvents {
        KEY_PRESS = KeyPressMask, // 0x01,
        KEY_RELEASE = KeyReleaseMask, // 0x02,
        ALL_EVENTS = KEY_PRESS | KEY_RELEASE
    };

public:
    SoWinKeyboard(int mask = ALL_EVENTS);
    ~SoWinKeyboard();
    
    virtual void enable(HWND widget, LRESULT CALLBACK func, void * data, HWND window = NULL);
    virtual void  disable(HWND widget, LRESULT CALLBACK func, void * data);
    
    virtual const SoEvent * translateEvent(MSG * msg);
  
private:
    static void makeTranslationTable(void);
    
    EventMask events;
    SoKeyboardEvent * keyboardEvent;	// keyboard press or release
    SoKeyboardEvent	* makeKeyboardEvent(MSG * msg, SoButtonEvent::State s);

    // Mapping from WIN32 virtual keys to SoKeyboardEvent::Key enum
    static SbDict * translatetable;
    static int keyMapInitFlag;
};

#define SO_WIN_ALL_KEYBOARD_EVENTS SoWinKeyboard::ALL_EVENTS

#endif