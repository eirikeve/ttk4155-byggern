// Joystick class for use in TTK4155
// Written by Håvard Borge, Eirik Vesterkjær
// 18/09/2017


#include "../adc/adc.h"
// #include "../utilities/bmath.h"
#include <stdint.h>

enum Direction 
{
    UP, DOWN, LEFT, RIGHT, NEUTRAL
};

struct Position
{
    uint8_t x = 0;
    uint8_t y = 0;
};


class Joystick
{
public:

    //bit 0: is_initialized
    volatile uint8_t state = 0;

    // Value read from ADC at joystick max y position
    volatile uint8_t x_max;
    // Value read from ADCadc.h at joystick max x position
    volatile uint8_t y_max;
    // Value read from ADC at joystick min y position
    volatile uint8_t x_min;
    // Value read from ADC at joystick min x position
    volatile uint8_t y_min;
    // Value read from ADC at joystick centre x
    volatile uint8_t centre_x;
    // Value read from ADC at joystick centre y
    volatile uint8_t centre_y;
    // Value with which the joystick can be away from the centre in a dir before registering as that dir
    volatile uint8_t threshold_lim  = 0;
    // Scale factor for reading from ADC, multiplied by 100.

    // volatile uint8_t x;
    // volatile uint8_t y;

    ADC adc;


public:
    Joystick();
    void read(int8_t &x, int8_t &y);
    void getDir(Direction * dir);
    uint8_t readX();
    uint8_t readY();

private:
    void autoCalibrate();


};