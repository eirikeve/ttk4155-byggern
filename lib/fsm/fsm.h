#pragma once

#include <stdint.h>
#include <stdlib.h>
#define NUM_STATES_NODE1 6

enum state_node1_t 
{
    STATE_STARTUP1,
    STATE_MENU,
    STATE_GAME,
    STATE_SNAKE,
    STATE_TUNE_PID,
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
    EV_START_TUNE_PID,
    EV_STOP_TUNE_PID,
    EV_NO_CAN_ACK,
    EV_MISSING_STATE_FUNCTIONS
};


// callback_function is a void *function_pointer(void) type
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

    /**
     * Sets the current state to startup, and clears the stateLoopFunction and
     * stateFunctionsArray.
     **/
    void reset();

    /**
     * Depending on state and event, might transition to a new state.
     * In that case, it changes stateLoopFunctions to the function in stateFunctionsArray
     * matching the new state.
     * @param event: Event from the enum ev_node1_t
     **/
    void handleEvent(uint8_t event);

    /**
     * Runs the stateLoopFunction. Might trigger transition to ERROR if the function
     * is NULL/not initialized
     **/
    void runStateLoop();

    /**
     * Adds a stateLoopFunction to the array of stateLoopFunctions
     * @param s_fun a stateFunctions struct with a state and a callback_function variable
     **/
    void addStateFunctions(stateFunctions s_fun);

    /**
     * Returns true if all stateFuntions are not NULL and not nothingHappens
     **/
    bool checkAllStateFunctionsExist();

    // Returns state, cased to int
    inline int getCurrentState() {return this->current_state;}

};

// Does absolutely nothing
void nothingHappens(void);

// Extern event handler, gets an instance of the fsm and calls fsm.handleEvent(event)
void _fsm_extern_handle_event(uint8_t event);