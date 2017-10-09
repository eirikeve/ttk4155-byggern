#pragma once
#include "MCP2515.h"

uint8_t mcp2515_init(){
	uint8_t value;
	 /* Set PB4 (SS' = OC3B) to low, activating the MCP2515 (slave) SPI*/
	clr_bit(DDRB, DDB4);

	SPI_init(); // initialize SPI
	mcp2515_reset();
	
	// Self test
	mcp2515_read(MCP_CANSTAT, &value);
	if ((value & MODE_MASK) != MODE_CONFIG){
		printf("MCP2515 is NOT in configuration mode after reset!\n");
		return 1;
	}
	
	// More initialization
	
	return 0;
}

uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	
	clr_bit(PORTB, 4); // Select CAN-controller
	
	SPI_send(MCP_READ); // Send read command
	SPI_send(address); // Send address
	result =SPI_read(); // Read result
	
	set_bit(PORTB, 4); // Deselect CAN-controller
	
	return result;
}