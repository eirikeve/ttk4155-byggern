#include "spi.h"
#include "lib/utilities/utilities.h"

SPI::SPI(PIN* ss) {
    this->ss = ss;
#ifdef __AVR_ATmega162__
    // Set      SS'         and   MOSI   and     SCK to output
    DDRB |= (1 << ss->nr) | (1 << DDB5) | (1 << DDB7);
    
#elif __AVR_ATmega2560__
    // Set      SS'        and   MOSI   and     SCK to output
    DDRB |= (1 << ss->nr) | (1 << DDB2) | (1 << DDB1) | (1 << DDB0);
    PORTB |= (1 << PB0);
#endif

    // Enable SPI, Master, set clock rate fck/16
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI::transmit(char data) {
    // Start transmission
    SPDR = data;

    // Wait for transmission to complete
    while (!(SPSR & (1 << SPIF)));

}

char SPI::receive() {
    this->transmit(0x00);
    return SPDR;
}

void SPI::selectSlave() {
    clr_bit(*this->ss->port, this->ss->nr);
}

void SPI::deselectSlave() {
    set_bit(*this->ss->port, this->ss->nr);
}
