#include "display.h"

Display::Display()
{
    this->bytes_x = 0;
    this->bytes_y = 0;
    this->x0 = 0;
    this->y0 = 0;
    screen = NULL;
}

Display::Display(uint8_t bytes_x, uint8_t bytes_y)
{
    this->bytes_x = bytes_x;
    this->bytes_y = bytes_y;
    this->x0 = 0;
    this->y0 = 0;

    // Allocate memory space for screen
    screen = (byte**)malloc(bytes_y * sizeof(byte*));
    for (uint8_t y = 0; y < bytes_y; ++y)
    {
        screen[y] = (byte*)malloc(bytes_x * sizeof(byte*));
    }
    Clr();
    
    return;
}


Display::~Display()
{
    if (screen != NULL)
    {
        // Free screen memory
        for (uint8_t y = 0; y < bytes_y; ++y)
        {
            free(screen[y]);
        }
        free(screen);
    }
    return;
}

void Display::Set(byte val, uint8_t x, uint8_t y)
{
    if (x < bytes_x && y < bytes_y)
    {
        screen[y0 + y][x0 + x] = val;
    }
}

void Display::Add(byte val, uint8_t x, uint8_t y)
{
    if (x < bytes_x && y < bytes_y)
    {
        screen[y0 + y][x0 + x] |= val;
    }
}

void Display::Mask(byte mask, uint8_t x, uint8_t y)
{
    if (x < bytes_x && y < bytes_y)
    {
        screen[y0 + y][x0 + x] &= mask;
    }
}

void Display::Clr(uint8_t x, uint8_t y)
{
    if (x < bytes_x && y < bytes_y)
    {
        screen[y0 + y][x0 + x] = 0;
    }
}

void Display::Clr()
{
    for (int y = 0; y < bytes_y; ++y)
    {
        for (int x = 0; x < bytes_x; ++x)
        {
            screen[y0 + y][x0 + x] = 0;
        }
    }
}

void Display::Draw(byte* p, uint8_t x, uint8_t y)
{
    if (x < bytes_x && y < bytes_y && screen != NULL)
    {
        *p = screen[y0 + y][x0 + x];
    }
}

void Display::Draw(byte ** p)
{
    if (screen != NULL)
    {
        for (uint8_t y = 0; y < bytes_y; ++y)
        {
            for (uint8_t x = 0; x < bytes_x; ++x)
            {
                // This will probably not work - but we'll see!
                // Might need to change x/y, or might not be possible at all.
                p[y0 + y][x0 + x] = screen[y0 + y][x0 + x];
            }
        }
    }
}


uint8_t Display::getMaxY()
{
    return bytes_y;
}
uint8_t Display::getMaxX()
{
    return bytes_x;
}

void Display::debugDisplay()
{
    #ifdef DEBUGDISPLAY
    for (uint8_t y = 0; y < bytes_y; ++y)
    {
        for (uint8_t x = 0; x < bytes_x; ++x)
        {

            std::cout << std::bitset<8>(screen[y0 + y][x0 + x]);
        }
        std::cout << std::endl;
    }
    #endif
}

void Display::testDeleteScreen()
{
    for (int y = 0; y < bytes_y; ++y)
    {
        std::cout << "y: " << y << std::endl;
        free(screen[y]);
    }
    std::cout << "screen**" << std::endl;
    free(screen);
    std::cout << "Deleted screen. It is now: " << screen << std::endl; 
}