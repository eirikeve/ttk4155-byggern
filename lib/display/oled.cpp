#ifdef __AVR_ATmega162__
#include "oled.h"
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
    write_c(0x02);
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
    for (int i = 0; i < 5; i++)
    {
        this->write(pgm_read_word(&font5[c - ' '][i]));
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

void OLED::goToPage(uint8_t page)
{
    this->write_c(0xB0 + page);
}

void OLED::goToColumn(uint8_t col)
{
    this->write_c(0x0F & col);
    this->write_c(0x10 | (0xF & col >> 4));
}

void OLED::goTo(uint8_t page, uint8_t col)
{
    goToPage(page);
    goToColumn(col);
}

void OLED::clear()
{
}
#endif