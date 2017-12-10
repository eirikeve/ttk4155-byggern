// fsm.cpp
// 13/11/2017

#include "fsm.h"
#include "../can/can.h"
#include "../can/canmsg.h"

#ifdef __AVR_ATmega162__


#include <stdio.h>


FSM::FSM()
{
    init();
}

void FSM::init()
{
    stateLoopFunction = NULL;
    for (uint8_t state = (uint8_t)STATE_STARTUP1; state < (uint8_t)STATE_STARTUP1 + NUM_STATES_NODE1; ++state)
    {
        stateFunctionsArray[state] = stateFunctions(state, nothingHappens);
    }
}

void FSM::reset()
{
    init();
}

void FSM::transitionTo(uint8_t s)
{
    // printf("New state %d\n", s);
    // Change state, set onState function, perform transition function
    current_state = s;
    stateLoopFunction = stateFunctionsArray[s].stateLoopFunction;
    return;
}

void FSM::handleEvent(uint8_t event)
{
    // Don't exit the error state except if resetting.
    if (current_state == STATE_ERROR) return;

    switch(event)
    {
            case EV_RESET:
            {
                // Always occurs after getting a reset CAN msg, respond with ACK
                transitionTo(STATE_STARTUP1);
                // Send ACK after RESET recv
                CAN & can = CAN::getInstance();
                CanMessage msg;
                msg.length = 1;
                msg.id = CAN_ID_ACK;
                can.transmit(&msg);

                break;
            }
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
            // case EV_START_DISPLAY:
            // {
            //     if (current_state == STATE_MENU)
            //     {
            //         transitionTo(STATE_DISPLAY);
            //     }
            //     break;
            // }
            // case EV_DISPLAY_END:
            // {
            //     if (current_state == STATE_DISPLAY)
            //     {
            //         transitionTo(STATE_MENU);
            //     }
            //     break;
            // }
            case EV_START_TUNE_PID:
            {
                if (current_state == STATE_MENU)
                {
                    transitionTo(STATE_TUNE_PID);
                }
                break;
            }
            case EV_STOP_TUNE_PID:
            {
                if (current_state == STATE_TUNE_PID)
                {
                    transitionTo(STATE_MENU);
                }
                break;
            }
            case EV_NO_CAN_ACK:
            case EV_MISSING_STATE_FUNCTIONS:
            default:
            {
                // Some error occurred.
                transitionTo(STATE_ERROR);
                // Set LED Blinking to very fast
                stateLoopFunction();
                // Send RESET to other nodes
                sendResetUntilACK();
                // If we ever get ACK, goto startup
                transitionTo(STATE_STARTUP1);
                
            }

    }

}

void FSM::runStateLoop()
{
    if (stateLoopFunction != nothingHappens && 
        stateLoopFunction != NULL           &&
        current_state     != STATE_ERROR)
    {
        stateLoopFunction();
    }
    else if (current_state != (uint8_t)STATE_ERROR)
    {
        // Should never happen under normal conditions :)
        transitionTo((uint8_t)STATE_ERROR);
    }
    
}

void FSM::addStateFunctions(stateFunctions s_fun)
{
    // Indexing is by state. Though index indicates state, we also update
    // the state variable (just to prevent any possible bugs)
    // If we are in s_fun.state, we need to change our stateLoopFunction to the one just added.
    stateFunctionsArray[s_fun.state].state              = s_fun.state;
    stateFunctionsArray[s_fun.state].stateLoopFunction  = s_fun.stateLoopFunction;
    
    if (s_fun.state == current_state)
    {
        stateLoopFunction = stateFunctionsArray[s_fun.state].stateLoopFunction;
    }
}

bool FSM::checkAllStateFunctionsExist()
{
    for (uint8_t i = 0; i < NUM_STATES_NODE1; ++i)
    {
        // transitionFunction can be nothingHappens (since it is not always necessary)
        // but stateLoopFunction can not be nothingHappens, as the FSM will then never exit the state
        if (stateFunctionsArray[i].state != i                   ||
            stateFunctionsArray[i].stateLoopFunction  == NULL   ||
            stateFunctionsArray[i].stateLoopFunction  == nothingHappens)
            {
                return false;
            }
        }
        return true;
}


void nothingHappens(void) {}

void _fsm_extern_handle_event(uint8_t event)
{
    FSM & fsm = FSM::getInstance();
    fsm.handleEvent(event);
}

#endif // __AVR_ATmega162__
