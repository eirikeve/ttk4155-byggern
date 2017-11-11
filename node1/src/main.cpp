// /*
//  * Test.c
//  *
//  * Created: 04.09.2017 11:26:38
//  *  Author: aasmune
//  */

// extern "C" {
// #include <avr/io.h>
// #include "util/delay.h"
// #include <stdio.h>
// #include "lib/comm/comm.h"
// #include <avr/pgmspace.h>
// }

// #include "../lib/CAN/SPI.h"
// #include "lib/tempDisplay/temp.h"
// #include "../lib/CAN/MCP2515.h"
// #include <stdint.h>
// #include "lib/fonts/fonts.h"
// #include "lib/CAN/can.h"

// int main(void)
// {
// 	// SPI_init();
// 	init_uart();
// 	// printf("Hei\n");
// 	// mcp2515_init();
// 	set_bit(DDRB, 0);
// 	clr_bit(DDRE, 0);
// 	init_uart();
// 	clr_bit(PORTB, PB4);
// 	can_init();
// 	sei();
// 	can_message msg;
// 	msg.id = 2;
// 	msg.length = 1;
// 	uint8_t i = 0;
// 	msg.data[0] = 0;

// 	// printf("\n\nAfter init:\n");
// 	// printf("RX0IF: %d\n", mcp2515_read(MCP_CANINTF) & 1);
// 	// printf("Sending now\n");
// 	// can_message_send(&msg);
// 	// printf("After sending msg:\n");
// 	// printf("RX0IF: %d\n", mcp2515_read(MCP_CANINTF) & 1);
// 	// can_message recv = can_data_receive();
// 	// printf("After recv msg:\n");
// 	// printf("RX0IF: %d\n", mcp2515_read(MCP_CANINTF) & 1);
// 	// printf("Sending now\n");
// 	// can_message_send(&msg);
// 	// printf("After sending msg:\n");
// 	// printf("RX0IF: %d\n", mcp2515_read(MCP_CANINTF) & 1);
// 	// can_message recv1 = can_data_receive();
// 	// printf("After recv1 msg:\n");
// 	// printf("RX0IF: %d\n", mcp2515_read(MCP_CANINTF) & 1);

// 	while (1)
// 	{
// 		(msg.data[0])++;
// 		can_message_send(&msg);
// 		can_message recv = can_data_receive();
// 		printf("id: %d, len: %d, data: %d\n", recv.id, recv.length, recv.data[0]);

// 	// 	// mcp2515_write(0x36, 'X');
// 	// 	// printf("%c\n", mcp2515_read(0x36));
// 	// 	// clr_bit(PORTB, PB4); // Select CAN-controller
// 	// 	// SPI_send(0xA5);
// 	// 	// // _delay_ms(1000);
// 	// 	// set_bit(PORTB, PB4); // Select CAN-controller
// 	// 	// mcp2515_write(0x00, 'z');
// 	// 	// printf("asd %d\n", mcp2515_read(0x01));
// 	// 	set_bit(PORTB, 0);
// 	// 	_delay_ms(100);
// 	// 	clr_bit(PORTB, 0);
// 	// 	_delay_ms(100);
// 	}
// }

extern "C" {
#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
// #include "../lib/comm/comm.h"
#include "../lib/utilities/utilities.h"
}
#include "../lib/CAN/SPI.h"
#include "../lib/CAN/MCP2515.h"
#include "lib/CAN/can.h"
#include "lib/timer/timer.h"
#include "lib/joystick/joystick.h"
#include <stdint.h>

// #include "lib/joystick/joystick.h"
#include "test/test.h"

void toggle_led() {
	PORTB ^= (1 << PB0);
}

int main(void)
{

	testTimer();
	set_bit(DDRB, 0);
	set_bit(PORTB, 0);
	// init_timer(500);

	can_init();
	testScreen();
	
	sei();
	can_message msg;
	msg.id = 2;
	msg.length = 3;
	// Joystick joystick(10);
	int8_t x;
	int8_t y;
	// }
	while (1)
	{
		// Direction dir = joystick.read(&x, &y);
		// printf("Node1\n");
		// PORTB ^= (1 << PB0);
		// _delay_ms(500);
		msg.data[0] = x;
		msg.data[1] = y;
		// msg.data[2] = dir;
		// (msg.data[1])++;		
		can_message_send(&msg);
	// 	can_message recv = can_data_receive();
	// 	if (recv.id != NULL)
	// 	{
	// 		printf("id: %d, len: %d, data: %d\n", recv.id, recv.length, recv.data[0]);
	// 	}
	}

	// while(1) {
	// 	// printf("Hello world\n");
	// 	// mcp2515_write(0x36, 0xa5);
	// 	// printf("Data: %d\n", mcp2515_read(0x36));
	// }
}
