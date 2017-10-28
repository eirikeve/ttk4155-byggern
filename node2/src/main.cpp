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

int main(void)
{
	init_uart();
	can_init();
	SPI_init();
	
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
	msg.data[0] = 0xa5;
	clr_bit(DDRE, DDE4);
	set_bit(PORTE, PB4);

	while (1)
	{
		(msg.data[0])++;
		can_message_send(&msg);
		// can_message recv = can_data_receive();
		// printf("id: %d, len: %d, data: %d\n", recv.id, recv.length, recv.data[0]);
	}
	
	
	// while(1) {
	// 	// printf("Hello world\n");
	// 	// mcp2515_write(0x36, 0xa5);
	// 	// printf("Data: %d\n", mcp2515_read(0x36));
	// }
}