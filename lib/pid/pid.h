#pragma once
#include <stdint.h>
#include <stdio.h>

/**
 * PID controller for calculating input given a reference, using the desired controller gains.
 * */
class PID
{
    public:
        PID();

		/**
		 * Initialize the PID with desired controller gains.
		 * @param P_Factor Proportional gain factor.
		 * @param I_Factor Integral gain factor.
		 * @param D_factor Derivate gain factor.
		 * */
        PID(float P_Factor, float I_Factor, float D_Factor);

		/**
		 * Change controller gains.
		 * @param P_Factor Proportional gain factor.
		 * @param I_Factor Integral gain factor.
		 * @param D_factor Derivate gain factor.
		 * */
        void setParameters(float P_Factor, float I_Factor, float D_Factor);

		/**
		 * Calculate input given reference and processValue.
		 * @param reference desired set point for process.
		 * @param processValue measured process value.
		 * @return calculated input signal.
		 * */
        int8_t controller(float reference, float processValue);

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
        
        

};