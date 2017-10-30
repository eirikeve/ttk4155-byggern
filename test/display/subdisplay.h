#pragma once
#include "display.h"

enum Orientation
{
    HORIZONTAL_LEFT, 
    HORIZONTAL_RIGHT,
    VERTICAL_UPPER,
    VERTICAL_LOWER
};

class SubDisplay : public Display
{
private:
    uint8_t x1;
    uint8_t y1;

    Orientation child_orientation = HORIZONTAL_RIGHT;

    SubDisplay * parent = NULL;
    SubDisplay * child  = NULL;

public:
    SubDisplay();
    SubDisplay(uint8_t bytes_x, uint8_t bytes_y);
    SubDisplay(uint8_t bytes, SubDisplay * parent, Orientation o);
    ~SubDisplay();

    void AddChild(SubDisplay * c, Orientation o);
    void DeleteChild();
};