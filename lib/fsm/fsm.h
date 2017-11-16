// fsm.h
// 13/11/2017

#pragma once

#include <stdint.h>
#include <stdlib.h>

//#ifdef __AVR_ATmega162__
#define     STATE_STARTUP1  0
#define     STATE_MENU      1
#define     STATE_GAME      2
#define     STATE_SNAKE     3
#define     STATE_DISPLAY   4
#define     STATE_NRF       5

#define EV_GOTO_MENU        0
#define EV_START_GAME       1
#define EV_GAME_OVER        2
#define EV_START_SNAKE      3
#define EV_SNAKE_OVER       4
#define EV_START_DISPLAY    5
#define EV_DISPLAY_END      6
#define EV_START_NRF        7
#define EV_NRF_END          8

//#elif __AVR_ATmega2560__
#define STATE_STARTUP2      20
#define STATE_IDLE          21
#define STATE_GAME_RUNNING  22
#define STATE_GAME_OVER     23

#define EV_GOTO_IDLE        20
#define EV_START_GAME       21
#define EV_GAME_OVER        22
#define EV_EXIT_GAME        23

//#endif //__AVR_ATmega162__


class FSM
{
private:
    int  current_state;
    void (*onStateFunc)(void);



public:
    static FSM& getInstance()
    {
        static FSM instance;
        return instance;
    }
    
    void transitionTo(uint8_t s);
private:
    // Private due to singleton design pattern
    FSM();
    void handleEventATmega162(uint8_t event);
    void handleEventATmega2560(uint8_t event);
    

public:
    // Deleted due to singleton design pattern
    FSM(FSM const&)    = delete;
    // Deleted due to singleton design pattern
    void operator=(FSM const&)  = delete;

    void handleEvent(uint8_t event);
    void  runOnState();
    inline int getCurrentState() {return this->current_state;}


};

