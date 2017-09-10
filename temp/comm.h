/*
 * utils.h
 *
 * Created: 04.09.2017 11:29:32
 *  Author: eirikeve
 */ 

#include <avr/io.h>
#include "utils.h"

int put_uart_char(char c)
{
	while (!test_bit(UCSR0A, UDRE0))
	{
		continue;
	}
	UDR0 = c;
	return 0;
}


unsigned char _recv_char()
{
	while (!test_bit(UCSR0A, RXC0))
	{
		continue;
	}
	return (unsigned char)UDR0;
}

void uart_flush()
{
	unsigned char dummy;
	while( UCSR0A & (1 << RXC0)) dummy = UDR0;
}

unsigned char recv_char()
{
	unsigned char c = _recv_char();
	uart_flush();
	return c;
}

int init_uart()
{
	// Set baudrate
	// Set pin UMSEL in UCSRC to 0 (select asynchronous)
	// http://wormfood.net/avrbaudcalc.php?bitrate=9600%2C+19200&clock=4.9152&databits=8
	// Set UBRR register to value 31, calculated with link above. For 9600 tick rate
	
	
	/* Set baud rate */
	int ubrr = 31;
	//set_byte(UBRR0H, (uint8_t)(ubrr >> 8));
	//set_byte(UBRR0L, (uint8_t) ubrr);
	///* Enable receiver and transmitter */
	//set_byte(UCSR0B, (1<<RXEN0)|(1<<TXEN0));
	///* Set frame format: 8data, 2stop bit */
	//set_byte(UCSR0C, (1<<URSEL0)|(3<<UCSZ00));
	////fdevopen(put_uart_char, recv_char);
	//return 0;
	/* Set baud rate */
	UBRR0L = ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<UCSZ01)|(1<<UCSZ00);
	fdevopen(put_uart_char, recv_char);
	return 0;
}



