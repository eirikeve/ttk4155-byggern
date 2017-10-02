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
#include <stdlib.h>
}

#include "../lib/joystick/joystick.h"
#include "lib/display/screen.h"
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

	int std_wait_time = 100;
	x  = 0;
	y  = 0;
	Screen bar;
	Screen o;
	bar.addSubScreen(&o, 7, LOWER);
	bar.addBorderLines();
	o.goTo(0, 0);
	o.clear();
	Screen sub;
	o.writeString("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	_delay_ms(std_wait_time);
	o.addSubScreen(&sub, 4, Orientation::LOWER);
	_delay_ms(std_wait_time);
	o.writeString("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	_delay_ms(std_wait_time);
	sub.writeString("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy");
	Screen subsub;
	_delay_ms(std_wait_time);
	sub.addSubScreen(&subsub, 64, Orientation::RIGHT);
	sub.writeString("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy");
	_delay_ms(std_wait_time);
	subsub.writeString("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
	_delay_ms(std_wait_time);
	subsub.clear();
	subsub.writeString("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
	
	char buffer[5];
	o.clear();
	o.goTo(0,1);
	o.writeString("SubSub: page0:");
    itoa(subsub.page0, buffer, 10);
	o.writeString(buffer);
	o.writeString(" page1:");
    itoa(subsub.page1, buffer, 10);
	o.writeString(buffer);
	o.writeString(" col0:");
    itoa(subsub.col0, buffer, 10);
	o.writeString(buffer);
	o.writeString(" col1:");
    itoa(subsub.col1, buffer, 10);
	o.writeString(buffer);
	o.writeString(" pgsz:");
    itoa(subsub.pagesize, buffer, 10);
	o.writeString(buffer);
	o.writeString(" colsz:");
    itoa(subsub.colsize, buffer, 10);
	o.writeString(buffer);

	_delay_ms(std_wait_time);
	sub.clear();
	sub.goTo(0,1);
	sub.writeString("1\nW\nPer\nLine");

	_delay_ms(std_wait_time);


	o.addBorderLines();
	_delay_ms(std_wait_time);
	sub.addBorderLines();
	_delay_ms(std_wait_time);
	subsub.addBorderLines();
	_delay_ms(std_wait_time);
	o.removeBorderLines();
	sub.removeBorderLines();
	subsub.removeBorderLines();
	sub.clear();
	sub.writeString("Removed Border Lines");

	char letter = '-';
	char loading_bar[10] {' '};
	int counter = 0;
	char val[3];
	
	while (true)
	{
		bar.clear();
		counter = (counter + 1) % 11;
		switch (letter)
		{
			case '-':
				letter = '\\';
				break;
			case '\\':
				letter = '|';
				break;
			case '|':
				letter = '/';
				break;
			case '/':
				letter = '-';
				break;
		}
		for (int i = 0; i < 10; ++i)
		{
			if (i < counter)
			{
				loading_bar[i] = '=';
			}
			else
			{
				loading_bar[i] = ' ';
			}
		}

		itoa(counter*10, val, 10);

		bar.goTo(0,1);
		bar.writeChar(letter);
		bar.writeChar(' ');
		bar.writeString(loading_bar);
		bar.writeChar(' ');
		bar.writeString(val);
		bar.writeChar('%');
		_delay_ms(300);
	}

	// sub.clear();
	// _delay_ms(1000);
	// o.writeString("123456789123456 abcdefghijklmnopqrstuvwxyz ja123456789123456 abcdefghijklmnopqrstuvwxyz ja123456789123456 abcdefghijklmnopqrstuvwxyz ja123456789123456 abcdefghijklmnopqrstuvwxyz ja123456789123456 abcdefghijklmnopqrstuvwxyz ja");
	// o.goTo(0, 9);
	// o.writeChar('B');
	// const unsigned char PROGMEM a[8] = {0b00100000, 0b01110100, 0b01010100, 0b01010100, 0b00111100, 0b01111000, 0b01000000, 0b00000000};
	// o.gotoPage(0);
	// for (int i = 0; i < 8; i++)
	// {
	// 	o.write(pgm_read_word(&font8[33][i]));
	// }
	// o.writeString("->Play game       Highscores      Extra           Credits         End Game");

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