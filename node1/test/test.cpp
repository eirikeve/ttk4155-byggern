    #include <stdio.h>
    #include <avr/io.h>
    #include <util/delay.h>
    #include <stdint.h>
    
    #include "test.h"
    #include "lib/utilities/printf.h"
    #include "lib/uart/uart.h"
    #include "lib/joystick/joystick.h"
    
void testUartTransmit() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    while (true) {
        uart.transmit('B');
        uart.transmit('\n');
    }
}

void testUartReceive() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);

    while (true) {
        uint8_t c = uart.receive();
        uart.transmit(c);
    }
}

void testPrintfWithUart() {
    UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();
    while (true) {
        printf("Test printf\n");
    }
}
    
void testJoystick()
{
        // init_uart();
        Joystick joystick(10);
        int8_t x;
        int8_t y;
    
        while (1)
        {
            Direction dir = joystick.read(&x, &y);
            printf("x: %d, y: %d, dir: %d\n", x, y, dir);
            // x = joystick.readY();
            // printf("%d\n", x);
        }
}