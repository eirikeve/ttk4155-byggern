#pragma once
#define DEBUGDISPLAY
#ifdef  DEBUGDISPLAY
#include <iostream>
#include <bitset>
#endif


#include <stdlib.h>
#include <stdint.h>
#define NULL 0
typedef unsigned char byte;





class Display
{
protected:

    uint8_t x0 = 0;
    uint8_t y0 = 0;

    uint8_t bytes_x;
    uint8_t bytes_y;

    // Pixel data, each screen[y][x] is a byte (8 pixels)
    byte ** screen = NULL;


public:
    Display();
    Display(uint8_t bytes_x, uint8_t bytes_y);
    ~Display();

    void Set(byte val, uint8_t x, uint8_t y);
    void Add(byte val, uint8_t x, uint8_t y);
    void Mask(byte mask, uint8_t x, uint8_t y);
    void Clr(uint8_t x, uint8_t y);
    void Clr();

    void Draw(byte *  p, uint8_t x, uint8_t y);
    void Draw(byte ** p);
    uint8_t getMaxY();
    uint8_t getMaxX();
    virtual void debugDisplay();
    void testDeleteScreen();
};

