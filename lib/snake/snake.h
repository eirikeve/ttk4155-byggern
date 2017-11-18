#pragma once
#include <stdint.h>
#include "lib/display/screen.h"
#include <util/delay.h>
#include "lib/uart/uart.h"
#include "lib/adc/adc.h"
#include "lib/joystick/joystick.h"

class Snake
{
private:
	// Snake Variables
	int headxpos;
	int headypos;
	int snakeLength = 3;
	int direction = 2;
	
	// Map dimensions
	const int mapwidth = 21;
	const int mapheight = 8;
	static const int s = 168;
	
	// Tile values on map
	int map[s];
	
	//others
	bool running;
	int difficulty = 1;
	int highscore = 0;
	Screen s1 = Screen();
	
	//menu
	int currentOption = 0;
	
public:
	void start();
	void run();
	void initMap();
	void move(int dx, int dy);
	void update();
	void changeDirection();
	void generateFood();
	char getMapValue(int value);
	int xytomapIndex(int x,int y);
	int getJoystick();
	bool getJoystickButton();
	void printMap();
	void printScore();
	void printMenu();
};
