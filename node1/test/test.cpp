#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "test.h"

#include "../lib/utilities/printf.h"
#include "../lib/pins/pins.h"
#include "../lib/uart/uart.h"
#include "../lib/adc/adc.h"
#include "../lib/joystick/joystick.h"
#include "../lib/timer/timer.h"
#include "../lib/utilities/utilities.h"
#include "../lib/spi/spi.h"
#include "../lib/can/can.h"
#include "../lib/slider/slider.h"
#include "../lib/fsm/fsm.h"
#include "../lib/display/screen.h"
#include "../lib/display/screenhandler.h"
#include "../lib/menu/menu.h"
#include "lib/snake/snake.h"

#ifndef TEST_UART
#define TEST_UART 0
#endif

#ifndef TEST_JOYSTICK
#define TEST_JOYSTICK 0
#endif

#ifndef TEST_LAB_8
#define TEST_LAB_8 0
#endif

#ifndef TEST_MAINLOOP
#define TEST_MAINLOOP 0
#endif

#ifndef TEST_MENU
#define TEST_MENU 1
#endif

#ifndef TEST_TIMER
#define TEST_TIMER 0
#endif

#ifndef TEST_SCREEN
#define TEST_SCREEN 0
#endif

#ifndef TEST_SERVO
#define TEST_SERVO 0
#endif

#ifndef TEST_SLIDER
#define TEST_SLIDER 0
#endif

#ifndef TEST_SPI_CAN
#define TEST_SPI_CAN 0
#endif

#ifndef TEST_SRAM
#define TEST_SRAM 0
#endif

#ifndef TEST_FSM
#define TEST_FSM 0
#endif

#ifndef TEST_SNAKE
#define TEST_SNAKE 0
#endif



#if TEST_UART
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
#endif //TEST_UART

#if TEST_TIMER
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
#endif //TEST_TIMER

#if TEST_JOYSTICK    
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
#endif TEST_JOYSTICK

#if TEST_SPI_CAN
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

#endif //TEST_SPI_CAN

#if TEST_SERVO
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
#endif //TEST_SERVO

#if TEST_SLIDER

void testSlider(){
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    ADC& adc = ADC::getInstance();

    Slider & slider0 = Slider::getInstance(0);
    slider0.initialize(&adc, NULL);

    Slider & slider1 = Slider::getInstance(1);
    slider1.initialize(&adc, NULL);

    while (true) {
        printf("Slider0 position: %d, Slider1 position: %d\n", slider0.read(), slider1.read());
    }
}

void testSliderButton() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    ADC& adc = ADC::getInstance();

    Slider & slider0 = Slider::getInstance(0);
    slider0.initialize(&adc, &pb2);

    Slider & slider1 = Slider::getInstance(1);
    slider1.initialize(&adc, &pb1);

    while (true) {
        if (slider0.buttonPressed()) {
            printf("Slider0 pressed\n");
        }
        if (slider1.buttonPressed()) {
            printf("Slider1 pressed\n");
        }
    }
}
#endif //TEST_SLIDER

#if TEST_SCREEN
// Test display
void testScreen()
{
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
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
    s1.goToStart();
    s1.writeString("Now Only calling render!");
    for (int i = 0; i < 100; ++i)
    {
        s1.render();
        _delay_ms(500);
    }
}

void doNothing(void){}

void testSubScreen()
{
    Screen s1 = Screen();
    Screen s2 = Screen();
    Screen s3 = Screen();
    s1.addSubScreen(&s2, 4, Orientation::LOWER);
    s1.goToStart();
    s2.goToStart();
    s3.goToStart();

    //



    //


    /*s1.writeString("Writing to 2 displays. This is display 1.");
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
    s1.render();
    _delay_ms(3000);
    s1.clear();
    s2.clear();
    s1.writeString("Display borders will now be added");
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(2000);
    */
    s1.addBorderLines();
    s2.addBorderLines();
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(3000);
    s1.clear();
    s2.clear();
    s2.addSubScreen(&s3, 64, Orientation::RIGHT);
    s3.addBorderLines();
    //s1.writeString("A third subscreen has been added.");
    //s3.writeString("Screen 3");
    s3.updateBorderLines();
    s1.render();
    //_delay_ms(3000);

    s1.clear();
    s2.clear();
    s3.clear();
    for (int i = 0; i < 100; ++i)
    {
        s1.writeChar('1');
        s2.writeChar('2');
        s3.writeChar('3');
        s1.updateBorderLines();
        s2.updateBorderLines();
        s3.updateBorderLines();
        s1.render();
        _delay_ms(200);
    }
    s3.updateBorderLines();
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(3000);
    //
    
/*
    printf("S1 page0: %d\n", s1.page0);
    printf("S1 page1: %d\n", s1.page1);
    printf("S1 col0: %d\n", s1.col0);
    printf("S1 col1: %d\n", s1.col1);

    printf("S2 page0: %d\n", s2.page0);
    printf("S2 page1: %d\n", s2.page1);
    printf("S2 col0: %d\n", s2.col0);
    printf("S2 col1: %d\n", s2.col1);

    printf("S3 page0: %d\n", s3.page0);
    printf("S3 page1: %d\n", s3.page1);
    printf("S3 col0: %d\n", s3.col0);
    printf("S3 col1: %d\n", s3.col1);
    printf("S3 pagesize: %d\n", s3.pagesize);
    printf("S3 colsize: %d\n", s3.colsize);
*/

/*
    //
    s2.removeSubScreen();
    s1.clear();
    s2.clear();
    //
    s1.writeString("Removed Subscreen 3");
    s2.writeString("Only these two subscreens are currently in use");
    s1.render((uint8_t*)AVR_VRAM_1);
    _delay_ms(3000);
    s2.clear();
    s1.clear();
    */
}


// // Test ScreenHandler

// // void testFSM()
// // {
// //     printf("TestFSM\n");

// //     FSM& fsm = fsm.getInstance();

// //     int i = 0;
// //     int event = 0; // EV_GOTO_MENU
// //     srand(1);
// //     while (i < 100)
// //     {
// //         ++i;
// //         printf("i: %4d \tOld state %2d \tEvent %2d \t", i, fsm.getCurrentState(), event);
// //         fsm.handleEvent(event);
// //         event = (rand() % (/*ev_node1_t::EV_NRF_END+1*/ 7));
// //         printf("New state %2d\n", (int)fsm.getCurrentState());
// //     }
// // }

// void testScreenHandler()
// {
//     UART & uart = UART::getInstance();
//     uart.initialize(9600);
//     enablePrintfWithUart();
//     printf("Test1..\n");
//     ScreenHandler& h = ScreenHandler::getInstance();
//     Screen s1 = Screen();
//     Screen s2 = Screen();
//     s1.clear();
//     s2.clear();
//     h.addScreen(&s1);

//     const unsigned char appleLogo[8] =
// 	{0b00000000, 0b01111000, 0b11111100, 0b11111110, 0b11001101, 0b01001000,0b00000000,0b00000000};
// 	s1.goTo(4,61);
// 	for (int i= 0; i < 8; ++i)
// 	{
// 		s1.write(appleLogo[i]);
//     }
//     s1.flagReadyToRender();
// 	_delay_ms(200);
// 	char letter = '-';
// 	for (int i = 0; i < 26; ++i)
// 	{
// 		switch (letter)
// 		{
// 			case '-':
// 				letter = '\\';
// 				break;
// 			case '\\':
// 				letter = '|';
// 				break;
// 			case '|':
// 				letter = '/';
// 				break;
// 			case '/':
// 				letter = '-';
// 				break;
// 		}
// 		s1.goTo(6, 29);
// 		s1.writeString("Initializing ");
// 		s1.writeChar(letter);
// 		s1.goTo(7, 0);
// 		for (int j = 0; j <= i; ++j)
// 		{
// 			s1.writeChar('-');
// 		}
// 		s1.flagReadyToRender();
// 		_delay_ms(100);
		
//     }
//     s1.goTo(6, 29);
//     s1.writeString("Initializing *");
//     s1.flagReadyToRender();
//     _delay_ms(350);
//     s1.clear();
//     s1.flagReadyToRender();
//     s2.clear();

//     h.addScreen(&s2);
//     s1.addSubScreen(&s2, 64, Orientation::RIGHT);
//     s1.writeString("Testing ScreenHandler. This is display 1.");
//     s2.writeString("This is display 2");
//     s1.flagReadyToRender();
//     _delay_ms(2000);
//     s1.addBorderLines();
//     s2.addBorderLines();
//     s1.flagReadyToRender();
//     _delay_ms(1000);
//     s1.fill(0b11111111);
//     s2.fill(0b00000000);
//     s1.flagReadyToRender();
//     _delay_ms(1000);
//     s1.clear();
//     s2.clear();
//     Screen s3 = Screen();
//     s3.addSubScreen(&s3, 4, Orientation::LOWER);
//     s3.addBorderLines();
//     s1.flagReadyToRender();
//     h.removeScreen(&s2);
//     h.removeScreen(&s3);
//     s1.removeSubScreen();
//     s1.writeString("Now, there is only one display again. \nNewline\nIt works!");
//     s1.flagReadyToRender();
//     _delay_ms(3000);    
//     printf("Test2...\n");
//     s1.fill(0b01010101);
//     printf("Test3...\n");

// }
// void testScreenHandlerAnimation();

#endif //TEST_SCREEN

#if TEST_LAB_8
void testLab8() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, false);

    ADC& adc = ADC::getInstance();
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, &pb3);

    int8_t x;
    int8_t y;
    bool button;

    CanMessage msg;
    msg.id = 2;
    msg.length = 2;

    while (true) {
        Direction dir = joystick.read(&x, &y);
        msg.data[0] = x;
        msg.data[1] = (uint8_t) joystick.buttonPressed();
        printf("x: %d, button: %d\n", x, msg.data[1]);
        can.transmit(&msg);
        _delay_ms(100);
    }
}
#endif // TEST_LAB_8

#if TEST_SRAM
void SRAM_test()
{
    set_bit(MCUCR, SRE);
    clr_bit(DDRE, 0);

    uint8_t *ext_ram = (uint8_t *) AVR_VRAM_1; // Start address for the SRAM
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n");
    // rand() stores some internal state, so calling this function in a loop will
    // yield different seeds each time (unless srand() is called before this
    //function)
    uint16_t seed = rand();
    // Write phase: Immediately check that the correct value was stored
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        //printf("SRAM[%4d] = %02X\n", i, ext_ram[i]);
    }
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        ext_ram[i] = some_value;
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i,retreived_value, some_value);
            write_errors++;
        }
}
    // Retrieval phase: Check that no values were changed during or after the write
    //phase
    srand(seed);    // reset the PRNG to the state it had before the write phase
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n",i, retreived_value, some_value);
            retrieval_errors++;
        }
}
    printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}
#endif // TEST_SRAM



#if TEST_MENU

void callback(uint8_t argv) {
    printf("Menu callback function called\n");
}

void testMenuCallback() {

    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    ADC& adc = ADC::getInstance();

    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, &pb3);

    Screen screen = Screen();
	screen.clear();
    screen.render((uint8_t*)AVR_VRAM_1);

    MenuNode main("");
	MenuNode nr1("Nr1", &callback, NULL);
	MenuNode nr2("Nr2");
    main.addChild(nr1);
	main.addChild(nr2);
    Menu menuStructure(&main);

    int8_t x;
	int8_t y;
	Direction currentDir = Direction::NEUTRAL;
	Direction lastDir = Direction::NEUTRAL;

	while (true)
	{
        screen.clear();
		lastDir = currentDir;
        currentDir = joystick.read(&x, &y);
		char **choices = NULL;
		if (menuStructure.getCurrent() != NULL)
		{
			choices = menuStructure.getCurrent()->getChildrenNames();
			for (int i = 0; i < menuStructure.getCurrent()->getTotNrOfChildren(); i++)
			{
				screen.goTo(i, 1);
				if (i == menuStructure.getSelectIndex())
				{
					screen.writeChar('>');
                }
                else {
                    screen.writeChar(' ');
                }
				screen.writeString(choices[i]);
				screen.writeChar('\n');
			}
			free(choices);
		}

		if (lastDir == Direction::NEUTRAL)
		{
			switch (currentDir)
			{
			case Direction::NORTH:
			{
				menuStructure.up();
				break;
			}
			case Direction::SOUTH:
			{
				menuStructure.down();
				break;
			}
			case Direction::EAST:
			{
				menuStructure.select();
				screen.clear();
				break;
			}
			case Direction::WEST:
			{
				menuStructure.back();
				screen.clear();
				break;
			}
			default:
			{
				break;
			}
			}
		}
        screen.render();
	}

}
void testMenu() {

    ADC& adc = ADC::getInstance();

    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, &pb3);

    Screen screen = Screen();
	screen.clear();
    screen.render((uint8_t*)AVR_VRAM_1);

	MenuNode main("");
	MenuNode nr1("Nr1");
	MenuNode nr2("Nr2");
	MenuNode nr3("Nr3");
	MenuNode nr4("Nr4");
	MenuNode nr5("Sub1");
	MenuNode nr6("Sub2");
	MenuNode nr8("Sub3");
	MenuNode nr9("Sub4");
	MenuNode nr10("Sub5");
	main.addChild(nr1);
	main.addChild(nr2);
	main.addChild(nr3);
	main.addChild(nr4);
	nr1.addChild(nr5);
	nr1.addChild(nr6);
	nr2.addChild(nr8);
	nr5.addChild(nr9);
	nr6.addChild(nr10);
	Menu menuStructure(&main);

	


	int8_t x;
	int8_t y;
	Direction currentDir = Direction::NEUTRAL;
	Direction lastDir = Direction::NEUTRAL;

	while (true)
	{
        screen.clear();
		lastDir = currentDir;
        currentDir = joystick.read(&x, &y);
		char **choices = NULL;
		if (menuStructure.getCurrent() != NULL)
		{
			choices = menuStructure.getCurrent()->getChildrenNames();
			for (int i = 0; i < menuStructure.getCurrent()->getTotNrOfChildren(); i++)
			{
				screen.goTo(i, 1);
				if (i == menuStructure.getSelectIndex())
				{
					screen.writeChar('>');
                }
                else {
                    screen.writeChar(' ');
                }
				screen.writeString(choices[i]);
				screen.writeChar('\n');
			}
			free(choices);
		}

		if (lastDir == Direction::NEUTRAL)
		{
			switch (currentDir)
			{
			case Direction::NORTH:
			{
				menuStructure.up();
				break;
			}
			case Direction::SOUTH:
			{
				menuStructure.down();
				break;
			}
			case Direction::EAST:
			{
				menuStructure.select();
				screen.clear();
				break;
			}
			case Direction::WEST:
			{
				menuStructure.back();
				screen.clear();
				break;
			}
			default:
			{
				break;
			}
			}
		}
        screen.render();
	}
}
#endif //TEST_MENU

#if TEST_MAINLOOP
void testMainLoop()
{
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, false);

    ADC& adc = ADC::getInstance();

    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, &pb3);

    Slider & slider0 = Slider::getInstance(0);
    slider0.initialize(&adc, &pb2);

    Slider & slider1 = Slider::getInstance(1);
    slider1.initialize(&adc, &pb1);

    Screen screen_main   = Screen();
    Screen screen_header = Screen(&screen_main, 1, UPPER); // 1 page high, located on top
    Screen screen_full   = Screen(); // Full screen, does not have a subscreen

    ScreenHandler &screen_handler = ScreenHandler::getInstance();
    screen_handler.addScreen(&screen_main);
    screen_handler.addScreen(&screen_header);
    screen_handler.addScreen(&screen_full);

    MenuNode node_main("Main Menu");
    Menu main_menu(&node_main);


    FSM& fsm = FSM::getInstance();
    
}


#endif // TEST_MAINLOOP


#if TEST_SNAKE
//Test snake
void testSnake(){

    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    ADC& adc = ADC::getInstance();
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, NULL);
    
	Snake sn;
	sn.start();
}
#endif

// Test ScreenHandler
#if TEST_FSM

void testFSM()
{
    printf("TestFSM\n");

    FSM& fsm = fsm.getInstance();
    #ifdef __AVR_ATmega162__

    int i = 0;
    int event = 0; // EV_GOTO_MENU
    srand(1);
    while (i < 100)
    {
        ++i;
        printf("i: %4d \tOld state %2d \tEvent %2d \t", i, fsm.getCurrentState(), event);
        fsm.handleEvent(event);
        event = (rand() % (/*ev_node1_t::EV_NRF_END+1*/ 7));
        printf("New state %2d\n", (int)fsm.getCurrentState());
    }

    #endif
}

#endif