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
#include "../lib/display/screen.h"
#include "../lib/display/screenhandler.h"

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
    // Screen init
    Screen s1 = Screen();

    // Animated apple logo
    const unsigned char appleLogo[8] =
	{0b00000000, 0b01111000, 0b11111100, 0b11111110, 0b11001101, 0b01001000,0b00000000,0b00000000};
	s1.clear();
	s1.goTo(4,61);
	for (int i= 0; i < 8; ++i)
	{
		s1.write(appleLogo[i]);
    }
    s1.render((uint8_t*)AVR_VRAM_1);
	_delay_ms(200);
	char letter = '-';
	for (int i = 0; i < 26; ++i)
	{
		switch (letter)
		{
			case '-':
				letter = '\\';
				break;
			case '\\':
				letter = '|';
				break;
			case '|':
				letter = '/';
				break;
			case '/':
				letter = '-';
				break;
		}
		s1.goTo(6, 29);
		s1.writeString("Initializing ");
		s1.writeChar(letter);
		s1.goTo(7, 0);
		for (int j = 0; j <= i; ++j)
		{
			s1.writeChar('-');
		}
		s1.render((uint8_t*)AVR_VRAM_1);
		_delay_ms(100);
		
	}
	s1.goTo(6, 29);
    s1.writeString("Initializing *");
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(350);
    
    // Basic display test:

    s1.clear();
    s1.goTo(0,0);
    s1.writeString("Writing to a single display");
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(2000);
    s1.writeString("\nFilling the rest of the display with lines");
    for (int i = 0; i < 100; ++i)
    {
        s1.writeChar('-');
    }
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(2000);


}
void testSubScreen()
{
    Screen s1 = Screen();
    Screen s2 = Screen();
    Screen s3 = Screen();
    s1.addSubScreen(&s2, 4, Orientation::LOWER);
    s1.goTo(0,0);
    s2.goTo(0,0);
    s3.goTo(0,0);

    //


    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    printf("S1 page0: %d\n", s1.page0);
    printf("S1 page1: %d\n", s1.page1);
    printf("S1 col0: %d\n", s1.col0);
    printf("S1 col1: %d\n", s1.col1);

    printf("S2 page0: %d\n", s2.page0);
    printf("S2 page1: %d\n", s2.page1);
    printf("S2 col0: %d\n", s2.col0);
    printf("S2 col1: %d\n", s2.col1);


    //


    s1.writeString("Writing to 2 displays. This is display 1.");
    s2.writeString("This is display 2.");
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(3000);
    s2.writeString("\nDisplay 1, 2 will be filled with x, y");
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(3000);
    s1.clear();
    s2.clear();
    for (int i = 0; i < 100; ++i)
    {
        s1.writeChar('x');
        s2.writeChar('y');
    }
    _delay_ms(3000);
    s1.clear();
    s1.writeString("Display borders will now be added");
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(2000);
    s1.addBorderLines();
    s2.addBorderLines();
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(3000);
    s1.clear();
    s2.clear();
    s2.addSubScreen(&s3, 64, Orientation::RIGHT);
    s1.writeString("A third subscreen has been added.");
    s3.writeString("Screen 3");
    s3.addBorderLines();
    s1.updateBorderLines();
    s2.updateBorderLines();
    s3.updateBorderLines();
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(3000);
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
    _delay_ms(3000);
    //

    printf("Before removing S3\n");
    printf("S3 page0: %d\n", s3.page0);
    printf("S3 page1: %d\n", s3.page1);
    printf("S3 col0: %d\n", s3.col0);
    printf("S3 col1: %d\n", s3.col1);


    //
    s2.removeSubScreen();
    s1.clear();
    s2.clear();
    //
    printf("Removed S3\n");

    printf("S2 page0: %d\n", s2.page0);
    printf("S2 page1: %d\n", s2.page1);
    printf("S2 col0: %d\n", s2.col0);
    printf("S2 col1: %d\n", s2.col1);
    printf("S2 pagesize: %d\n", s2.pagesize);
    printf("S2 colsize: %d\n", s2.colsize);


    //
    s1.writeString("Removed Subscreen 3");
    s2.writeString("Only these two subscreens are currently in use");
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(3000);
    s2.clear();
    s1.clear();
}

// Test ScreenHandler
void testScreenHandler()
{
    ScreenHandler& h = ScreenHandler::getInstance();
    Screen s1 = Screen();
    Screen s2 = Screen();
    s1.clear();
    s2.clear();
    h.addScreen(&s1);
    h.addScreen(&s2);

    const unsigned char appleLogo[8] =
	{0b00000000, 0b01111000, 0b11111100, 0b11111110, 0b11001101, 0b01001000,0b00000000,0b00000000};
	s1.goTo(4,61);
	for (int i= 0; i < 8; ++i)
	{
		s1.write(appleLogo[i]);
    }
    s1.flagReadyToRender();
	_delay_ms(200);
	char letter = '-';
	for (int i = 0; i < 26; ++i)
	{
		switch (letter)
		{
			case '-':
				letter = '\\';
				break;
			case '\\':
				letter = '|';
				break;
			case '|':
				letter = '/';
				break;
			case '/':
				letter = '-';
				break;
		}
		s1.goTo(6, 29);
		s1.writeString("Initializing ");
		s1.writeChar(letter);
		s1.goTo(7, 0);
		for (int j = 0; j <= i; ++j)
		{
			s1.writeChar('-');
		}
		s1.flagReadyToRender();
		_delay_ms(100);
		
    }
    s1.goTo(6, 29);
    s1.writeString("Initializing *");
    s1.flagReadyToRender();
    _delay_ms(350);

    s1.clear();
    s1.flagReadyToRender();

    h.addScreen(&s2);
    s1.addSubScreen(&s2, 64, Orientation::RIGHT);
    s1.writeString("Testing ScreenHandler. This is display 1.");
    s2.writeString("This is display 2");
    s1.flagReadyToRender();
    _delay_ms(2000);
    s1.addBorderLines();
    s2.addBorderLines();
    s1.flagReadyToRender();
    _delay_ms(1000);
    s1.fill(0b11111111);
    s2.fill(0b00000000);
    s1.flagReadyToRender();
    _delay_ms(1000);
    s1.clear();
    s2.clear();
    s1.flagReadyToRender();
    h.removeScreen(&s2);
    s1.removeSubScreen();
    s1.writeString("Now, there is only one display again. \nNewline\nIt works!");
    s1.flagReadyToRender();
    _delay_ms(3000);
    s1.fill(0b01010101);


}
void testScreenHandlerAnimation();

#endif // DO_TESTS not defined