#include "joystick.h"
extern "C" {
    #include "../../node1/include/comm.h"
    #include <stdio.h>
    #include <stdlib.h>
    
}

namespace {
    enum MUX_SELECT {
        X = 0b100,
        Y = 0b101,
        LSLIDE = 0b110,
        RSLIDE = 0b111
    };
}

Joystick::Joystick(){
    state = 0;
    this->autoCalibrate();
    return;
}

uint8_t Joystick::readX() {
    return this->adc.read(CHANNEL::CH1);
}

uint8_t Joystick::readY() {
    return this->adc.read(CHANNEL::CH2);
}

void Joystick::autoCalibrate() {
    printf("\n");
    // Get center points
    
    this->centre_x = this->readX();
    printf("X: %d, ", centre_x);
    this->centre_y = this->readY();
    printf("Y: %d, ", this->centre_y);
    
    // printf("X etter: %d\n", centre_x);
    // while (true) {
    //     this->centre_x = this->readX();
    //     printf("X: %d, ", centre_x);
    //     this->centre_y = this->readY();
    //     printf("Y: %d, ", centre_y);
    //     printf("X etter: %d\n", centre_x);
    // }

    this->x_max = this->centre_x;
    this->x_min = this->centre_x;
    this->y_max = this->centre_y;
    this->y_min = this->centre_y;

    const uint8_t CALIBRATION_BREAK_LOOPS_X = 15;
    const uint8_t CALIBRATION_BREAK_LOOPS_Y = 15;

    uint8_t countX = 0;
    uint8_t countY = 0;
    uint8_t currentX;
    uint8_t currentY;
    // volatile uint8_t this->x;
    // volatile uint8_t currentY;
    // uint8_t* p1 = (uint8_t*) malloc(1);
    // printf("%p", p1);
    // uint8_t* p2 = (uint8_t*) malloc(1);
    
    do {
        // Get current value for X and Y
       
        currentX = this->readX();
        currentY = this->readY();
        // uint8_t *p = (uint8_t*) 0x1400;
        // *p = (uint8_t) 1000;
        // currentY = this->centre_y;
        

        // Check if current value > max or current value < min
        // If not, increment count
        if ( abs(currentX - this->centre_x) > 10 && !(currentX > this->x_max || currentX < this->x_min)) {
            countX++;
        } else if (currentX > this->x_max) {
            this->x_max = currentX;
        } else if (currentX < this->x_min) {
            this->x_min = currentX;
        }

        // *p2 = this->readY();
        // currentY = *p2;
        if (abs(currentY == this->centre_y) > 10 && !(currentY > this->y_max || currentY < this->y_min)) {
            countY++;
        } else if (currentY > this->y_max) {
            this->y_max = currentY;
        } else if (currentY < this->y_min) {
            this->y_min = currentY;
        }
        printf("CX: %d, MAX: %d, MIX: %d, ", currentX, this->x_max, this->x_min);
        printf("CY: %d, MAY: %d, MIY: %d\n", currentY, this->y_max, this->y_min);
    } while (((abs(currentX - this->centre_x) < 10 && abs(currentY == this->centre_y) < 10)) && \
            (countX < CALIBRATION_BREAK_LOOPS_X || countY < CALIBRATION_BREAK_LOOPS_Y));
}

// void Joystick::getRaw(Position * p)
// {
//     // Read raw values
//     ADC.selectChannel(Channel::X);
//     int8_t x = ADC.read() - centre_x;
//     ADC.selectChannel(Channel::Y);
//     int8_t y = ADC.read() - centre_y;

//     p->x = x;
//     p->y = y;

//     return;
// }

// void Joystick::getDir(dir_t * d)
// {
//     // Read raw values
//     ADC.selectChannel(Channel::X);
//     int8_t x = ADC.read() - centre_x;
//     ADC.selectChannel(Channel::Y);
//     int8_t y = ADC.read() - centre_y;

//     uint8_t x_offset_abs = bmath::abs(x);
//     uint8_t y_offset_abs = bmath::abs(y);

//     // Check if non-neutral
//     if (x_offset_abs >= threshold_lim || y_offset_abs >= threshold_lim)
//     {
//         // Check if joystick is currently offset the most along the y or x axis
//         if (x_offset_abs >= y_offset_abs)
//         {
//             if (x > 0)
//             {
//                 *d = RIGHT;
//             }
//             else
//             {
//                 *d = LEFT;
//             }
//         }
//         else
//         {
//             if (y > 0)
//             {
//                 *d = UP;
//             }
//             else
//             {
//                 *d = DOWN;
//             }
//         }
//     }
//     else
//     {
//         *d = NEUTRAL;
//     }
//     return;
// }

// void Joystick::autoCalibrate()
// {
//     // Check centre x/y-values
//     ADC.selectChannel(Channel::X);
//     centre_x = ADC.read()
//     ADC.selectChannel(Channel::Y);
//     centre_y = ADC.read();
    
// }
    
//     void Joystick::autoCalibrate()
//     {
//         // Check centre x/y-values
//         ADC.selectChannel(Channel::X);
//         centre_x = ADC.read()
//         ADC.selectChannel(Channel::Y);
//         centre_y = ADC.read();
    
//         y_max = centre_y;
//         y_min = centre_y;
//         x_max = centre_x;
//         x_min = centre_x;
    
//         uint8_t x = 0;
//         uint8_t y = 0;
//         int i = 0;
//         const uint calibration_break_loops = 500;
    
//         while (i < calibration_break_loops)
//         {
//             ADC.selectChannel(Channel::X);
//             x = ADC.read()
//             ADC.selectChannel(Channel::Y);
//             y = ADC.read();
    
//             // If we read a new max/min, save it. Set var for loops without max/min to 0.
//             if      (x > x_max) x_max = x;  i = 0;
//             else if (x < x_min) x_min = x;  i = 0;
//             else if (y > y_max) y_max = y;  i = 0;
//             else if (y < y_min) y_min = y;  i = 0;
//             else
//             {
//                 // Did not find a new max/min this loop. Increment the var for number of loops without max/min.
//                 ++i;
//             }
//         }
//         return;
//     }
    
    

//     y_max = centre_y;
//     y_min = centre_y;
//     x_max = centre_x;
//     x_min = centre_x;

//     uint8_t x = 0;
//     uint8_t y = 0;
//     int i = 0;
//     const uint calibration_break_loops = 500;

//     while (i < calibration_break_loops)
//     {
//         ADC.selectChannel(Channel::X);
//         x = ADC.read()
//         ADC.selectChannel(Channel::Y);
//         y = ADC.read();

//         // If we read a new max/min, save it. Set var for loops without max/min to 0.
//         if      (x > x_max) x_max = x;  i = 0;
//         else if (x < x_min) x_min = x;  i = 0;
//         else if (y > y_max) y_max = y;  i = 0;
//         else if (y < y_min) y_min = y;  i = 0;
//         else
//         {
//             // Did not find a new max/min this loop. Increment the var for number of loops without max/min.
//             ++i;
//         }
//     }
//     return;
// }

