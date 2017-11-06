#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "../lib/uart/uart.h"
#include "printf.h"

int put_char(char c, FILE* f) {
    UART& uart = UART::getInstance();
    if (c == '\n') {
        uart.transmit('\r');
    }
    uart.transmit(c);
    return 0;
}

int get_char(FILE* f) {
    UART& uart = UART::getInstance();
    return uart.receive();
}

void enablePrintfWithUart() {
    fdevopen(put_char, get_char);
}