#include <avr/io.h>
#include <stdio.h>
#include "../utilities/utilities.h"
#include "uart.h"

void UART::initialize(uint16_t baudRate) {
    UBRR0L = FOSC/16/baudRate-1;

    // Enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    
    // Set frame format: 8data, 2stop bit
#ifdef __AVR_ATmega162__
    UCSR0C = (1<<URSEL0)|(1<<UCSZ01)|(1<<UCSZ00);
#elif __AVR_ATmega2560__
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
#endif
}

int UART::transmit(char byte) {
    
    loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = byte;
}

uint8_t UART::receive() {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}
