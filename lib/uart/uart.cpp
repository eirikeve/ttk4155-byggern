#include "UART.h"
#include "../utilities/utilities.h"
#include <iostream>

void UART::Init(uint16_t baud_rate) {
    baud_rate = (uint16_t) (F_CPU / 16 / baud_rate - 1);
    std::cout << baud_rate << std::endl;
}

int main() {
    UART a = UART;
    a.Init(9600);
}