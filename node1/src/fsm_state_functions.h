#pragma once

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
#include "../lib/slider/slider.h"
#include "../lib/utilities/eeprom.h"




void startupLoop();
void menuLoop();
void gameLoop();
void snakeLoop();
void displayLoop();
void gameNRFLoop();
void errorLoop();
void errorTransition();
void loadStateFunctionsToFSM();
