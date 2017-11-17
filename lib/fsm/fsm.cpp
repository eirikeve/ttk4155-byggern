// fsm.cpp
// 13/11/2017

#include "fsm.h"
#ifdef __AVR_ATmega162__

void nothingHappens(void) {}

FSM::FSM()
{
    init();
}

void FSM::init()
{
    stateLoopFunction = NULL;
    for (uint8_t state = (uint8_t)STATE_STARTUP1; state < (uint8_t)STATE_STARTUP1 + NUM_STATES_NODE1; ++state)
    {
        stateFunctionsArray[state] = stateFunctions(state, NULL, NULL);
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

void FSM::runStateLoop()
{
    if (stateLoopFunction != nothingHappens   && 
        stateLoopFunction != NULL             &&
        current_state != (uint8_t)STATE_ERROR)
    {
        uint8_t state = current_state;
        while (current_state == state)
        {
            stateLoopFunction();
        }
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
    stateFunctionsArray[s_fun.state].state = s_fun.state;
    stateFunctionsArray[s_fun.state].transitionFunction = s_fun.transitionFunction;
    stateFunctionsArray[s_fun.state].stateLoopFunction    = s_fun.stateLoopFunction;
}


#endif // __AVR_ATmega162__
