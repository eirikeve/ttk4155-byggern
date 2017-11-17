// fsm.cpp
// 13/11/2017

#include "fsm.h"
#ifdef __AVR_ATmega162__

void nothingHappens(void) {}

FSM::FSM()
{
<<<<<<< HEAD
    #ifdef __AVR_ATmega162__
    //stateTrans_t stateTransMx[STATE_TRANS_MATRIX_SIZE] 
    stateTransMatrix  = {
        //STATE     EVENT               NEXT_STATE      ON_ENTER_F  ON_STATE_F
        {STARTUP,   EV_GOTO_MENU,       IN_MENU,        NULL,       NULL},
        {IN_MENU,   EV_START_GAME,      IN_GAME,        NULL,       NULL},
        {IN_MENU,   EV_START_SNAKE,     IN_SNAKE,       NULL,       NULL},
        {IN_MENU,   EV_START_DISPLAY,   IN_DISPLAY,     NULL,       NULL},
        {IN_MENU,   EV_START_NRF,       IN_NRF,         NULL,       NULL},
        {IN_GAME,   EV_GOTO_MENU,       IN_MENU,        NULL,       NULL},
        {IN_SNAKE,  EV_GOTO_MENU,       IN_MENU,        NULL,       NULL},
        {IN_DISPLAY,EV_GOTO_MENU,       IN_MENU,        NULL,       NULL},
        {IN_NRF,    EV_GOTO_MENU,       IN_MENU,        NULL,       NULL}
    };
    
    #elif __AVR_ATmega2560__
    stateTrans_t stateTransMx[STATE_TRANS_MATRIX_SIZE] = {
        //STATE         EVENT               NEXT_STATE      ON_ENTER_F  ON_STATE_F
        {STARTUP,       EV_GOTO_IDLE,       IDLE,           NULL,       NULL},
        {IDLE,          EV_START_GAME,      GAME_RUNNING,   NULL,       NULL},
        {GAME_RUNNING,  EV_GAME_OVER,       GAME_OVER,      NULL,       NULL},
        {GAME_OVER,     EV_EXIT_GAME,       IDLE,           NULL,       NULL}
    };
    #endif
    //stateTransMatrix  = stateTransMx;
    onStateFunc = &nothingHappens;
    
}

void FSM::initialize(function_pointer functions[2 * STATE_TRANS_MATRIX_SIZE])
{
    for (uint8_t i = 0; i < STATE_TRANS_MATRIX_SIZE; i++)
    {       
        stateTransMatrix[i].onEnterFunc = functions[2 * i];
        stateTransMatrix[i].onStateFunc = functions[2 * i + 1];
=======
    init();
}

void FSM::init()
{
    stateLoopFunction = NULL;
    for (uint8_t state = (uint8_t)STATE_STARTUP1; state < (uint8_t)STATE_STARTUP1 + NUM_STATES_NODE1; ++state)
    {
        stateFunctionsArray[state] = stateFunctions(state, NULL, NULL);
>>>>>>> feature/fsm
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
<<<<<<< HEAD
    for (int i = 0; i < STATE_TRANS_MATRIX_SIZE; i++)
=======
    // Don't exit the error state except if resetting.
    if (current_state == STATE_ERROR) return;

    switch(event)
>>>>>>> feature/fsm
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
<<<<<<< HEAD
    //printf("In handleEvent: Event %d\n", (int)event);
    stateTrans_t const *transition = lookUpNextTransition(event);
    //printf("In handleEvent: Transition %d\n", (int)transition);
    if (transition != NULL)
    {

        current_state = transition->next_state;
        onStateFunc   = transition->onStateFunc;

        transition->onEnterFunc();

=======
    if (stateLoopFunction != nothingHappens   && 
        stateLoopFunction != NULL             &&
        current_state != (uint8_t)STATE_ERROR)
    {
        uint8_t state = current_state;
        while (current_state == state)
        {
            stateLoopFunction();
        }
>>>>>>> feature/fsm
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


<<<<<<< HEAD
void FSM::printMx()
{
    printf("MX SZ %d\n", STATE_TRANS_MATRIX_SIZE);
    for (int i = 0; i < STATE_TRANS_MATRIX_SIZE; ++i)
    {
        printf("StateTransMx %d\n", (int)(stateTransMatrix[i].state));
    }

}
=======
#endif // __AVR_ATmega162__
>>>>>>> feature/fsm
