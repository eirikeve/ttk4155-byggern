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
	uint8_t headxpos;
	uint8_t headypos;
	uint8_t snakeLength = 3;
	uint8_t direction = 2;
	
	// Map dimensions
	const uint8_t mapwidth = 21;
	const uint8_t mapheight = 8;
	static const uint8_t s = 168;
	
	// Tile values on map
	int8_t map[s];
	
	//others
	bool running;
	uint8_t difficulty = 1;
	uint8_t highscore = 0;
	Screen s1 = Screen();
	
	//menu
	uint8_t currentOption = 0;

	void initMap();
	void move(int8_t dx, int8_t dy);
	void update();
	void changeDirection();
	void generateFood();
	char getMapValue(uint8_t value);
	uint8_t xytomapIndex(uint8_t x,uint8_t y);
	uint8_t getJoystick();
	bool getJoystickButton();
	void printMap();
	void printScore();
	void printMenu();
	
public:
	void run();
	inline uint8_t getHighScore() const {return highscore;} 

};
