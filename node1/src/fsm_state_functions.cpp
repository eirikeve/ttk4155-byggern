#include "fsm_state_functions.h"
void playStartupVideo()
{
    Screen s1 = Screen();

    // Animated apple logo
    const unsigned char appleLogo[8] =
	{0b00000000, 0b01111000, 0b11111100, 0b11111110, 0b11001101, 0b01001000,0b00000000,0b00000000};
	s1.clear();
	s1.goTo(1,61);
	for (int i= 0; i < 8; ++i)
	{
		s1.write(appleLogo[i]);
    }
    s1.render((uint8_t*)AVR_VRAM_1);
	_delay_ms(300);
	char letter = '-';
    uint8_t max_char_on_screen = 21;
	for (int i = 0; i < 30; ++i)
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
		s1.goTo(3, 29);
		s1.writeString("Initializing ");
		s1.writeChar(letter);
		s1.goTo(4, 0);
		for (int j = 0; j <= i; ++j)
		{
            if (j <= max_char_on_screen)
            {
                s1.writeChar( '-' );
            }
		}
        s1.goTo(5, 0);
		for (int j = 0; j <= i; ++j)
		{
            if (j > 2 && j - 3 <= max_char_on_screen)
            {
                s1.writeChar( '-' );
            }

		}
        s1.goTo(6, 0);
		for (int j = 0; j <= i; ++j)
		{
            if (j > 5 && j - 6 <= max_char_on_screen)
            {
                s1.writeChar( '-' );
            }
		}
        s1.goTo(7, 0);
		for (int j = 0; j <= i; ++j)
		{
            if (j > 8 && j - 9 <= max_char_on_screen)
            {
                s1.writeChar( '-' );
            }
		}
		s1.render();
		_delay_ms(50);
		
	}
    s1.goTo(3, 29);
	s1.writeString("Initializing *");
    s1.render();
    _delay_ms(250);
}

void startupLoop()
{   
    // Reset timer blink period here, in case of reset after ERROR.
    Timer& timer = Timer::getInstance(0);
    timer.setInterruptPeriod(500);

    FSM & fsm = FSM::getInstance();
    CAN & can = CAN::getInstance();

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

void menuLoop() {
    const uint8_t nrOfItems = 4;

    char* menu[] = {"Play game", "BLE demo", "Display demo", "Snake"};
    uint8_t index = 0;

    Joystick & joystick = Joystick::getInstance();
    FSM & fsm = FSM::getInstance();

    Screen screen = Screen();
	screen.clear();
    screen.render((uint8_t*)AVR_VRAM_1);

    int8_t x;
	int8_t y;
	Direction currentDir = Direction::NEUTRAL;
    Direction lastDir = Direction::NEUTRAL;
    
    //uint8_t old_state = (uint8_t)fsm.getCurrentState();

	while (true)
	{
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
                        fsm.handleEvent(EV_START_GAME);
                        break;
                    case 1:
                        fsm.handleEvent(EV_START_GAME_NRF);
                        break;
                    case 2:
                        fsm.handleEvent(EV_START_DISPLAY);
                        break;
                    case 3:
                    fsm.handleEvent(EV_START_SNAKE);
                }
                return;
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
    Slider & slider1 = Slider::getInstance(1);
    CAN & can = CAN::getInstance();

    // Send msg to node 2 that the game is starting
    CanMessage msg;
    CanMessage recv;
    bool ack;

    msg.id = CAN_ID_START_GAME;
    do{
        can.transmit(&msg);
        ack = checkForACK();
    } while(ack == false); 
    printf("Got Start ACK - running game\n");

    int8_t joystick_x;
    int8_t joystick_y;
    int8_t slider_x;
    bool slider_button_pressed = false;

        while (true) 
        {
            // In game
            // Transmit control data, and check for END_GAME event
            joystick.read(&joystick_x, &joystick_y);
            slider_x = slider1.read();
            slider_button_pressed = slider1.buttonPressed();
            //printf("x: %d, y: %d, dir: %d\n", x, y, dir);
            msg.id = CAN_ID_SEND_USR_INPUT;
            msg.length = 3;
            msg.data[0] = joystick_x;
            msg.data[1] = slider_x;
            msg.data[2] = (int8_t)slider_button_pressed;
            can.transmit(&msg);
            _delay_ms(100);

            recv = can.receive();
            if (recv.id == CAN_ID_STOP_GAME)
            {
                printf("\tRecvd STOP. Sending ACK.\n");
                msg.id = CAN_ID_ACK;
                msg.length = CAN_LENGTH_ACK;
                msg.data[0] = 0b0;
                can.transmit(&msg);
                fsm.handleEvent(EV_GAME_OVER);
                return;
            }
            else if (recv.id == CAN_ID_RESET)
            {
                printf("\tRecvd Reset! Exiting Loop\n");
                // Usually, trigger event here.
                fsm.handleEvent(EV_RESET);
                return;
               
            }
        }
    // Should not ever reach this, but added just in case
    fsm.handleEvent(EV_GAME_OVER);
}

void snakeLoop()
{
    // Get initialized instance
    FSM & fsm = FSM::getInstance();

    // The snake game runs until exit is requested by user.
	Snake sn;
    printf("Started snek\n");
    sn.run();
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
    _delay_ms(500); // Remove when actual display stuff is added.
}

void gameNRFLoop()
{
    FSM & fsm = FSM::getInstance();
    // todo add the NRF functionality
    fsm.handleEvent(EV_GAME_NRF_END);
}

void errorLoop()
{
    // LED blink timer
    Timer& timer = Timer::getInstance(0);
    timer.setInterruptPeriod(100);

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
