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




void startupLoop()
{
    FSM & fsm = FSM::getInstance();
    CAN & can = CAN::getInstance();

    // Todo: Add graphic/ print showing that we are waiting for CAN response.

    CanMessage msg;
    msg.id = CAN_ID_RESET;
    msg.length = CAN_LENGTH_RESET;
    msg.data[0] = 0b0;
    can.transmit(&msg);
    while(!(checkForACK())
    {
        can.transmit(&msg);
    }

    // Todo: Add graphic/ print showing that we got CAN response.

    // If all state functions are loaded into the fsm, go to the menu state
    if (fsm.checkAllStateFunctionsExist())
    {
        fsm.handleEvent(EV_GOTO_MENU);
        return;
    }
    else
    {
        fsm.handleEvent(EV_MISSING_STATE_FUNCTIONS);
        return;
    }

}

void menuLoop();

void gameLoop(void)
{
    // Get initialized instances
    FSM & fsm = FSM::getInstance();
    Joystick & joystick = Joystick::getInstance();
    Slider & slider = Slider::getInstance(1);
    CAN & can = CAN::getInstance();

    // Send msg to node 2 that the game is starting
    CanMessage msg;
    CanMeddage recv;

    msg.id = CAN_ID_START_GAME;
    msg.length = CAN_LENGTH_START_GAME;
    msg.data[0] = 0b0;
    can.transmit(&msg);

    // Wait for ACK from node 2. If none is received, inform the FSM
    if (!(checkForACK()))
    {
        fsm.handleEvent(EV_NO_CAN_ACK);
        return; // return to main while loop, where new onStateLoop will run
    }

    msg.id = CAN_ID_SEND_USR_INPUT;
    msg.length = CAN_LENGTH_SEND_USR_INPUT;
    
    // Joystick and slider read values
    int8_t joystick_x;
    int8_t slider_x;
    bool slider_button_pressed;

    while (true) 
    {
        // Transmit control data, and check for END_GAME event
        joystick_x = joystick.readX();
        slider_x = slider.read();
        slider_button_pressed = slider.buttonPressed();

        //printf("x: %d, y: %d, dir: %d\n", x, y, dir);
        msg.data[0] = joystick_x;
		msg.data[1] = slider_x;
        msg.data[2] = (int8_t)slider_button_pressed;
        can.transmit(&msg);
        _delay_ms(100);

        recv = can.receive();
        if (recv.id == CAN_ID_STOP_GAME)
        {
            msg.ID = CAN_ID_ACK;
            msg.length = CAN_LENGTH_ACK;
            msg.data[0] = 0b0;

            can.transmit(&msg);
            fsm.handleEvent(EV_GAME_OVER);
            return; // return to main while loop, where new onStateLoop will run
        }
    }
}

void snakeLoop()
{
    // Get initialized instance
    FSM & fsm = FSM::getInstance();

    // The snake game runs until exit is requested by user.
	Snake sn;
    sn.start();

    // Highscore is stored in the EEPROM, so we check if the new score is higher than the current highscore.
    uint16_t highscore = (uint16_t)sn.getHighScore();
    uint8_t current_highscore_L = eepromRead(EEPROM_SNAKE_HIGHSCORE_ADDR_L);
    uint8_t current_highscore_H = eepromRead(EEPROM_SNAKE_HIGHSCORE_ADDR_H);
    uint16_t current_highscore = (uint16_t)current_highscore_L | ((uint16_t)current_highscore_H < 8);
    if (highscore > current_highscore)
    {
        current_highscore_H = (uint8_t)((highscore > 8) & 0xFF);
        current_highscore_L = (uint8_t)(highscore & 0xFF);
        eepromWrite(EEPROM_SNAKE_HIGHSCORE_ADDR_H, current_highscore_H);
        eepromWrite(EEPROM_SNAKE_HIGHSCORE_ADDR_L, current_highscore_L);

        // Todo: Add a nice splash screen which congratulates the user!
    }

    fsm.handleEvent(EV_SNAKE_OVER);
    
}

