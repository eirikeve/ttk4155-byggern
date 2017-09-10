#ifndef UART_H
#define UART_H

#include<avr/io.h>

#include "../stream/stream.h"
class UART : public Stream {
public:

    void Init(uint16_t baud_rate);
    void Write(uint8_t *string, uint16_t size);
    void 

    UART(const UART&) = delete;
    void operator=(const UART&) = delete;
};

#endif //UART_H