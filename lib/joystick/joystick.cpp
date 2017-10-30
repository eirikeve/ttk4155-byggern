#include "joystick.h"
extern "C" {
#include "../../node1/include/comm.h"
#include <stdio.h>
#include <stdlib.h>
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
    this->autoCalibrate();
}

uint8_t Joystick::readX()
{
    this->x = this->adc.read(CHANNEL::CH1);
    if (this->x < this->centre_x + this->threshold && this->x > this->centre_x - this->threshold)
    {
        this->x = this->centre_x;
    }
    // this->formatValue(&raw, &this->x, &this->centre_x, &this->threshold);
    return this->x;
}

uint8_t Joystick::readRawX()
{
    this->x = this->adc.read(CHANNEL::CH1);

    return this->x;
}

uint8_t Joystick::readY()
{
    this->y = this->adc.read(CHANNEL::CH2);

    if (this->y < this->centre_y + this->threshold && this->y > this->centre_y - this->threshold)
    {
        this->y = this->centre_y;
    }
    // this->formatValue(&raw, &this->y, &this->centre_y, &this->threshold);
    return this->y;
}

uint8_t Joystick::readRawY()
{
    this->y = this->adc.read(CHANNEL::CH2);
    return this->y;
}

Direction Joystick::read(uint8_t *x, uint8_t *y)
{
    this->x = this->readX();
    this->y = this->readY();
    *x = this->x;
    *y = this->y;
    return this->getDir();
}

void Joystick::formatValue(uint8_t *raw, uint8_t *result, uint8_t *center, uint8_t *threshold)
{
    // uint8_t temp = *raw - *center;
    // *result = (int8_t)temp;
    // printf("%d\n", *result);
    // *result = abs(*result) >= *threshold ? *result : 0;
    // return *result;
    *result = abs(*raw - *center) >= *threshold ? *raw : *center;
    return;
}

Direction Joystick::getDir() const
{
    //     printf("CX: %d, CY: %d\n", this->centre_x, this->centre_y);
    // printf("X: %d, Y: %d\n", this->x, this->y);
    Direction d = Direction::NEUTRAL;
    if (this->x > this->centre_x && this->y > this->centre_y)
    {
        d = Direction::NORTH_EAST;
    }
    else if (this->x < this->centre_x && this->y > this->centre_y)
    {
        d = Direction::NORTH_WEST;
    }
    else if (this->x > this->centre_x && this->y < this->centre_y)
    {
        d = Direction::SOUTH_EAST;
    }
    else if (this->x < this->centre_x && this->y < this->centre_y)
    {
        d = Direction::SOUTH_WEST;
    }
    else if (this->x > this->centre_x)
    {
        d = Direction::EAST;
    }
    else if (this->x < this->centre_x)
    {
        d = Direction::WEST;
    }
    else if (this->y > this->centre_y)
    {
        return Direction::NORTH;
    }
    else if (this->y < this->centre_y)
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
    //     printf("cx: %d, cy: %d\n", this->x, this->y);
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
