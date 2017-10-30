#pragma once
extern "C" {
	#include <stdint.h>
	#include <stdlib.h>
}

struct can_message{
	uint8_t id = NULL;
	uint8_t length;
	uint8_t data[8];
};



void can_init();
uint8_t getB0();
void clrB0();

void can_message_send(can_message* msg);
void can_error();
void can_transmit_complete();
can_message can_data_receive();
void can_int_vect();