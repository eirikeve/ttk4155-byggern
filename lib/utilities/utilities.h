// #ifndef UTILITIES_H
// #define UTILITIES_H

// #define F_CPU 4915200

// #endif // UTILITIES_H

#pragma once

#define set_bit(reg, bit) (reg |= (1 << (bit)))
#define set_bit_value(reg, bit, val) (reg |= (val << (bit)))
#define clr_bit(reg, bit) (reg &= ~(1 << (bit)))
#define test_bit(reg, bit) (reg & (1 << (bit)))
#define set_byte(reg, val) (reg = val)