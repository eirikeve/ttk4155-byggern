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

	// clears map, places snake and the first food
	void initMap();
	// shifts head of snake to the new position
	void move(int8_t dx, int8_t dy);
	// updates map, new snake head postion, new food, death of snake
	void update();
	// takes joystick input and changes direction
	void changeDirection();
	// generates new food randomly
	void generateFood();
	// changes map from ints to chars
	char getMapValue(int8_t value);
	// makes 2d coordinates into 1d coordinates
	uint8_t xytomapIndex(uint8_t x,uint8_t y);
	// reads joystick direction
	uint8_t getJoystick();
	// prints map to oled screen
	void printMap();
	// prints ending score screen
	void printScore(uint8_t best_highscore);
	
public:
	Snake() {}
	// ~Snake() {s1.clear(); free(map);}
	// initial run function 
	void run();
	// returns highscore, used to save the highscore for later
	inline uint8_t getHighScore() const {return highscore;} 


};
