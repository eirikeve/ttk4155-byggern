#pragma once
#include <avr/io.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include "../adc/adc.h"
#include "../pins/pins.h"

/**
 * Class for reading capacitive slider signals in one direction using an ADC, and single button.
 * */
class Slider
{
    public:


        static Slider& getInstance(uint8_t id) {
            if(id == 0){
                static Slider instance(0);
                return instance;
            }
            else {
                static Slider instance(1);
                return instance;
            }
        }
        /**
         * Initializes the instance.
         * @param adc: Pointer to ADC object
         * @param buttonPin: the pin we read the slider button from
         **/
        void initialize(ADC *adc, PIN *buttonPin);

        /**
         * Read the current slider position, where center is 0
         **/
        int8_t read();

        /**
         * Read the current slider position, where left is 0
         **/
        uint8_t readRaw();

        /**
         * Return true if this slider's button is pressed down
         **/
        bool buttonPressed();

    private:

        // Private due to singleton design pattern
        Slider(uint8_t id);

        // Id of slider
        uint8_t id;

        // Is button pressed
        bool buttonPressedDown;
        
        // ADC for reading joystick signals
        ADC *adc;

        // Input pin for button
        PIN *buttonPin;
        
    public:
        // Deleted due to singleton design pattern
        Slider(Slider const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(Slider const&)  = delete;

};