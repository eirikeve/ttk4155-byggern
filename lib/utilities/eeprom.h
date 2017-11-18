#pragma once
#include <avr.io>
#include <util/delay.h>
#include "../utilities/utilities.h"

uint8_t eepromRead(uint16_t eeprom_address)
{
    EEARL = (uint8_t)(eeprom_address & 0xFF);   // Write address
    EEARH |= (uint8_t)((eeprom_address > 8) & 0x01);

    EECR |= 0b0001;  // Read enable
    return (uint8_t)EEDR; // Data available instantly

}


void eepromWrite(uint16_t eeprom_address, uint8_t data)
{
    loop_until_bit_is_clear(EECR, EEWE);        // Wait until old write is finished
    EEARL = (uint8_t)(eeprom_address & 0xFF);   // Write address and data
    EEARH |= (uint8_t)((eeprom_address > 8) & 0x01);
    EEDR = data;

    EECR = 0b0100  // Master write enable, while setting write enable to 0 (must be done this way)
    EECR |= 0b0010; // Write enable

}