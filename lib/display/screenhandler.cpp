// screenhandler.cpp
// 6/11/2017
#ifdef __AVR_ATmega162__
#include "screenhandler.h"

ScreenHandler::ScreenHandler()
{
    num_screens = 0;
    currentBuffer = (uint8_t*)AVR_VRAM_1;
    Timer& interruptTimer = Timer::getInstance(1);
    interruptTimer.initialize((uint16_t)(1000.0/OLED_UPDATE_FPS), &ScreenHandlerTimerInterrupt, NULL);
    interruptTimer.start();
}

void ScreenHandler::_render()
{
    if (num_screens > 0)
    {   uint8_t* otherBuffer = (uint8_t*)AVR_VRAM_1;
        if (otherBuffer == currentBuffer)
        {
            otherBuffer = (uint8_t*)AVR_VRAM_2;
        }
        screens[0]->render(otherBuffer); // Renders the whole screen!
    }
}





void ScreenHandler::_changeVRAMBuffer()
{
    if ((uint8_t*)AVR_VRAM_1 == currentBuffer)
    {
        currentBuffer = (uint8_t*)AVR_VRAM_2;
    }
    else
    {
        currentBuffer = (uint8_t*)AVR_VRAM_1;
    }
    for (uint8_t i = 0; i < num_screens; ++i)
    {
        screens[i]->changeBufferTo(currentBuffer);
        if (i == 0)
        {
            screens[0]->copyVRAMtoCurrentBuffer();
        }
    }
    
}

bool ScreenHandler::isReadyToRender()
{
    for (uint8_t i = 0; i < num_screens; ++i)
    {
        if (screens[i]->ready_to_render)
        {
            return true;
        }
    }
    return false;
}

void ScreenHandler::_clearRenderFlags()
{
    for (uint8_t i = 0; i < num_screens; ++i)
    {
        screens[i]->ready_to_render = false;
    }
}


void ScreenHandler::addScreen(Screen * s)
{
    for (uint8_t i = 0; i < num_screens; ++i)
    {
        if (screens[i] == s)
        {
            // Screen already added to handler, don't add again
            return;
        }
    }
    if (num_screens >= max_num_screens)
    {
        // Not room for more screens
        return; 
    }
    screens[num_screens] = s;
    ++num_screens;
}


void ScreenHandler::removeScreen(Screen * s)
{
    for (uint8_t i = 0; i < num_screens; ++i)
    {
        if (screens[i] == s)
        {
            for (int k = i; k < num_screens; ++k)
            {
                if (k == num_screens - 1)
                {
                    screens[k] = NULL;
                }
                else
                {
                    screens[k] = screens[k+1];
                }
            }
            num_screens--;
            return;
        }
    }
}

uint8_t ScreenHandler::getNumScreens() const
{
    return num_screens;
}

Screen * ScreenHandler::getScreenPtr(uint8_t screen_index)
{
    if (screen_index < num_screens && screen_index >= 0)
    {
        return screens[screen_index];
    }
    return NULL;
}


void ScreenHandler::_interruptHandlerRoutine()
{
    if (isReadyToRender()){
        _changeVRAMBuffer();
        _render();
        //_clearRenderFlags(); // Comment out this line (or the if check) to make the display always update when the interrupt is called
    }
}

void ScreenHandlerTimerInterrupt()
{
    ScreenHandler& h = ScreenHandler::getInstance();
    h._interruptHandlerRoutine();
}

#endif