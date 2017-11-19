#ifdef __AVR_ATmega162__

#include <stdio.h>
#include <avr/io.h>

#include "adc.h"
#include "../utilities/utilities.h"

ADC::ADC() : addr((uint16_t*) 0x1400) {
    set_bit(MCUCR, SRE);
    clr_bit(DDRE, 0);
}

uint8_t ADC::read(CHANNEL c)
{
    clr_bit(DDRE, 0);
    *(this->addr) = (uint8_t)c;
    loop_until_bit_is_clear(PINE, PE0);
    return *(this->addr);
}
#endif