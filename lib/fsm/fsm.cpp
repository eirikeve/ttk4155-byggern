// fsm.cpp
// 13/11/2017

#include "fsm.h"

FSM::FSM()
{

    //stateTransMatrix  = stateTransMx;
    onStateFunc = &nothingHappens;
    
}

void FSM::initialize(function_pointer functions[2 * STATE_TRANS_MATRIX_SIZE])
{
    for (uint8_t i = 0; i < STATE_TRANS_MATRIX_SIZE; i++)
    {       
        stateTransMatrix[i].onEnterFunc = functions[2 * i];
        stateTransMatrix[i].onStateFunc = functions[2 * i + 1];
    }
    current_state = state_t::STARTUP;
    initialized = true;
}

stateTrans_t const* FSM::lookUpNextTransition(event_t event)
{
    for (int i = 0; i < STATE_TRANS_MATRIX_SIZE; i++)
    {
        if (stateTransMatrix[i].state == current_state &&
            stateTransMatrix[i].event == event)
            {
                return &stateTransMatrix[i];
            }
    }
    return NULL;
}

void FSM::handleEvent(event_t event)
{
    //printf("In handleEvent: Event %d\n", (int)event);
    stateTrans_t const *transition = lookUpNextTransition(event);
    //printf("In handleEvent: Transition %d\n", (int)transition);
    if (transition != NULL)
    {

        current_state = transition->next_state;
        onStateFunc   = transition->onStateFunc;

        transition->onEnterFunc();

    }
}


void FSM::runOnState()
{
    onStateFunc();
}


void FSM::printMx()
{
    printf("MX SZ %d\n", STATE_TRANS_MATRIX_SIZE);
    for (int i = 0; i < STATE_TRANS_MATRIX_SIZE; ++i)
    {
        printf("StateTransMx %d\n", (int)(stateTransMatrix[i].state));
    }

}
