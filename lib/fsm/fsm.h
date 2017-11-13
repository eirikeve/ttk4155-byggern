// fsm.h
// 13/11/2017
#ifndef FSM_H
#define FSM_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __AVR_ATmega162__
#define STATE_TRANS_MATRIX_SIZE 9
enum state_t {
    STARTUP,
    IN_MENU,
    IN_GAME,
    IN_SNAKE,
    IN_DISPLAY,
    IN_NRF
};
enum event_t {
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
#define STATE_TRANS_MATRIX_SIZE 4
enum state_t {
    STARTUP,
    IDLE,
    GAME_RUNNING,
    GAME_OVER
};
enum event_t {
    EV_GOTO_IDLE,
    EV_START_GAME,
    EV_GAME_OVER,
    EV_EXIT_GAME
};
#endif //__AVR_ATmega162__


struct stateTrans_t {
    state_t state;
    event_t event;
    state_t next_state;

    void (*onEnterFunc)(void);
    void (*onStateFunc)(void);
};

class FSM
{
private:
    state_t  current_state;
    static stateTrans_t *stateTransMatrix;



public:
    static FSM& getInstance()
    {
        static FSM instance;
        return instance;
    }
    uint16_t read();
private:
    // Private due to singleton design pattern
    FSM();
    
public:
    // Deleted due to singleton design pattern
    FSM(FSM const&)    = delete;
    // Deleted due to singleton design pattern
    void operator=(FSM const&)  = delete;

    void initialize(void (*FnPointers[2 * STATE_TRANS_MATRIX_SIZE])(void));



};



#endif