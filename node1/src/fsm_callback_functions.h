#pragma once

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
#include "../lib/spi/spi.h"
#include "../lib/can/can.h"
#include "../lib/slider/slider.h"
#include "../lib/fsm/fsm.h"
#include "../lib/display/screen.h"
//#include "../lib/display/screenhandler.h"
#include "../lib/menu/menu.h"




void runGame(void)
{
    // Get initialized instances
    FSM & fsm = FSM::getInstance();
    Joystick & joystick = Joystick::getInstance();
    CAN & can = CAN::getInstance();

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