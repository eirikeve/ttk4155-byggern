extern "C" {
    #include <avr/io.h>
    #include "util/delay.h"
    #include <stdio.h>
    #include "lib/comm/comm.h"
    }
    
    #include "lib/joystick/joystick.h"
    #include <stdint.h>
    
void testJoystick()
{
        init_uart();
        Joystick joystick(10);
        uint8_t x;
        uint8_t y;
    
        while (1)
        {
            Direction dir = joystick.read(&x, &y);
            printf("x: %d, y: %d, dir: %d\n", x, y, dir);
            // x = joystick.readY();
            // printf("%d\n", x);
        }
}