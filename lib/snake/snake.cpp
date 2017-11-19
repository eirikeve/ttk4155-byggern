#ifdef __AVR_ATmega162__
#pragma once
#include "snake.h"
#include <stdlib.h>

void Snake::run(){
	//Test
	this->initMap();
	running = true;
	while(running){
		//change direction
		this->changeDirection();
		
		//update map
		this->update();
		
		//Send map to screen
		this->printMap();

		//wait for length of difficulty
		if (difficulty==1)_delay_ms(150);
		if (difficulty==2)_delay_ms(100);
		if (difficulty==3)_delay_ms(50);

	}
	this->printScore();
	_delay_ms(2000);
	return;
	
}

void Snake::changeDirection(){
	/*
	    UP
    LEFT + RIGHT
       DOWN

      1
    4 + 2
      3
    */
	uint8_t newDir;
	newDir = this->getJoystick();
	if(newDir == 1 && this->direction != 3) this->direction = 1;
	else if(newDir == 2 && this->direction != 4) this->direction = 2;
	else if(newDir == 3 && this->direction != 1) this->direction = 3;
	else if(newDir == 4 && this->direction != 2) this->direction = 4;
}

uint8_t Snake::getJoystick(){
	// Initilize things needed to read joystick
    Joystick & joystick = Joystick::getInstance();

    int8_t x;
    int8_t y;

	// If joystick returns up, right, down or left
    Direction dir = joystick.read(&x, &y);
	uint8_t threshold = 90;
	if (x > threshold) return 2;
	if (x < -threshold) return 4;
	if (y > threshold) return 1;
	if (y < -threshold) return 3;
	return 0;

}

void Snake::update(){
	// move snake head
	switch (this->direction) {
	case 0:
		break;
    case 1: this->move(0, -1);
        break;
    case 2: this->move(1, 0);
        break;
    case 3: this->move(0, 1);
        break;
    case 4: this->move(-1, 0);
        break;
    }
	
	// Reduce snake values on map by 1
    for (uint8_t i = 0; i < s; i++) {
        if (map[i] > 0) map[i]--;
    }
}

void Snake::move(int8_t dx,int8_t dy){
	 // determine new head position
    uint8_t newx = headxpos + dx;
    uint8_t newy = headypos + dy;

    // Check if there is food at location
    if (map[this->xytomapIndex(newx,newy)] == -1) {
        // Increase food value (body length)
        snakeLength++;

        // Generate new food on map
        this->generateFood();
    }
	
	//Game over if snake is outside map
	if (newx>mapwidth-1 || newy>mapheight-1 || newx < 0 || newy < 0){
		running = false;
		return;
	}

	// Game over if crashing into snake
	if (map[this->xytomapIndex(newx,newy)] > 0){
		running = false;
		return;
	}

    // Move head to new location
    headxpos = newx;
    headypos = newy;
    map[this->xytomapIndex(headxpos,headypos)] = snakeLength + 1;
}

// Generates new food on map
void Snake::generateFood() {
    uint8_t x = 0;
    uint8_t y = 0;
    do {
        // Generate random x and y values within the map
        x = rand() % (mapwidth);
        y = rand() % (mapheight);

        // If location is not free try again
    } while (map[this->xytomapIndex(x,y)] != 0);

    // Place new food
    map[this->xytomapIndex(x,y)] = -1;
}

uint8_t Snake::xytomapIndex(uint8_t x,uint8_t y){
	return x + y * mapwidth;
}

// Initializes map
void Snake::initMap()
{	// clears map
	snakeLength = 3;
	for (uint8_t i = 0;i<s;i++){
		map[i] = 0;
	}
	this->printMap();
    // Places the initual head location in middle of map
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    map[this->xytomapIndex(headxpos,headypos)] = 1;

    // Generates first food
    this->generateFood();

}

// Returns graphical character for display from map value
char Snake::getMapValue(uint8_t value)
{
    // Returns a part of snake body
    if (value > 0) return 'o';
	// Returns food
    if (value == -1) return 95 + ' '; //Apple
	// Returns empty space
	if (value == 0) return ' ';
}

void Snake::printMap(){
	// Screen init
	s1.clear();
    s1.goToStart();
	
	char pmap[s+1];
	// numbers to icons
	for (uint8_t i = 0; i < s; i++){
		pmap[i] = getMapValue(map[i]);
	}
	pmap[s] = '\0';
	
	s1.writeString(pmap);
	s1.render();
}

void Snake::printScore(){
	// screen init
	s1.clear();
    s1.goTo(3,32);
	
	// write game over and score
	s1.writeString("GAME OVER");
	s1.goTo(4,32);
	char score[3];
	s1.writeString("SCORE: ");
	itoa(snakeLength-3, score, 10);
	s1.writeString(score);
	
	// set new highscore
	if (snakeLength -3 > highscore) highscore = snakeLength -3;
	s1.render();
}


#endif