#pragma once
#include <avr/io.h>
#include <stdint.h>
#include "lib/adc_internal/adc_internal.h"

/**
 * Class for shooting solenoid using an external power supply and a relay.
 * */
class Solenoid
{
    public:

        static Solenoid& getInstance()
        {
            static Solenoid instance;
            return instance;
        }

        /** 
         * Shoot solenoid
         * */
        void shoot();

    private:

        // Private due to singleton design pattern
        Solenoid();
        
    public:
        // Deleted due to singleton design pattern
        Solenoid(Solenoid const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(Solenoid const&)  = delete;

};