#pragma once

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "mcp2515.h"
#include "lib/spi/spi.h"

struct CanMessage{
	uint8_t id;
	uint8_t length;
    uint8_t data[8];
    
    CanMessage(uint8_t id, uint8_t length, uint8_t data[8]): id(id), length(length){
        data = data;
    }
    CanMessage(): id(NULL) {};
};
namespace {
#ifdef __AVR_ATmega162__
    #define MCP2515_vect INT1_vect
#elif __AVR_ATmega2560__
    #define MCP2515_vect INT4_vect
#endif
}

ISR(MCP2515_vect);
class CAN
{
    public:


        static CAN& getInstance()
        {
            static CAN instance;
            return instance;
        }

        /**
         * Initialize MCP2515 to transmit and recieve can messages.
         * @param spi spi to be used with communicating with mcu
         * @param enableLoopbackMode if true, then configure MCP2515 in loopback mode
         *  else, normal mode
         * */
        void initialize(SPI* spi, bool enableLoopbackMode);

        /**
         * Transmit can message over the CANbus.
         * @param msg can message to be transmitted.
         * */
        void transmit(CanMessage* msg);

        /**
         * Recieve can message over the CANbus. If no message have been received,
         * then id of the returned message is NULL.
         * @return received can message.
         * */
        CanMessage receive();

    private:

        // Private due to singleton design pattern
        CAN() {};

        

        // SPI to use for communicating with the mcu
        SPI* spi;
        // Flag that is set in interrupt vector when new message is received
        volatile bool canMessageReceived;
        
        uint8_t mcp2515Read(uint8_t address);
        void mcp2515Write(uint8_t address, uint8_t data);
        void mcp2515RequestToSend(uint8_t rts);
        void mcp2515BitModify(uint8_t address, uint8_t mask, uint8_t data);
        void mcp2515Reset();
        void mcp2515ReadStatus();

    public:

        // Deleted due to singleton design pattern
        CAN(CAN const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(CAN const&)  = delete;

        // Declare interrupt vector friend of class
        friend void MCP2515_vect();

};
    

bool checkForACK();
void sendResetUntilACK();
