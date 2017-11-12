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

        int16_t read();

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