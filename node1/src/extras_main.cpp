#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
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



void loopUntilRIGHT(Joystick * joystick)
{
    Direction dir;
    int8_t x; int8_t y;
    do{
        _delay_ms(20);
        dir = joystick->read(&x, &y);
    } while (dir != NEUTRAL);
    do{
        _delay_ms(20);
        dir = joystick->read(&x, &y);
    } while (dir != EAST);

}

void displayFunction()
{
    Joystick & joystick = Joystick::getInstance();

    Screen s1 = Screen();
	s1.clear();
    s1.writeString("This is a display demonstration. Push the joystick RIGHT to advance.");
    s1.render();
    Screen s2 = Screen();
    Screen s3 = Screen();

    loopUntilRIGHT(&joystick);

    s1.addSubScreen(&s2, 4, Orientation::LOWER);
    s1.goToStart();
    s2.goToStart();
    s3.goToStart();

    s1.writeString("We can split the display into subdisplays. This is display 1.");
    s2.writeString("This is display 2.");
    s1.render();

    loopUntilRIGHT(&joystick);
    s1.clear();
    s2.clear();
    s1.writeString("Here you see the split between the displays.");
    
    s2.writeString("This is display 2.");
    s1.addBorderLines();
    s2.addBorderLines();
    s3.addBorderLines();

    s1.render();
    
    loopUntilRIGHT(&joystick);

    s2.addSubScreen(&s3, 64, RIGHT);

    s2.writeString("There can be tons of small displays!");
    s3.writeString("It's pretty cool!");
    s1.render();
    loopUntilRIGHT(&joystick);
	s1.clear();

    s1.removeSubScreen(); // removes all subscreens

    s1.addSubScreen(&s2, 7, LOWER);
    s1.writeString("This is a header!");
    s2.writeString("You can even se an animated header in the main menu!");
	s1.updateBorderLines();
	s1.render();

	loopUntilRIGHT(&joystick);

}


void cubeMenu()
{

    const uint8_t nrOfItems = 3;
    char* menu[] = {"With FLEX", "Without FLEX", "Screen Example"};
    uint8_t index = 0;

    Joystick & joystick = Joystick::getInstance();

    Screen top_line = Screen();

    Screen screen = Screen();

    Screen bottom = Screen();


    top_line.addSubScreen(&screen, 7, LOWER);
    screen.addSubScreen(&bottom, 3, LOWER);

    screen.addBorderLines();
    top_line.addBorderLines();
    bottom.addBorderLines();

    screen.clear();
    top_line.clear();
    bottom.clear();

    screen.render();

    c3DCube cube;

    int8_t x;   
    int8_t y;
    
	Direction currentDir = joystick.read(&x, &y);
    Direction lastDir = currentDir;
    
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
            zero_delay_counter = 128;
            scrolling_text_index_counter += 1;
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
        
        
        screen.clear();
        bottom.clear();
        bottom.writeString("Note:\nSelect: RIGHT\nExit Demo: PRESS");

        screen.goToPage(1);
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
                    case 2:
                        displayFunction();
                        break;
                }
			}
			default:
			{
			}
			}
		}
		top_line.updateBorderLines();
		screen.updateBorderLines();
		bottom.updateBorderLines();
        screen.render();
	}
}


int main(void)
{
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    
    ADC& adc = ADC::getInstance();
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, &pb3);
    
    cubeMenu();
}