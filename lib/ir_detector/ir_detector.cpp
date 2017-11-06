#include <stdio.h>
#include "ir_detector.h"

void IR_detector::initialize(ADC_internal* adc, uint8_t threshold, uint8_t filterDegree) {
    this->adc = adc;
    this->filterDegree = filterDegree;
    this->beamBlocked = false;

    if (threshold != NULL) {
        this->threshold = threshold;
    }
    else {
        uint8_t valueUnblocked = adc->read();
        printf("Unblocked value: %d\n", valueUnblocked);
        this->threshold = valueUnblocked / 2.0;
    }
}

bool IR_detector::blocked() {
    float value = 0.0;

    for (int i = 0; i < this->filterDegree; i++) {
        value += ((float) this->adc->read()) / this->filterDegree;
    }

    if (value < this->threshold) {
        if (!this->beamBlocked) {
            this->beamBlocked = true;
            return this->beamBlocked;
        }
        else {
            return false;
        }
    }
    this->beamBlocked = false;
    return beamBlocked;

}
