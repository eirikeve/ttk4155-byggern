#pragma once
#include <avr/io.h>
#include <stdint.h>

class ADC_internal
{
    public:


        static ADC_internal& getInstance()
        {
            static ADC_internal instance;
            return instance;
        }

        uint8_t read();

    private:

        // Private due to singleton design pattern
        ADC_internal();
        
    public:
        // ~ADC_internal() {}
        // Deleted due to singleton design pattern
        ADC_internal(ADC_internal const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(ADC_internal const&)  = delete;

};