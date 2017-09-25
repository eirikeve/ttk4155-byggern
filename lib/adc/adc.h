// ADC class for use in TTK4155
// Written by Håvard Borge, Eirik Vesterkjær
// 18/09/2017

#pragma once
#include "../utilities/utilities.h"
#include <stdint.h>


enum CHANNEL {
    CH1 = 0b100,
    CH2 = 0b101,
    CH3 = 0b110,
    CH4 = 0b111
};


class ADC
{
private:
    CHANNEL c;
    const uint8_t t_c = 45; 
    volatile uint16_t *addr = (uint16_t *) ADC_ADDR;

public:
    ADC();
    uint8_t read(CHANNEL c);
    uint8_t testAdc();

};