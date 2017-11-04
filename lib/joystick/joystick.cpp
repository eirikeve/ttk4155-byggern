#ifdef __AVR_ATmega162__
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "joystick.h"
#include "../adc/adc.h"
#include "../utilities/utilities.h"

namespace
{
enum MUX_SELECT
{
    X = 0b100,
    Y = 0b101,
    LSLIDE = 0b110,
    RSLIDE = 0b111
};

void formatValue(uint8_t raw, int8_t *result, uint8_t center, uint8_t threshold){
    if (raw < center + threshold && raw > center - threshold)
    {
        raw = center;
    }
    if (center > 128 && raw < center - 128) {
        *result = -128;
    }
    else if (center < 128 && raw > 128 + center) {
        *result = 128;
    }
    else {
        *result = raw - center;
    }
    *result /= 1.28;

    return;
}
}

void Joystick::initialize(ADC *adc, uint8_t threshold, PIN *buttonPin) {
    this->adc = adc;
    clr_bit(DDRE, 0);
    this->calibrate();

    this->buttonPin = buttonPin;
    this->buttonPressedDown = false;
    // TODO: Initialize the button.
    if (buttonPin != NULL) {
        // Enable pin for input
        clr_bit(*buttonPin->ddr, buttonPin->nr);
    }
}

int8_t Joystick::readX()
{
    this->readRawX();
    formatValue(this->rawX, &this->x, this->centerX, this->threshold);
    return this->x;
}

uint8_t Joystick::readRawX()
{
    this->rawX = this->adc->read(CHANNEL::CH1);
    return this->rawX;
}

int8_t Joystick::readY()
{
    this->readRawY();
    formatValue(this->rawY, &this->y, this->centerY, this->threshold);
    return this->y;
}

uint8_t Joystick::readRawY()
{
    this->rawY = this->adc->read(CHANNEL::CH2);
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

Direction Joystick::getDir()
{
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

Direction Joystick::getDirX() {
    Direction d = Direction::NEUTRAL;
    if (this->x > 0) {
        d = Direction::EAST;
    }
    else if (this->x < 0) {
        d = Direction::WEST;
    }
}

Direction Joystick::getDirY() {
    Direction d = Direction::NEUTRAL;
    if (this->y > 0) {
        d = Direction::NORTH;
    }
    else if (this->y < 0) {
        d = Direction::SOUTH;
    }
}

bool Joystick::buttonPressed() {
    // Check if button is pressed
    if (this->buttonPin != NULL && !test_bit(*this->buttonPin->pin, this->buttonPin->nr)) {
        if (!this->buttonPressedDown) {
            this->buttonPressedDown = true;
            return this->buttonPressedDown;
        }
        else {
            return false;
        }
    }
    this->buttonPressedDown = false;
    return this->buttonPressedDown;
}

void Joystick::calibrate()
{
    // Get center points
    this->centerX = this->readRawX();
    this->centerY = this->readRawY();
    this->buttonPressedDown = false;
}
#endif