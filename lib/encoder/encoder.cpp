#ifdef __AVR_ATmega2560__
#include <util/delay.h>
#include "encoder.h"
#include "../utilities/utilities.h"
#include "lib/pins/pins.h"


#define SEL_PIN ph3

#define OE_PIN ph5
#define RST_PIN ph6

Encoder::Encoder() {
    set_bit(*SEL_PIN.ddr, SEL_PIN.nr); // Pin for selecting high/low encoder output
    set_bit(*OE_PIN.ddr, OE_PIN.nr); // Pin for encoder output enable
    set_bit(*RST_PIN.ddr, RST_PIN.nr); // Pin for encoder reset

    DDRK = 0;

    this->reset();
}


int16_t Encoder::read() {
    int16_t value = 0;
    clr_bit(*OE_PIN.port, OE_PIN.nr);
    clr_bit(*SEL_PIN.port, SEL_PIN.nr);
    _delay_us(20);
    value |= (PINK) << 8;
    set_bit(*SEL_PIN.port, SEL_PIN.nr);
    _delay_us(20);
    value |= PINK;
    this->reset();
    set_bit(*OE_PIN.port, OE_PIN.nr);
    return value;
}


void Encoder::reset() {
    clr_bit(*RST_PIN.port, RST_PIN.nr);
    _delay_us(20);
    set_bit(*RST_PIN.port, RST_PIN.nr);
}


#endif