#pragma once
#include <avr/io.h>
#include <stdint.h>

extern "C" {
    #include "lib/twi/twi.h"
    
}

class DAC
{
    public:


        static DAC& getInstance()
        {
            static DAC instance;
            return instance;
        }

        void initialize(uint8_t address);

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