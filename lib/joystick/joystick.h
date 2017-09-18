// Joystick class for use in TTK4155
// Written by Håvard Borge, Eirik Vesterkjær
// 18/09/2017


#include "../adc/adc.h"
#include "../utilities/bmath.h"

enum Direction 
{
    UP, DOWN, LEFT, RIGHT, NEUTRAL;
} typedef Direction dir_t;

struct Position
{
    int8_t X = 0;
    int8_t Y = 0;
}


class Joystick
{
public:

    //bit 0: is_initialized
    volatile uint8_t state = 0;

    // Value read from ADC at joystick max y position
    volatile uint8_t x_max         = 0;
    // Value read from ADC at joystick max x position
    volatile uint8_t y_max      = 0;
    // Value read from ADC at joystick min y position
    volatile uint8_t x_min       = 0;
    // Value read from ADC at joystick min x position
    volatile uint8_t y_min       = 0;
    // Value read from ADC at joystick centre x
    volatile uint8_t centre_x       = 0;
    // Value read from ADC at joystick centre y
    volatile uint8_t centre_y       = 0;
    // Value with which the joystick can be away from the centre in a dir before registering as that dir
    volatile uint8_t threshold_lim  = 0;
    // Scale factor for reading from ADC, multiplied by 100.


public:
    Joystick();
    void getRaw(int8_t * x, int8_t * y);
    void getDir(Direction * dir);

private:
    void autoCalibrate();


}