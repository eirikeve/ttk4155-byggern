#pragma once
#include <avr/io.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include "../adc/adc.h"
#include "../pins/pins.h"

class Slider
{
    public:


        static Slider& getInstance(uint8_t id) {
            if(id == 0){
                static Slider instance(0);
                return instance;
            }
            else if (id == 1){
                static Slider instance(1);
                return instance;
            }
            else {
                printf("Slider error: Maximum number of instances are: 2, with the highest id: 1. Trying to access Slider id: %d\n", id);
                assert(false);
            }
        }
        void initialize(ADC *adc, PIN *buttonPin);

        int8_t read();

        uint8_t readRaw();
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