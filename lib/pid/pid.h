#pragma once
#include <stdint.h>
#include <stdio.h>
namespace {
#define MAX_INT INT8_MAX
#define MAX_LONG INT8_MAX
#define MAX_I_TERM MAX_LONG
#define SCALING_FACTOR 0.5
}


class PID
{
    public:
        PID();
        PID(int16_t P_Factor, int16_t I_Factor, int16_t D_Factor);

        void setParameters(int16_t P_Factor, int16_t I_Factor, int16_t D_Factor);
        int8_t controller(int16_t reference, int16_t processValue);

        friend void testTuneMotor();
        void print() { printf("Kp: %d, Ki: %d, Kd: %d\n", P_Factor, I_Factor, D_Factor);}
    private:

    //! Last process value, used to find derivative of process value.
	int16_t lastProcessValue;
	//! Summation of errors, used for integrate calculations
	int16_t sumError;
	//! The Proportional tuning constant
	int16_t P_Factor;
	//! The Integral tuning constant
	int16_t I_Factor;
	//! The Derivative tuning constant
	int16_t D_Factor;
    //! Max input value
    int16_t maxInput;
	//! Maximum allowed error, avoid overflow
	int16_t maxError;
	//! Maximum allowed sumerror, avoid overflow
	int16_t maxSumError;

    int16_t debug;
        
        

};