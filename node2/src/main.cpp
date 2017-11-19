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
#include "game_functions.h"

int main(void)
{
	// initilize everything
	UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    printf("Node2 startup\n");

    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, false);

    Servo& servo = Servo::getInstance();
    servo.initialize(45);

    TWI_Master_Initialise();
    sei();
    
    DAC& dac = DAC::getInstance();
    dac.initialize(0x00);

    Timer& timer = Timer::getInstance(0);
    Encoder& encoder = Encoder::getInstance();

    Motor& motor = Motor::getInstance();

    Solenoid & solenoid = Solenoid::getInstance();

    ADC_internal & adc = ADC_internal::getInstance();

    IR_detector& ir = IR_detector::getInstance();
    ir.initialize(&adc, NULL, 4);

    float Kp = 0.008;
    float Ti = 100000;
    float Td = 0;
    motor.initialize(&dac, &timer, &encoder, Kp,Ti,Td, 5);

    CanMessage recv;
    CanMessage msg;

    printf("Sending RESET Until ACK\n");
    sendResetUntilACK();


    msg.id = CAN_ID_ACK;
    msg.length = CAN_LENGTH_ACK;
    msg.data[0] = 0b0;

    printf("Node2 starting loop\n");
	
	while(1){
        recv = can.receive();
        // RESET is transmitted by node1 upon startup. Respond with ACK to show that node2 is running.
        if (recv.id == CAN_ID_RESET)
        {
            printf("Revcd RESET\n");
            can.transmit(&msg);
        }
        else if (recv.id == CAN_ID_START_GAME)
        {
            printf("Recvd START, sending ACK\n");
            can.transmit(&msg);
			runGame();
            printf("Back to Main Loop\n");
        }
	}
}