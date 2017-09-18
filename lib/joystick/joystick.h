// Joystick class for use in TTK4155
// Written by Håvard Borge, Eirik Vesterkjær
// 18/09/2017

class Joystick
{
public:

    /*
    bit 0: is_currently_autocalibrating
    bit 1: is_initialized
    */
    volatile uint8_t state = 0;
    

public:
    Joystick()
    {
        state = 0;
        return;
    }

private:
    void autoCalibrate()
    {
        return;
    }

}