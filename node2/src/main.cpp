/*
 * Test.c
 *
 * Created: 04.09.2017 11:26:38
 *  Author: aasmune
 */
extern "C" {
#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
// #include "../lib/comm/comm.h"
#include "../lib/utilities/utilities.h"
}
#include <stdint.h>
#include "lib/timer/timer.h"
#include "lib/adc_internal/adc_internal.h"
#include "lib/servo/servo.h"
#include "test/test.h"
#include "lib/uart/uart.h"
#include "lib/utilities/printf.h"

int main(void)
{
	// initilize everything
	UART & uart = UART::getInstance();
    uart.initialize(9600);

    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, false);

    Servo& servo = Servo::getInstance();
    servo.initialize(90);

    TWI_Master_Initialise();
    sei();
    
    DAC& dac = DAC::getInstance();
    dac.initialize(0x00);

    Timer& timer = Timer::getInstance(0);
    Encoder& encoder = Encoder::getInstance();

    Motor& motor = Motor::getInstance();

    Solenoid & solenoid = Solenoid::getInstance();

    IR_detector& ir = IR_detector::getInstance();
    ir.initialize(&adc, NULL, 4);

    float Kp = 0.008;
    float Ti = 100000;
    float Td = 0;
    motor.initialize(&dac, &timer, &encoder, Kp,Ti,Td, 5);
	
	while(1){
		// if we want to start pingpong game
		if (recv.data[4]){
			testGame();
		}
		
		// etc
	}
}