/*
 * canmsg.h
 * Defines IDs and LENGTHs for all CAN messages used in the project
 * IDs have some space between them, in case other messages are added
 * All lengths are >= 1, as it is necessary in our CanMessage implementation
 */

#pragma once


#define CAN_ID_RESET 1
#define CAN_LENGTH_RESET 1 // Data does not matter

#define CAN_ID_ACK 5
#define CAN_LENGTH_ACK 1 // Data does not matter

#define CAN_ID_STOP_GAME 10
#define CAN_LENGTH_STOP_GAME 1 // Data does not matter

#define CAN_ID_START_GAME 20 
#define CAN_LENGTH_START_GAME 1 // Data does not matter

#define CAN_ID_SEND_USR_INPUT 30
#define CAN_LENGTH_SEND_USR_INPUT 3 // [(int8_t)joystick_x, (int8_t)slider_x, (bool)slider_button_pressed]

#define CAN_ID_SEND_SOUND 40
#define CAN_LENGTH_PLAY_SOUND 1 // [(uint8_t)sound_id]

#define CAN_ID_STOP_SOUND 50
#define CAN_LENGTH_STOP_SOUND 1 // Data does not matter

