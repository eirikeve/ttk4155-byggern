#pragma once

#include <stdint.h>

enum CHANNEL {
    CH1 = 0b100,
    CH2 = 0b101,
    CH3 = 0b110,
    CH4 = 0b111
};



/**
 * Class for reading analog signal using an external ADC accessed via
 * an external addres in the memory map.
 * */
class ADC
{
    public:
        static ADC& getInstance()
        {
            static ADC instance;
            return instance;
        }

        /**
         * Read a value of a channel in the ADC
         * @param c channel to be read from.
         * */
        uint8_t read(CHANNEL c);

    private:

        // Private due to singleton design pattern
        ADC();

        // The address of the external memory map the ADC is located at
        volatile uint16_t *addr;
        
    public:

        // Deleted due to singleton design pattern
        ADC(ADC const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(ADC const&)  = delete;

};