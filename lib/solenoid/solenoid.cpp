#include <stdio.h>
#include "solenoid.h"

Solenoid::Solenoid() {
	// set PB4 output
    set_bit(DDRB, DDB4);
	
	// sit high to deactivate solenoid
	set_bit(PINB, DDB4);
}

void Solenoid::Shoot(){
	//Set low to activate solenoid
	clr_bit(PINB, DDB4);
	_delay_ms(0.02);
	// sit high to deactivate solenoid
	set_bit(PINB, DDB4);
}