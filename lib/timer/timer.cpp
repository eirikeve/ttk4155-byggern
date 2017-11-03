#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "../utilities/utilities.h"


namespace {
#ifdef __AVR_ATmega162__
    #define TIMER0_TCCR TCCR1B
    #define TIMER0_OCRn OCR1A
    #define TIMER0_TIMSK TIMSK
    #define TIMER0_WGM2 WGM12
    #define TIMER0_OCIE OCIE1A
    #define TIMER0_TCNT TCNT1
    #define TIMER0_CS0 CS10
    #define TIMER0_CS0 CS11
    #define TIMER0_CS2 CS12

    #define TIMER1_TCCR TCCR3B
    #define TIMER1_OCRn OCR3A
    #define TIMER1_TIMSK TIMSK
    #define TIMER1_WGM2 WGM32
    #define TIMER1_OCIE OCIE3A
    #define TIMER1_TCNT TCNT3
    #define TIMER1_CS0 CS30
    #define TIMER1_CS1 CS31
    #define TIMER1_CS2 CS32

#elif __AVR_ATmega2560__
    #define TIMER0_TCCR TCCR3B
    #define TIMER0_OCRn OCR3A
    #define TIMER0_TIMSK TIMSK3
    #define TIMER0_WGM2 WGM32
    #define TIMER0_OCIE OCIE3A
    #define TIMER0_TCNT TCNT3
    #define TIMER0_CS0 CS30
    #define TIMER0_CS1 CS31
    #define TIMER0_CS2 CS32

    #define TIMER1_TCCR TCCR4B
    #define TIMER1_OCRn OCR4A
    #define TIMER1_TIMSK TIMSK4
    #define TIMER1_WGM2 WGM42
    #define TIMER1_OCIE OCIE4A
    #define TIMER1_TCNT TCNT4
    #define TIMER1_CS0 CS40
    #define TIMER1_CS1 CS41
    #define TIMER1_CS2 CS42
#endif
}

void TIMER0_vect() {
    Timer &t = Timer::getInstance(0);
    if(t.callbackFunction != NULL){
        (*(t.callbackFunction))();
    }
}

void TIMER1_vect() {
    Timer &t = Timer::getInstance(1);
    if(t.callbackFunction != NULL){
        (*(t.callbackFunction))();
    }
}

Timer::Timer(uint8_t id): id(id), callbackFunction(NULL) {}

void Timer::initialize(uint16_t ms, void (*callbackFunction)(void), PIN* pin) {
    cli();
    // Calculate top value for timer using a prescaler at 1024.
    uint16_t OCRn = (uint16_t) (ms * 0.001 *  (F_CPU) / (1024));
    if (this->id == 0) {

        // CTC mode
        TIMER0_TCCR |= (1<<TIMER0_WGM2);

        // Set top value for timer.
        TIMER0_OCRn = OCRn;

        // Enable interrupt for timer
        TIMER0_TIMSK |= (1<<TIMER0_OCIE);

    }
    else if (this->id == 1) {
        // CTC mode
        TIMER1_TCCR |= (1<<TIMER1_WGM2);

        // Set top value for timer.
        TIMER1_OCRn = OCRn;

        // Enable interrupt for timer
        TIMER1_TIMSK |= (1<<TIMER1_OCIE);
    }

    if (pin != NULL) {
        // Enable pin for output
        set_bit(*pin->ddr, pin->nr);
        set_bit(*pin->port, pin->nr);
    }

    this->callbackFunction = callbackFunction;

    // Enable global interrupts
    sei();

}

void Timer::start() {
    if (this->id == 0) {
        TIMER0_TCNT = 0x0000;
        TIMER0_TCCR |= ((1 << TIMER0_CS0) | (1 << TIMER0_CS2));
    }
    else if (this->id == 1) {
        TIMER1_TCNT = 0x0000;
        TIMER1_TCCR |= ((1 << TIMER1_CS0) | (1 << TIMER1_CS2));
    }
}

void Timer::stop() {
    if (this->id == 0) {
        TIMER0_TCCR &= ~((1 << TIMER0_CS0) | (1 << TIMER0_CS1) | (1 << TIMER0_CS2));
    }
    else if (this->id == 1) {
        TIMER1_TCCR &= ~((1 << TIMER1_CS0) | (1 << TIMER1_CS1) | (1 << TIMER1_CS2));
    }
}
