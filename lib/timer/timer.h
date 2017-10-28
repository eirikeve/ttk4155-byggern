extern "C" {
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include <stdint.h>
    #include <stdio.h>
}

#include "../utilities/utilities.h"

// class Timer {
// public:
//     Timer(uint16_t ms);
// }
void init_timer(uint16_t ms){
    #ifdef __AVR_ATmega162__
        // set_bit(TCCR1A, COM1A0); // Compare match
        // set_bit(TIMSK, OCIE1A);
        // TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12);
        // OCR1A = 4800;
    
        set_bit(DDRB, 0);
        set_bit(PORTB, 0);

        TCCR1B |= (1<<WGM12);
        OCR1A = (uint16_t) (ms * 0.001 *  (4915200) / (1024));
        sei();
        TIMSK |= (1<<OCIE1A);

        TCNT1 = 0x0000;
        TCCR1B |= ((1 << CS10) | (1 << CS12));
    #endif
    }

ISR(TIMER1_COMPA_vect) {
    PORTB ^= (1 << PB0);
}