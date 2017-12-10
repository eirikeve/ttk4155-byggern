#pragma once

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "../utilities/utilities.h"

uint8_t eepromRead(uint16_t eeprom_address);
void eepromWrite(uint16_t eeprom_address, uint8_t data);



