#pragma once

#include <stdint.h>
#include <stdio.h>

/**
 * Class for communication over UART for AVR atmega162 and atmega2560
 * */
class UART
{
    public:
        static UART& getInstance()
        {
            static UART instance;
            return instance;
        }
        /**
         * Initialize the UART with the given baud rate. 
         * Frame format: 8data, 2stop bit.
         * @param baudRate desired baud rate for the transmission.
         * */
        void initialize(uint16_t baudRate);

        /**
         * Transmit the following char over uart.
         * Frame format: 8data, 2stop bit.
         * @param byte char to be transmitted over uart
         * */
        int transmit(char byte);

        /**
         * Receive the following byte over uart.
         * Frame format: 8data, 2stop bit.
         * */
        uint8_t receive();



    private:


        // Private due to singleton design pattern
        UART() {}

        
    public:

        // Deleted due to singleton design pattern
        UART(UART const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(UART const&)  = delete;

};