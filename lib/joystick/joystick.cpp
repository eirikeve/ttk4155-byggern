#include "joystick.h"

void Joystick::Joystick()
{
    state = 0;
    return;
}

void Joystick::getRaw(Position * p)
{
    // Read raw values
    ADC.selectChannel(Channel::X);
    int8_t x = ADC.read() - centre_x;
    ADC.selectChannel(Channel::Y);
    int8_t y = ADC.read() - centre_y;

    p->x = x;
    p->y = y;

    return;
}

void Joystick::getDir(dir_t * d)
{
    // Read raw values
    ADC.selectChannel(Channel::X);
    int8_t x = ADC.read() - centre_x;
    ADC.selectChannel(Channel::Y);
    int8_t y = ADC.read() - centre_y;

    uint8_t x_offset_abs = bmath::abs(x);
    uint8_t y_offset_abs = bmath::abs(y);

    // Check if non-neutral
    if (x_offset_abs >= threshold_lim || y_offset_abs >= threshold_lim)
    {
        // Check if joystick is currently offset the most along the y or x axis
        if (x_offset_abs >= y_offset_abs)
        {
            if (x > 0)
            {
                *d = RIGHT;
            }
            else
            {
                *d = LEFT;
            }
        }
        else
        {
            if (y > 0)
            {
                *d = UP;
            }
            else
            {
                *d = DOWN;
            }
        }
    }
    else
    {
        *d = NEUTRAL;
    }
    return;
}

void Joystick::autoCalibrate()
{
    // Check centre x/y-values
    ADC.selectChannel(Channel::X);
    centre_x = ADC.read()
    ADC.selectChannel(Channel::Y);
    centre_y = ADC.read();

    y_max = centre_y;
    y_min = centre_y;
    x_max = centre_x;
    x_min = centre_x;

    uint8_t x = 0;
    uint8_t y = 0;
    int i = 0;
    const uint calibration_break_loops = 500;

    while (i < calibration_break_loops)
    {
        ADC.selectChannel(Channel::X);
        x = ADC.read()
        ADC.selectChannel(Channel::Y);
        y = ADC.read();

        // If we read a new max/min, save it. Set var for loops without max/min to 0.
        if      (x > x_max) x_max = x;  i = 0;
        else if (x < x_min) x_min = x;  i = 0;
        else if (y > y_max) y_max = y;  i = 0;
        else if (y < y_min) y_min = y;  i = 0;
        else
        {
            // Did not find a new max/min this loop. Increment the var for number of loops without max/min.
            ++i;
        }
    }
    return;
}

