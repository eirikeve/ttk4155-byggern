// #ifndef UTILITIES_H
// #define UTILITIES_H

// #define F_CPU 4915200

// #endif // UTILITIES_H

#pragma once

#define ADC_ADDR    0x1400
#define AVR_VRAM_1  0x1800
#define AVR_VRAM_2  0x1C00
#define OLED_UPDATE_FPS 20
#define OLED_PIXELS_WIDTH 128
#define OLED_PIXELS_HEIGHT 64
#define OLED_PAGES_HEIGHT 8
#define INDEX_APPLE 95
#define INDEX_SQUARE 96

#define EEPROM_SNAKE_HIGHSCORE_ADDR_L 0
#define EEPROM_SNAKE_HIGHSCORE_ADDR_H 1

#define set_bit(reg, bit) (reg |= (1 << (bit)))
#define set_bit_value(reg, bit, val) (reg |= (val << (bit)))
#define clr_bit(reg, bit) (reg &= ~(1 << (bit)))
#define test_bit(reg, bit) (reg & (1 << (bit)))
#define set_byte(reg, val) (reg = val)

#define loop_until_bit_is_clear(sfr,bit) \
do { } while (bit_is_set(sfr, bit)) 

#define loop_until_bit_is_set(sfr,bit) \
do { } while (bit_is_clear(sfr, bit)) 