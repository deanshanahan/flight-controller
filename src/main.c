/*****************************************************************************
* FILENAME:     main.c
*
* AUTHOR :      Dean Shanahan
*
* DESCRIPTION :
*   The main file for the flight controller, this file will determine the 
*   sequence of controls used to pilot the UAVs.
*
* FUNCTIONS :
*   int        main         (void)
*
* NOTES :
*   -   This file is just a skeleton file for later addition.
*
*/

// Set controller clock frequency if not already set
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

// Librabries
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <stdint.h>
#include <stdio.h>
#include "i2c.h"


int i, j, k;

// Buffer for serial data
char output_buff[30];

int main(void)
{
	cli();
	
	// Setup i2c
	i2c_init_master();
	
	// Setup watchdog timer
	wdt_disable();
	wdt_reset();
	wdt_enable(WDTO_120MS);
	
	sei();
	
	while(1)
	{
		; // Do nothing
		wdt_reset();
	}
}
