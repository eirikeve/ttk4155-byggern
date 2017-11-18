#pragma once

#include "../lib/can/can.h"
#include "../lib/can/canmsg.h"
#include "../lib/servo/servo.h"
#include "../lib/motor/motor.h"
#include "../lib/solenoid/solenoid.h"
#include "../lib/ir_detector/ir_detector.h"


void runGame(){
    CAN& can = CAN::getInstance();
    Servo& servo = Servo::getInstance();
    Motor& motor = Motor::getInstance();
    Solenoid & solenoid = Solenoid::getInstance();
    IR_detector & ir = IR_detector::getInstance();

    

    while (true) {
        if (ir.blocked())
        {
            // Game over
            CanMessage msg;
            msg.id = CAN_ID_STOP_GAME;
            msg.length = 1;
            msg.data[0] = 0b0;
            can.transmit(&msg);

            if (!(checkForACK()))
            {
                // Try to retransmit once if msg didn't go through
                can.transmit(&msg);
            }
            return;
        }
        CanMessage recv = can.receive();
        if (recv.id == CAN_ID_SEND_USR_INPUT) 
        {
			// input to motor, from joystick
            motor.run((int8_t)recv.data[0]);

			// activate solenoid
            if (recv.data[2]) {
                solenoid.shoot();
                servo.setAngle((int8_t)recv.data[1]);
            }
			
			// input to servo
            servo.setAngle((int8_t)recv.data[1]);
			
        }
        else if (recv.id == CAN_ID_RESET)
        {
            CanMessage msg;
            msg.id = CAN_ID_ACK;
            msg.length = CAN_LENGTH_ACK;
            msg.data[0] = 0b0;
            can.transmit(&msg);
            return;
        }
    }
}
