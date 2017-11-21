// #ifndef UTILITIES_H
// #define UTILITIES_H

// #define F_CPU 4915200

// #endif // UTILITIES_H

#pragma once

// Address to Node 1's ADC
#define ADC_ADDR    0x1400
// Address to start of Node 1's first SRAM vram buffer
#define AVR_VRAM_1  0x1800
// Address to start of Node 1's second SRAM vram buffer
#define AVR_VRAM_2  0x1C00
// Frequency of ScreenHandler's interrupt routine
#define OLED_UPDATE_FPS 20

#define OLED_PIXELS_WIDTH 128
#define OLED_PIXELS_HEIGHT 64
#define OLED_PAGES_HEIGHT 8

// font5 index to an apple character we added
#define INDEX_APPLE 95
// font5 index to a black square we added
#define INDEX_SQUARE 96

// EEPROM addresses for PID parameters
#define EEPROM_PID_P_ADDR 10
#define EEPROM_PID_I_ADDR 11
#define EEPROM_PID_D_ADDR 12

// EEPROM address for Snake highscore
#define EEPROM_SNAKE_ADDR 15

/**
 * Below: Some useful macros
 **/

#define set_bit(reg, bit) (reg |= (1 << (bit)))
#define set_bit_value(reg, bit, val) (reg |= (val << (bit)))
#define clr_bit(reg, bit) (reg &= ~(1 << (bit)))
#define test_bit(reg, bit) (reg & (1 << (bit)))
#define set_byte(reg, val) (reg = val)

#define loop_until_bit_is_clear(sfr,bit) \
do { } while (bit_is_set(sfr, bit)) 

#define loop_until_bit_is_set(sfr,bit) \
do { } while (bit_is_clear(sfr, bit)) 