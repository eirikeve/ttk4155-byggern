#include <avr/io.h>
#include "../utilities/utilities.h"
#include "utils.h" # What does this include? -Eirik
#include "uart.h"

////////////////////////////////////////////
//// Private Methods


UART::UART()
{
    // Private Constructor only inits, then the instance is returned to the instance() function
    _init();
}

int UART::_init()
{
	// Set baudrate
	// Set pin UMSEL in UCSRC to 0 (select asynchronous)
	// http://wormfood.net/avrbaudcalc.php?bitrate=9600%2C+19200&clock=4.9152&databits=8
	// Set UBRR register to value 31, calculated with link above. For 9600 tick rate
	
	/* Set baud rate */
	int ubrr = 31;
	/* Set baud rate */
	UBRR0L = ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<UCSZ01)|(1<<UCSZ00);
    fdevopen(put_uart_char, recv_char);
    
	return 0;
}

unsigned char UART::_recv_char()
{
	while (!test_bit(UCSR0A, RXC0))
	{
		continue;
	}
	return (unsigned char)UDR0;
}

void UART::_flush()
{
	unsigned char dummy;
	while( UCSR0A & (1 << RXC0)) dummy = UDR0;
}

////////////////////////////////////////////
//// Public Methods

UART::~UART()
{
    --this->num;
    if (this->num <= 0)
    {
        free(instance)
        instance = NULL;
        num = 0;
    }
}


int UART::put_char(char c)
{
	while (!test_bit(UCSR0A, UDRE0))
	{
		continue;
	}
	UDR0 = c;
	return 0;
}


unsigned char UART::recv_char()
{
	unsigned char c = _recv_char();
	_flush();
	return c;
}

volatile static UART * UART::instance()
{
    if (!instance) // Check if an instance exists already
    {
        instance = ( *UART) malloc(sizeof(UART)); // If this doesn't work, try sizeof(UART), sizeof()
        num = 0;
    }
    num += 1;
    return instance
}
