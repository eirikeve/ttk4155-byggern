#pragma once
#include "SPI.h"
extern "C" {
	#include <stdio.h>
}

void SPI_init(void)
{
#ifdef __AVR_ATmega162__
	/* Set 		 SS' 	  MOSI and 	 SCK to output, all others input */
	DDRB |= (1 << DDB4) | (1 << DDB5) | (1 << DDB7);
#elif __AVR_ATmega2560__
	/* Set 		 SS' 	  MOSI and 	 SCK to output, all others input */
	DDRB |= (1 << DDB7) | (1 << DDB2) | (1 << DDB1) | (1 << DDB0);
	PORTB |= (1 << PB0);
#endif
	// DDRB |= (1 << DDB4) | (1 << DDB5) | (1 << DDB7);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_send(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	//while(!(SPSR & (1<<SPIF))); // Changed to the line below
	// loop_until_bit_is_set(SPSR, SPIF);
	while (!(SPSR & (1 << SPIF)));
	// printf("hei\n");
}

void SPI_send_string(char *c_string)
{
	uint8_t index = 0;
	while (c_string[index] != '\0')
	{
		SPI_send(c_string[index]);
		index += 1;
		if (index == UINT8_MAX)
			return; // To avoid infinite loop
	}
}
char SPI_read()
{
	SPI_send(0x00);
	return SPDR;
}

void SPI_select_slave() {
#ifdef __AVR_ATmega162__
	clr_bit(PORTB, 4);
#elif __AVR_ATmega2560__
	clr_bit(PORTB, 7);
#endif
}

void SPI_deselect_slave() {
#ifdef __AVR_ATmega162__
		set_bit(PORTB, 4);
#elif __AVR_ATmega2560__
		set_bit(PORTB, 7);
#endif
	}