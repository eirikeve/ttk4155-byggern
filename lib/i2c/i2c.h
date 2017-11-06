// #pragma once
// #include <avr/io.h>
// #include <stdint.h>

// // Status byte holding flags.
// union I2CStatusReg                       
// {
//     unsigned char all;
//     struct
//     {
//         unsigned char lastTransOK:1;      
//         unsigned char unusedBits:7;
//     };
// };

// class I2C
// {
//     public:


//         static I2C& getInstance()
//         {
//             static I2C instance;
//             return instance;
//         }

//         unsigned char transceiverBusy();
//         unsigned char getStateInfo();
//         void startTransceiverWithData(unsigned char *, unsigned char);
//         void startTransceiver();
//         unsigned char getDataFromTransceiver(unsigned char *, unsigned char);

//     private:

//         // Private due to singleton design pattern
//         I2C();

        
//         union I2CStatusReg I2CStatusReg;
        
//     public:
//         // Deleted due to singleton design pattern
//         I2C(I2C const&)    = delete;

//         // Deleted due to singleton design pattern
//         void operator=(I2C const&)  = delete;

// };