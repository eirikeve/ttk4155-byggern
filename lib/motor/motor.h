#pragma once
#include <stdint.h>

#include "lib/dac/dac.h"

class Motor
{
    public:


        static Motor& getInstance()
        {
            static Motor instance;
            return instance;
        }

        void initialize(DAC* dac, uint8_t Kp, uint8_t Ki, uint8_t Kd);

        void setPIDparameters(uint8_t Kp, uint8_t Ki, uint8_t Kd);

        

        void run(int8_t speed);

    private:

        // Private due to singleton design pattern
        Motor() {};

        // PID controller parameters
        uint8_t Kp;
        uint8_t Ki;
        uint8_t Kd;

        // DAC
        DAC* dac;

        // Time step for controller
        uint8_t T;

        void setSpeed(uint8_t speed);
        
        /**
         * > 0: right
         * < 0: left
         * */
        void setDirection(int8_t dir);

        uint8_t controller(int8_t ref);

        int16_t getEncoderValue();

        void encoderReset();
        
    public:
        // Deleted due to singleton design pattern
        Motor(Motor const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(Motor const&)  = delete;

};