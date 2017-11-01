#ifdef __AVR_ATmega2560__

#include "servo.h"
#include <stdio.h>

Servo::Servo(){
    // set PB5 output
    set_bit(DDRB, DDB5);
    // clr at cmp match, set at bottom
    set_bit(TCCR1A, COM1A1);

    // Set mode 14, fast PWM
    set_bit(TCCR1A, WGM11);
    set_bit(TCCR1B, WGM12);
    set_bit(TCCR1B, WGM13);

    // prescaler 8
    set_bit(TCCR1B, CS11);

    // TOP
    ICR1 = 39999;
}


void Servo::initialize(uint16_t maxAngle) {
    this->maxAngle = maxAngle;
}

void Servo::setAngle(int16_t angle) {

    // Calculate duty cycle 0 <= D <= 1, with period
    // T = 0.02 sec (50 Hz). Calculates time in ms
    // the pwn signal should be high to get the desired angle.
    // DT = 2 => angle = -90 deg, DT = 1 => angle = +90 deg
    // time in ms is calculated with the following formula
    // DT = 1.5 - angle / 180
    float ms = 1.5 - (float) angle / 180;
    this->setDutyCycle(ms);
}

void Servo::setAnglePercentage(int8_t percentage) {

    // Calculate duty cycle 0 <= D <= 1, with period
    // T = 0.02 sec (50 Hz). Calculates time in ms
    // the pwn signal should be high to get the desired angle.
    // DT = 2 => angle = -90 deg, DT = 1 => angle = +90 deg
    // time in ms is calculated with the following formula
    // DT = 1.5 - percentage * maxAngle / (100 * 180)

    float ms = 1.5 - percentage * (float) this->maxAngle / (18000);
    this->setDutyCycle(ms);
}

void Servo::setDutyCycle(float ms) { 
    // printf("ms: %d\n", (int) (ms * 100));
    OCR1A = (uint16_t) (ms*ICR1)/20;
}



#endif