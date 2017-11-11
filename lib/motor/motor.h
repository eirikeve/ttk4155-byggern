#pragma once
#include <stdint.h>

#include "lib/dac/dac.h"
#include "lib/timer/timer.h"

namespace {
    
#define MAX_INT INT16_MAX
#define MAX_LONG INT32_MAX
#define MAX_I_TERM (MAX_LONG / 2)


    struct PID_DATA {
	//! Last process value, used to find derivative of process value.
	int16_t lastProcessValue;
	//! Summation of errors, used for integrate calculations
	int32_t sumError;
	//! The Proportional tuning constant, multiplied with SCALING_FACTOR
	int16_t P_Factor;
	//! The Integral tuning constant, multiplied with SCALING_FACTOR
	int16_t I_Factor;
	//! The Derivative tuning constant, multiplied with SCALING_FACTOR
	int16_t D_Factor;
	//! Maximum allowed error, avoid overflow
	int16_t maxError;
	//! Maximum allowed sumerror, avoid overflow
	int32_t maxSumError;

    PID_DATA(int16_t P_Factor, int16_t I_Factor, int16_t D_Factor): P_Factor(P_Factor),
                                                                    I_Factor(I_Factor),
                                                                    D_Factor(D_Factor),
                                                                    lastProcessValue(0),
                                                                    sumError(0),
                                                                    maxError(MAX_INT/(P_Factor + 1)),
                                                                    maxSumError(MAX_I_TERM / (I_Factor + 1)) {};
    PID_DATA(): P_Factor(0),
                I_Factor(0),
                D_Factor(0),
                lastProcessValue(0),
                sumError(0),
                maxError(0),
                maxSumError(0) {};
};
}

class Motor
{
    public:


        static Motor& getInstance()
        {
            static Motor instance;
            return instance;
        }

        void initialize(DAC* dac, Timer* timer, int16_t Kp, int16_t Ki, int16_t Kd, uint8_t T);

        void setPIDparameters(int16_t Kp, int16_t Ki, int16_t Kd);

        int16_t getEncoderValue();

        void run(int8_t speed);

    private:

        // Private due to singleton design pattern
        Motor() {};

        // PID controller parameters
        int16_t Kp;
        int16_t Ki;
        int16_t Kd;

        // DAC
        DAC* dac;

        // Timer
        Timer* timer;

        // Time step for controller
        uint8_t T;

        // Reference point
        int16_t ref;

        PID_DATA pid;

        void setSpeed(uint8_t speed);
        
        /**
         * > 0: right
         * < 0: left
         * */
        void setDirection(int8_t dir);

        int16_t pidController(int16_t processValue);

        void encoderReset();
        
    public:
        // Deleted due to singleton design pattern
        Motor(Motor const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(Motor const&)  = delete;

        friend void PID();

};