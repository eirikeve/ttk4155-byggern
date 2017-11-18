// fsm.cpp
// 13/11/2017

#include "fsm.h"
#ifdef __AVR_ATmega162__



FSM::FSM()
{
    init();
}

void FSM::init()
{
    stateLoopFunction = NULL;
    for (uint8_t state = (uint8_t)STATE_STARTUP1; state < (uint8_t)STATE_STARTUP1 + NUM_STATES_NODE1; ++state)
    {
        stateFunctionsArray[state] = stateFunctions(state, nothingHappens, nothingHappens);
    }
}

void FSM::reset()
{
    init();
}

void FSM::transitionTo(uint8_t s)
{
    // Change state, set onState function, perform transition function
    current_state = s;
    stateLoopFunction = stateFunctionsArray[s].stateLoopFunction;
    stateFunctionsArray[s].transitionFunction();
    return;
}

void FSM::handleEvent(uint8_t event)
{
    // Don't exit the error state except if resetting.
    if (current_state == STATE_ERROR) return;

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
            case EV_START_GAME_NRF:
            {
                if (current_state == STATE_MENU)
                {
                    transitionTo(STATE_GAME_NRF);
                }
                break;
            }
            case EV_GAME_NRF_END:
            {
                if (current_state == STATE_GAME_NRF)
                {
                    transitionTo(STATE_MENU);
                }
                break;
            }
            case EV_NO_CAN_ACK:
                {
                    if (current_state != STATE_ERROR)
                    {
                        transitionTo(STATE_ERROR);
                    }
                    break;
                }
            case EV_MISSING_STATE_FUNCTIONS:
            {
                if (current_state != STATE_ERROR)
                {
                    transitionTo(STATE_ERROR);
                }
                break;
            }
            default:
                transitionTo(STATE_ERROR);
                break;
    }

}

void FSM::runStateLoop()
{
    if (stateLoopFunction != nothingHappens   && 
        stateLoopFunction != NULL             &&
        current_state != (uint8_t)STATE_ERROR)
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
    stateFunctionsArray[s_fun.state].transitionFunction = s_fun.transitionFunction;
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
            stateFunctionsArray[i].transitionFunction == NULL   ||
            stateFunctionsArray[i].stateLoopFunction  == NULL   ||
            stateFunctionsArray[i].stateLoopFunction  == nothingHappens)
            {
                return false;
            }
        }
        return true;
}


void nothingHappens(void) {}
#endif // __AVR_ATmega162__
