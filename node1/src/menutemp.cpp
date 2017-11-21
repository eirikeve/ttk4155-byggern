// #include <stdio.h>
// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdint.h>

// #include "test.h"
// #include "lib/utilities/printf.h"
// #include "lib/pins/pins.h"
// #include "lib/uart/uart.h"
// #include "lib/adc/adc.h"
// #include "../lib/joystick/joystick.h"
// #include "lib/timer/timer.h"
// #include "../lib/spi/spi.h"
// #include "../lib/can/can.h"
// #include "../lib/slider/slider.h"
// #include "../lib/fsm/fsm.h"
// #include "../lib/display/screen.h"
// //#include "../lib/display/screenhandler.h"
// #include "../lib/menu/menu.h"
// #include "../lib/can/canmsg.h"
// #include "../lib/slider/slider.h"
// #include "../lib/utilities/eeprom.h"
// #include "../lib/snake/snake.h"



// void menuLoop1() {
//     const uint8_t nrOfItems = 4;

//     char* menu[] = {"Play game", "BLE demo", "Display demo", "Snake"};
//     uint8_t index = 0;

//     Joystick & joystick = Joystick::getInstance();
//     FSM & fsm = FSM::getInstance();

//     Screen screen = Screen();
// 	screen.clear();
//     screen.render((uint8_t*)AVR_VRAM_1);

//     int8_t x;
// 	int8_t y;
// 	Direction currentDir = Direction::NEUTRAL;
//     Direction lastDir = Direction::NEUTRAL;
    
//     uint8_t old_state = (uint8_t)fsm.getCurrentState();

// 	while (true)
// 	{
//         screen.clear();
// 		lastDir = currentDir;
//         currentDir = joystick.read(&x, &y);

//         for (int i = 0; i < nrOfItems; i++) {
//             if (i == index) {
//                 screen.writeChar('>');
//             }
//             else {
//                 screen.writeChar(' ');
//             }
//             screen.writeString(menu[i]);
//             screen.writeChar('\n');
//         }

// 		if (lastDir == Direction::NEUTRAL)
// 		{
// 			switch (currentDir)
// 			{
// 			case Direction::NORTH:
// 			{
// 				if (index > 1) {
//                     index--;
//                 }
// 				break;
// 			}
// 			case Direction::SOUTH:
// 			{
// 				if (index < nrOfItems - 1) {
//                     index++;
//                 }
// 				break;
// 			}
// 			case Direction::EAST:
// 			{
//                 screen.clear();
//                 switch (index) {
//                     case 0:
//                         fsm.handleEvent(EV_START_GAME);
//                         break;
//                     case 1:
//                         fsm.handleEvent(EV_START_GAME_NRF);
//                         break;
//                     case 2:
//                         fsm.handleEvent(EV_START_DISPLAY);
//                         break;
//                     case 3:
//                     fsm.handleEvent(EV_START_SNAKE);
//                 }
//                 return;
// 			}
// 			default:
// 			{
// 				break;
// 			}
// 			}
// 		}
//         screen.render();
// 	}
// }