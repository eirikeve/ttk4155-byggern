#pragma once

#include <stdint.h>

#include "lib/joystick/joystick.h"
#include "lib/display/screen.h"
#include "lib/utilities/utilities.h"



/**
 * c3DCUBE implements drawing a 3D cube to the oled display.
 * The the cube angle is changed when moving the joystick.
 * Also implements a "FLEX" mode, where the cube bounces after sudden movements.
 * Absolutely useless, but very fun to watch!
 * 
 * 3D is simulated by drawing two squares.
 *  - lo, the "lower" square. The smaller of the two squares.
 *  - hi, the "higher" square. Appears to be above the lower square.
 * Lines are drawn between the corners of the two squares.
 * When the joystick is moved, the hi square is displaced.
 **/
class c3DCube
{
// Private variables
private:
    Joystick & joystick = Joystick::getInstance();
    Screen s;
    // Flex flag
    bool flex;

    // Coordinates of the edges of the upper square
    uint8_t hi_upper_coord = 15; // Pixel # 16, counted from above
    uint8_t hi_lower_coord = 47; 
    uint8_t hi_left_coord = 48; // Pixel # 49, counted from the left
    uint8_t hi_right_coord = 80;

    // Coordinates of the lower square.
    uint8_t lo_upper_coord = 19; // Pixel # 20, counted from above
    uint8_t lo_lower_coord = 43; 
    uint8_t lo_left_coord = 52; // Pixel # 49, counted from the left
    uint8_t lo_right_coord = 76;
    
    // Offset of the hi square, taken from the joystick read values
    int8_t y_offset = 0;
    int8_t x_offset = 0;

    // Flex of the hi square
    int8_t y_flex = 0;
    int8_t x_flex = 0;

    // Variables used to simulate the change in flex
    int8_t x_flex_max = 0;
    int8_t y_flex_max = 0;
    int8_t x_flex_dir = 0;
    int8_t y_flex_dir = 0;

    // Stored values of joystick, for computing change in joystick position
    int8_t last_joystick_x = 0;
    int8_t last_joystick_y = 0;

    // Pointer to the SRAM memory area where we render from
    uint8_t* vram = (uint8_t*)AVR_VRAM_1;


// Private methods
private:

    /**
     * Update x/y_offset, update flex (if enabled) and draw the cube to vram
     * @param joystick_x: Current joystick x value
     * @param joystick_y: Current joystick y value
     **/
    void runTimeStep(int8_t joystick_x, int8_t joystick_y);

    /**
     * Draws the two squares to vram.
     * Quite complex, more explanation in the function.
     **/
    void drawToVram();

    /**
     * Based on flex, this calculates the displacement of the edge of the upper square.
     * Basically a 2nd order algebraic function.
     * @param a_coord: Position at cube, between 0 and 32.
     * @param opposite_dim_flex: x_flex or y_flex
     **/
    int8_t calcLineOffset(uint8_t a_coord, int8_t opposite_dim_flex);

    /**
     * Calculates x_flex_max and dir, and y_flex_max and dir, which depend on the change in joystick position.
     * @param joystick_x: Current joystick x pos
     * @param joystick_y: current joystick y pos
     **/
    void simFlex(int8_t joystick_x, int8_t joystick_y);

    /**
     * Bresenham's Line Algorithm, based on this:
     * http://raspberrycompote.blogspot.no/2014/04/low-level-graphics-on-raspberry-pi.html
     * @param (x0,y0): coord indexes of line start
     * @param (x1,y1): coord indexes of line end
    **/
    void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

    /**
     * Draws a pixel at (x,y)
     * @param x: x index
     * @param y: y index
     **/
    void putPixel(uint8_t x, uint8_t y);

    /**
     * Removes a pixel at (x,y) (sets to 0)
     * @param x: x index
     * @param y: y index
     **/
    void remPixel(uint8_t x, uint8_t y);

    /**
     * Updates x_flex or y_flex based on the max_flex and dir
     * @param current_flex: x_flex or y_flex
     * @param max_flex: x_flex_max or y_flex_max
     * @param current_dir: x_flex_dir or y_flex_dir
     * x / y must be the same for all args!
     **/
    void updateFlex(int8_t &current_flex, int8_t &max_flex, int8_t &current_dir);





// Public methods
public:
    c3DCube();
    /**
     * Run the cube with or without flex!
     **/
    void run(bool flexOn = false);


};
