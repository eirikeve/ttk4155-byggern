#pragma once
#include <avr/io.h>
#include <stdint.h>

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
         * Return value is the position change since the last call to Encoder::read()
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