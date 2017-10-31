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
#include "../lib/comm/comm.h"
#include "../lib/utilities/utilities.h"
}
#include "../lib/CAN/SPI.h"
#include "../lib/CAN/MCP2515.h"
#include "lib/CAN/can.h"
#include <stdint.h>
#include "lib/timer/timer.h"
#include "lib/adc_internal/adc_internal.h"
#include "lib/servo/servo.h"
#include "test/test.h"

int main(void)
{
	// testServoPercentage();
	testServoAngle();
	// Servo& servo = Servo::getInstance();
	// servo.initialize(40);
	// init_timer();
	init_uart();
    // can_init();
	// ADC_internal& adc_internal = ADC_internal::getInstance();
	
	// while (true) {
	// 	printf("ADC: %d\n", adc_internal.read());
	// }
	// SPI_init();

	// while(1) {
	// 	SPI_send(0xa5);
	// }
	// mcp2515_write(0x36, 0xa5);
	// while(1) {
	// 	printf("%d\n", mcp2515_read(0x36));
	// }
		
	sei();
	can_message msg;
	msg.id = 2;
	msg.length = 1;
	uint8_t i = 0;
	msg.data[0] = 0x00;
	int8_t percentage = -100;
	// clr_bit(DDRE, DDE4);
	// set_bit(PORTE, PB4);

	while (1)
	{
		// printf("percentage: %d, ", percentage);
		// servo.setAnglePercentage(percentage);
		// percentage++;
		// if (percentage > 100) {
		// 	percentage = -100;
		// }
		// pwm_set_duty(1.0);
		// printf("HEi\n");
		// (msg.data[0])++;
		// can_message_send(&msg);
		// // _delay_ms(1000);
		// // can_message recv = can_data_receive();
		// // printf("id: %d, len: %d, data: %d\n", recv.id, recv.length, recv.data[0]);
		// can_message recv = can_data_receive();
		// if (recv.id != NULL)
		// {
		// 	// printf("Hei\n");
		// 	// printf("%d\n", (uint8_t) (((float)((int8_t) recv.data[0]) / 200 + 1.50) * 100));
		// 	// printf("%f\n", 0.1);
		// 	pwm_set_duty((float)(((float)((int8_t) recv.data[0]) / 200 + 1.50)));
		// 	// printf("x: %d, y: %d, dir: %d\n", (int8_t) recv.data[0],(int8_t)  recv.data[1], -1);
		// 	// printf("id: %d, len: %d, data: %d\n", recv.id, recv.length, recv.data[0]);
		// }
		// _delay_ms(100);
	}

	// while(1) {
	// 	// printf("Hello world\n");
	// 	// mcp2515_write(0x36, 0xa5);
	// 	// printf("Data: %d\n", mcp2515_read(0x36));
	// }
}