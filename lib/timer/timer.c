// #include "timer.h"
// #include "../utilities/utilities.h"
// #include <stdint.h>

// void init_timer(){
// #ifdef __AVR_ATmega162__
//     set_bit(TCCR1A, COM1A0); // Compare match
//     set_bit(TIMSK, OCIE1A);
//     TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12);
//     OCR1A = 4800;

//     clr_bit(DDRB, 0);
//     set_bit(PORTB, 0);
// #endif
// }