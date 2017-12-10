#pragma once
#include <avr/io.h>
#include <stdint.h>

extern "C" {
    #include "lib/twi/twi.h"
    
}

/**
 * Class for converting a digital value 0 - 255 to an analog value 0 - 5V using a DAC
 * communicating using I2C (TWI).
 **/
class DAC
{
    public:


        static DAC& getInstance()
        {
            static DAC instance;
            return instance;
        }

        /**
         * Initialize DAC.
         * @param address I2C address for device.
         **/
        void initialize(uint8_t address);

        /**
         * Start convertion of value.
         * @param value value to be converted.
         * */
        void convert(uint8_t value);

    private:

        // Private due to singleton design pattern
        DAC() {};

        // Address of DAC on I2C
        uint8_t address;


        //I2C driver
        
    public:
        // Deleted due to singleton design pattern
        DAC(DAC const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(DAC const&)  = delete;

};