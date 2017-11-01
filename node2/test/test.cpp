#include <stdio.h>

#include "test.h"
#include "lib/utilities/printf.h"
#include "lib/servo/servo.h"
#include "lib/uart/uart.h"

void testUartTransmit() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    while (true) {
        uart.transmit('B');
        uart.transmit('\n');
    }
}

void testUartReceive() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);

    while (true) {
        uint8_t c = uart.receive();
        uart.transmit(c);
    }
}

void testPrintfWithUart() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    while (true) {
        printf("Test printf\n");
    }
}


void testServoPercentage() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    Servo& servo = Servo::getInstance();
    servo.initialize(40);

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
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    Servo& servo = Servo::getInstance();
    servo.initialize(40);

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