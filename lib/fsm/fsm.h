// fsm.h
// 13/11/2017

#pragma once

#include <stdint.h>
#include <stdlib.h>
#define NUM_STATES_NODE1 7


//#ifdef __AVR_ATmega162__
enum state_node1_t 
{
    STATE_STARTUP1,
    STATE_MENU,
    STATE_GAME,
    STATE_SNAKE,
    STATE_DISPLAY,
    STATE_GAME_NRF,
    STATE_ERROR
};


enum ev_node1_t 
{
    EV_RESET,
    EV_GOTO_MENU,
    EV_START_GAME,
    EV_GAME_OVER,
    EV_START_SNAKE,
    EV_SNAKE_OVER,
    EV_START_DISPLAY,
    EV_DISPLAY_END,
    EV_START_GAME_NRF,
    EV_GAME_NRF_END,
    EV_NO_CAN_ACK,
    EV_MISSING_STATE_FUNCTIONS
};
/*#define     STATE_STARTUP1  0
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
#define EV_NRF_END          8*/


//#elif __AVR_ATmega2560__
/*enum state_node2_t
{
    STATE_STARTUP2,
    STATE_IDLE,
    STATE_GAME_RUNNING,
    STATE_GAME_OVER
};


enum ev_node2_t
{
    EV_GOTO_IDLE,
    EV_START_GAME,
    EV_GAME_OVER,
    EV_EXIT_GAME
};
*/
/*
#define STATE_STARTUP2      20
#define STATE_IDLE          21
#define STATE_GAME_RUNNING  22
#define STATE_GAME_OVER     23

#define EV_GOTO_IDLE        20
#define EV_START_GAME       21
#define EV_GAME_OVER        22
#define EV_EXIT_GAME        23
*/

//#endif //__AVR_ATmega162__


typedef void (*callback_function)(void);

/*
 * stateFunctions is a struct which links a state and two callback functions.
 * This indicates that upon entering that state, transitionFunction is called.
 * After calling transitionFunction, onStateFunction will loop indefinitely until
 * the next state change.
 */
struct stateFunctions{
    // A state from state_node1_t
    uint16_t state;
    // A void *function(void) which will be called repeatedly after the
    // transition function was called.
    
    // A void *function(void) which will be called upon transitioning to state
    callback_function stateLoopFunction;

    
    stateFunctions() {state = NULL; stateLoopFunction = NULL;}
    stateFunctions(uint8_t s,  callback_function stateLoopFun)
    {
        state = s;
        stateLoopFunction = stateLoopFun;
    }

};

/*
 * FSM is a class which implements a Moore state machine
 * It is a singleton class, so only one instance can exist
 * The states of the FSM are defined in the state_node1_t enum
 * Before using, stateFunctions must be loaded into the FSM
 */
class FSM
{
private:
    uint8_t  current_state;
    callback_function stateLoopFunction;
    stateFunctions stateFunctionsArray[NUM_STATES_NODE1];

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
    void init();

public:
    // Deleted due to singleton design pattern
    FSM(FSM const&)    = delete;
    // Deleted due to singleton design pattern
    void operator=(FSM const&)  = delete;
    void reset();
    void handleEvent(uint8_t event);
    void runStateLoop();
    void addStateFunctions(stateFunctions s_fun);
    bool checkAllStateFunctionsExist();

    inline int getCurrentState() {return this->current_state;}

};

void nothingHappens(void);
void _fsm_extern_handle_event(uint8_t event);