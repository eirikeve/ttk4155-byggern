#include "pid.h"

PID::PID(): P_Factor(0),
            I_Factor(0),
            D_Factor(0),
            lastProcessValue(0),
            sumError(0){};

PID::PID(float P_Factor, float I_Factor, float D_Factor):   P_Factor(P_Factor),
                                                            I_Factor(I_Factor),
                                                            D_Factor(D_Factor),
                                                            lastProcessValue(0),
                                                            sumError(0){};


void PID::setParameters(float P_Factor, float I_Factor, float D_Factor) {
    this->P_Factor = P_Factor > 0 ? P_Factor : 0;
    this->I_Factor = I_Factor > 0 ? I_Factor : 0;
    this->D_Factor = D_Factor > 0 ? D_Factor : 0;
}

int8_t PID::controller(float reference, float processValue) {
    // int16_t errors, p_term, d_term;
	// int16_t i_term, ret, temp;

    // errors = reference - processValue;

    // // Calculate Pterm and limit error overflow
    // if (errors > this->maxError) {
    //     p_term = MAX_INT;
    // }
    // else if (errors < - this->maxError) {
    //     p_term = - MAX_INT;
    // }
    // else {
    //     p_term = this->P_Factor * errors;
    // }

    // // this->debug = this->sumError;
    // // Calculate Iterm and limit integral runaway
    // temp = this->sumError + errors;
    // // this->debug = temp;
    // if (temp > this->maxSumError) {
    //     i_term = MAX_I_TERM;
    //     this->sumError = this->maxSumError;
    // }
    // else if (temp < - this->maxSumError) {
    //     i_term = -MAX_I_TERM;
    //     this->sumError = -this->maxSumError;
    // }
    // else {
    //     this->sumError = temp;
    //     i_term = this->I_Factor * this->sumError;
    // }
    // this->debug = i_term;

    

    // // Calculate Dterm
	// d_term = this->D_Factor * (this->lastProcessValue - processValue);

	// this->lastProcessValue = processValue;

	// ret = (p_term + i_term + d_term);
	// if (ret > MAX_INT) {
	// 	ret = MAX_INT;
	// } else if (ret < -MAX_INT) {
	// 	ret = -MAX_INT;
	// }

	// return ((int16_t)ret);
    float p_term, i_term, d_term;
    float error = reference - processValue;
    
    p_term = this->P_Factor * error;

    this->sumError += error;
    i_term = this->I_Factor * this->sumError;

    d_term = this->D_Factor * (this->lastProcessValue - processValue);

    float input = p_term + i_term + d_term;
    
    if (input > 1.0) {
        input = 1.0;
    }
    else if (input < -1.0) {
        input = - 1.0;        
    }
    this->debug = input;
    return input * 127;
}