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
    this->debug = (int16_t) (input * 127);
    return input * 127;
}