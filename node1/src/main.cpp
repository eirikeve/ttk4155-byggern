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
#include "../lib/3dcube/c3dcube.h"


void toggle_led() {
    PORTB ^= 0b1;
}

int main(void)
{
	  UART & uart = UART::getInstance();
    uart.initialize(9600);
    enablePrintfWithUart();

    printf("Node 1 startup\n");
    Timer& timer0 = Timer::getInstance(0);
    timer0.initialize(500, toggle_led, &pb0);
    timer0.start();

    

    SPI& spi = SPI::getInstance(0);
    CAN& can = CAN::getInstance();
    can.initialize(&spi, false);
    
     
    ADC& adc = ADC::getInstance();
    Joystick & joystick = Joystick::getInstance();
    joystick.initialize(&adc, 30, &pb3);

    Slider & slider0 = Slider::getInstance(0);
    slider0.initialize(&adc, &pb2);

    Slider & slider1 = Slider::getInstance(1);
    slider1.initialize(&adc, &pb1);

    FSM & fsm = FSM::getInstance();
    loadStateFunctionsToFSM();

    sendResetUntilACK();
    printf("Node1 Starting\n");
    playStartupVideo();

	while (true)
	{
        fsm.runStateLoop();
  }
}