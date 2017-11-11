
// screenhandler.h
// 6/11/2017
#ifndef SCREENHANDLER_H
#define SCREENHANDLER_H
#include "screen.h"
#include "../timer/timer.h"

class ScreenHandler
{
// Private variables
private:
    uint8_t num_screens; // Number of screens in handler
    uint8_t array_size;
    uint8_t* currentBuffer;
    Screen ** screens;

// Public variables
public:

// Private methods
private:
    ScreenHandler();
    
    void _render();
    void _increaseArraySize();
    void _addScreenToArray(Screen * s);
    void _changeVRAMBuffer();
    void _clearRenderFlags();

// Public methods
public:

    static ScreenHandler& getInstance()
    {
        static ScreenHandler instance;
        return instance;
    }

    void addScreen(Screen * s);
    void removeScreen(Screen * s);
    uint8_t getNumScreens() const;
    Screen* getScreenPtr(uint8_t screen_index);
    bool isReadyToRender();
    
    void _interruptHandlerRoutine();

    // Deleted due to singleton design pattern
    ScreenHandler(ScreenHandler const&)    = delete;
    
    // Deleted due to singleton design pattern
    void operator=(ScreenHandler const&)  = delete;
};

void ScreenHandlerTimerInterrupt();



#endif