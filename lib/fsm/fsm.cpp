// fsm.cpp
// 13/11/2017

#include "fsm.h"

FSM::FSM()
{
    onStateFunc = &nothingHappens;
}

void FSM::transitionTo(state_t s)
{
    // Change state, perform transition function, set onState function
    current_state = s;
    return;
}

void FSM::handleEventATmega162(event_t event)
{
    switch(event)
    {
            case EV_GOTO_MENU:
            {
                if (current_state != IN_MENU)
                {
                    transitionTo(IN_MENU);
                }
                
                break;
            }
            case EV_START_GAME:
            {
                if (current_state == IN_MENU)
                {
                    transitionTo(IN_GAME);
                }
                break;
            }
            case EV_GAME_OVER:
            {
                break;
            }
            case EV_START_SNAKE:
            {
                if (current_state == IN_MENU)
                {
                    transitionTo(IN_SNAKE);
                }
                break;
            }
            case EV_SNAKE_OVER:
            {
                break;
            }
            case EV_START_DISPLAY:
            {
                if (current_state == IN_MENU)
                {
                    transitionTo(IN_DISPLAY);
                }
                break;
            }
            case EV_DISPLAY_END:
            {
                break;
            }
            case EV_START_NRF:
            {
                if (current_state == IN_MENU)
                {
                    transitionTo(IN_NRF);
                }
                break;
            }
            case EV_NRF_END:
            {
                break;
            }
            default:
                break;
    }

}
void FSM::handleEventATmega2560(event_t event)
{
    switch(event)
    {
        case EV_GOTO_IDLE:
        {
            if (current_state == STARTUP_NODE2)
            {
                transitionTo(IDLE);
            }
            break;
        }
        case EV_START_GAME:
        {
            if (current_state == IDLE)
            {
                transitionTo(GAME_RUNNING);
            }
            break;
        }
        case EV_GAME_OVER:
        {
            if (current_state == GAME_RUNNING)
            {
                transitionTo(GAME_OVER);
            }
            break;
        }
        case EV_EXIT_GAME:
        {
            if (current_state == GAME_OVER)
            {
                transitionTo(IDLE);
            }
            break;
        }
        default:
            break;
    }
}

void FSM::handleEvent(event_t event)
{
    #ifdef __AVR_ATmega162__
    handleEventATmega162(event);

    #elif __AVR_ATmega2560__
    handleEventATmega2560(event);

    #endif //__AVR_ATmega162__
}


void FSM::runOnState()
{
    onStateFunc();
}



