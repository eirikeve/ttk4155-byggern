#include "fsm_state_functions.h"



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
    // while(!(checkForACK()))
    // {
    //     can.transmit(&msg);
    // }

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

void menuLoop()
{
    Joystick & joystick = Joystick::getInstance();
    FSM & fsm = FSM::getInstance();
    OLED & oled = OLED::getInstance();

    Screen screen = Screen(&oled);
	screen.clear();
    screen.render((uint8_t*)AVR_VRAM_1);

    MenuNode main("");
	MenuNode nr1("PingPong Game");
	MenuNode nr2("Snake Game");
    MenuNode nr3("Display Test");
    MenuNode nr4("Play PingPong with controller", &_fsm_extern_handle_event, (uint8_t)EV_START_GAME);
    MenuNode nr5("Play PingPong with Bluetooth", &_fsm_extern_handle_event, (uint8_t)EV_START_GAME_NRF);
    MenuNode nr6("Play Snake", &_fsm_extern_handle_event, (uint8_t)EV_START_SNAKE);
    main.addChild(nr1);
	main.addChild(nr2);
    main.addChild(nr3);
    nr1.addChild(nr4);
    nr1.addChild(nr5);
    nr2.addChild(nr6);

    Menu menuStructure(&main);

    int8_t x;
	int8_t y;
	Direction currentDir = Direction::NEUTRAL;
    Direction lastDir = Direction::NEUTRAL;
    
    uint8_t old_state = (uint8_t)fsm.getCurrentState();

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
                // Here: Need to exit if we did call a function!
				menuStructure.select();
                screen.clear();
                if (old_state != (uint8_t)fsm.getCurrentState())
                {
                    return;
                }
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

void gameLoop()
{
    // Get initialized instances
    FSM & fsm = FSM::getInstance();
    Joystick & joystick = Joystick::getInstance();
    Slider & slider = Slider::getInstance(1);
    CAN & can = CAN::getInstance();

    // Send msg to node 2 that the game is starting
    CanMessage msg;
    CanMessage recv;

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
            msg.id = CAN_ID_ACK;
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
    printf("Started snek\n");
    //sn.start();
    printf("Snek finished\n");
    // Highscore is stored in the EEPROM, so we check if the new score is higher than the current highscore.
    /*uint16_t highscore = (uint16_t)sn.getHighScore();
    uint8_t current_highscore_L = eepromRead(EEPROM_SNAKE_HIGHSCORE_ADDR_L);
    uint8_t current_highscore_H = eepromRead(EEPROM_SNAKE_HIGHSCORE_ADDR_H);
    uint16_t current_highscore = (uint16_t)current_highscore_L | ((uint16_t)current_highscore_H << 8);
    if (highscore > current_highscore)
    {
        current_highscore_H = (uint8_t)((highscore >> 8) & 0xFF);
        current_highscore_L = (uint8_t)(highscore & 0xFF);
        eepromWrite(EEPROM_SNAKE_HIGHSCORE_ADDR_H, current_highscore_H);
        eepromWrite(EEPROM_SNAKE_HIGHSCORE_ADDR_L, current_highscore_L);

        // Todo: Add a nice splash screen which congratulates the user!
    }
    */

    fsm.handleEvent(EV_SNAKE_OVER);
    
}


void displayLoop()
{
    FSM & fsm = FSM::getInstance();
    // todo add some awesome graphic stuff here!
    fsm.handleEvent(EV_DISPLAY_END);
}

void gameNRFLoop()
{
    FSM & fsm = FSM::getInstance();
    // todo add the NRF functionality
    fsm.handleEvent(EV_GAME_NRF_END);
}

void errorLoop()
{
    return;
}
void errorTransition()
{
    // Broadcast RESET to other nodes
    CAN & can = CAN::getInstance();
    CanMessage msg;
    msg.id = CAN_ID_RESET;
    msg.length = CAN_LENGTH_RESET;
    msg.data[0] = 0b0;
    can.transmit(&msg);
    if(!(checkForACK()))
    {
        // Try twice
        can.transmit(&msg);
    }

}

void loadStateFunctionsToFSM()
{
    FSM & fsm = FSM::getInstance();

    stateFunctions s_fun;

    s_fun.state = STATE_STARTUP1;
    // s_fun.transitionFunction    = nothingHappens;
    s_fun.stateLoopFunction     = startupLoop;
    fsm.addStateFunctions(s_fun);

    s_fun.state = STATE_MENU;
    // s_fun.transitionFunction    = nothingHappens;
    s_fun.stateLoopFunction     = menuLoop;
    fsm.addStateFunctions(s_fun);

    s_fun.state = STATE_GAME;
    // s_fun.transitionFunction    = nothingHappens;
    s_fun.stateLoopFunction     = gameLoop;
    fsm.addStateFunctions(s_fun);

    s_fun.state = STATE_SNAKE;
    // s_fun.transitionFunction    = nothingHappens;
    s_fun.stateLoopFunction     = snakeLoop;
    fsm.addStateFunctions(s_fun);

    s_fun.state = STATE_DISPLAY;
    // s_fun.transitionFunction    = nothingHappens;
    s_fun.stateLoopFunction     = displayLoop;
    fsm.addStateFunctions(s_fun);

    s_fun.state = STATE_GAME_NRF;
    // s_fun.transitionFunction    = nothingHappens;
    s_fun.stateLoopFunction     = gameNRFLoop;
    fsm.addStateFunctions(s_fun);

    s_fun.state = STATE_ERROR;
    // s_fun.transitionFunction    = errorTransition;
    s_fun.stateLoopFunction     = errorLoop;
    fsm.addStateFunctions(s_fun);
}
