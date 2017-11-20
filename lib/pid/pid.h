#pragma once
#include <stdint.h>
#include <stdio.h>

class PID
{
    public:
        PID();
        PID(float P_Factor, float I_Factor, float D_Factor);

        void setParameters(float P_Factor, float I_Factor, float D_Factor);
        int8_t controller(float reference, float processValue);

        friend void runGame();
        void print() { printf("Kp: %d, Ki: %d, Kd: %d\n", (int16_t) (P_Factor * 100000), (int16_t) (I_Factor * 1000), (int16_t) D_Factor);}
    private:

    //! Last process value, used to find derivative of process value.
	float lastProcessValue;
	//! Summation of errors, used for integrate calculations
	float sumError;
	//! The Proportional tuning constant
	float P_Factor;
	//! The Integral tuning constant
	float I_Factor;
	//! The Derivative tuning constant
	float D_Factor;

    int16_t debug;
        
        

};