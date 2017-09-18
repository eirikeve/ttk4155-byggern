#include "adc.h"
extern "C" {
    #include "avr/io.h"  
    #include <util/delay.h>
}
#include "../utilities/utilities.h"

ADC::ADC() {
	set_bit(MCUCR, SRE);
}

volatile uint8_t ADC::read(CHANNEL c){
    // _delay_ms(this->t_c);
    loop_until_bit_is_clear(PORTE, PE0);
    *(this->addr) = (uint8_t) c;
    // _delay_ms(this->t_c);
    loop_until_bit_is_clear(PORTE, PE0);
    return *(this->addr);
}


uint8_t ADC::testAdc(){

    volatile uint8_t *ext_ram = (uint8_t *) 0x1400;
    
    loop_until_bit_is_clear(PORTE, PE0);
    uint8_t mux = 0b100;
    ext_ram[0] = mux;
    loop_until_bit_is_clear(PORTE, PE0);
    return ext_ram[0];	
}