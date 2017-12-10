#pragma once
#include <avr/io.h>
#include <stdint.h>

/**
 * Class for reading analog signal using an external ADC accessed via
 * an external addres in the memory map, for Node 2.
 * */
class ADC_internal
{
    public:


        static ADC_internal& getInstance()
        {
            static ADC_internal instance;
            return instance;
        }

        uint16_t read();

    private:

        // Private due to singleton design pattern
        ADC_internal();
        
    public:
        // Deleted due to singleton design pattern
        ADC_internal(ADC_internal const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(ADC_internal const&)  = delete;

};