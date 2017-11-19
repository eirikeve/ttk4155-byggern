#include "eeprom.h"
#ifdef __AVR_ATmega162__
#include <avr/interrupt.h>

uint8_t eepromRead(uint16_t eeprom_address)
{
    eeprom_address %= 512;
    loop_until_bit_is_clear(EECR, EEWE);
    // EEARL = (uint8_t)(eeprom_address & 0xFF);   // Write address
    // EEARH |= (uint8_t)((eeprom_address >> 8) & 0x01);
    EEAR = eeprom_address;
    EECR |= (1 << EERE);  // Read enable
    return (uint8_t)EEDR; // Data available instantly
    

}


void eepromWrite(uint16_t eeprom_address, uint8_t data)
{
    
    eeprom_address %= 512;
    loop_until_bit_is_clear(EECR, EEWE);        // Wait until old write is finished
    loop_until_bit_is_clear(SPMCR, SPMEN);  
    // EEARL = (uint8_t)(eeprom_address & 0xFF);   // Write address and data
    // EEARH |= (uint8_t)((eeprom_address >> 8) & 0x01);
    EEAR = eeprom_address;
    EEDR = data;
    cli();
    EECR |= (1 << EEMWE);  // Master write enable, while setting write enable to 0 (must be done this way)
    EECR |= (1 << EEWE); // Write enable
    sei();

}

#endif // __AVR_ATmega162__