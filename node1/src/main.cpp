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
#include <avr/pgmspace.h>
#include <stdlib.h>
#include "comm.h"
}

#include "../lib/joystick/joystick.h"
#include "lib/display/screen.h"
#include <stdint.h>
#include "lib/fonts/fonts.h"

void init(Screen main)
{
	const unsigned char appleLogo[8] =
	{0b00000000, 0b01111000, 0b11111100, 0b11111110, 0b11001101, 0b01001000,0b00000000,0b00000000};
	main.clear();
	main.goTo(4,61);
	for (int i= 0; i < 8; ++i)
	{
		main.write(appleLogo[i]);
	}
	_delay_ms(200);
	char letter = '-';
	for (int i = 0; i < 26; ++i)
	{
		if (i == 1)
		{
			set_bit(DDRB, 0);
			clr_bit(DDRE, 0);
		}
		if (i == 10)
		{
			init_uart();
		}
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
		main.goTo(6, 29);
		main.writeString("Initializing ");
		main.writeChar(letter);
		main.goTo(7, 0);
		for (int j = 0; j <= i; ++j)
		{
			main.writeChar('-');
		}
		
		_delay_ms(100);
		
	}
	main.goTo(6, 29);
	main.writeString("Initializing *");
	_delay_ms(250);

	main.goTo(7, 0);
	for (int j = 0; j <= 26; ++j)
	{
		main.writeChar('=');
	}

	_delay_ms(250);

	main.goTo(7, 0);
	for (int j = 0; j <= 26; ++j)
	{
		main.writeChar('-');
	}

	_delay_ms(150);

	main.clear();

	
}

int main(void)
{

	

	// Joystick joystick(10);
	uint8_t x;
	uint8_t y;

	int std_wait_time = 5000;
	put_uart_char('B');
	printf("Test\n");
	put_uart_char('A');
	x  = 0;
	y  = 0;
	Screen bar;

	init(bar);

	printf("\n\nAdding bar:\n");
	printf("\nBar:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
	bar.page0, bar.page1, bar.col0, bar.col1, bar.pagesize, bar.colsize, bar.superScreen != NULL, bar.subScreen != NULL);
	
	Screen o;
	bar.addSubScreen(&o, 7, LOWER);
	printf("\n\nAdding o:\n");
	printf("\nBar:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
	bar.page0, bar.page1, bar.col0, bar.col1, bar.pagesize, bar.colsize, bar.superScreen != NULL, bar.subScreen != NULL);
	printf("\no:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
	o.page0, o.page1, o.col0, o.col1, o.pagesize, o.colsize, o.superScreen != NULL, o.subScreen != NULL);
	// bar.addBorderLines();
	// o.goTo(0, 0);
	// o.clear();
	Screen sub;
	//o.writeString("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	// _delay_ms(std_wait_time);
	o.addSubScreen(&sub, 4, Orientation::LOWER);
	printf("\n\nAdding sub:\n");
	printf("\nBar:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
	bar.page0, bar.page1, bar.col0, bar.col1, bar.pagesize, bar.colsize, bar.superScreen != NULL, bar.subScreen != NULL);
	printf("\no:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
	o.page0, o.page1, o.col0, o.col1, o.pagesize, o.colsize, o.superScreen != NULL, o.subScreen != NULL);
	printf("\nSub:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
	sub.page0, sub.page1, sub.col0, sub.col1, sub.pagesize, sub.colsize, sub.superScreen != NULL, sub.subScreen != NULL);
	// _delay_ms(std_wait_time);
	// o.writeString("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	// _delay_ms(std_wait_time);
	// sub.writeString("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy");
	Screen subsub;
	// _delay_ms(std_wait_time);
	sub.addSubScreen(&subsub, 64, Orientation::RIGHT);
	printf("\n\nAdding subsub:\n");
	// sub.writeString("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy");
	// _delay_ms(std_wait_time);
	// subsub.writeString("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
	// _delay_ms(std_wait_time);
	// subsub.clear();
	// subsub.writeString("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
	printf("\nBar:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
	bar.page0, bar.page1, bar.col0, bar.col1, bar.pagesize, bar.colsize, bar.superScreen != NULL, bar.subScreen != NULL);
	printf("\no:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
	o.page0, o.page1, o.col0, o.col1, o.pagesize, o.colsize, o.superScreen != NULL, o.subScreen != NULL);
	printf("\nSub:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
	sub.page0, sub.page1, sub.col0, sub.col1, sub.pagesize, sub.colsize, sub.superScreen != NULL, sub.subScreen != NULL);
	printf("\nSubsub:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
	subsub.page0, subsub.page1, subsub.col0, subsub.col1, subsub.pagesize, subsub.colsize, subsub.superScreen != NULL, subsub.subScreen != NULL);
	

	// char buffer[5];
	// o.clear();
	// o.goTo(0,1);
	// o.writeString("SubSub: page0:");
    // itoa(subsub.page0, buffer, 10);
	// o.writeString(buffer);
	// o.writeString(" page1:");
    // itoa(subsub.page1, buffer, 10);
	// o.writeString(buffer);
	// o.writeString(" col0:");
    // itoa(subsub.col0, buffer, 10);
	// o.writeString(buffer);
	// o.writeString(" col1:");
    // itoa(subsub.col1, buffer, 10);
	// o.writeString(buffer);
	// o.writeString(" pgsz:");
    // itoa(subsub.pagesize, buffer, 10);
	// o.writeString(buffer);
	// o.writeString(" colsz:");
    // itoa(subsub.colsize, buffer, 10);
	// o.writeString(buffer);

	// _delay_ms(std_wait_time);
	// sub.clear();
	// sub.goTo(0,1);
	// sub.writeString("1\nW\nPer\nLine");

	// _delay_ms(std_wait_time);

	bar.addBorderLines();

	o.addBorderLines();

	sub.addBorderLines();

	subsub.addBorderLines();



	char letter = '-';
	char loading_bar[11] {' '};
	int counter = 0;
	char val[4];
	bar.clear();
	o.clear();
	sub.clear();
	subsub.clear();

	bool do_anim = false;
	bool do_joystick = true;

	while (do_anim)
	{
		
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
		loading_bar[10] = '\0';

		itoa(counter*10, val, 10);

		bar.goTo(0,1);
		bar.writeChar(letter);
		bar.writeChar(' ');
		bar.writeString(loading_bar);
		bar.writeChar(' ');
		bar.writeString(val);
		bar.writeChar('%');
		bar.writeChar('\n');
		_delay_ms(300);
		
		for (int i = 0; i < 5; ++i)
		{
			o.writeString("abacabadabacabaeabacabadabacaba");
			sub.writeString("The red fox was beautiful. ");
			subsub.writeString("Ipsum lorem fucking shit! ");
		}
		
	}

	// Joystick j(10);

	// uint8_t x;
	// uint8_t y;

	// while (do_joystick)
	// {
	// 	c = r
	// }

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