// 3dcube.h
// 19/11/2017

#ifndef _3DCUBE_H_
#define _3DCUBE_H_

#include "../utilities/utilities.h"
#include <stdint.h>
#include "../joystick/joystick.h"



class c3DCube
{
// Private variables
private:
    Joystick & joystick = Joystick::getInstance();
    Screen s;

    uint8_t hi_upper_coord = 16; // Pixel # 17, counted from above
    uint8_t hi_lower_coord = 48; 
    uint8_t hi_left_coord = 48; // Pixel # 49, counted from the left
    uint8_t hi_right_coord = 80;

    uint8_t lo_upper_coord = 20; // Pixel # 17, counted from above
    uint8_t lo_lower_coord = 44; 
    uint8_t lo_left_coord = 52; // Pixel # 49, counted from the left
    uint8_t lo_right_coord = 76;
    
    int8_t y_offset = 0;
    int8_t x_offset = 0;

    int8_t y_flex = 0;
    int8_t y_flex_spd = 0;
    int8_t y_flex_accel = 0;

    int8_t x_flex = 0;
    int8_t x_flex_spd = 0;
    int8_t x_flex_accel = 0;

    int8_t last_joystick_x = 0;
    int8_t last_joystick_y = 0;

    uint8_t* vram = AVR_VRAM_1;

// Public variables
public:

// Private methods
private:
    void runTimeStep(int8_t joystick_x, int8_t joystick_y);
    void drawToVRam();
    int8_t calcLineOffset(uint8_t a_coord, uint8_t opposite_dim_flex);
    void simFlex(int8_t joystick_x, int8_t joystick_y);
    void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    inline void putPixel(uint8_t x, uint8_t y) {vram[(y%OLED_PIXELS_HEIGHT)/8 + (x%OLED_PIXELS_WIDTH)] |= (0b1<<((y%OLED_PIXELS_HEIGHT)%8));}
    inline void remPixel(uint8_t x, uint8_t y) {vram[(y%OLED_PIXELS_HEIGHT)/8 + (x%OLED_PIXELS_WIDTH)] &= (0x11111110<<((y%OLED_PIXELS_HEIGHT)%8));}




// Public methods
public:
    c3DCube();
    run();


};

#endif //_3DCUBE_H_