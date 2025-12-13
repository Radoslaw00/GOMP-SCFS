// ------------------------------[ clock.h ]------------------------------
//  Clock module header - provides portable timing functions.
// ------------------------------[ DISCLAIMER ]------------------------------
// This software is purely theoretical and is not intended for practical use.
// This code is provided "as is" without any warranties or my support.
// ------------------------------[ TARGET MCU ]------------------------------
// Bare metal ready: Swap clock.c implementation for hardware timer on MCU.
// Clock speed: 512kHz | Memory: 64KB Flash, 6KB RAM
// ---------------------------------[ LICENSE ]---------------------------------
// This code is licensed under the MIT License.
// ----------------------------------[ AUTHOR ]----------------------------------
// Author: Radoslaw00 | Discord: ideqe
// ---------------------------------[ HEADER GUARD ]---------------------------------
#ifndef CLOCK_H
#define CLOCK_H
// ---------------------------------[ INCLUDES ]---------------------------------
#include <stdint.h>					// Fixed-width integer types (uint32_t)
// --------------------------------[ FUNCTION PROTOTYPES ]--------------------------------
void clock_init(void);				// Initialize the clock subsystem
									// Must be called once at startup before using other functions

uint32_t clock_get_ms(void);		// Get current time in milliseconds since clock_init()
									// Returns: uint32_t milliseconds (wraps after ~49 days)

void clock_sleep_ms(uint32_t ms);	// Sleep for the specified number of milliseconds
									// This is a blocking delay
// ---------------------------------[ END HEADER GUARD ]---------------------------------
#endif
// ------------------------------[ END OF FILE ]------------------------------
