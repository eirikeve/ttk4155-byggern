#ifdef __AVR_ATmega162__
#include "snake.h"
#include <util/delay.h>
#include "lib/uart/uart.h"
#include "lib/adc/adc.h"
#include "lib/joystick/joystick.h"
#include "lib/display/screen.h"

void Snake::run(){
	//Test
	this->initmap();
	running = true;
	while(running){
		//change direction
		this->changeDirection();
		
		//update map
		this->update();
		
		//Send map to screen
		this->printMap();
		
		//wait for length of difficulty
		_delay_ms(difficulty);
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
	int joystick;
	joystick = this->getJoystick();
	if(joystick == 1 && direction != 3) direction = 1
	else if(joystick == 2 && direction != 4) direction = 2
	else if(joystick == 3 && direction != 1) direction = 3
	else if(joystick == 4 && direction != 2) direction = 4
}

void getJoystick(){
	// Initilize things needed to read joystick
	UART & uart = UART::getInstance();
    ADC& adc = ADC::getInstance();
    Joystick & joystick = Joystick::getInstance();

    int8_t x;
    int8_t y;

	// If joystick returns up, right, down or left
    Direction dir = joystick.read(&x, &y);
    printf("x: %d, y: %d, dir: %d\n", x, y, dir);
	if (dir == 1 || dir == 3 || dir == 5 || dir == 7){
		joystick = (dir-1)/2 + 1;
	}
	// If joystick returns anything else, we need to change it to one of the four directions
	else{
		// changes north-east to right or up
		if (dir == 2){
			if (direction == 1){
				return 2;
			}
			if (direction == 2){
				return 1;
			}
			if (direction == 3){
				return 2;
			}
			if (direction == 4){
				return 1;
			}
		}
		// chanes south-east to right or down
		if (dir == 4){
			if (direction == 1){
				return 2;
			}
			if (direction == 2){
				return 3;
			}
			if (direction == 3){
				return 2;
			}
			if (direction == 4){
				return 3;
			}
		}
		// changes south-west to left or down
		if (dir == 6){
			if (direction == 1){
				return 4;
			}
			if (direction == 2){
				return 3;
			}
			if (direction == 3){
				return 4;
			}
			if (direction == 4){
				return 3;
			}
		}
		//changes north-west to left or up
		if (dir == 8){
			if (direction == 1){
				return 4;
			}
			if (direction == 2){
				return 1;
			}
			if (direction == 3){
				return 4;
			}
			if (direction == 4){
				return 1;
			}
		}
	}
}

int Snake::update(){
	// move snake head
	switch (direction) {
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
    for (int i = 0; i < size; i++) {
        if (map[i] > 0) map[i]--;
    }
}

int Snake::move(dx,dy){
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
	
	// Game over if snake is outside map
	if (newx>mapheight || newy>mapwidth || newx < 0 || newy < 0){
		running = false;
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

int Snake::xytomapIndex(x,y){
	return x + y * mapwidth;
}

// Initializes map
void Snake::initMap()
{	// sets difficulty
	int difficulty = 500;
	
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
    if (value == -1) return '+';
	// Returns empty space
	if (value == 0) return ' ';
}

void Snake::printMap(){
	// Screen init
	s1.clear();
    s1.goToStart();
	
	int pmap[size];
	// numbers to icons
	for (i = 0; i < size; i++){
		pmap[i] = getMapValue(map[i])
	}
	
	sl->writeString(pmap);
	sl->render();
}

#endif