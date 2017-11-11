#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "test.h"
#include "lib/utilities/printf.h"
#include "lib/utilities/utilities.h"
#include "lib/pins/pins.h"
#include "lib/servo/servo.h"
#include "lib/uart/uart.h"
#include "lib/timer/timer.h"
#include "lib/adc_internal/adc_internal.h"
#include "lib/ir_detector/ir_detector.h"
#include "lib/spi/spi.h"
#include "lib/can/can.h"
#include "lib/motor/motor.h"
#include "lib/dac/dac.h"
#include "lib/solenoid/solenoid.h"

extern "C" {
    #include "lib/twi/twi.h"
    
}

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
void callbackTimer0() {
    printf("Test timer0\n");
}
void callbackTimer1() {
    PORTB ^= (1 << PB4);
}
void testTimer() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    Timer& timer0 = Timer::getInstance(0);
    timer0.initialize(100, &callbackTimer0, NULL);

    PIN pin(&DDRB, &PORTB, &PINB, PB4);

    Timer& timer1 = Timer::getInstance(1);
    timer1.initialize(1000, &callbackTimer1, &pin);

    timer0.start();
    timer1.start();
    while (true) {
        continue;
    }
}

void stopTimerInTestTimerStop() {
    Timer& t = Timer::getInstance(1);
    t.stop();
}
void testTimerStop() {

    Timer& timer0 = Timer::getInstance(0);
    timer0.initialize(4190, &stopTimerInTestTimerStop, NULL);

    PIN pin(&DDRB, &PORTB, &PINB, PB4);
    Timer& timer1 = Timer::getInstance(1);
    timer1.initialize(100, &callbackTimer1, &pin);

    timer0.start();
    timer1.start();
    while (true) {
        continue;
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

void testADC() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    ADC_internal& adc = ADC_internal::getInstance();
    while (true) {
        printf("%d\n", adc.read());
    }
}

void testIRDetector() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    ADC_internal& adc = ADC_internal::getInstance();

    IR_detector& ir = IR_detector::getInstance();
    ir.initialize(&adc, NULL, 4);
    while (true) {
        if(ir.blocked()) {
            printf("Beam blocked\n");
        }
    }
}

void testSpi() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    SPI& spi = SPI::getInstance(0);
    while (true) {
        spi.transmit(0xA5);
    }
}

void testCanLoopback() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, true);

    CanMessage msg;
    msg.id = 2;
    msg.length = 1;
    msg.data[0] = 0;

    while (true) {
        can.transmit(&msg);
        CanMessage recv = can.receive();
        if (recv.id != NULL) {
            printf("id: %d, length: %d, data: %d\n", recv.id, recv.length, recv.data[0]);
        }

        msg.data[0]++;
    }
}

void testCanTransmit() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, false);

    CanMessage msg;
    msg.id = 2;
    msg.length = 1;
    msg.data[0] = 0;

    while (true) {
        can.transmit(&msg);
        msg.data[0]++;
    }
}

void testCanReceive() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, false);

    while (true) {
        CanMessage recv = can.receive();
        if (recv.id != NULL) {
            printf("id: %d, length: %d, data: %d\n", recv.id, recv.length, recv.data[0]);
        }
    }
}

void testControlServoOverCan() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, false);

    Servo& servo = Servo::getInstance();
    servo.initialize(90);

    while (true) {
        CanMessage recv = can.receive();
        if (recv.id != NULL) {
            printf("id: %d, length: %d, percentage: %d\n", recv.id, recv.length, (int8_t) recv.data[0]);
            servo.setAnglePercentage(recv.data[0]);
        }
    }
}

void testMotor() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    TWI_Master_Initialise();
    sei();

    // printf("%x\n", 0b0101 << 4 | 0);
    Motor& motor = Motor::getInstance();
    unsigned char foo[1] = {0xa5};
    while (true) {
        motor.run(127);
        // TWI_Start_Transceiver_With_Data(foo, 1);
    }
}

void testMotorOverCan() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, false);

    TWI_Master_Initialise();
    sei();
    
    DAC& dac = DAC::getInstance();
    dac.initialize(0x00);

    Timer& timer = Timer::getInstance(0);

    Motor& motor = Motor::getInstance();
    motor.initialize(&dac, &timer, 100,0,0, 10);
    

    while (true) {
        CanMessage recv = can.receive();
        if (recv.id != NULL) {
            printf("id: %d, length: %d, percentage: %d\n", recv.id, recv.length, (int8_t) recv.data[0]);
            motor.run(recv.data[0]);
        }
    }
}

void testMotorEncoder() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    TWI_Master_Initialise();
    sei();
    
    DAC& dac = DAC::getInstance();
    dac.initialize(0x00);

    Timer& timer = Timer::getInstance(0);

    Motor& motor = Motor::getInstance();
    motor.initialize(&dac, &timer, 100,0,0, 10);
    

    while (true) {
        printf("Encoder value: %d\n", motor.getEncoderValue());
    }
}

void testSolenoid() {
    Solenoid & solenoid = Solenoid::getInstance();

    while(1){
		solenoid.shoot();
		_delay_ms(500);
	}
}