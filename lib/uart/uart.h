// /*
// * utils.h
// *
// * Created: 04.09.2017 11:29:32
// *  Author: eirikeve
// */

// #pragma once

// class UART{
// private:
//     volatile static UART * instance;
//     volatile static int8_t num;

//     UART();
//     static int init();
//     static unsigned char _recv_char();
//     static void _flush();

// public:

//     ~UART();

//     static int put_char(char c);

//     static unsigned char recv_char();

//     volatile static UART * instance();

// };

#pragma once
#include <stdint.h>
#include <stdio.h>


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