#pragma once

#include "../lib/can/can.h"
#include "../lib/can/canmsg.h"
#include "../lib/servo/servo.h"
#include "../lib/motor/motor.h"
#include "../lib/solenoid/solenoid.h"
#include "../lib/ir_detector/ir_detector.h"
#include "lib/utilities/sound.h"


void runGame(){
    CAN& can = CAN::getInstance();
    Servo& servo = Servo::getInstance();
    Motor& motor = Motor::getInstance();
    Solenoid & solenoid = Solenoid::getInstance();
    IR_detector & ir = IR_detector::getInstance();

    
    printf("\tRunning game\n");
    while (true) {
        _delay_ms(15);
        if (ir.blocked())
        {
            printf("\tIR Blocked. Sending STOP\n");
            // Game over
            CanMessage msg;
            msg.id = CAN_ID_STOP_GAME;
            msg.length = 1;
            msg.data[0] = 0b0;
            can.transmit(&msg);
            printf("\tChecking for ACK\n");
            if (!(checkForACK()))
            {
                printf("\tNo ACK. Retransmitting once\n");
                // Try to retransmit once if msg didn't go through
                can.transmit(&msg);
            }
            motor.run(0); // Stop motor and reset servo!
            servo.setAngle(0);
            return;
        }

        CanMessage recv = can.receive();

        if (recv.id == CAN_ID_SEND_USR_INPUT) 
        {
            printf("\tRecv usr input. JS %d, SL %d, BTN %d\n", (int8_t)recv.data[0],(int8_t)recv.data[1],recv.data[2]);
			// input to motor, from joystick
            motor.run((int8_t)recv.data[0]);

			// activate solenoid
            if (recv.data[2]) {
                printf("\tShooting\n");
                solenoid.shoot();
                servo.setAngle((int8_t)recv.data[1]);
            }
			
			// input to servo
            servo.setAngle((int8_t)recv.data[1]);
			
        }
        else if (recv.id == CAN_ID_RESET)
        {
            printf("\tRecv RESET in game, sending ACK\n");
            CanMessage msg;
            msg.id = CAN_ID_ACK;
            msg.length = CAN_LENGTH_ACK;
            msg.data[0] = 0b0;
            can.transmit(&msg);
            return;
        }

        
    }
}

