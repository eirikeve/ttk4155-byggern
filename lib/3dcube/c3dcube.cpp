// 3dcube.cpp
// 19/11/2017

#ifdef __AVR_ATmega162__

#include "c3dcube.h"
#include <util/delay.h>

#define DIR_INCREASE 1
#define DIR_DECREASE -1
#define DIR_NONE 0

c3DCube::c3DCube() 
{
    s.clear();
}

void c3DCube::run(bool flexOn)
{
    flex = flexOn;
    bool btnPress;
    int8_t joystick_x;
    int8_t joystick_y;
    btnPress = joystick.buttonPressed();
    _delay_ms(20);
    do{
        joystick_x = joystick.readX();
        joystick_y = -joystick.readY(); // Up reads as positive, but pixel index increase downwards
        btnPress = joystick.buttonPressed();//joystick.buttonPressed();
        s.clear();
        runTimeStep(joystick_x, joystick_y);
        s.render();
        _delay_ms(5);
    } while (!btnPress);
}

void c3DCube::runTimeStep(int8_t joystick_x, int8_t joystick_y)
{
    y_offset = joystick_y / 6;
    x_offset = joystick_x / 6;
    if (flex)
    {
        simFlex(joystick_x, joystick_y);
    }
    drawToVram();
    
}



void c3DCube::drawToVram()
{



    // Draw upper cube
    if ( !(flex) )
    {
    drawLine(hi_right_coord + x_offset, hi_upper_coord + y_offset, hi_left_coord + x_offset, hi_upper_coord + y_offset);
    drawLine(hi_left_coord + x_offset, hi_upper_coord + y_offset, hi_left_coord + x_offset, hi_lower_coord + y_offset);
    drawLine(hi_left_coord + x_offset, hi_lower_coord + y_offset, hi_right_coord + x_offset, hi_lower_coord + y_offset);
    drawLine(hi_right_coord + x_offset, hi_lower_coord + y_offset, hi_right_coord + x_offset, hi_upper_coord + y_offset);
    }
    else // Flex on; draw surface which bounces as the upper square
    {
        // Draws the first part of the upper square. The left/right edges are straight, while the upper/lower edges can be bent.
        for (uint8_t x = hi_left_coord + x_offset; x < hi_right_coord + x_offset + 1; ++x)
        {
            int8_t y_line_offset_here = calcLineOffset(x - (hi_left_coord + x_offset), y_flex);
            int8_t y0 = hi_upper_coord + y_offset + y_line_offset_here;
            if (y0 < 0) y0 = 0;
            int8_t y1 = hi_lower_coord + y_offset + y_line_offset_here + 1;
            if (y1 > OLED_PIXELS_HEIGHT) y1 = OLED_PIXELS_HEIGHT;
            for (uint8_t y = y0; y < y1; ++y)
            {
                putPixel(x,y);
            }
        }
        // Here, we make the left/right edges bent. So we "carve" a bend on one side, and add a bend on the other.
        for (uint8_t y = 0; y < OLED_PIXELS_HEIGHT; ++y)
        {
            if (y < hi_lower_coord + y_offset && y >= hi_upper_coord + y_offset)
            {
                int8_t x_line_offset_here = calcLineOffset(y - (hi_upper_coord + y_offset), x_flex);
                if (x_line_offset_here < 0)
                {
                    for (uint8_t x = hi_left_coord + x_offset + x_line_offset_here - 1; x < hi_left_coord + x_offset; ++x)
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
                    for (uint8_t x = hi_left_coord + x_offset - 1; x < hi_left_coord + x_offset + x_line_offset_here; ++x)
                    {
                        remPixel(x,y);
                    }
                    for (uint8_t x = hi_right_coord + x_offset; x < hi_right_coord + x_offset + x_line_offset_here + 1; ++x)
                    {
                        putPixel(x,y);
                    }
                } 

            }
        }
    }

    // Draw lower cube
    drawLine(lo_left_coord, lo_upper_coord, lo_right_coord, lo_upper_coord);
    drawLine(lo_left_coord, lo_upper_coord, lo_left_coord, lo_lower_coord);
    drawLine(lo_right_coord, lo_lower_coord, lo_left_coord, lo_lower_coord);
    drawLine(lo_right_coord, lo_lower_coord, lo_right_coord, lo_upper_coord);

    // Draw lines between the lower and upper corners, to simulate 3d effect
    drawLine(lo_left_coord, lo_upper_coord, hi_left_coord + x_offset, hi_upper_coord + y_offset);
    drawLine(lo_right_coord, lo_upper_coord, hi_right_coord + x_offset, hi_upper_coord + y_offset);
    drawLine(lo_left_coord, lo_lower_coord, hi_left_coord + x_offset, hi_lower_coord + y_offset);
    drawLine(lo_right_coord, lo_lower_coord, hi_right_coord + x_offset, hi_lower_coord + y_offset);


    return;
}
int8_t c3DCube::calcLineOffset(uint8_t a_coord, int8_t opposite_dim_flex)
{
    if (a_coord <= 0 || a_coord >= 31) return 0;
    // Height and with is 32 pixels
    opposite_dim_flex /= 16; // Max abs of 8

    int8_t length = 32;
    int8_t base_offset = ((a_coord*(32-a_coord))/16); // Max abs 16
    return (base_offset * opposite_dim_flex) / 8; // Max abs 16
}

void c3DCube::putPixel(uint8_t x, uint8_t y) 
    {
        if ( x < 0 || x >= OLED_PIXELS_WIDTH || y < 0 || y >= OLED_PIXELS_HEIGHT)
        {
            return;
        }
        vram[((y%OLED_PIXELS_HEIGHT)/8)*OLED_PIXELS_WIDTH + (x%OLED_PIXELS_WIDTH)] |= (0b1<<((y%OLED_PIXELS_HEIGHT)%8));
    }
void c3DCube::remPixel(uint8_t x, uint8_t y) 
    {
        if ( x < 0 || x >= OLED_PIXELS_WIDTH || y < 0 || y >= OLED_PIXELS_HEIGHT)
        {
            return;
        }
        vram[((y%OLED_PIXELS_HEIGHT)/8)*OLED_PIXELS_WIDTH + (x%OLED_PIXELS_WIDTH)] &= (0x11111110<<((y%OLED_PIXELS_HEIGHT)%8));
    }

void c3DCube::simFlex(int8_t joystick_x, int8_t joystick_y)
{
    
    int16_t delta_joystick_x = (joystick_x - last_joystick_x);
    int16_t delta_joystick_y = (joystick_y - last_joystick_y);
    last_joystick_x = joystick_x;
    last_joystick_y = joystick_y;
    int8_t threshold = 5;

    // Determine new flex directions and max flex
    if (delta_joystick_x > threshold || delta_joystick_x < -threshold)
    {
        int8_t x_factor = delta_joystick_x/2;
        
        
        if (x_flex_max < 0)
        {
        if ( x_factor < x_flex) 
            {
                x_flex_max = x_factor;
                x_flex_dir = DIR_DECREASE;
            }
            else if( x_factor > threshold)
            {
                x_flex_max = x_factor;
                x_flex_dir = DIR_INCREASE;
            }
        }
        else if (x_flex_max > 0) 
        {
            if (x_factor > x_flex)
            {
            x_flex_max = x_factor;
            x_flex_dir = DIR_INCREASE;
            }
            else if (x_factor < -threshold)
            {
                x_flex_max = x_factor;
                x_flex_dir = DIR_DECREASE;
            }
        }
        else
        {
            x_flex_max = x_factor;
            if (x_factor > 0) x_flex_dir = DIR_INCREASE;
            else x_flex_dir = DIR_DECREASE;
        }
    }
    if (delta_joystick_y > threshold || delta_joystick_y < -threshold)
    {
        int8_t y_factor = delta_joystick_y/2;
        if (y_flex_max < 0) 
        {
            if (y_factor < y_flex)
            {
                y_flex_max = y_factor;
                y_flex_dir = DIR_DECREASE;
            }
            else if (y_factor > threshold)
            {
                y_flex_max = y_factor;
                y_flex_dir = DIR_INCREASE;
            }

        }
        else if (y_flex_max > 0) 
        {
            if (y_factor > y_flex)
            {
                y_flex_max = y_factor;
                y_flex_dir = DIR_INCREASE;
            }
            else if (y_factor < -threshold)
            {

            }

        }
        else
        {
            y_flex_max = y_factor;
            if (y_factor > 0) y_flex_dir = DIR_INCREASE;
            else y_flex_dir = DIR_DECREASE;
        }
    }


    // Find new flex values
    updateFlex(x_flex, x_flex_max, x_flex_dir);
    updateFlex(y_flex, y_flex_max, y_flex_dir);

    

    return;
}

void c3DCube::updateFlex(int8_t &current_flex, int8_t &max_flex, int8_t &current_dir)
{
    max_flex = max_flex < -50 ? -50 : max_flex;
    max_flex = max_flex >  50 ?  50 : max_flex;

    if (current_dir == DIR_INCREASE)
    {
        if (current_flex == 0 && max_flex < 0)
        {
            current_dir = DIR_NONE;
        }
        else if (current_flex > 0 && current_flex >= max_flex)
        {
            current_dir = DIR_DECREASE;
        }
        else
        {
            current_flex+= 15;

        }
    }
    else if (current_dir == DIR_DECREASE)
    {
        if (current_flex == 0 && max_flex > 0)
        {
            current_dir = DIR_NONE;
        }
        else if (current_flex < 0 && current_flex <= max_flex)
        {
            current_dir = DIR_INCREASE;
        }
        else
        {
            current_flex-= 15;
        }
    }
    else
    {
        current_dir = DIR_NONE;
        max_flex = 0;
        current_flex = 0;
    }

}

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