    #include <stdio.h>
    #include <avr/io.h>
    #include <util/delay.h>
    #include <stdint.h>
    
    #include "test.h"
    #include "lib/utilities/printf.h"
    #include "lib/utilities/pin.h"
    #include "lib/uart/uart.h"
    #include "lib/adc/adc.h"
    #include "lib/joystick/joystick.h"
    #include "lib/timer/timer.h"

    
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
    ADC& adc = ADC::getInstance();
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10);

    int8_t x;
    int8_t y;

    while (1)
    {
        Direction dir = joystick.read(&x, &y);
        printf("x: %d, y: %d, dir: %d\n", x, y, dir);
        // x = joystick.readY();
        // printf("%d\n", x);
    }
}

void testJoystickButton() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    ADC& adc = ADC::getInstance();
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10);

    while (true) {
        if (joystick.buttonPressed()) {
            printf("Button pressed at joystick\n");
        }
    }
}