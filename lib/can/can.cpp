
#include <util/delay.h>
#include <stdio.h>

#include "can.h"
#include "../CAN/SPI.h"
#include "../CAN/MCP2515.h"

ISR(MCP2515_vect) {
    // printf("Recieved\n");
    CAN& can = CAN::getInstance();
    uint8_t reg = can.mcp2515Read(MCP_CANINTF);
    // printf("Interrupt\n");
    // Check if message have been received
	if (reg & 1) {
		can.canMessageReceived = true;
	}
}


void CAN::initialize(SPI* spi, bool enableLoopbackMode) {
    this->spi = spi;

    // Reset MCP2515
    this->mcp2515Reset();
    // mcp2515_reset();

    // Put MCP2515 in config mode for configuring can
    this->mcp2515BitModify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);
    // mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);

    // Check that MCP2515 is in config mode before continuing
    uint8_t value = this->mcp2515Read(MCP_CANSTAT);
    // uint8_t value = mcp2515_read(MCP_CANSTAT);
    if ((value & MODE_MASK) != MODE_CONFIG)	{
        printf("MCP2515 error: NOT in configuration mode after reset!\n");
        return;
    }

    // Set MCP mask registers to 0, to accept all messages
    this->mcp2515BitModify(MCP_RXM0SIDH, 0xFF, 0x0); 
    this->mcp2515BitModify(MCP_RXM0SIDL, 0xE0, 0x0);
    this->mcp2515BitModify(MCP_RXM1SIDH, 0xFF, 0x0);
    this->mcp2515BitModify(MCP_RXM1SIDL, 0xE0, 0x0);

    // Clr one-shot bit to reattempt transmission
    this->mcp2515BitModify(MCP_CANCTRL, 0x80, 0x0);

    // Set buffer 0 operating mode to 00 (receive any message matching mask/filters), and disable rollover bit
    this->mcp2515BitModify(MCP_RXB0CTRL, 0x64, 0x00); 

    // Set buffer 1 operating mode to 10 (receive only extended ID msg, which we do not send.)
    this->mcp2515BitModify(MCP_RXB1CTRL, 0x60, 0x40); 

    
    if (enableLoopbackMode) {
        this->mcp2515BitModify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
    } 
    else {
        this->mcp2515BitModify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
    }
    
    // Enable GP interrupt on MCP2515
    this->mcp2515BitModify(MCP_CANINTE, 0x1, 0xFF);
    
    // Enable interrupt on mcu
#ifdef __AVR_ATmega162__
	GICR  |= (1 << INT1); // Enable interrupt1
	MCUCR |= (1 << ISC11); // Trigger falling edge
#elif __AVR_ATmega2560__
    EIMSK |= (1<<INT4); // Enable the interrupt
    EICRB |= (2<<ISC40); // Falling edge
#endif

    // Enable global interrupts
    sei();

    // No messages have been received
    this->canMessageReceived = false;
}

void CAN::transmit(CanMessage* msg) {
    _delay_ms(30);

    // Check if buffer is ready for transmission
	uint8_t is_clear = this->mcp2515Read(MCP_TXB0CTRL);
	if (bit_is_set(is_clear, 3)) {
		printf("CAN transmit error: Buffer0 is already pending transmission when sending message with id: %d\n", msg->id);
		return;
    }
    // Write ID
	this->mcp2515Write(MCP_TXB0SIDH, msg->id >> 3); // Highest 5 bits of ID
	this->mcp2515Write(MCP_TXB0SIDL, msg->id << 5); // Lowest 3 bits of ID

    // Message length in bytes
	this->mcp2515Write(MCP_TXB0DLC, msg->length & 0x0F);

    // Write data
	for (int i = 0; i < msg->length & 0x0F; i++) {
		this->mcp2515Write(MCP_TXB0D0 + i, msg->data[i]);
	}	

    // Request transmission, highest priority
	this->mcp2515BitModify(MCP_TXB0CTRL, 0x0B, 0x0B); 
}

CanMessage CAN::receive() {
    
    CanMessage msg;

    // Check if message is received
	if (this->canMessageReceived) {
        
		// Get message id
		msg.id =  this->mcp2515Read(MCP_RXB0SIDH) << 3;
		msg.id |= this->mcp2515Read(MCP_RXB0SIDL) >> 5;
        
        // Get message lenght
		msg.length = this->mcp2515Read(MCP_RXB0DLC) & 0x0F;

        // Get message data
		for (int i = 0; i < msg.length; i++) {
			msg.data[i] = this->mcp2515Read(MCP_RXB0D0 + i);
        }
        // Message received, get ready for receiving new message
        this->canMessageReceived = 0;
        
		// Clear interrupt flag
        this->mcp2515BitModify(MCP_CANINTF, 0x01, 0x00); 
    }
	return msg;
}

uint8_t CAN::mcp2515Read(uint8_t address) {

    this->spi->selectSlave();

    // Send read command
    this->spi->transmit(MCP_READ);

    // Which address
    this->spi->transmit(address);

    // Receive value
    uint8_t result = this->spi->receive();

    this->spi->deselectSlave();

    return result;
}

void CAN::mcp2515Write(uint8_t address, uint8_t data) {
    this->spi->selectSlave();

    // Send write command
    this->spi->transmit(MCP_WRITE);

    // Which address
    this->spi->transmit(address);

    // Send data
    this->spi->transmit(data);

    this->spi->deselectSlave();
}

void CAN::mcp2515RequestToSend(uint8_t rts) {
    this->spi->selectSlave();

    this->spi->transmit(0x80 | rts);

    this->spi->deselectSlave();
}

void CAN::mcp2515BitModify(uint8_t address, uint8_t mask, uint8_t data) {
    this->spi->selectSlave();

    // Send bit modify command
    this->spi->transmit(MCP_BITMOD);

    // Send address
    this->spi->transmit(address);
    
    // Mask
    this->spi->transmit(mask);

    // Data
    this->spi->transmit(data);

    this->spi->deselectSlave();
    // SPI_select_slave(); // Select CAN-controller
    
    // this->spi->transmit(MCP_BITMOD);
    // this->spi->transmit(address);
    // this->spi->transmit(mask);
    // this->spi->transmit(data);

    // SPI_deselect_slave(); // Deselect CAN-controller
}

void CAN::mcp2515Reset() {
    this->spi->selectSlave();

    // Send reset command
    this->spi->transmit(MCP_RESET);

    this->spi->deselectSlave();
}

void CAN::mcp2515ReadStatus() {
    this->spi->selectSlave();
    
    // Send read status command
    this->spi->transmit(MCP_READ_STATUS);

    this->spi->deselectSlave();
}