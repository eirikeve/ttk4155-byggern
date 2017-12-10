
// screenhandler.h
// 6/11/2017
#ifndef SCREENHANDLER_H
#define SCREENHANDLER_H
#include "screen.h"
#include "../timer/timer.h"

/**
 * ScreenHandler implements interrupt-based rendering and dual buffering to SRAM
 **/
class ScreenHandler
{

private:
    // We limit the number of screens in the handler to 5, to avoid using dynamic memory
    const uint8_t max_num_screens = 5; 
    // Current number of screens in the handler
    uint8_t num_screens;
    // Currently used SRAM buffer
    uint8_t* currentBuffer;
    // Array of screens in
    Screen * screens[5];

private:
    // Standard constructor
    ScreenHandler();
    // Renders the SRAM
    void _render();
    // Changes VRAM buffer for the screens in screenhandler.
    void _changeVRAMBuffer();
    // Clears ready_to_render flags for screens in the handler, usually not called!
    void _clearRenderFlags();

public:
    // Singleton implementation
    static ScreenHandler& getInstance()
    {
        static ScreenHandler instance;
        return instance;
    }

    // Deleted due to singleton design pattern
    ScreenHandler(ScreenHandler const&)    = delete;
    
    // Deleted due to singleton design pattern
    void operator=(ScreenHandler const&)  = delete;

    /**
     * Adds screen to the Handler if there is space. (max 4 screens in it already)
     * @param s: Screen object pointer
     **/
    void addScreen(Screen * s);

    /**
     * Removes that screen from the handler if it is in the array.
     * @param s:  Screen object pointer
     **/
    void removeScreen(Screen * s);

    // Number of screens currently in handler.
    uint8_t getNumScreens() const;

    /**
     * Returns a pointer to element # screen_index in the handler's array
     * @param screen_index: Element # in array
    **/
    Screen* getScreenPtr(uint8_t screen_index);

    /**
     * Returns true if at least one screen in the handler is ready to render
     **/
    bool isReadyToRender();
    
    /**
     * Called each interrupt to render the screens
     **/
    void _interruptHandlerRoutine();

};
/**
 * Calls _interruptHandlerRoutine
**/
void ScreenHandlerTimerInterrupt();



#endif