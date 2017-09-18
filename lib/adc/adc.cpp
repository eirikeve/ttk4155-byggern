#include "adc.h"
#include "avr/io.h"

uint8_t ADC::testAdc() {

    uint16_t test = 0x1401;
    while (test_bit(PINE, 0)) {}

    return *test;
}