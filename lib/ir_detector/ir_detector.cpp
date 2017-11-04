#include "ir_detector.h"

void IR_detector::initialize(ADC_internal* adc, uint8_t threshold, uint8_t filterDegree) {
    this->adc = adc;
    this->threshold = threshold;
    this->filterDegree = filterDegree;
    this->beamBlocked = false;
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
