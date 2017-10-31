#pragma once
extern "C" {
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include <stdint.h>
    #include <stdio.h>
}

#include "../utilities/utilities.h"


// class Timer{
// private:

//     Timer();
//     void (*func)();

// public:

//     static Timer instance(int nr) {
//         if (nr == 0) {
//             static Timer timer0 = Timer();
//             return timer0;
//         }
//     }

//     void init(int nr, uint16_t ms, void (*func)());
//     void start();
//     void stop();
//     void callFunc();

// };

#ifdef __AVR_ATmega162__
void init_timer(uint16_t ms);
ISR(TIMER1_COMPA_vect);

// #elif __AVR_ATmega2560__

// void init_timer();
// void pwm_set_duty(float ms);
#endif
