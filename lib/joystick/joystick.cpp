#ifdef __AVR_ATmega162__
#include "joystick.h"
extern "C" {
#include "../comm/comm.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utilities/utilities.h"
}

namespace
{
enum MUX_SELECT
{
    X = 0b100,
    Y = 0b101,
    LSLIDE = 0b110,
    RSLIDE = 0b111
};
}

Joystick::Joystick(uint8_t threshold) : threshold(threshold)
{
    clr_bit(DDRE, 0);
    this->autoCalibrate();
}

int8_t Joystick::readX()
{
    uint8_t raw = this->adc.read(CHANNEL::CH1);
    // if (this->x < this->centre_x + this->threshold && this->x > this->centre_x - this->threshold)
    // {
    //     this->x = this->centre_x;
    // }
    this->formatValue(raw, &this->x, &this->centre_x, &this->threshold);
    return this->x;
}

uint8_t Joystick::readRawX()
{
    this->rawX = this->adc.read(CHANNEL::CH1);

    return this->rawX;
}

int8_t Joystick::readY()
{
    uint8_t raw = this->adc.read(CHANNEL::CH2);

    // if (this->y < this->centre_y + this->threshold && this->y > this->centre_y - this->threshold)
    // {
    //     this->y = this->centre_y;
    // }
    this->formatValue(raw, &this->y, &this->centre_y, &this->threshold);
    return this->y;
}

uint8_t Joystick::readRawY()
{
    this->rawY = this->adc.read(CHANNEL::CH2);
    return this->rawY;
}

Direction Joystick::read(int8_t *x, int8_t *y)
{
    this->x = this->readX();
    this->y = this->readY();
    *x = this->x;
    *y = this->y;
    return this->getDir();
}

void Joystick::formatValue(uint8_t raw, int8_t *result, uint8_t *center, uint8_t *threshold)
{
    if (raw < *center + *threshold && raw > *center - *threshold)
    {
        raw = *center;
    }
    if (*center > 128 && raw < *center - 128) {
        *result = -128;
    }
    else if (*center < 128 && raw > 128 + *center) {
        *result = 128;
    }
    else {
        *result = raw - *center;
    }
    *result /= 1.28;

    return;
}

Direction Joystick::getDir() const
{
    //     printf("CX: %d, CY: %d\n", this->centre_x, this->centre_y);
    // printf("X: %d, Y: %d\n", this->x, this->y);
    Direction d = Direction::NEUTRAL;
    if (this->x > 0 && this->y > 0)
    {
        d = Direction::NORTH_EAST;
    }
    else if (this->x < 0 && this->y > 0)
    {
        d = Direction::NORTH_WEST;
    }
    else if (this->x > 0 && this->y < 0)
    {
        d = Direction::SOUTH_EAST;
    }
    else if (this->x < 0 && this->y < 0)
    {
        d = Direction::SOUTH_WEST;
    }
    else if (this->x > 0)
    {
        d = Direction::EAST;
    }
    else if (this->x < 0)
    {
        d = Direction::WEST;
    }
    else if (this->y > 0)
    {
        return Direction::NORTH;
    }
    else if (this->y < 0)
    {
        d = Direction::SOUTH;
    }
    return d;
}

void Joystick::autoCalibrate()
{
    // Get center points
    this->centre_x = this->readRawX();
    this->centre_y = this->readRawY();
    // while (true)
    // {
    //     printf("cx: %u, cy: %u\n", this->centre_x, this->centre_y);
    // }
    // this->x_max = this->centre_x;
    // this->x_min = this->centre_x;
    // this->y_max = this->centre_y;
    // this->y_min = this->centre_y;

    // const uint8_t CALIBRATION_BREAK_LOOPS_X = 15;
    // const uint8_t CALIBRATION_BREAK_LOOPS_Y = 15;

    // uint8_t countX = 0;
    // uint8_t countY = 0;
    // uint8_t currentX;
    // uint8_t currentY;
    // bool movedInY = false;
    // bool movedInX = false;

    // do
    // {
    //     // Get current value for X and Y

    //     currentX = this->readRawX();
    //     currentY = this->readRawY();

    //     // Check if current value > max or current value < min
    //     // If not, increment count
    //     if (abs(currentX - this->centre_x) > threshold && !(currentX > this->x_max || currentX < this->x_min))
    //     {
    //         movedInX = true;
    //         countX++;
    //     }
    //     else if (currentX > this->x_max)
    //     {
    //         this->x_max = currentX;
    //     }
    //     else if (currentX < this->x_min)
    //     {
    //         this->x_min = currentX;
    //     }

    //     if (abs(currentY - this->centre_y) > threshold && !(currentY > this->y_max || currentY < this->y_min))
    //     {
    //         movedInY = true;
    //         countY++;
    //     }
    //     else if (currentY > this->y_max)
    //     {
    //         this->y_max = currentY;
    //     }
    //     else if (currentY < this->y_min)
    //     {
    //         this->y_min = currentY;
    //     }
    //     printf("CX: %d, MAX: %d, MIX: %d, ", currentX, this->x_max, this->x_min);
    //     printf("CY: %d, MAY: %d, MIY: %d\n", currentY, this->y_max, this->y_min);
    //     // printf("X: %d, Y: %d\n", movedInX, movedInY);
    //     // printf("bool: %d\n", (!(movedInX && movedInY)) || (countX < CALIBRATION_BREAK_LOOPS_X || countY < CALIBRATION_BREAK_LOOPS_Y));
    // } while ((!(movedInX && movedInY)) ||
    //          (countX < CALIBRATION_BREAK_LOOPS_X || countY < CALIBRATION_BREAK_LOOPS_Y));
}
#endif