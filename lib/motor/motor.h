#pragma once
#include <stdint.h>

#include "lib/dac/dac.h"
#include "lib/timer/timer.h"
#include "lib/encoder/encoder.h"
#include "lib/pid/pid.h"


class Motor
{
    public:


        static Motor& getInstance()
        {
            static Motor instance;
            return instance;
        }

        /**
         * Initializes the instance with the specified objects.
         * @param dac: DAC object pointer
         * @param timer: Timer object pointer
         * @param encoder: Encoder object pointer
         * @param Kp: Kp value for PID controller
         * @param Ki: Ti value for the PID controller
         * @param Kd: Td value for the PID controller
         * @param T: Sampling time
         **/
        void initialize(DAC* dac, Timer* timer, Encoder* encoder, float Kp, float Ki, float Kd, uint8_t T);

        /**
         * Sets the PID parameters of the motor
         * @param Kp: PID Kp
         * @param Ti: PID Ti
         * @param Td: PID Td
         **/
        void setPIDparameters(float Kp, float Ti, float Td);

        /**
         * Set the reference speed of the PID controller
         * @param speed: [-127, 127], dir depends on sign, while spd depends on abs value.
         **/
        void run(int8_t speed);

        

    private:

        // Private due to singleton design pattern
        Motor() {};

        // Encoder
        Encoder* encoder;

        // DAC
        DAC* dac;

        // Timer
        Timer* timer;

        // Time step for controller
        uint8_t T;

        // Reference point
        int16_t ref;

        // Pid
        PID pid;

        void setSpeed(uint8_t speed);
        
        /**
         * > 0: right
         * < 0: left
         * */
        void goRight();

        void goLeft();
        
    public:
        // Deleted due to singleton design pattern
        Motor(Motor const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(Motor const&)  = delete;

        friend void controller();


};