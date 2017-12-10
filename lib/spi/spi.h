#pragma once
#include <avr/io.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib/uart/uart.h"
#include "lib/pins/pins.h"

namespace {
#ifdef __AVR_ATmega162__
    #define SS0 pb4
    #define SS1 pe0
#elif __AVR_ATmega2560__
    #define SS0 pb7
    #define SS1 pa0
#endif
};

/**
 * Class for communicating over SPI configured as master.
 * */
class SPI
{
    public:


        static SPI& getInstance(uint8_t id) {
            if(id == 0){
                static SPI instance(&SS0);
                return instance;
            }
            else if (id == 1){
                static SPI instance(&SS1);
                return instance;
            }
            else {
            
                assert(false);
            }
        }

        /**
         * Transmit data over spi.
         * @param data byte to be sent.
         * */
        void transmit(char data);

        /** Receive data over spi. Calls SPI::transmit with a 
         * dummy data of 0x00 and then return the data on MISO
         * @return data received from slave.
         * */
        char receive();

        // Select slave for sending
        void selectSlave();
        
        // Deselect slave after sending
        void deselectSlave();

    private:

        // Private due to singleton design pattern
        SPI(PIN* ss);

        // Slave select pin
        PIN* ss;

    public:
        // Deleted due to singleton design pattern
        SPI(SPI const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(SPI const&)  = delete;

};