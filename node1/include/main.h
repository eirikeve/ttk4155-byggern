#pragma once
extern "C" {
    #include <avr/io.h>
    #include "util/delay.h"
    #include <stdio.h>
    #include <avr/pgmspace.h>
    #include <stdlib.h>
    #include "comm.h"
    }
    
#include "lib/joystick/joystick.h"
#include "lib/display/screen.h"
#include <stdint.h>
#include "lib/fonts/fonts.h"
#include "lib/menu/menuNode.h"

void menu_test();
void disp_test();
void init(Screen main);