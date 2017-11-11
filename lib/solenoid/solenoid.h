#pragma once
#include <avr/io.h>
#include <stdint.h>
#include "lib/adc_internal/adc_internal.h"

class Solenoid
{
    public:

        static Solenoid& getInstance()
        {
            static Solenoid instance;
            return instance;
        }

        /** 
         * Check if IR beam is blocked.
         * @return true if beam is blocked since last check, false else
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