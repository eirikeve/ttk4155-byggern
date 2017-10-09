#pragma once
#include "SPI.h"

 SPI_init(void){

	/* Set 		 SS' 	  MOSI and 	 SCK to output, all others input */
	DDRB = (1 <<DDB4)|(1<<DDB5)|(1<<DDB7);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

}

void SPI_send(char cData){
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	//while(!(SPSR & (1<<SPIF))); // Changed to the line below
	loop_until_bit_is_set(SPSR, SPIF);
}

void SPI_send_string(char * c_string)
{
	uint8_t index = 0;
	while (c_string[index] != '\0')
	{
		SPI_send(c_string[index])
		index += 1;
		if (index == UINT8_MAX) return; // To avoid infinite loop
	}
}

char SPI_read(){
	SPI_send(0x00);
	return SPDR;
}