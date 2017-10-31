#include "timer.h"
#include "../utilities/utilities.h"
#include <stdint.h>
#include <stdio.h>


// Timer::Timer(): func(NULL) {}

// void Timer::init(int nr, uint16_t ms, void (*func)()) {
// #ifdef __AVR_ATmega162__
//     if (nr == 0) {
//         TCCR1B |= (1<<WGM12);
//         OCR1A = (uint16_t) (ms * 0.001 *  (F_CPU) / (1024));
//         TIMSK |= (1<<OCIE1A);
//     }
// #endif
//     this->func = func;
// }

// void Timer::start() {
// #ifdef __AVR_ATmega162__
//     TCNT1 = 0x0000;
//     TCCR1B |= ((1 << CS10) | (1 << CS12));
// #endif
// }

// void Timer::stop() {
// #ifdef __AVR_ATmega162__
//     clr_bit(TCCR1B, CS10);
//     clr_bit(TCCR1B, CS11);
//     clr_bit(TCCR1B, CS12);
// #endif
// }

// void Timer::callFunc()
// {
//     if (this->func != NULL)
//     {
//         this->func();
//     }
// }




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
#ifdef __AVR_ATmega162__
void init_timer(uint16_t ms)
{

    // set_bit(TCCR1A, COM1A0); // Compare match
    // set_bit(TIMSK, OCIE1A);
    // TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12);
    // OCR1A = 4800;

    set_bit(DDRB, 0);
    set_bit(PORTB, 0);

    TCCR1B |= (1<<WGM12);
    OCR1A = (uint16_t) (ms * 0.001 *  (F_CPU) / (1024));
    TIMSK |= (1<<OCIE1A);
    sei();
    TCNT1 = 0x0000;
    TCCR1B |= ((1 << CS10) | (1 << CS12));
}   

ISR(TIMER1_COMPA_vect) {
    // Timer t = Timer::instance(0);
    // t.callFunc();
    PORTB ^= (1 << PB0);
}
// #elif __AVR_ATmega2560__
// void init_timer() 
// {
//     // set PB5 output
//     set_bit(DDRB, DDB5);
//     // clr at cmp match, set at bottom
//     set_bit(TCCR1A, COM1A1);

//     // Set mode 14, fast PWM
//     set_bit(TCCR1A, WGM11);
//     set_bit(TCCR1B, WGM12);
//     set_bit(TCCR1B, WGM13);

//     // prescaler 8
//     set_bit(TCCR1B, CS11);

//     // top = 39999
//     ICR1 = 39999;
    
//     sei();
// }

// void pwm_set_duty(float ms) {
//     printf("%d\n", (uint8_t) ms * 1000);
//     if (ms >= 1.0 && ms <= 2.0) {
//         uint16_t foo = (ms*ICR1)/20;
//         OCR1A = foo;
//     }

// }
#endif

