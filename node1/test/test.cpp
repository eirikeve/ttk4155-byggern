#define DO_TESTS

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

#ifdef DO_TESTS
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
        // x = joystick.readY();
        // printf("%d\n", x);
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
        // printf("%d\n", joystick.buttonPressed());
    }
}


// Test display
void testScreen()
{
    Screen s1 = Screen();
    Screen s2 = Screen();
    s1.changeBufferTo((uint8_t*)AVR_VRAM_1);
    s2.changeBufferTo((uint8_t*)AVR_VRAM_1);

    s1.goTo(0,0);
    s1.writeString("Writing to a single display");
    s1.render((uint8_t*)AVR_VRAM_1);
    __delay_ms(2000);
    s1.writeString("\nFilling the rest of the display with lines");
    for (int i = 0; i < 100; ++i)
    {
        s1.writeChar('-');
    }
    s1.render((uint8_t*)AVR_VRAM_1);
    __delay_ms(2000);
    s1.clear();

    s1.addSubScreen(&s2, 4, Orientation::LOWER);
    s1.goTo(0,0);
    s2.goTO(0,0);
    s1.writeString("Writing to 2 displays. This is display 1.");
    s2.writeString("This is display 2.")
    s1.render((uint8_t*)AVR_VRAM_1);
    __delay_ms(2000);
    s2.writeString("\nDisplay 1, 2 will be filled with #, !");
    s1.render((uint8_t*)AVR_VRAM_1);
    __delay_ms(2000);
    s1.clear();
    s2.clear();
    for (int i = 0; i < 100; ++i)
    {
        s1.writeChar('#');
        s2.writeChar('!');
    }
    __delay_ms(2000);
    s1.clear();
    s1.writeString("Display borders will now be added");
    s1.render((uint8_t*)AVR_VRAM_1);
    __delay_ms(2000);
    s1.addBorderLines();
    s2.addBorderLines();
    s1.render((uint8_t*)AVR_VRAM_1);
    __delay_ms(2000);




}
void testSubScreen()
{
    Screen s1 = Screen();
    Screen s2 = Screen();
    Screen s3 = Screen();
    s1.changeBufferTo((uint8_t*)AVR_VRAM_1);
    s2.changeBufferTo((uint8_t*)AVR_VRAM_1);
    s3.changeBufferTo((uint8_t*)AVR_VRAM_1);
    s1.addSubScreen(&s2, 4, Orientation::LOWER);
    s1.goTo(0,0);
    s2.goTO(0,0);
    s3.goTo(0,0);

    s1.writeString("Writing to 2 displays. This is display 1.");
    s2.writeString("This is display 2.")
    s1.render((uint8_t*)AVR_VRAM_1);
    __delay_ms(2000);
    s2.writeString("\nDisplay 1, 2 will be filled with #, !");
    s1.render((uint8_t*)AVR_VRAM_1);
    __delay_ms(2000);
    s1.clear();
    s2.clear();
    for (int i = 0; i < 100; ++i)
    {
        s1.writeChar('#');
        s2.writeChar('!');
    }
    __delay_ms(2000);
    s1.clear();
    s1.writeString("Display borders will now be added");
    s1.render((uint8_t*)AVR_VRAM_1);
    __delay_ms(2000);
    s1.addBorderLines();
    s2.addBorderLines();
    s1.render((uint8_t*)AVR_VRAM_1);
    __delay_ms(2000);
    s1.clear();
    s2.clear();
    s2.addSubScreen(&s3, 64, Orientation::RIGHT);
    s1.writeString("A third subscreen has been added.");
    s3.writeString("Screen 3");
    s3.addBorderLines();
    s1.render((uint8_t*)AVR_VRAM_1);
    __delay_ms(2000);
    s1.clear();
    s2.clear();
    s3.clear();
    for (int i = 0; i < 100; ++i)
    {
        s1.writeChar('1');
        s2.writeChar('2');
        s3.writeChar('3');
    }
    s1.render((uint8_t*)AVR_VRAM_1);
}

// Test ScreenHandler
void testScreenHandler();
void testScreenHandlerAnimation();

#endif