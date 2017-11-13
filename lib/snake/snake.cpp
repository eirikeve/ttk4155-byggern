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
		printf("%d\n", direction);
		//update map
		this->update();
		
		//Send map to screen
		this->printMap();

		//wait for length of difficulty
		_delay_ms(100);
	}
	while(!running){
		this->printScore();
	}
	
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
	int newDir;
	newDir = this->getJoystick();
	if(newDir == 1 && this->direction != 3) this->direction = 1;
	else if(newDir == 2 && this->direction != 4) this->direction = 2;
	else if(newDir == 3 && this->direction != 1) this->direction = 3;
	else if(newDir == 4 && this->direction != 2) this->direction = 4;
}

int Snake::getJoystick(){
	// Initilize things needed to read joystick
    Joystick & joystick = Joystick::getInstance();

    int8_t x;
    int8_t y;

	// If joystick returns up, right, down or left
    Direction dir = joystick.read(&x, &y);
	int nx = joystick.readX();
	int ny = joystick.readY();
	int threshold = 90;
	if (nx > threshold) return 2;
	if (nx < -threshold) return 4;
	if (ny > threshold) return 1;
	if (ny < -threshold) return 3;


}

void Snake::update(){
	// move snake head
	switch (this->direction) {
	case 0:
		break;
    case 1: this->move(0, -1);
		printf("Dette er case 1");
        break;
    case 2: this->move(1, 0);
		printf("dette er case 2");
        break;
    case 3: this->move(0, 1);
		printf("dette er case 3");
        break;
    case 4: this->move(-1, 0);
		printf("dette er case 4");
        break;
    }
	
	// Reduce snake values on map by 1
    for (int i = 0; i < s; i++) {
        if (map[i] > 0) map[i]--;
    }
}

void Snake::move(int dx,int dy){
	 // determine new head position
    int newx = headxpos + dx;
    int newy = headypos + dy;

    // Check if there is food at location
    if (map[this->xytomapIndex(newx,newy)] == -1) {
        // Increase food value (body length)
        snakeLength++;

        // Generate new food on map
        this->generateFood();
    }
	
	printf("%d\n", newx);
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
    int x = 0;
    int y = 0;
    do {
        // Generate random x and y values within the map
        x = rand() % (mapwidth);
        y = rand() % (mapheight);

        // If location is not free try again
    } while (map[this->xytomapIndex(x,y)] != 0);

    // Place new food
    map[this->xytomapIndex(x,y)] = -1;
}

int Snake::xytomapIndex(int x,int y){
	return x + y * mapwidth;
}

// Initializes map
void Snake::initMap()
{	// sets difficulty
	difficulty = 500;
	for (int i = 0;i<s;i++){
		map[i] = 0;
	}
    // Places the initual head location in middle of map
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    map[this->xytomapIndex(headxpos,headypos)] = 1;

    // Generates first food
    this->generateFood();
}

// Returns graphical character for display from map value
char Snake::getMapValue(int value)
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
	for (int i = 0; i < s; i++){
		pmap[i] = getMapValue(map[i]);
	}
	pmap[s] = '\0';
	// printf(pmap);
	// printf("\n");
	s1.writeString(pmap);
	s1.render();
}

void Snake::printScore(){
	s1.clear();
    s1.goTo(3,32);
	// printf(pmap);
	// printf("\n");
	s1.writeString("GAME OVER");
	s1.goTo(4,32);
	char score[3];
	s1.writeString("SCORE: ");
	itoa(snakeLength-3, score, 10);
	s1.writeString(score);
	// s1.writeString('\0');
	s1.render();

}

#endif