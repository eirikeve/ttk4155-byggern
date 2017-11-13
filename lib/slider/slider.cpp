#ifdef __AVR_ATmega162__
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "slider.h"
#include "../adc/adc.h"
#include "../utilities/utilities.h"


Slider::Slider(uint8_t id) {
    this->id = id;
    
}

void Slider::initialize(ADC *adc, PIN *buttonPin) {
    this->adc = adc;
    this->buttonPressedDown = false;
    this->buttonPin = buttonPin;

    // TODO: Initialize the button.
    if (buttonPin != NULL) {
        // Enable pin for input
        clr_bit(*buttonPin->ddr, buttonPin->nr);
    }
}


int8_t Slider::read()
{
    return this->readRaw() - 127;
}

uint8_t Slider::readRaw()
{
    if (this->id == 0) {
        return this->adc->read(CHANNEL::CH3);
    }
    else if (this->id == 1) {
        return this->adc->read(CHANNEL::CH4);
    }
}

bool Slider::buttonPressed() {
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

#endif