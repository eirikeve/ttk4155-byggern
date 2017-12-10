#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../pins/pins.h"

namespace {
    #ifdef __AVR_ATmega162__
        #define TIMER0_vect TIMER1_COMPA_vect
        #define TIMER1_vect TIMER3_COMPA_vect
    
    #elif __AVR_ATmega2560__
        #define TIMER0_vect TIMER3_COMPA_vect
        #define TIMER1_vect TIMER4_COMPA_vect
    #endif
}
ISR(TIMER0_vect);
ISR(TIMER1_vect);


/**
 * A class for using 16-bits timers on atmega162 and 2560. 
 * Using a multiton design pattern.
 * 
 * ATmega162:
 *  Id 0: Timer 1
 *  Id 1: Timer 3
 *
 * ATmega2560:
 *  Id 0: Timer 3
 *  Id 1: Timer 4
 * */
class Timer
{
    public:
        static Timer& getInstance(uint8_t id) {
            if(id == 0){
                static Timer instance(0);
                return instance;
            }
            else if (id == 1){
                static Timer instance(1);
                return instance;
            }
            else {
            
                assert(false);
            }
        }
        
        /**
         * Initialize the timer to trigger every given ms.
         * @param ms number of milli seconds between each trigger.
         *  ATmega162: max(ms) < 13650 ms.
         *  ATmega2560: max(ms) < 4190 ms.
         * @param callbackFunction function to be called during trigger.
         * */
        void initialize(uint16_t ms, void (*callbackFunction)(void), PIN* pin);

        /**
         * Start timer.
         * */
        void start();

        /**
         * Stop timer.
         * */
        void stop();

        /**
         * Set new desired interrupt period for timer.
         * @param ms new desired value between each interrupt
         * */
        void setInterruptPeriod(uint16_t ms);


    private:


        // Private due to multiton design pattern
        Timer(uint8_t id);

        // Id of timer
        uint8_t id;
        uint16_t period;

        // // Maximum number of instances
        // const static int MAXIMUM_NUMBER_OF_INSTANCES = 2;

        // // All instances of the timer
        // static Timer instances[MAXIMUM_NUMBER_OF_INSTANCES];

        // Function to be called during interrupt
        void (*callbackFunction)(void);

        

        
    public:

        // Interrupt handler for timer 0
        friend void TIMER0_vect();

        // Interrupt handler for timer 1
        friend void TIMER1_vect();

        // Deleted due to multiton design pattern
        Timer(Timer const&)    = delete;

        // Deleted due to multiton design pattern
        Timer& operator=(Timer const&) = delete;


};