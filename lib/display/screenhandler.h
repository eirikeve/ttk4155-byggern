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
    static ScreenHandler * handler;
    uint8_t num_screens; // Number of screens in handler
    uint8_t array_size;
    uint8_t* currentBuffer;
    Screen ** screens;

// Public variables
public:

// Private methods
private:
    ScreenHandler();
    void render();
    void increaseArraySize();
    void addScreenToArray(Screen * s);
    void _changeVRAMBuffer();
    void _clearRenderFlags();
    void _interruptActionRoutine();
    void _interruptHandlerRoutine();

// Public methods
public:
    static ScreenHandler getInstance();
    void addMainScreen(Screen * s);
    Screen createMainScreen();
    void addSubScreen(Screen * superscreen, Screen *subscreen, uint8_t sz, Orientation o);
    Screen createSubScreen(Screen *superscreen, uint8_t sz, Orientation o);
    void removeScreen(Screen * s);
    uint8_t getNumScreens() const;
    Screen* getScreenPtr(uint8_t screen_index);
    bool isReadyToRender();
    

};

#endif