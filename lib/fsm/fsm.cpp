// fsm.cpp
// 13/11/2017

#include "fsm.h"
void nothingHappens(void) {}

FSM::FSM()
{
    onStateFunc = nothingHappens;
}

void FSM::transitionTo(uint8_t s)
{
    // Change state, perform transition function, set onState function
    current_state = s;
    return;
}

void FSM::handleEventATmega162(uint8_t event)
{
    switch(event)
    {
            case EV_GOTO_MENU:
            {
                if (current_state == STATE_STARTUP1)
                {
                    transitionTo(STATE_MENU);
                }
                
                break;
            }
            case EV_START_GAME:
            {
                if (current_state == STATE_MENU)
                {
                    transitionTo(STATE_GAME);
                }
                break;
            }
            case EV_GAME_OVER:
            {
                if (current_state == STATE_GAME)
                {
                    transitionTo(STATE_MENU);
                }
                break;
            }
            case EV_START_SNAKE:
            {
                if (current_state == STATE_MENU)
                {
                    transitionTo(STATE_SNAKE);
                }
                break;
            }
            case EV_SNAKE_OVER:
            {
                if (current_state ==  STATE_SNAKE)
                {
                    transitionTo(STATE_MENU);
                }
                
                break;
            }
            case EV_START_DISPLAY:
            {
                if (current_state == STATE_MENU)
                {
                    transitionTo(STATE_DISPLAY);
                }
                break;
            }
            case EV_DISPLAY_END:
            {
                if (current_state == STATE_DISPLAY)
                {
                    transitionTo(STATE_MENU);
                }
                break;
            }
            case EV_START_NRF:
            {
                if (current_state == STATE_MENU)
                {
                    transitionTo(STATE_NRF);
                }
                break;
            }
            case EV_NRF_END:
            {
                if (current_state == STATE_NRF)
                {
                    transitionTo(STATE_MENU);
                }
                break;
            }
            default:
                break;
    }

}
void FSM::handleEventATmega2560(uint8_t event)
{
    switch(event)
    {
        case EV_GOTO_IDLE:
        {
            if (current_state == STATE_STARTUP2)
            {
                transitionTo(STATE_IDLE);
            }
            break;
        }
        case EV_START_GAME:
        {
            if (current_state == STATE_IDLE)
            {
                transitionTo(STATE_GAME_RUNNING);
            }
            break;
        }
        case EV_GAME_OVER:
        {
            if (current_state == STATE_GAME_RUNNING)
            {
                transitionTo(STATE_GAME_OVER);
            }
            break;
        }
        case EV_EXIT_GAME:
        {
            if (current_state == STATE_GAME_OVER)
            {
                transitionTo(STATE_IDLE);
            }
            break;
        }
        default:
            break;
    }
}

void FSM::handleEvent(uint8_t event)
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


void addToTransFnArray(transitionFunction tf)
{
    #ifdef __AVR_ATmega162__
    if (tf.state == (int)(state_node1_t)tf.state) // State is defined in node1 state enum
    {
        if (transFnArraySize == 0)
        {
            transFnArray = calloc(1, sizeof(transitionFunction));
            transFnArray[0] = tf;
        }
        else{
            // Check if state is already in the array, if so, replace it instead of re-adding
        }
    }

    #elif __AVR_ATmega2560__
    // Same as above, but with state_node2_t instead

    #endif //__AVR_ATmega162__
}
