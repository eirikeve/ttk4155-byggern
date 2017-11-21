#pragma once
#include <stdint.h>

#include "lib/dac/dac.h"
#include "lib/timer/timer.h"
#include "lib/encoder/encoder.h"
#include "lib/pid/pid.h"


class Motor
{
    public:


        static Motor& getInstance()
        {
            static Motor instance;
            return instance;
        }

        void initialize(DAC* dac, Timer* timer, Encoder* encoder, float Kp, float Ki, float Kd, uint8_t T);

        void setPIDparameters(float Kp, float Ti, float Td);

        float getEncoderValue();

        void run(int8_t speed);

        

    private:

        // Private due to singleton design pattern
        Motor() {};

        // Encoder
        Encoder* encoder;

        // DAC
        DAC* dac;

        // Timer
        Timer* timer;

        // Time step for controller
        uint8_t T;

        // Reference point
        int16_t ref;

        // Pid
        PID pid;

        void setSpeed(uint8_t speed);
        
        /**
         * > 0: right
         * < 0: left
         * */
        void goRight();

        void goLeft();
        
    public:
        // Deleted due to singleton design pattern
        Motor(Motor const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(Motor const&)  = delete;

        friend void controller();

};