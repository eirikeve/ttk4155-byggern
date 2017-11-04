#pragma once
#include <stdint.h>

struct PIN {
    volatile uint8_t* ddr;
    volatile uint8_t* port;
    volatile uint8_t* pin;
    uint8_t nr;

    PIN(volatile uint8_t *ddr, volatile uint8_t* port, volatile uint8_t* pin, uint8_t nr): ddr(ddr),port(port),pin(pin),nr(nr) {}
};