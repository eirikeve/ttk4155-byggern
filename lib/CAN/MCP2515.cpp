#pragma once
#include "MCP2515.h"

uint8_t mcp2515_init(){
	uint8_t value;
	 /* Set PB4 (SS' = OC3B) to low, activating the MCP2515 (slave) SPI*/
	//clr_bit(DDRB, DDB4);

	SPI_init(); // initialize SPI
	mcp2515_reset();
	
	// Self test
	value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG){
		printf("MCP2515 is NOT in configuration mode after reset!\n");
		return 1;
	}
	
	// More initialization¨
	// Enable pin interrupt upon receiving messages
	// mcp2515_bit_modify(MCP_RX_INT, 1);
	mcp2515_bit_modify(0xF0, 0xE0, 0x40);

	
	return 0;
}

uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	
	clr_bit(PORTB, 4); // Select CAN-controller
	
	SPI_send(MCP_READ); // Send read command
	SPI_send(address); // Send address
	result = SPI_read(); // Read result
	
	set_bit(PORTB, 4); // Deselect CAN-controller
	
	return result;
}

void mcp2515_write(uint8_t address, uint8_t data)
{
	clr_bit(PORTB, 4); // Select CAN-controller

	SPI_send(MCP_WRITE);
	SPI_send(address);
	SPI_send(data);

	set_bit(PORTB, 4); // Deselect CAN-controller

	return;

}
void mcp2515_request_to_send(uint8_t rts)
{
	clr_bit(PORTB, 4); // Select CAN-controller
	SPI_send(rts);
	set_bit(PORTB, 4); // Deselect CAN-controller	
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
	clr_bit(PORTB, 4); // Select CAN-controller
	
	SPI_send(MCP_BITMOD);
	SPI_send(address);
	SPI_send(mask);
	SPI_send(data);
	
	set_bit(PORTB, 4); // Deselect CAN-controller
	
		return;
}

void mcp2515_reset()
{
	clr_bit(PORTB, 4); // Select CAN-controller
	SPI_send(MCP_RESET);
	set_bit(PORTB, 4); // Deselect CAN-controller
	
}
void mcp_read_status()
{
	clr_bit(PORTB, 4); // Select CAN-controller
	SPI_send(MCP_READ_STATUS);
	set_bit(PORTB, 4); // Deselect CAN-controller
}
