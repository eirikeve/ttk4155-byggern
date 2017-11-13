#ifdef __AVR_ATmega2560__
#include <avr/io.h>
#include <util/delay.h>

#include "dac.h"


void DAC::initialize(uint8_t address) {
    this->address = address;
}

void DAC::convert(uint8_t value) {
    unsigned char i2c_package[3] = {(0b0101 << 4) | this->address, 0x00, value};
    TWI_Start_Transceiver_With_Data(i2c_package, 3);
    _delay_ms(0.5);
}
#endif