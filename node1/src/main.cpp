#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
// #include "../lib/comm/comm.h"
#include "../lib/utilities/utilities.h"
#include "lib/utilities/printf.h"

#include "lib/can/can.h"
#include "lib/spi/spi.h"
#include "lib/timer/timer.h"
#include "lib/joystick/joystick.h"
#include <stdint.h>

#include "../test/test.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "test.h"
#include "lib/utilities/printf.h"
#include "lib/pins/pins.h"
#include "lib/uart/uart.h"
#include "lib/adc/adc.h"
#include "lib/joystick/joystick.h"
#include "lib/timer/timer.h"
#include "../lib/spi/spi.h"
#include "../lib/can/can.h"
#include "../lib/slider/slider.h"
#include "../lib/fsm/fsm.h"
#include "../lib/display/screen.h"
//#include "../lib/display/screenhandler.h"
#include "../lib/menu/menu.h"
#include "../lib/can/canmsg.h"
#include "../lib/utilities/eeprom.h"
#include "fsm_state_functions.h"

void toggle_led() {
    PORTB ^= 0b1;
}



int main(void)
{
    // clr_bit(DDRE, 0);  
	UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    printf("Node 2 startup\n");
    Timer& timer0 = Timer::getInstance(0);
    timer0.initialize(500, toggle_led, &pb0);
    timer0.start();

    

    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, false);
    
     
    ADC& adc = ADC::getInstance();
    printf("Success!!\n");
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, &pb3);
    printf("SUCCESSS\n");
    Slider & slider0 = Slider::getInstance(0);
    
    slider0.initialize(&adc, &pb2);

    Slider & slider1 = Slider::getInstance(1);
    slider1.initialize(&adc, &pb1);

    FSM & fsm = FSM::getInstance();
    loadStateFunctionsToFSM();

    printf("Success\n");
    /*ADC& adc = ADC::getInstance();
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 10, &pb3);*/
    

    printf("Node1 Starting\n");
	while (true)
	{
	 	//fsm.runStateLoop();
        
        CanMessage msg;
        CanMessage recv;

        msg.id = CAN_ID_RESET;
        msg.length = CAN_LENGTH_RESET;
        msg.data[0] = 0;
        bool ack;

        printf("Sending Reset\n");
        can.transmit(&msg);
        ack = checkForACK();
        printf("ACK for reset? %d\n", ack);

        

        

        msg.id = CAN_ID_START_GAME;
        do{
            printf("Sending StartGame\n");
            can.transmit(&msg);
            ack = checkForACK();
            printf("ACK for startGame? %d\n", ack);
        } while(ack == false);

        int i = 0;
        int8_t joystick_x;
        int8_t joystick_y;
        int8_t slider_x = 0;
        bool slider_button_pressed = false;
        printf("Running game\n");
            while (true) 
            {
                i += 5;
                //int8_t joystick_x = ((i % 99) - 49);
                // Transmit control data, and check for END_GAME event
                joystick.read(&joystick_x, &joystick_y);

                //printf("x: %d, y: %d, dir: %d\n", x, y, dir);
                msg.id = CAN_ID_SEND_USR_INPUT;
                msg.length = 3;
                msg.data[0] = joystick_x;
                msg.data[1] = slider_x;
                msg.data[2] = (int8_t)slider_button_pressed;
                can.transmit(&msg);
                _delay_ms(100);
                printf("Sending id %d Joystick.x %d\n", msg.id, joystick_x);

                recv = can.receive();
                if (recv.id == CAN_ID_STOP_GAME)
                {
                    printf("Recvd STOP. Sending ACK.\n");
                    msg.id = CAN_ID_ACK;
                    msg.length = CAN_LENGTH_ACK;
                    msg.data[0] = 0b0;

                    can.transmit(&msg);
                    return 0; // return to main while loop, where new onStateLoop will run
                }
            }
            printf("Restarting loop in..\n3\n");
            _delay_ms(1000);
            printf("2\n");
            _delay_ms(1000);
            printf("1\n");
            _delay_ms(1000);
	}
}