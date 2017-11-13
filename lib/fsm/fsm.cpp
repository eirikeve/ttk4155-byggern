// fsm.cpp
// 13/11/2017

#include "fsm.h"

FSM::FSM()
{
    #ifdef __AVR_ATmega162__
    stateTrans_t stateTransMx[STATE_TRANS_MATRIX_SIZE] = {
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
    stateTransMx[STATE_TRANS_MATRIX_SIZE] = {
        //STATE         EVENT               NEXT_STATE      ON_ENTER_F  ON_STATE_F
        {STARTUP,       EV_GOTO_IDLE,       IDLE,           NULL,       NULL},
        {IDLE,          EV_START_GAME,      GAME_RUNNING,   NULL,       NULL},
        {GAME_RUNNING,  EV_GAME_OVER,       GAME_OVER,      NULL,       NULL},
        {GAME_OVER,     EV_EXIT_GAME,       IDLE,           NULL,       NULL}
    };
    #endif
    this->stateTransMatrix  = stateTransMx;
}

void FSM::initialize(void (*FnPointers[2 * STATE_TRANS_MATRIX_SIZE])(void))
{
    for (uint8_t i = 0; i < STATE_TRANS_MATRIX_SIZE; ++i)
    {       
        stateTransMatrix[i  ].onEnterFunc = FnPointers[2 * i];
        stateTransMatrix[i+1].onStateFunc = FnPointers[2 * i + 1];
    }
}