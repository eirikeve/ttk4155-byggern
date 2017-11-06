// #ifndef UTILITIES_H
// #define UTILITIES_H

// #define F_CPU 4915200

// #endif // UTILITIES_H

#pragma once

#define ADC_ADDR    0x1400
#define AVR_VRAM_1  0x1800
#define AVR_VRAM_2  0x1C00

#define set_bit(reg, bit) (reg |= (1 << (bit)))
#define set_bit_value(reg, bit, val) (reg |= (val << (bit)))
#define clr_bit(reg, bit) (reg &= ~(1 << (bit)))
#define test_bit(reg, bit) (reg & (1 << (bit)))
#define set_byte(reg, val) (reg = val)

#define loop_until_bit_is_clear(sfr,bit) \
do { } while (bit_is_set(sfr, bit)) 

#define loop_until_bit_is_set(sfr,bit) \
do { } while (bit_is_clear(sfr, bit)) 