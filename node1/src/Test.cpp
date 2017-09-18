/*
 * Test.c
 *
 * Created: 04.09.2017 11:26:38
 *  Author: aasmune
 */ 

extern "C" {
	#include <avr/io.h>	
	#include "util/delay.h"
	#include <stdio.h>
	#include "comm.h"
}

 #include "../lib/joystick/joystick.h"
 #include <stdint.h>

 
 int main(void)
 {

	 set_bit(DDRB, 0);
	 clr_bit(DDRE, 0);
	 init_uart();

	Joystick joystick;
	uint8_t x;
	 
	 while(1)
	 {
		// printf("%d\n", *ext_ram);
		 set_bit(PORTB, 0);
		 _delay_ms(100);
		 clr_bit(PORTB, 0);
		 _delay_ms(100);
		joystick.readX(x);
		printf("%d\n", x);
	 }
 }