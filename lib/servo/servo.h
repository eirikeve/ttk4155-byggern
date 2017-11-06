#pragma once
#include <stdint.h>



class Servo
{
    public:
        static Servo& getInstance()
        {
            static Servo instance;
            return instance;
        }
        /**
         * Initialize the servo with a max angle of +- maxAngle
         * @param maxAngle max angle for servo. Should be less or equal to 90 deg
         * */
        
        void initialize(uint16_t maxAngle);

        /** Sets the desired angle for the Servo in degrees.
         * Must be less or equal to maxAngle.
         * */
        void setAngle(int16_t angle);

        /** Set the desired angle for the servo in percentage 
         * to maxAngle
         * @param percentage percentage of max angle, should be between +- 100
         * */
        void setAnglePercentage(int8_t percentage);

    private:


        // Private due to singleton design pattern
        Servo();

        // Set duty cycle in ms
        void setDutyCycle(float ms);

        // Max angle of servo
         uint8_t maxAngle;
        
    public:

        // Deleted due to singleton design pattern
        Servo(Servo const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(Servo const&)  = delete;

};