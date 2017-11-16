#pragma once

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

// Test slider
void testSlider();
void testSliderButton();

// Test spi
void testSpi();

// Test can
void testCanLoopback();
void testCanTransmit();
void testCanReceive();

// Test servo over can
void testControlServoOverCan();

// Test FSM
void testFSM();