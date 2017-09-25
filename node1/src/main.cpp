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
#include <avr/pgmspace.h>
}

#include "../lib/joystick/joystick.h"
#include "lib/tempDisplay/temp.h"
#include <stdint.h>
#include "lib/fonts/fonts.h"

int main(void)
{

	set_bit(DDRB, 0);
	clr_bit(DDRE, 0);
	init_uart();

	// Joystick joystick(10);
	uint8_t x;
	uint8_t y;
	OLED o;

	o.clear();
	// const unsigned char PROGMEM a[8] = {0b00100000, 0b01110100, 0b01010100, 0b01010100, 0b00111100, 0b01111000, 0b01000000, 0b00000000};
	o.gotoPage(0);
	// for (int i = 0; i < 8; i++)
	// {
	// 	o.write(pgm_read_word(&font8[33][i]));
	// }
	o.writeString("->Play game       Highscores      Extra           Credits         End Game");

	while (1)
	{
		// printf("%d\n", *ext_ram);
		set_bit(PORTB, 0);
		_delay_ms(100);
		clr_bit(PORTB, 0);
		_delay_ms(100);
		// Direction dir = joystick.read(&x, &y);
		// printf("x: %d, y: %d, dir: %d\n", x, y, dir);
		// x = joystick.readY();
		// printf("%d\n", x);
	}
}