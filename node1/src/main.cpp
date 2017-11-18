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

#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
// #include "../lib/comm/comm.h"
#include "../lib/utilities/utilities.h"
#include "lib/utilities/printf.h"

#include "lib/can/can.h"
#include "lib/spi/spi.h"
#include "lib/timer/timer.h"
#include "lib/joystick/joystick.h"
#include <stdint.h>

#include "../test/test.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "test.h"
#include "lib/utilities/printf.h"
#include "lib/pins/pins.h"
#include "lib/uart/uart.h"
#include "lib/adc/adc.h"
#include "lib/joystick/joystick.h"
#include "lib/timer/timer.h"
#include "../lib/spi/spi.h"
#include "../lib/can/can.h"
#include "../lib/slider/slider.h"
#include "../lib/fsm/fsm.h"
#include "../lib/display/screen.h"
//#include "../lib/display/screenhandler.h"
#include "../lib/menu/menu.h"
#include "../lib/can/canmsg.h"



int main(void)
{
	// Whad does these do?
	//set_bit(DDRB, 0);
	//set_bit(PORTB, 0);
	
	//testLab8();
	//testPrintfWithUart();
	//testMainLoop();
	// testCanLoopback();

	// Initialize all

	UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, false);

    ADC& adc = ADC::getInstance();

    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, &pb3);

    Slider & slider0 = Slider::getInstance(0);
    slider0.initialize(&adc, &pb2);

    Slider & slider1 = Slider::getInstance(1);
    slider1.initialize(&adc, &pb1);

    Screen screen_main   = Screen();
    Screen screen_header = Screen(&screen_main, 1, UPPER); // 1 page high, located on top
	Screen screen_full   = Screen(); // Full screen, does not have a subscreen
	

    MenuNode node_main("Main Menu");
    Menu main_menu(&node_main);


	FSM& fsm = FSM::getInstance();
	
	
	/*
	// Here: Load callback fns into FSM
	

	while (true)
	{
		fsm.runStateLoop();
	}*/
}
