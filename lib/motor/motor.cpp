#ifdef __AVR_ATmega2560__
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


#include "lib/utilities/utilities.h"
#include "lib/pins/pins.h"

#include "motor.h"


#define DIR_PIN ph1
#define SEL_PIN ph3
#define EN_PIN ph4
#define OE_PIN ph5
#define RST_PIN ph6


void Motor::initialize(DAC* dac, uint8_t Kp, uint8_t Ki, uint8_t Kd, uint8_t T) {
    this->dac = dac;
    this->T = T;

    set_bit(*DIR_PIN.ddr, DIR_PIN.nr); // Pin for motor direction
    set_bit(*SEL_PIN.ddr, SEL_PIN.nr); // Pin for motor enable
    set_bit(*EN_PIN.ddr, EN_PIN.nr); // Pin for encoder reset
    set_bit(*OE_PIN.ddr, OE_PIN.nr); // Pin for encoder output enable
    set_bit(*RST_PIN.ddr, RST_PIN.nr); // Pin for selecting high/low encoder output
    set_bit(PORTD, PD0); // Move to I2C when ready
    set_bit(PORTD, PD1); // Move to I2C when ready

    this->setPIDparameters(Kp, Ki, Kd);
    this->encoderReset();
}

void setPIDparameters(uint8_t Kp, uint8_t Ki, uint8_t Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
}

void Motor::setSpeed(uint8_t speed) {
    this->dac->convert(speed);
}

void Motor::setDirection(int8_t dir) {

    if (dir & (1 << 8)) {
        clr_bit(*DIR_PIN.port, DIR_PIN.nr);
    }
    else {
        set_bit(*DIR_PIN.port, DIR_PIN.nr);
    }
    
}

void Motor::run(int8_t speed) {
    if (abs(speed) > 100) {
        printf("Motor error: Max value in motor::run is 100, got %d\n", speed);
        return;
    }
    if (speed & (1 << 8)) {
        speed = ((~speed) + 1);
    }
    this->setSpeed((uint8_t) speed * 2.55);

    this->setDirection(speed);

    if (speed == 0) {
        clr_bit(*EN_PIN.port, EN_PIN.nr);
    }
    else {
        set_bit(*EN_PIN.port, EN_PIN.nr);
    }
}
uint8_t Motor::controller(int8_t ref) {
    int16_t encoderValue = this->getEncoderValue();

    int16_t error = ref - encoderValue;
}

int16_t Motor::getEncoderValue() {
    int16_t value = 0;
    clr_bit(*EN_PIN.port, EN_PIN.nr);
    clr_bit(*SEL_BIT.port, SEL_BIT.nr);
    _delay_ms(0.02);
    value |= (PINK) << 8;
    set_bit(*SEL_BIT.port, SEL_BIT.nr);
    _delay_ms(0.02);
    value |= PINK;
    this->encoderReset();
    set_bit(*EN_PIN.port, EN_PIN.nr);
    return value;
}

void Motor::encoderReset() {
    clr_bit(*RST_BIT.port, RST_BIT.nr);
}
#endif