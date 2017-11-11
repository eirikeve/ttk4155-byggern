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






void PID() {
    Motor& motor = Motor::getInstance();
    int16_t val = 0;
    
    int8_t u = (int8_t) motor.pidController(val);
    printf("Input: %d\n", u);

    motor.setDirection(u);
    if (u & (1 << 8)) {
        u = ((~u) + 1);
    }
    motor.setSpeed((uint8_t) u);

    if (u == 0) {
        clr_bit(*EN_PIN.port, EN_PIN.nr);
    }
    else {
        set_bit(*EN_PIN.port, EN_PIN.nr);
    }
}


void Motor::initialize(DAC* dac, Timer* timer, int16_t Kp, int16_t Ki, int16_t Kd, uint8_t T) {
    this->dac = dac;
    this->timer = timer;
    this->T = T;
    this->pid = PID_DATA(Kp, Ki, Kd);
    this->ref = 0;

    set_bit(*DIR_PIN.ddr, DIR_PIN.nr); // Pin for motor direction
    set_bit(*SEL_PIN.ddr, SEL_PIN.nr); // Pin for motor enable
    set_bit(*EN_PIN.ddr, EN_PIN.nr); // Pin for encoder reset
    set_bit(*OE_PIN.ddr, OE_PIN.nr); // Pin for encoder output enable
    set_bit(*RST_PIN.ddr, RST_PIN.nr); // Pin for selecting high/low encoder output
    set_bit(PORTD, PD0); // Move to I2C when ready
    set_bit(PORTD, PD1); // Move to I2C when ready


    this->encoderReset();

    this->timer->initialize(this->T, PID, NULL);
    this->timer->start();
}

void Motor::setPIDparameters(int16_t Kp, int16_t Ki, int16_t Kd) {
    this->pid.P_Factor = Kp;
    this->pid.I_Factor = Ki;
    this->pid.D_Factor = Kd;
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
    if (speed > 100 || speed < -100) {
        printf("Motor error: Max value in motor::run is 100, got %d\n", speed);
        return;
    }

    this->ref = speed;
}

int16_t Motor::getEncoderValue() {
    int16_t value = 0;
    clr_bit(*OE_PIN.port, OE_PIN.nr);
    clr_bit(*SEL_PIN.port, SEL_PIN.nr);
    _delay_us(20);
    value |= (PINK) << 8;
    set_bit(*SEL_PIN.port, SEL_PIN.nr);
    _delay_us(20);
    value |= PINK;
    this->encoderReset();
    set_bit(*OE_PIN.port, OE_PIN.nr);
    return value;
}

void Motor::encoderReset() {
    clr_bit(*RST_PIN.port, RST_PIN.nr);
    _delay_us(20);
    set_bit(*RST_PIN.port, RST_PIN.nr);
}


int16_t Motor::pidController(int16_t processValue) {
    int16_t errors, p_term, d_term;
	int32_t i_term, ret, temp;

    errors = this->ref - processValue;

    // Calculate Pterm and limit error overflow
    if (errors > this->pid.maxError) {
        p_term = MAX_INT;
    }
    else if (errors < - this->pid.maxError) {
        p_term = - MAX_INT;
    }
    else {
        p_term = this->pid.P_Factor * errors;
    }

    // Calculate Iterm and limit integral runaway
    temp = this->pid.sumError + errors;
    if (temp > this->pid.sumError) {
        i_term = MAX_I_TERM;
        this->pid.sumError = this->pid.maxSumError;
    }
    else if (temp < - this->pid.maxSumError) {
        i_term = -MAX_I_TERM;
        this->pid.sumError = -this->pid.maxSumError;
    }
    else {
        this->pid.sumError = temp;
        i_term = this->pid.I_Factor * this->pid.sumError;
    }

    // Calculate Dterm
	d_term = this->pid.D_Factor * (this->pid.lastProcessValue - processValue);

	this->pid.lastProcessValue = processValue;

	ret = (p_term + i_term + d_term);
	if (ret > MAX_INT) {
		ret = MAX_INT;
	} else if (ret < -MAX_INT) {
		ret = -MAX_INT;
	}

	return ((int16_t)ret);


}
#endif