#pragma once
#include "MCP2515.h"

uint8_t mcp2515_init()
{
	uint8_t value;
	/* Set PB4 (SS' = OC3B) to low, activating the MCP2515 (slave) SPI*/
	//clr_bit(DDRB, DDB4);

	SPI_init(); // initialize SPI
	
	mcp2515_reset();
	
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);
	// Self test
	// while (1) {
	// 	printf("Bo2\n");
	// }
	value = mcp2515_read(MCP_CANSTAT);
	// printf("%d\n", value & MODE_MASK);
	
	if ((value & MODE_MASK) != MODE_CONFIG)
	{
		printf("MCP2515 is NOT in configuration mode after reset!\n");
		return 1;
	}

	// mcp2515_write_register(CANINTE, (1 << RX1IE) | (1 << RX0IE));
	// More initialization¨
	// Enable pin interrupt upon receiving messages
	// mcp2515_bit_modify(MCP_RX_INT, 1);
	// mcp2515_bit_modify(0xF0, 0xE0, 0x40);

	return 0;
}

uint8_t mcp2515_read(uint8_t address)
{
	uint8_t result;

	SPI_select_slave(); // Select CAN-controller
	// PORTB &= ~(1 << 0x04);

	SPI_send(MCP_READ);  // Send read command
	SPI_send(address);   // Send address
	result = SPI_read(); // Read result

	SPI_deselect_slave(); // Deselect CAN-controller
	// PORTB |= (1 << 0x04);

	return result;
}

void mcp2515_write(uint8_t address, uint8_t data)
{
	SPI_select_slave(); // Select CAN-controller
	// PORTB &= ~(1 << 0x04);

	SPI_send(MCP_WRITE);
	SPI_send(address);
	SPI_send(data);

	SPI_deselect_slave(); // Deselect CAN-controller
	// PORTB |= (1 << 0x04);

	return;
}
void mcp2515_request_to_send(uint8_t rts)
{
	SPI_select_slave(); // Select CAN-controller
	printf("IN MCP Before: %d\n", (mcp2515_read(MCP_TXB0CTRL) & 0x4) >> 3);	
	SPI_send(0x80 | rts);
	printf("IN MCP After: %d\n", (mcp2515_read(MCP_TXB0CTRL) & 0x4) >> 3);
	SPI_deselect_slave(); // Deselect CAN-controller
	
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
	SPI_select_slave(); // Select CAN-controller

	SPI_send(MCP_BITMOD);
	SPI_send(address);
	SPI_send(mask);
	SPI_send(data);

	SPI_deselect_slave(); // Deselect CAN-controller

	return;
}

void mcp2515_reset()
{
	SPI_select_slave(); // Select CAN-controller
	SPI_send(MCP_RESET);
	SPI_deselect_slave(); // Deselect CAN-controller
}
void mcp_read_status()
{
	SPI_select_slave(); // Select CAN-controller
	SPI_send(MCP_READ_STATUS);
	SPI_deselect_slave(); // Deselect CAN-controller
}
