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
#include "../lib/joystick/joystick.h"
#include "lib/timer/timer.h"
#include "../lib/spi/spi.h"
#include "../lib/can/can.h"
#include "../lib/slider/slider.h"
#include "../lib/fsm/fsm.h"
#include "../lib/display/screen.h"
#include "../lib/menu/menu.h"
#include "../lib/can/canmsg.h"
#include "../lib/slider/slider.h"
#include "../lib/utilities/eeprom.h"
#include "../lib/snake/snake.h"
#include "../lib/utilities/utilities.h"


/**
 * Plays an animated startup video
 **/
void playStartupVideo();

/**
 * State loop for STATE_STARTUP1
 **/
void startupLoop();

/**
 * State loop for STATE_MENU
 **/
void menuLoop();

/**
 * State loop for STATE_GAME
 **/
void gameLoop();

/**
 * State loop for STATE_SNAKE
 **/
void snakeLoop();

/**
 * State loop for STATE_TUNE_PID
 **/
void tunePID_loop();

/**
 * State loop called exactly once when transitioning to STATE_ERROR
 * */
void errorLoop();

/**
 * Helper function to load the above functions to the FSM
 **/
void loadStateFunctionsToFSM();
