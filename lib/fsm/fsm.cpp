// fsm.cpp
// 13/11/2017

#include "fsm.h"

FSM::FSM()
{
    onStateFunc = &nothingHappens;
}


void FSM::handleEvent(event_t event)
{
    stateTrans_t const *transition = lookUpNextTransition(event);
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



