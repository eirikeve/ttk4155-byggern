#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
// #include "../lib/comm/comm.h"
#include "../lib/utilities/utilities.h"
#include "lib/utilities/printf.h"

#include "lib/can/can.h"
#include "lib/spi/spi.h"
#include "lib/timer/timer.h"
#include "lib/joystick/joystick.h"
#include <stdint.h>

#include "../test/test.h"

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
#include "../lib/spi/spi.h"
#include "../lib/can/can.h"
#include "../lib/slider/slider.h"
#include "../lib/fsm/fsm.h"
#include "../lib/display/screen.h"
//#include "../lib/display/screenhandler.h"
#include "../lib/menu/menu.h"
#include "../lib/can/canmsg.h"
#include "../lib/utilities/eeprom.h"
#include "fsm_state_functions.h"
#include "../lib/3dcube/c3dcube.h"

void toggle_led() {
    PORTB ^= 0b1;
}


void cubeMenu()
{

    const uint8_t nrOfItems = 2;
    char* menu[] = {"With FLEX", "Without FLEX"};
    uint8_t index = 0;

    Joystick & joystick = Joystick::getInstance();

    Screen top_line = Screen();

    Screen screen = Screen();
    top_line.addSubScreen(&screen, 7, LOWER);
    screen.addBorderLines();
    top_line.addBorderLines();
    screen.clear();
    top_line.clear();

    screen.render((uint8_t*)AVR_VRAM_1);

    c3DCube cube;

    int8_t x;
    int8_t y;
    
	Direction currentDir = Direction::NEUTRAL;
    Direction lastDir = Direction::NEUTRAL;
    
    //uint8_t old_state = (uint8_t)fsm.getCurrentState();
    char* scrolling_text = "3DCube Demo!         Run the 3DCube with, or without FLEX PHYSICS (TM)!  ";
    uint8_t scrolling_text_length = 73;
    uint16_t scrolling_text_index_counter = 0;
    uint8_t scrolling_text_index = 0;
    uint8_t zero_delay_counter = 1;

	while (true)
	{
        if (scrolling_text_index_counter == 0 && zero_delay_counter > 0)
        {
            ++zero_delay_counter; // Will overflow
        }
        else
        {
            zero_delay_counter = 1;
            ++scrolling_text_index_counter;
        }
        
        if (scrolling_text_index_counter > 739)
        {
            scrolling_text_index_counter = 0;
        }
        scrolling_text_index = scrolling_text_index_counter / 10;

        top_line.clear();

        for (uint8_t i = scrolling_text_index; i < scrolling_text_index + 25; ++i)
        {
            top_line.writeChar(scrolling_text[i % scrolling_text_length]);
        }
        top_line.updateBorderLines();
        
        screen.clear();
		lastDir = currentDir;
        currentDir = joystick.read(&x, &y);

        for (int i = 0; i < nrOfItems; i++) {
            if (i == index) {
                screen.writeChar('>');
            }
            else {
                screen.writeChar(' ');
            }
            screen.writeString(menu[i]);
            screen.writeChar('\n');
        }

		if (lastDir == Direction::NEUTRAL)
		{
			switch (currentDir)
			{
			case Direction::NORTH:
			{
				if (index > 0) {
                    index--;
                }
				break;
			}
			case Direction::SOUTH:
			{
				if (index < nrOfItems - 1) {
                    index++;
                }
				break;
			}
			case Direction::EAST:
			{
                screen.clear();
                screen.render();
                switch (index) {
                    case 0:
                        cube.run(true);
                        break;
                    case 1:
                        cube.run(false);
                        break;
                }
			}
			default:
			{
			}
			}
		}
        screen.render();
	}
}




int main(void)
{
    // clr_bit(DDRE, 0);  
	/*UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    printf("Node 1 startup\n");
    Timer& timer0 = Timer::getInstance(0);
    timer0.initialize(500, toggle_led, &pb0);
    timer0.start();

    

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

    FSM & fsm = FSM::getInstance();
    loadStateFunctionsToFSM();

    sendResetUntilACK();

    printf("Node1 Starting\n");
	while (true)
	{
        fsm.runStateLoop();
    }*/


    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    
    ADC& adc = ADC::getInstance();
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, &pb3);
    
    cubeMenu();
}