// #pragma once
// #include "SPI.h"
// #include "can.h"
// #include "MCP2515.h"
// extern "C" {
// 	#include <avr/interrupt.h>
// 	#include <avr/io.h>
// 	#include <stdio.h>
// 	#include "util/delay.h"
// }

// // #ifdef __AVR_ATmega162__
// // #define MCP2515_INT INT1_vect
// // #elif __AVR_ATmega2560__
// // #define MCP2515_INT INT4_vect
// // #endif

// static volatile uint8_t received_buffer_0 = 0;
// static uint8_t received_buffer_1 = 0;

// uint8_t getB0() {return received_buffer_0;}
// void clrB0() {received_buffer_0 = 0;}
// uint8_t getB1() {return received_buffer_1;}

// void can_init() {
// 	mcp2515_init();
//     // set CNF 1..3
// 	// Possible set TXRTSCRTL
// 	mcp2515_bit_modify(MCP_RXM0SIDH, 0xFF, 0x0); // Set MCP mask registers to 0, to accept all messages
// 	mcp2515_bit_modify(MCP_RXM0SIDL, 0xE0, 0x0);
// 	mcp2515_bit_modify(MCP_RXM1SIDH, 0xFF, 0x0);
// 	mcp2515_bit_modify(MCP_RXM1SIDL, 0xE0, 0x0);
	
// 	// Clr one-shot bit to reattempt transmission
// 	mcp2515_bit_modify(MCP_CANCTRL, 0x80, 0x0);
	
// 	// Set buffer 0 operating mode to 00 (receive any message matching mask/filters), and disable rollover bit
// 	mcp2515_bit_modify(MCP_RXB0CTRL, 0x64, 0x00); 

// 	// Set buffer 1 operating mode to 10 (receive only extended ID msg, which we do not send.)
// 	mcp2515_bit_modify(MCP_RXB1CTRL, 0x60, 0x40); 


// 	// Enable loopback mode
// 	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);

// 	mcp2515_bit_modify(MCP_CANINTE, 0x1, 0xFF);

// 		// Enable interrupt pin on AVR
// #ifdef __AVR_ATmega162__
// 	set_bit(GICR, INT1); // Enable interrupt1
// 	set_bit(MCUCR, ISC11); // Trigger falling edge
// #elif __AVR_ATmega2560__
//     EICRB |= (2<<ISC40); // Falling edge
// 	EIMSK |= (1<<INT4); // Enable the interrupt
// #endif
// }

// void can_message_send(can_message* msg){
// 	_delay_ms(1);
// 	uint8_t is_clear = mcp2515_read(MCP_TXB0CTRL);
// 	// printf("%d\n", is_clear);
// 	if (bit_is_set(is_clear, 3)) {
// 		//ERROR
// 		printf("ERROR, buffer is already pending transmission\n");
// 		return;
// 	}
// 	mcp2515_write(MCP_TXB0SIDH, msg->id >> 3); // Highest 5 bits of ID
// 	mcp2515_write(MCP_TXB0SIDL, msg->id << 5); // Lowest 3 bits of ID

// 	mcp2515_write(MCP_TXB0DLC, msg->length & 0x0F); // Msg length in bytes.

// 	for (int i = 0; i < msg->length & 0x0F; i++) {
// 		mcp2515_write(MCP_TXB0D0 + i, msg->data[i]);
// 	}	

// 	mcp2515_bit_modify(MCP_TXB0CTRL, 0x0B, 0x0B); //Request transmission, highest priority
// }

// can_message can_data_receive() {

// 	can_message msg;
	
// 	if (received_buffer_0) {
// 		// Get msg ID
// 		msg.id =  mcp2515_read(MCP_RXB0SIDH) << 3;
// 		msg.id |= mcp2515_read(MCP_RXB0SIDL) >> 5;

// 		msg.length = mcp2515_read(MCP_RXB0DLC) & 0x0F;

// 		for (int i = 0; i < msg.length; i++) {
// 			msg.data[i] = mcp2515_read(MCP_RXB0D0 + i);
// 		}
// 		received_buffer_0 = 0;
// 		// Clear interrupt flag
// 		mcp2515_bit_modify(MCP_CANINTF, 0x01, 0x00); 
// 		// printf("Recv flag %d\n", mcp2515_read(MCP_CANINTF));
		
// 	} else if (received_buffer_1) {
// 		// Buffer 1 not currently used. This code should never run.
// 		printf("ERROR, buffer 1 should not receive messages\n");
// 		received_buffer_1 = 0;
// 		mcp2515_bit_modify(MCP_CANINTF, 0x02, 0x00); // Clear interrupt flag
// 	}

// 	return msg;
// } 

// // ISR(MCP2515_INT) {
// // 	uint8_t reg = mcp2515_read(MCP_CANINTF);
// // 	// printf("Hei\n");
// // 	if (reg & 1) {
// // 		received_buffer_0 = true;
// // 	}
// // }