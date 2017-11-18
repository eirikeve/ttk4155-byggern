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
#include "../lib/can/canmsg.h"





void runGameJoystick(void)
{
    // Get initialized instances
    FSM & fsm = FSM::getInstance();
    Joystick & joystick = Joystick::getInstance();
    CAN & can = CAN::getInstance();

    // Joystick read values
    int8_t x;
    int8_t y;

    // Send msg to node 2 that the game is starting
    CanMessage msg;
    CanMeddage recv;

    msg.id = CAN_ID_START_GAME;
    msg.length = CAN_LENGTH_START_GAME;
    msg.data[0] = 0b0;
    can.transmit(&msg);

    // Wait for ACK from node 2. If none is received, inform the FSM
    for (uint8_t i = 0; i < 20; ++i )
    {
        recv = can.receive();
        if (recv.id == CAN_ID_ACK)
        {
            break; // for loop
        }
        _delay_ms(1);
    }
    if(recv.id != CAN_ID_ACK)
    {
        fsm.handleEvent(EV_NO_CAN_ACK);
        return; // return to main while loop, where new onStateLoop will run
    }

    // 
    msg.id = CAN_ID_SEND_USR_INPUT;
    msg.length = CAN_LENGTH_SEND_USR_INPUT;

    while (true) 
    {
        Direction dir = joystick.read(&x, &y);
        printf("x: %d, y: %d, dir: %d\n", x, y, dir);
        msg.data[0] = x;
		msg.data[1] = y;
        msg.data[2] = dir;
        can.transmit(&msg);
        _delay_ms(100);

        recv = can.receive();
        if (recv.id == CAN_ID_STOP_GAME)
        {
            msg.ID = CAN_ID_ACK;
            msg.length = CAN_LENGTH_ACK;
            can.transmit(&msg);

            fsm.handleEvent(EV_GAME_OVER);
            return; // return to main while loop, where new onStateLoop will run
        }
    }
}