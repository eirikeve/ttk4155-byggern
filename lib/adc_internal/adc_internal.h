#pragma once
#include <avr/io.h>
#include <stdint.h>

class ADC_internal
{
    public:
        static ADC_internal& getInstance()
        {
            static ADC_internal    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }

        uint8_t read();

    private:
        ADC_internal();
    public:
        ADC_internal(ADC_internal const&)    = delete;
        void operator=(ADC_internal const&)  = delete;

};