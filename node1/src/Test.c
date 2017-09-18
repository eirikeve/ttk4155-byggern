/*
 * Test.c
 *
 * Created: 04.09.2017 11:26:38
 *  Author: aasmune
 */ 


#include <avr/io.h>
#include"utils.h"
#include "util/delay.h"
#include "comm.h"
#include "lib/adc/adc.h"

char* s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent vestibulum erat a sapien luctus fermentum.";
int main(void)
{
	set_bit(DDRB, 3);
	
	init_uart();
	uint8_t c;
	ADC test;
	
    while(1)
    {
        set_bit(PORTB, 3);
        _delay_ms(500);
		clr_bit(PORTB, 3);
		_delay_ms(500);
		printf("%d\n", test.testAdc());
		// printf("Hello World\n");
		//put_uart_char('a');
		//printf("This is a really long string: %s\n", s);
    }
}