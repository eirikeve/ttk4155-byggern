/*
 * utils.h
 *
 * Created: 04.09.2017 11:29:32
 *  Author: aasmune
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define F_CPU 4915200

#define set_bit(reg, bit) (reg |= (1 << (bit)))
#define set_bit_value(reg, bit, val) (reg |= (val << (bit)))
#define clr_bit(reg, bit) (reg &= ~(1 << (bit)))
#define test_bit(reg, bit) (reg & (1 << (bit)))
#define set_byte(reg, val) (reg = val)



#endif /* UTILS_H_ */