// 3dcube.cpp
// 19/11/2017

#ifdef __AVR_ATmega162__

#include "c3dcube.h"
#include <util/delay.h>

c3DCube::c3DCube() 
{
    s.clear();
}

void c3DCube::run()
{
    Joystick & joystick = Joystick::getInstance();
    bool btnPress;
    int8_t joystick_x;
    int8_t joystick_y;
    do{
        joystick_x = joystick.readX();
        joystick_y = joystick.readY();
        btnPress = joystick.buttonPressed();
        runTimeStep(joystick_x, joystick_y);
        s.render();
    } while (!btnPress);
}

void c3DCube::runTimeStep(int8_t joystick_x, int8_t joystick_y)
{
    y_offset = joystick_y / 6;
    x_offset = joystick_x / 6;
    //simFlex(joystick_x, joystick_y);
    drawToVram();
}



void c3DCube::drawToVram()
{
    // Draw lower cube
    drawLine(lo_left_coord, lo_upper_coord, lo_right_coord, lo_upper_coord);
    drawLine(lo_left_coord, lo_upper_coord, lo_left_coord, lo_lower_coord);
    drawLine(lo_right_coord, lo_lower_coord, lo_left_coord, lo_lower_coord);
    drawLine(lo_right_coord, lo_lower_coord, lo_right_coord, lo_upper_coord);
    // Replaced that with this:
    /*for (uint8_t x = hi_left_coord + x_offset; x < hi_right_coord + x_offset + 1; ++x)
    {
        putPixel(x, lo_upper_coord);
        putPixel(x, lo_lower_coord);
    }
    for (uint8_t y = lo_upper_coord; y < lo_lower_coord + 1; ++y)
    {
        putPixel(lo_left_coord, y);
        putPixel(lo_right_coord,y);
    } */

    // Draw lines between the lower and upper corners, to simulate 3d effect
    drawLine(lo_left_coord, lo_upper_coord, hi_left_coord, hi_upper_coord);
    drawLine(lo_right_coord, lo_upper_coord, hi_right_coord, hi_upper_coord);
    drawLine(lo_left_coord, lo_lower_coord, hi_left_coord, hi_lower_coord);
    drawLine(lo_right_coord, lo_lower_coord, hi_right_coord, hi_lower_coord);


    // Draw upper cube
    // Version 1: No flex considered
    for (uint8_t x = hi_left_coord + x_offset; x < hi_right_coord + x_offset + 1; ++x)
    {
        for (uint8_t y = hi_upper_coord + y_offset; y < hi_lower_coord + y_offset + 1; ++y)
        {
            putPixel(x,y);
        } 
    }
    

    /*

    // Version 2: Flex considered
    // Place pixels with Y flex
    for (uint8_t x = 0; x < OLED_PIXELS_WIDTH; ++x)
    {
        if (x < hi_right_coord + x_offset && x > hi_left_coord + x_offset)
        {
            int8_t y_line_offset_here = calcLineOffset(x - (hi_upper_coord + x_offset), y_flex);
            for (uint8_t y = hi_upper_coord + y_offset + y_line_offset_here; y < hi_lower_coord + y_offset + y_line_offset_here + 1; ++y)
            {
                putPixel(x,y);
            }
        }
    }
    // Place pixels with X flex, remove pixels that are flexed away
    for (uint8_t y = 0; y < OLED_PIXELS_HEIGHT; ++y)
    {
        if (y < hi_lower_coord + y_offset && y > hi_upper_coord + y_offset)
        {
            int8_t x_line_offset_here = calcLineOffset(y - (hi_upper_coord + y_offset), x_flex);
            if (x_line_offset_here < 0)
            {
                for (uint8_t x = hi_left_coord + x_offset + x_line_offset_here; x < hi_left_coord + x_offset + 1; ++x)
                {
                    putPixel(x,y);
                }
                for (uint8_t x = hi_right_coord + x_offset + x_line_offset_here; x < hi_right_coord + x_offset + 1; ++x)
                {
                    remPixel(x,y);
                }
            }
            else
            {
                for (uint8_t x = hi_left_coord + x_offset; x < hi_left_coord + x_offset + x_line_offset_here + 1; ++x)
                {
                    remPixel(x,y);
                }
                for (uint8_t x = hi_right_coord + x_offset; x < hi_right_coord + x_offset + x_line_offset_here + 1; ++x)
                {
                    putPixel(x,y);
                }
            }
            
        }
    }*/


    return;
}
int8_t c3DCube::calcLineOffset(uint8_t a_coord, int8_t opposite_dim_flex)
{
    // Height and with is 32 pixels
    opposite_dim_flex /= 16; // Max abs of 8

    int8_t length = 32;
    int8_t base_offset = ((a_coord*(32-a_coord))/16); // Max abs 16
    return (base_offset * opposite_dim_flex) / 8; // Max abs 16
}
void c3DCube::simFlex(int8_t joystick_x, int8_t joystick_y)
{
    int8_t delta_joystick_x = (joystick_x/2 - last_joystick_x/2);
    int8_t delta_joystick_y = (joystick_y/2 - last_joystick_y/2);
    last_joystick_x = joystick_x;
    last_joystick_y = joystick_y;

    y_flex_accel = (- delta_joystick_y / 64 - y_flex / 64 - y_flex_spd/32);
    y_flex_spd += y_flex_accel;
    y_flex += y_flex_spd;

    x_flex_accel = (- delta_joystick_x / 64 - x_flex / 64 - x_flex_spd/32);
    x_flex_spd += x_flex_accel;
    x_flex += x_flex_spd;

    return;
}
/*
Bresenham's Line Algorithm, based on this:
http://raspberrycompote.blogspot.no/2014/04/low-level-graphics-on-raspberry-pi.html
*/
void c3DCube::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    int8_t dx = x1 - x0;
    dx = (dx >= 0) ? dx : -dx; // abs()
    int8_t dy = y1 - y0;
    dy = (dy >= 0) ? dy : -dy; // abs()
    int8_t sx;
    int8_t sy;
    if (x0 < x1) sx = 1;
    else sx = -1;
    if (y0 < y1) sy = 1;
    else sy = -1;
    int8_t err = dx - dy;
    int8_t e2;
    bool done = false;
    while (!done) 
    {
        putPixel(x0, y0);
        if ((x0 == x1) && (y0 == y1)) done = true;
        else {
            e2 = 2 * err;
            if (e2 > -dy) {
            err = err - dy;
            x0 = x0 + sx;
            }
        if (e2 < dx) {
            err = err + dx;
            y0 = y0 + sy;
            }
        }
    }
}









#endif //__AVR_ATmega162__