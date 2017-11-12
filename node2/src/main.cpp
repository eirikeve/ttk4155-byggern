/*
 * Test.c
 *
 * Created: 04.09.2017 11:26:38
 *  Author: aasmune
 */
extern "C" {
#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
// #include "../lib/comm/comm.h"
#include "../lib/utilities/utilities.h"
}
#include <stdint.h>
#include "lib/timer/timer.h"
#include "lib/adc_internal/adc_internal.h"
#include "lib/servo/servo.h"
#include "test/test.h"
#include "lib/uart/uart.h"
#include "lib/utilities/printf.h"

int main(void)
{
	// testSolenoid();
	testTuneMotor();
	// testMotorOverCan();
	// testMotor();
}