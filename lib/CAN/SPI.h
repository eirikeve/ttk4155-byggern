#pragma once
#include "../utilities/utilities.h"
#include <stdint.h>
extern "C"{
    #include <avr/io.h>
}


void SPI_init(void);
void SPI_send(char cData);
void SPI_send_string(char * c_string);
char SPI_read();



