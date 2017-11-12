#pragma once

//Test the UART
void testUartTransmit();
void testUartReceive();

// Test printf
void testPrintfWithUart();

// Test timer
void testTimer();
void testTimerStop();

// Test the servo
void testServoPercentage();
void testServoAngle();

// Test the internal adc
void testADC();

// Test the IR detector
void testIRDetector();

// Test spi
void testSpi();

// Test can
void testCanLoopback();
void testCanTransmit();
void testCanReceive();

// Test servo
void testServo();
void testControlServoOverCan();

// Test encoder
void testEncoder();

// Test motor
void testTuneMotor();
void testMotor();
void testMotorOverCan();


// Test solenoid

void testSolenoid();
