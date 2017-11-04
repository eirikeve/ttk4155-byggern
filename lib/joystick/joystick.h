#pragma once

#include <stdint.h>

#include "../adc/adc.h"
#include "../utilities/pin.h"

enum Direction
{
    NEUTRAL = 0,
    NORTH = 1,
    NORTH_EAST = 2,
    EAST = 3,
    SOUTH_EAST = 4,
    SOUTH = 5,
    SOUTH_WEST = 6,
    WEST = 7,
    NORTH_WEST = 8
};

/**
 * Class for reading Joystick signals in two directions using an ADC, and single button.
 * */
class Joystick
{
  public:
    static Joystick &getInstance()
    {
        static Joystick instance;
        return instance;
    }

    /**
         * Initialize the joystick with a threshold value
         * around the neutral position.
         * @param adc which adc to use.
         * @param threshold threshold for joystick. If
         *        abs(value - center) < threshold, then
         *        value = center.
         * @param buttonPin pin for button.
         * */
    void initialize(ADC *adc, uint8_t threshold, PIN *buttonPin);

    /**
         * Read joystick signal in both x and y direction. 
         * Values are formatted to be in range -128 to 127.
         * @param x pointer to variable for storing value in x direction.
         * @param y pointer to variable for storing value in y direction.
         * @return direction of joystick.
         * */
    Direction read(int8_t *x, int8_t *y);

    /**
         * Read joystick signal in x direction.
         * Values are formatted to be in range -128 to 127.
         * @return value in x direction.
         * */
    int8_t readX();

    /**
         * Read joystick signal in y direction.
         * Values are formatted to be in range -128 to 127.
         * @return value in y direction.
         * */
    int8_t readY();

    /**
         * Read raw value of joystick signal in x direction.
         * Values are not formatted, and in range 0 to 255.
         * @return value in x direction.
         * */
    uint8_t readRawX();

    /**
         * Read raw value of joystick signal in y direction.
         * Values are not formatted, and in range 0 to 255.
         * @return value in y direction.
         * */
    uint8_t readRawY();

    /**
         * Get direction of last read.
         * @return last direction of joystick.
         * 
         * NOTE: Uncertain behavior if used together with read
         * in a single direction. Use instead getDirX/y
         * */
    Direction getDir();

    /**
         * Get direction of last read in x direction.
         * @return last direction of joystick (EAST / WEST).
         * */
    Direction getDirX();

    /**
         * Get direction of last read in y direction.
         * @return last direction of joystick (SOUTH / NORTH).
         * */
    Direction getDirY();

    /**
         * Check if button is pressed.
         * @return true if button is pressed down, false else.
         * */
    bool buttonPressed();

  private:
    // Private due to singleton design pattern
    Joystick(){};

    // Calibrates the joystick with reading
    // center positions at initialize.
    void calibrate();

    // Center for joystick in x direction.
    uint8_t centerX;

    // Center for joystick in y direction.
    uint8_t centerY;

    // Value with which the joystick can be away from the centre in a dir before registering as that dir
    uint8_t threshold;

    // Last read value in x direction
    int8_t x;

    //Last read raw unfiltered value in x direction
    uint8_t rawX;

    // Last read value in y direction
    int8_t y;

    //Last read raw unfiltered value in y direction
    uint8_t rawY;

    // Is button pressed
    bool buttonPressedDown;

    // ADC for reading joystick signals
    ADC *adc;

    // Input pin for button
    PIN *buttonPin;

  public:
    // Deleted due to singleton design pattern
    Joystick(Joystick const &) = delete;

    // Deleted due to singleton design pattern
    void operator=(Joystick const &) = delete;
};