#include <stdio.h>
extern "C" {
    #include "../lib/comm/comm.h"
}
#include "test.h"
#include "lib/servo/servo.h"


void testServoPercentage() {
    Servo& servo = Servo::getInstance();
    servo.initialize(40);
    init_uart();
    int8_t percentage = -100;
    while (true) {
        printf("percentage: %d, ", percentage);
		servo.setAnglePercentage(percentage);
		percentage++;
		if (percentage > 100) {
			percentage = -100;
		}
    }

}

void testServoAngle() {
    Servo& servo = Servo::getInstance();
    servo.initialize(40);
    init_uart();
    int8_t angle = -90;
    while (true) {
        printf("angle: %d, ", angle);
		servo.setAngle(angle);
		angle++;
		if (angle > 90) {
			angle = -90;
		}
    }

}