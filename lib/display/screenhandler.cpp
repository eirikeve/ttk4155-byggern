// screenhandler.cpp
// 6/11/2017

#include "screenhandler.h"

ScreenHandler::ScreenHandler()
{
    handler = this; // Flag that an instance exists
    num_screens = 0;
    array_size = 5;
    screens = (Screen**)calloc(array_size, sizeof(Screen*));
    currentBuffer = (uint8_t*)AVR_VRAM_1;
    Timer interruptTimer = Timer::getInstance(1);
    interruptTimer.initialize((uint16_t)(1000 / OLED_UPDATE_FPS), &_interruptHandlerRoutine, NULL);
    interruptTimer.start();
}
void ScreenHandler::render()
{
    if (num_screens > 0)
    {
        screens[0]->render(); // Renders the whole screen!
    }
}

void ScreenHandler::increaseArraySize()
{
    int new_size = array_size * 2;
    Screen  ** new_screens = (Screen**)calloc(new_size, sizeof(Screen*));
    for (uint8_t i = 0; i < num_screens; ++i)
    {
        new_screens[i] = screens[i];
    }
    // Might be a bug here! Need to check.
    free(screens);
    screens = new_screens;
    array_size = new_size;
    
}

void ScreenHandler::addScreenToArray(Screen * s)
{
    if (num_screens >= array_size)
    {
        increaseArraySize();
    }
    screens[num_screens] = s;
    ++num_screens;
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

ScreenHandler ScreenHandler::getInstance()
{
    if (handler)
    {
        return *handler;
    }
    else
    {
        ScreenHandler h = ScreenHandler();
        return h;
    }
}
void ScreenHandler::addMainScreen(Screen * s)
{
    addScreenToArray(s);
}
Screen ScreenHandler::createMainScreen()
{
    Screen s;
    addScreenToArray(&s);
    return s;
}

void ScreenHandler::addSubScreen(Screen * superscreen, Screen *subscreen, uint8_t sz, Orientation o)
{
    // Check if superscreen is in the handler. If not, do nothing!
    for (uint8_t i = 0; i < num_screens; ++i)
    {
        if (screens[i] == superscreen)
        {
            superscreen->addSubScreen(subscreen, sz, o);
            addScreenToArray(subscreen);
            return;
        }
    }
}
Screen ScreenHandler::createSubScreen(Screen *superscreen, uint8_t sz, Orientation o)
{
        // Check if superscreen is in the handler. If not, do nothing!
        for (uint8_t i = 0; i < num_screens; ++i)
        {
            if (screens[i] == superscreen)
            {
                Screen subscreen = Screen(superscreen, sz, o);
                addScreenToArray(&subscreen);
                return subscreen;
            }
        }
}
void ScreenHandler::removeScreen(Screen * s)
{
    if (s->hasSubScreen()){
        removeScreen(s->subScreen);
    }

    for (uint8_t i = 0; i < num_screens; ++i)
    {
        if (screens[i] == s)
        {
            s->~Screen();
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
        _interruptActionRoutine();
    }
}

void ScreenHandler::_interruptActionRoutine()
{
    _changeVRAMBuffer();
    render();
    _clearRenderFlags();
}