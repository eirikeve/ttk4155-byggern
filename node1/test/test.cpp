#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "test.h"
#include "lib/utilities/printf.h"
#include "lib/pins/pins.h"
#include "lib/uart/uart.h"
#include "lib/adc/adc.h"
#include "lib/joystick/joystick.h"
#include "lib/timer/timer.h"
#include "lib/utilities/utilities.h"
#include "lib/spi/spi.h"
#include "lib/can/can.h"

#ifndef TEST_NRF
#define TEST_NRF 1
#endif

    
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
    PORTB ^= (1 << PB0);
}
void testTimer() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    Timer& timer0 = Timer::getInstance(0);
    timer0.initialize(100, &callbackTimer0, NULL);

    PIN pin(&DDRB, &PORTB, &PINB, PB0);

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
    
void testJoystick()
{
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    ADC& adc = ADC::getInstance();
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, NULL);

    int8_t x;
    int8_t y;

    while (1)
    {
        Direction dir = joystick.read(&x, &y);
        printf("x: %d, y: %d, dir: %d\n", x, y, dir);
    }
}

void testJoystickButton() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    ADC& adc = ADC::getInstance();

    PIN pin(&DDRB, &PORTB, &PINB, PB3);
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, &pin);

    while (true) {
        if (joystick.buttonPressed()) {
            printf("Button pressed at joystick\n");
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

    ADC& adc = ADC::getInstance();
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, NULL);

    int8_t x;
    int8_t y;

    CanMessage msg;
    msg.id = 2;
    msg.length = 3;

    while (true) {
        Direction dir = joystick.read(&x, &y);
        printf("x: %d, y: %d, dir: %d\n", x, y, dir);
        msg.data[0] = x;
		msg.data[1] = y;
        msg.data[2] = dir;
        can.transmit(&msg);
    }
}

#if TEST_NRF

void callbackSPITimer() {
    PORTB ^= (1 << PB0);
}
void testNrf() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    Timer& timer1 = Timer::getInstance(1);
    timer1.initialize(1000, &callbackSPITimer, &pb0);
    timer1.start();

    SPI& spi = SPI::getInstance(1);
    uint8_t val;

    while (true) {
        spi.selectSlave();
        val = spi.receive();
        printf("Value read from NRF: %d\n", val);
        spi.deselectSlave();
    }
}
#endif // TEST_NRF