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
#include "lib/menu/testMenu.h"

int main(void)
{

	set_bit(DDRB, 0);
	clr_bit(DDRE, 0);
	init_uart();

	// Joystick joystick(10);
	uint8_t x;
	uint8_t y;
	// Screen o;
	// o.goTo(0, 0);
	// o.clear(0x00);

	printf("\n\n\n\n\n\n\nStarting\n");

	TestMenu main("main");
	TestMenu nr1("u1");
	TestMenu nr2("u2");
	TestMenu nr3("u3");
	TestMenu nr4("u4");

	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr1.getName(), nr1.getSibling(0)->getName(), nr1.getParent()->getName(), nr1.getParent()->getTotNrOfChildren());
	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr2.getName(), nr2.getSibling(0)->getName(), nr2.getParent()->getName(), nr2.getParent()->getTotNrOfChildren());
	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr3.getName(), nr3.getSibling(0)->getName(), nr3.getParent()->getName(), nr3.getParent()->getTotNrOfChildren());

	main.addChild(nr1);
	// printf("c: %d\n", main.getTotNrOfChildren());
	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr1.getName(), nr1.getSibling(0)->getName(), nr1.getParent()->getName(), nr1.getParent()->getTotNrOfChildren());
	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr2.getName(), nr2.getSibling(0)->getName(), nr2.getParent()->getName(), nr2.getParent()->getTotNrOfChildren());
	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr3.getName(), nr3.getSibling(0)->getName(), nr3.getParent()->getName(), nr3.getParent()->getTotNrOfChildren());

	main.addChild(nr2);
	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr1.getName(), nr1.getSibling(0)->getName(), nr1.getParent()->getName(), nr1.getParent()->getTotNrOfChildren());
	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr2.getName(), nr2.getSibling(0)->getName(), nr2.getParent()->getName(), nr2.getParent()->getTotNrOfChildren());
	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr3.getName(), nr3.getSibling(0)->getName(), nr3.getParent()->getName(), nr3.getParent()->getTotNrOfChildren());
	main.addChild(nr3);
	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr1.getName(), nr1.getSibling(0)->getName(), nr1.getParent()->getName(), nr1.getParent()->getTotNrOfChildren());
	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr2.getName(), nr2.getSibling(0)->getName(), nr2.getParent()->getName(), nr2.getParent()->getTotNrOfChildren());
	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr3.getName(), nr3.getSibling(0)->getName(), nr3.getParent()->getName(), nr3.getParent()->getTotNrOfChildren());
	main.addChild(nr4);
	// printf("siblings main: %d\n", main.getTotNrOfSiblings());
	char **res = nr2.getSiblingNames();
	for (int i = 0; i < main.getTotNrOfChildren() - 1; i++)
	{
		printf("%s\n", res[i]);
	}
	char **res1 = main.getChildrenNames();
	for (int i = 0; i < main.getTotNrOfChildren(); i++) {
		printf("%s\n", res1[i]);
	}
	// printf("%s\n", main.getChild(1)->getName());

	// SubMenu main("main", 3);
	// // printf("Adding 1\n");
	// SubMenu sub1 = main.addSubMenu("sub1", 1);
	// // printf("After sub1 %s\n", sub1.getName());
	// // printf("Adding 2\n");
	// SubMenu sub2 = main.addSubMenu("sub2", 0);
	// // printf("Adding 3\n");
	// SubMenu sub3 = main.addSubMenu("sub3", 0);
	// SubMenu sub4 = sub1.addSubMenu("sub4", 0);
	// // Menu menu = Menu(&main);
	// // printf("Hei");

	// char **p = main.getChildrenNames();

	// for (int i = 0; i < 3; i++)
	// {
	// 	printf("%s\n", p[i]);
	// 	// o.writeString(p[i]);
	// 	// o.goTo(i, 0);
	// }
	// p = sub1.getChildrenNames();
	// for (int i = 0; i < 1; i++)
	// {
	// 	printf("%s\n", p[i]);
	// 	// o.writeString(p[i]);
	// 	// o.goTo(i, 0);
	// }
	// if (&sub1 != p[0])
	// {
	// 	printf("sub1: %x, p[0]: %x\n", sub1, p[0]);
	// }
	// else if (&sub2 != &p[1])
	// {
	// 	printf("sub2: %x, p[1]: %x\n", sub2, p[1]);
	// }
	// else if (&sub3 != &p[2])
	// {
	// 	printf("sub3: %x, p[2]: %x\n", sub3, p[2]);
	// }

	// printf("Finished\n");

	// sub.clear(0xFF);
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
	// int k = 0;
	// char **p;
	while (1)
	{
		// p = main.getChildrenNames();
		// for (int i = 0; i < 3; i++)
		// {
		// 	if (!sizeof(p[i]) > 0)
		// 	{
		// 		k++;
		// 	}
		// 	// printf("%s\n", p[i]);
		// 	// o.writeString(p[i]);
		// 	// o.goTo(i, 0);
		// }
		// if (k)
		// {
		// 	printf("k: %d\n", k);
		// }
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