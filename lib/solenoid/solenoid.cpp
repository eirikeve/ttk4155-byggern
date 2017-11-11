#include <stdio.h>
#include "solenoid.h"

Solenoid::Solenoid() {
	// set PB4 output
    set_bit(DDRB, DDB4);
	
	// sit high to deactivate solenoid
	set_bit(PINB, DDB4);
}

void Solenoid::shoot(){
	//Set low to activate solenoid
	clr_bit(PINB, DDB4);
	_delay_ms(200);
	// sit high to deactivate solenoid
	set_bit(PINB, DDB4);
}

void Solenoid::test(){
	while(1){
		this->shoot();
		delay(500);
	}
}