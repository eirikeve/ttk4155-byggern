#pragma once
#include <avr/io.h>
#include <stdint.h>
#include "lib/adc_internal/adc_internal.h"

class IR_detector
{
    public:

        static IR_detector& getInstance()
        {
            static IR_detector instance;
            return instance;
        }

        /**
         * Initialzes the IR detector to check if the beam is blocked.
         * @param adc ADC for reading value from photodiode.
         * @param threshold threshold for detecting a blocked beam.
         *  value < threshold => blocked == true
         *  value > threshold => blocked == false
         * @param filterDegree number of values averaged to filter signal.
         * */
        void initialize(ADC_internal* adc, uint8_t threshold, uint8_t filterDegree);

        /** 
         * Check if IR beam is blocked.
         * @return true if beam is blocked since last check, false else
         * */
        bool blocked();

    private:

        // Private due to singleton design pattern
        IR_detector() {};

        // Threshold value
        uint8_t threshold;

        // Filter degree
        uint8_t filterDegree;

        // ADC for reading values
        ADC_internal* adc;

        // Is beam blocked?
        bool beamBlocked;
        
    public:
        // Deleted due to singleton design pattern
        IR_detector(IR_detector const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(IR_detector const&)  = delete;

};