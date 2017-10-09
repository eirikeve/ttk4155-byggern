#pragma once
#include "SPI.h"
#include "MCP2515.h"

struct can_message{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
};

int main(void){
	can_init();
	struct can_message message;
	message.id = 3;
	message.length = 1;
	message.data[0] = (uint8_t)'U';
	can_message_send(&message);
}

void can_message_send(struct can_message* msg){
	//...
	uint8_t i;
	for (i = 0;i < msg->length; i++){
		
	}
	//...
}