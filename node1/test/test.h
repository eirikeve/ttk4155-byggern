#pragma once
#include <stdlib.h>

//Test the UART
void testUartTransmit();
void testUartReceive();

// Test printf
void testPrintfWithUart();

// Test timer
void testTimer();
void testTimerStop();

// Test joystick
void testJoystick();
void testJoystickButton() ;

// Test display
void testScreen();
void testSubScreen();

// Test ScreenHandler
void testScreenHandler();
void testScreenHandlerAnimation();

void SRAM_test();

// Test snake
void testSnake();
