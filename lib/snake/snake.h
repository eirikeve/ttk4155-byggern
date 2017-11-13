#pragma once
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
	const int mapheight = 7;
	const int size = mapwidth * mapheight;
	
	// Tile values on map
	int map[size];
	
	//others
	bool running;
	int difficulty;
	Screen s1 = Screen();
	
public:
	void run();
	void initMap();
	void move(int dx, int dy);
	void update();
	void changeDirection();
	void generateFood();
	int getMapValue(int value);
	int xytomapIndex(x,y);
	void getJoystick()
	void printMap();
};
