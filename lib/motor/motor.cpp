#ifdef __AVR_ATmega2560__
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


#include "lib/utilities/utilities.h"


#include "motor.h"

#define DIR_PIN ph1
#define EN_PIN ph4



void controller() {
    Motor& motor = Motor::getInstance();
    int16_t value = motor.encoder->read();
    motor.processValue += value;
    
    int8_t u = motor.pid.controller(motor.ref, motor.processValue);
    // printf("Input: %d\n", u);
    motor.u = u;
    motor.enc = value;

    if (u & (1 << 8)) {
        motor.goLeft();

        // Take absolute value of input signal
        u = ((~u) + 1);
    }
    else {
        motor.goRight();
    }

    motor.setSpeed((uint8_t) u);

    if (u == 0) {
        clr_bit(*EN_PIN.port, EN_PIN.nr);
    }
    else {
        set_bit(*EN_PIN.port, EN_PIN.nr);
    }
}


void Motor::initialize(DAC* dac, Timer* timer, Encoder* encoder, float Kp, float Ti, float Td, uint8_t T) {
    this->dac = dac;
    this->timer = timer;
    this->encoder = encoder;
    this->T = T;
    this->pid = PID();
    this->ref = 0;
    this->processValue = 0;

    set_bit(*EN_PIN.ddr, EN_PIN.nr); // Pin for motor enable
    set_bit(*DIR_PIN.ddr, DIR_PIN.nr); // Pin for motor direction

    
    set_bit(PORTD, PD0); // Move to I2C when ready
    set_bit(PORTD, PD1); // Move to I2C when ready

    this->setPIDparameters(Kp, Ti, Td);
    this->timer->initialize(this->T, controller, NULL);
    this->timer->start();
}

void Motor::setPIDparameters(float Kp, float Ti, float Td) {
    this->pid.setParameters(Kp, Kp * this->T / (float) Ti, Kp * Td / (float) this->T);
}

void Motor::setSpeed(uint8_t speed) {
    this->dac->convert(speed);
}

void Motor::goRight() {
    set_bit(*DIR_PIN.port, DIR_PIN.nr);
}

void Motor::goLeft() {
    clr_bit(*DIR_PIN.port, DIR_PIN.nr);
}

void Motor::run(int8_t speed) {
    if (speed > 100 || speed < -100) {
        printf("Motor error: Max value in motor::run is 100, got %d\n", speed);
        return;
    }

    this->ref = speed;
    // motor.setDirection(u);
    // if (u & (1 << 8)) {
    //     u = ((~u) + 1);
    // }
    // motor.setSpeed((uint8_t) u);

    // if (u == 0) {
    //     clr_bit(*EN_PIN.port, EN_PIN.nr);
    // }
    // else {
    //     set_bit(*EN_PIN.port, EN_PIN.nr);
    // }
}


#endif