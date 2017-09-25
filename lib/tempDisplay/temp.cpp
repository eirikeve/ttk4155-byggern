#include "temp.h"
#include "../utilities/utilities.h"

extern "C" {
#include <avr/io.h>
#include "../fonts/fonts.h"
#include <stdio.h>
}

OLED::OLED()
{

    set_bit(MCUCR, SRE);
    set_bit(SFIOR, XMM2);
    this->dataAddr = (uint8_t *)0x1200;
    this->commandAddr = (uint8_t *)0x1000;
    write_c(0xae);
    // display off
    write_c(0xa1);
    //segment remap
    write_c(0xda);
    //common pads hardware: alternative
    write_c(0x12);
    write_c(0xc8);
    //common output scan direction:com63~com0
    write_c(0xa8);
    //multiplex ration mode:63
    write_c(0x3f);
    write_c(0xd5);
    //display divide ratio/osc. freq. mode
    write_c(0x80);
    write_c(0x81);
    //contrast control
    write_c(0x50);
    write_c(0xd9);
    //set pre-charge period
    write_c(0x21);
    write_c(0x20);
    //Set Memory Addressing Mode
    write_c(0x00);
    write_c(0xdb);
    //VCOM deselect level mode
    write_c(0x30);
    write_c(0xad);
    //master configuration
    write_c(0x00);
    write_c(0xa4);
    //out follows RAM content
    write_c(0xa6);
    //set normal display
    write_c(0xaf);
    // display on
}

void OLED::write_c(uint8_t command)
{
    *this->commandAddr = command;
}

void OLED::write(uint8_t c)
{
    *this->dataAddr = c;
}

void OLED::writeChar(unsigned char c)
{
    for (int i = 0; i < 8; i++)
    {
        this->write(pgm_read_word(&font8[c - 32][i]));
        // printf("%d\n", font8[33][i]);
    }
}

void OLED::writeString(char *string)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        this->writeChar(string[i]);
    }
}

void OLED::gotoPage(uint8_t page)
{
    this->write_c(0xB0 + page);
    this->write_c(0x00);
    this->write_c(0x10);
}

void OLED::clear()
{
    for (int j = 0; j < 8; j++)
    {
        this->gotoPage(j);

        for (int i = 0; i < 128; i++)
        {
            this->write(0x00);
        }
    }
}