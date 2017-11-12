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

        void initialize(DAC* dac, Timer* timer, Encoder* encoder, int16_t Kp, int16_t Ki, int16_t Kd, uint8_t T);

        void setPIDparameters(int16_t Kp, int16_t Ti, int16_t Td);

        int16_t getEncoderValue();

        void run(int8_t speed);

        Encoder* encoder;
    private:

        // Private due to singleton design pattern
        Motor() {};

        // Encoder
        

        // DAC
        DAC* dac;

        // Timer
        Timer* timer;

        // Time step for controller
        uint8_t T;

        // Reference point
        int16_t ref;

        int16_t processValue;

        int16_t u;
        int16_t enc;

        PID pid;

        void setSpeed(uint8_t speed);
        
        /**
         * > 0: right
         * < 0: left
         * */
        void setDirection(int8_t dir);
        
    public:
        // Deleted due to singleton design pattern
        Motor(Motor const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(Motor const&)  = delete;

        friend void controller();
        friend void testTuneMotor();

        int16_t getInput() {return this->u;}

};