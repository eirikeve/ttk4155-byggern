#ifdef __AVR_ATmega2560__
#include "adc_internal.h"
#include "../utilities/utilities.h"
ADC_internal::ADC_internal() {

    // // Enable the ADC
    // set_bit(ADCSRA, ADEN);

    // // ref voltage to AREF 
    // set_bit(ADMUX, REFS0);
    // clr_bit(ADMUX, REFS1);
      
    
    // // prescale clock frequency down with a factor of 128
    // set_bit(ADCSRA, ADPS0);
    // set_bit(ADCSRA, ADPS1);
    // set_bit(ADCSRA, ADPS2);

    // //Select channel 0
    // clr_bit(ADMUX, MUX2);
    // clr_bit(ADMUX, MUX1);
    // clr_bit(ADMUX, MUX0);

    // Enable the ADC
    ADCSRA |= (1 << ADEN);
    
    // Set reference voltage for ADC to AREF
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    // Set the prescaler
    ADCSRA |= (1 << ADPS0);
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 << ADPS2);

    // Select channel for internal adc. Default is ADC0
    ADMUX &= ~(1 << MUX0);
    ADMUX &= ~(1 << MUX1);
    ADMUX &= ~(1 << MUX2);
}


uint8_t ADC_internal::read() {
    // Start conversion
    set_bit(ADCSRA, ADSC);

    while (test_bit(ADCSRA, ADSC));
    uint8_t data = ADCL;
    uint8_t dataH = ADCH;
    return data;
}


#endif