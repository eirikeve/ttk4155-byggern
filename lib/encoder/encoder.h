#pragma once
#include <avr/io.h>
#include <stdint.h>

/**
 * Class for reading encoder values of the DC motor used in the project.
 * */
class Encoder
{
    public:


        static Encoder& getInstance()
        {
            static Encoder instance;
            return instance;
        }

        /**
         * Reads from the encoder.
         * Return value is the position change since last time.
         **/
        int16_t read();

        /**
         * Sets the current encoder value to 0
         **/
        void reset();

    private:

        // Private due to singleton design pattern
        Encoder();
        
    public:
        // Deleted due to singleton design pattern
        Encoder(Encoder const&)    = delete;

        // Deleted due to singleton design pattern
        void operator=(Encoder const&)  = delete;

};