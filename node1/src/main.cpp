/*
 * Test.c
 *
 * Created: 04.09.2017 11:26:38
 *  Author: aasmune
 */

#include "../include/main.h"

int main(void)
{
	set_bit(DDRB, 0);
	clr_bit(DDRE, 0);

	init_uart();
	// printf("Hei\n");
	// menu_test();
	menu_navigate();

	// disp_test();

	// Screen test;
	// test.clear();
	// test.goTo(0, 1);
	// test.writeString("Hello world");

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

void menu_navigate()
{
	// set_bit(DDRB, 0);
	// init_uart();
	// printf("menu1\n");
	MenuNode main("main");
	// printf("nr1 start\n");
	MenuNode nr1("This");
	// printf("nr2 start\n");
	MenuNode nr2("Use");
	// printf("nr3 start\n");
	MenuNode nr3("and");
	// printf("nr4 start\n");
	MenuNode nr4("to");
	// printf("nr5 start\n");
	MenuNode nr5("Lorem");
	// // printf("nr6 start\n");
	MenuNode nr6("consectetur");
	// // printf("nr7 start\n");
	MenuNode nr7("sed");
	// // printf("nr8 start\n");
	MenuNode nr8("ut labore");
	// // printf("nr9 start\n");
	MenuNode nr9("Ut");
	// // printf("nr10 start\n");
	MenuNode nr10("quis");
	// printf("menu2\n");
	main.addChild(nr1);
	main.addChild(nr2);
	main.addChild(nr3);
	main.addChild(nr4);
	// printf("menu3\n");
	nr1.addChild(nr5);
	printf("%s\n", nr1.getChild(0)->getName());
	nr1.addChild(nr6);
	// printf("menu4\n");
	// nr2.addChild(nr7);
	nr2.addChild(nr8);
	// printf("menu5\n");
	nr5.addChild(nr9);
	nr6.addChild(nr10);
	// printf("menu6\n");
	Menu menuStructure(&main);

	Screen disp;
	disp.clear();

	Joystick stick(20);
	// printf("Bo\n");

	uint8_t x;
	uint8_t y;
	Direction currentDir = Direction::NEUTRAL;
	Direction lastDir = Direction::NEUTRAL;

	while (true)
	{
		// _delay_ms(100);
		// printf("%d\n", stick.readX());

		// Direction dir = stick.read(&x, &y);
		x = stick.readX();
		y = stick.readY();
		// printf("x: %d, y: %d\n", x, y);
		lastDir = currentDir;
		currentDir = stick.getDir();
		// printf("Dir: %d\n", currentDir);
		char **choices = NULL;
		if (menuStructure.getCurrent() != NULL)
		{
			choices = menuStructure.getCurrent()->getChildrenNames();
			for (int i = 0; i < menuStructure.getCurrent()->getTotNrOfChildren(); i++)
			{
				disp.goTo(i, 1);
				if (i == menuStructure.getSelectIndex())
				{
					disp.writeChar('>');
				}
				// printf("hei\n");
				// printf("%d\n", menuStructure.getSelectIndex());
				// printf("%s\n", choices[i]);
				disp.writeString(choices[i]);
				disp.writeChar('\n');
				// disp.writeString("test");
			}
			free(choices);
		}
		else
		{
			disp.clear();
		}

		// _delay_ms(100);

		if (lastDir == Direction::NEUTRAL)
		{
			switch (currentDir)
			{
			case Direction::NORTH:
			{
				menuStructure.up();
				break;
			}
			case Direction::SOUTH:
			{
				menuStructure.down();
				break;
			}
			case Direction::EAST:
			{
				menuStructure.select();
				disp.clear();
				break;
			}
			case Direction::WEST:
			{
				menuStructure.back();
				disp.clear();
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}

// void menu_test()
// {
// 	init_uart();
// 	printf("\n\n\n\n\n\n\nStarting\n");
// 	MenuNode main("main");
// 	MenuNode nr1("u1");
// 	MenuNode nr2("u2");
// 	MenuNode nr3("u3");
// 	MenuNode nr4("u4");

// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr1.getName(), nr1.getSibling(0)->getName(), nr1.getParent()->getName(), nr1.getParent()->getTotNrOfChildren());
// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr2.getName(), nr2.getSibling(0)->getName(), nr2.getParent()->getName(), nr2.getParent()->getTotNrOfChildren());
// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr3.getName(), nr3.getSibling(0)->getName(), nr3.getParent()->getName(), nr3.getParent()->getTotNrOfChildren());

// 	main.addChild(nr1);
// 	// printf("c: %d\n", main.getTotNrOfChildren());
// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr1.getName(), nr1.getSibling(0)->getName(), nr1.getParent()->getName(), nr1.getParent()->getTotNrOfChildren());
// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr2.getName(), nr2.getSibling(0)->getName(), nr2.getParent()->getName(), nr2.getParent()->getTotNrOfChildren());
// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr3.getName(), nr3.getSibling(0)->getName(), nr3.getParent()->getName(), nr3.getParent()->getTotNrOfChildren());

// 	main.addChild(nr2);
// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr1.getName(), nr1.getSibling(0)->getName(), nr1.getParent()->getName(), nr1.getParent()->getTotNrOfChildren());
// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr2.getName(), nr2.getSibling(0)->getName(), nr2.getParent()->getName(), nr2.getParent()->getTotNrOfChildren());
// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr3.getName(), nr3.getSibling(0)->getName(), nr3.getParent()->getName(), nr3.getParent()->getTotNrOfChildren());
// 	main.addChild(nr3);
// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr1.getName(), nr1.getSibling(0)->getName(), nr1.getParent()->getName(), nr1.getParent()->getTotNrOfChildren());
// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr2.getName(), nr2.getSibling(0)->getName(), nr2.getParent()->getName(), nr2.getParent()->getTotNrOfChildren());
// 	// printf("name: %s, sibling: %s, par: %s, par ch: %d\n", nr3.getName(), nr3.getSibling(0)->getName(), nr3.getParent()->getName(), nr3.getParent()->getTotNrOfChildren());
// 	main.addChild(nr4);
// 	// printf("siblings main: %d\n", main.getTotNrOfSiblings());
// 	// printf("sib 0 for u2: %s\n", nr2.getSibling(-1)->getName());
// 	char **res = nr2.getSiblingNames();
// 	for (int i = 0; i < main.getTotNrOfChildren() - 1; i++)
// 	{
// 		printf("%s\n", res[i]);
// 	}
// 	char **res1 = main.getChildrenNames();
// 	for (int i = 0; i < main.getTotNrOfChildren(); i++)
// 	{
// 		printf("%s\n", res1[i]);
// 	}
// 	// printf("%s\n", main.getChild(1)->getName());
// }

// void init(Screen main)
// {
// 	const unsigned char appleLogo[8] =
// 		{0b00000000, 0b01111000, 0b11111100, 0b11111110, 0b11001101, 0b01001000, 0b00000000, 0b00000000};
// 	main.clear();
// 	main.goTo(4, 61);
// 	for (int i = 0; i < 8; ++i)
// 	{
// 		main.write(appleLogo[i]);
// 	}
// 	_delay_ms(200);
// 	char letter = '-';
// 	for (int i = 0; i < 26; ++i)
// 	{

// 		switch (letter)
// 		{
// 		case '-':
// 			letter = '\\';
// 			break;
// 		case '\\':
// 			letter = '|';
// 			break;
// 		case '|':
// 			letter = '/';
// 			break;
// 		case '/':
// 			letter = '-';
// 			break;
// 		}
// 		main.goTo(6, 29);
// 		main.writeString("Initializing ");
// 		main.writeChar(letter);
// 		main.goTo(7, 0);
// 		for (int j = 0; j <= i; ++j)
// 		{
// 			main.writeChar('-');
// 		}

// 		_delay_ms(100);
// 	}
// 	main.goTo(6, 29);
// 	main.writeString("Initializing *");
// 	_delay_ms(250);

// 	main.goTo(7, 0);
// 	for (int j = 0; j <= 26; ++j)
// 	{
// 		main.writeChar('=');
// 	}

// 	_delay_ms(250);

// 	main.goTo(7, 0);
// 	for (int j = 0; j <= 26; ++j)
// 	{
// 		main.writeChar('-');
// 	}

// 	_delay_ms(150);

// 	main.clear();
// }

// void disp_test()
// {
// 	// Joystick joystick(10);
// 	uint8_t x;
// 	uint8_t y;
// 	// Screen o;
// 	// o.goTo(0, 0);
// 	// o.clear(0x00);

// 	int std_wait_time = 5000;
// 	put_uart_char('B');
// 	printf("Test\n");
// 	put_uart_char('A');
// 	x = 0;
// 	y = 0;
// 	Screen bar;

// 	init(bar);

// 	printf("\n\nAdding bar:\n");
// 	printf("\nBar:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
// 		   bar.page0, bar.page1, bar.col0, bar.col1, bar.pagesize, bar.colsize, bar.superScreen != NULL, bar.subScreen != NULL);

// 	Screen o;
// 	bar.addSubScreen(&o, 7, LOWER);
// 	printf("\n\nAdding o:\n");
// 	printf("\nBar:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
// 		   bar.page0, bar.page1, bar.col0, bar.col1, bar.pagesize, bar.colsize, bar.superScreen != NULL, bar.subScreen != NULL);
// 	printf("\no:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
// 		   o.page0, o.page1, o.col0, o.col1, o.pagesize, o.colsize, o.superScreen != NULL, o.subScreen != NULL);
// 	// bar.addBorderLines();
// 	// o.goTo(0, 0);
// 	// o.clear();
// 	Screen sub;
// 	//o.writeString("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
// 	// _delay_ms(std_wait_time);
// 	o.addSubScreen(&sub, 4, Orientation::LOWER);
// 	printf("\n\nAdding sub:\n");
// 	printf("\nBar:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
// 		   bar.page0, bar.page1, bar.col0, bar.col1, bar.pagesize, bar.colsize, bar.superScreen != NULL, bar.subScreen != NULL);
// 	printf("\no:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
// 		   o.page0, o.page1, o.col0, o.col1, o.pagesize, o.colsize, o.superScreen != NULL, o.subScreen != NULL);
// 	printf("\nSub:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
// 		   sub.page0, sub.page1, sub.col0, sub.col1, sub.pagesize, sub.colsize, sub.superScreen != NULL, sub.subScreen != NULL);
// 	// _delay_ms(std_wait_time);
// 	// o.writeString("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
// 	// _delay_ms(std_wait_time);
// 	// sub.writeString("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy");
// 	Screen subsub;
// 	// _delay_ms(std_wait_time);
// 	sub.addSubScreen(&subsub, 64, Orientation::RIGHT);
// 	printf("\n\nAdding subsub:\n");
// 	// sub.writeString("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy");
// 	// _delay_ms(std_wait_time);
// 	// subsub.writeString("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
// 	// _delay_ms(std_wait_time);
// 	// subsub.clear();
// 	// subsub.writeString("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
// 	printf("\nBar:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
// 		   bar.page0, bar.page1, bar.col0, bar.col1, bar.pagesize, bar.colsize, bar.superScreen != NULL, bar.subScreen != NULL);
// 	printf("\no:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
// 		   o.page0, o.page1, o.col0, o.col1, o.pagesize, o.colsize, o.superScreen != NULL, o.subScreen != NULL);
// 	printf("\nSub:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
// 		   sub.page0, sub.page1, sub.col0, sub.col1, sub.pagesize, sub.colsize, sub.superScreen != NULL, sub.subScreen != NULL);
// 	printf("\nSubsub:\nPage0 %d, Page1 %d, Col0 %d, Col1 %d, Pagesize %d, Colsize %d, HasSuperScreen %d, HasSubScreen %d",
// 		   subsub.page0, subsub.page1, subsub.col0, subsub.col1, subsub.pagesize, subsub.colsize, subsub.superScreen != NULL, subsub.subScreen != NULL);

// 	// char buffer[5];
// 	// o.clear();
// 	// o.goTo(0,1);
// 	// o.writeString("SubSub: page0:");
// 	// itoa(subsub.page0, buffer, 10);
// 	// o.writeString(buffer);
// 	// o.writeString(" page1:");
// 	// itoa(subsub.page1, buffer, 10);
// 	// o.writeString(buffer);
// 	// o.writeString(" col0:");
// 	// itoa(subsub.col0, buffer, 10);
// 	// o.writeString(buffer);
// 	// o.writeString(" col1:");
// 	// itoa(subsub.col1, buffer, 10);
// 	// o.writeString(buffer);
// 	// o.writeString(" pgsz:");
// 	// itoa(subsub.pagesize, buffer, 10);
// 	// o.writeString(buffer);
// 	// o.writeString(" colsz:");
// 	// itoa(subsub.colsize, buffer, 10);
// 	// o.writeString(buffer);

// 	// _delay_ms(std_wait_time);
// 	// sub.clear();
// 	// sub.goTo(0,1);
// 	// sub.writeString("1\nW\nPer\nLine");

// 	// _delay_ms(std_wait_time);

// 	bar.addBorderLines();

// 	o.addBorderLines();

// 	sub.addBorderLines();

// 	subsub.addBorderLines();

// 	char letter = '-';
// 	char loading_bar[11]{' '};
// 	int counter = 0;
// 	char val[4];
// 	bar.clear();
// 	o.clear();
// 	sub.clear();
// 	subsub.clear();

// 	bool do_anim = false;
// 	bool do_joystick = true;

// 	while (do_anim)
// 	{

// 		counter = (counter + 1) % 11;
// 		switch (letter)
// 		{
// 		case '-':
// 			letter = '\\';
// 			break;
// 		case '\\':
// 			letter = '|';
// 			break;
// 		case '|':
// 			letter = '/';
// 			break;
// 		case '/':
// 			letter = '-';
// 			break;
// 		}
// 		for (int i = 0; i < 10; ++i)
// 		{
// 			if (i < counter)
// 			{
// 				loading_bar[i] = '=';
// 			}
// 			else
// 			{
// 				loading_bar[i] = ' ';
// 			}
// 		}
// 		loading_bar[10] = '\0';

// 		itoa(counter * 10, val, 10);

// 		bar.goTo(0, 1);
// 		bar.writeChar(letter);
// 		bar.writeChar(' ');
// 		bar.writeString(loading_bar);
// 		bar.writeChar(' ');
// 		bar.writeString(val);
// 		bar.writeChar('%');
// 		bar.writeChar('\n');
// 		_delay_ms(300);

// 		for (int i = 0; i < 5; ++i)
// 		{
// 			o.writeString("abacabadabacabaeabacabadabacaba");
// 			sub.writeString("The red fox was beautiful. ");
// 			subsub.writeString("Ipsum lorem fucking shit! ");
// 		}
// 	}

// 	// Joystick j(10);

// 	// uint8_t x;
// 	// uint8_t y;

// 	// while (do_joystick)
// 	// {
// 	// 	c = r
// 	// }

// 	// sub.clear();
// 	// _delay_ms(1000);
// 	// o.writeString("123456789123456 abcdefghijklmnopqrstuvwxyz ja123456789123456 abcdefghijklmnopqrstuvwxyz ja123456789123456 abcdefghijklmnopqrstuvwxyz ja123456789123456 abcdefghijklmnopqrstuvwxyz ja123456789123456 abcdefghijklmnopqrstuvwxyz ja");
// 	// o.goTo(0, 9);
// 	// o.writeChar('B');
// 	// const unsigned char PROGMEM a[8] = {0b00100000, 0b01110100, 0b01010100, 0b01010100, 0b00111100, 0b01111000, 0b01000000, 0b00000000};
// 	// o.gotoPage(0);
// 	// for (int i = 0; i < 8; i++)
// 	// {
// 	// 	o.write(pgm_read_word(&font8[33][i]));
// 	// }
// 	// o.writeString("->Play game       Highscores      Extra           Credits         End Game");
// 	// int k = 0;
// 	// char **p;
// }