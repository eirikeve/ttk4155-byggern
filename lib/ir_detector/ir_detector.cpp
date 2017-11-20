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
        printf("Startup value IR: %d\n", valueUnblocked);
        this->threshold =(uint8_t)  valueUnblocked / 2.0;
    }
}

bool IR_detector::blocked() {
    uint8_t value = this->adc->read();

    if (value < this->threshold) {
        if (!this->beamBlocked) {
            this->beamBlocked = true;
            printf("Blocked IR value: %d\n", value);
            return this->beamBlocked;
        }
        else {
            return false;
        }
    }
    this->beamBlocked = false;
    return beamBlocked;

}
