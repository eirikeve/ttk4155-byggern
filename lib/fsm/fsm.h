// fsm.h
// 13/11/2017

#pragma once

#include <stdint.h>
#include <stdlib.h>

#ifdef __AVR_ATmega162__
enum state_t {
    STARTUP = 0,
    IN_MENU,
    IN_GAME,
    IN_SNAKE,
    IN_DISPLAY,
    IN_NRF
};
enum event_t {
    EV_DUMMY = 0,
    EV_GOTO_MENU,
    EV_START_GAME,
    EV_GAME_OVER,
    EV_START_SNAKE,
    EV_SNAKE_OVER,
    EV_START_DISPLAY,
    EV_DISPLAY_END,
    EV_START_NRF,
    EV_NRF_END
};
#elif __AVR_ATmega2560__
enum state_t {
    STARTUP,
    IDLE,
    GAME_RUNNING,
    GAME_OVER
};
enum event_t {
    EV_DUMMY,
    EV_GOTO_IDLE,
    EV_START_GAME,
    EV_GAME_OVER,
    EV_EXIT_GAME
};
#endif //__AVR_ATmega162__


class FSM
{
private:
    state_t  current_state;
    stateTrans_t currentTransition;
    void (*onStateFunc)(void);



public:
    static FSM& getInstance()
    {
        static FSM instance;
        return instance;
    }
    static void nothingHappens(void) {}
private:
    // Private due to singleton design pattern
    FSM();
    

public:
    // Deleted due to singleton design pattern
    FSM(FSM const&)    = delete;
    // Deleted due to singleton design pattern
    void operator=(FSM const&)  = delete;

    void handleEvent(event_t event);
    void  runOnState();
    inline state_t getCurrentState() {return this->current_state;}


};

