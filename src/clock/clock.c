// ------------------------------[ clock.c ]------------------------------
//  Clock module implementation - portable timing for Windows/Linux/Bare Metal.
// ------------------------------[ DISCLAIMER ]------------------------------
// This software is purely theoretical and is not intended for practical use.
// This code is provided "as is" without any warranties or my support.
// ------------------------------[ TARGET MCU ]------------------------------
// Bare metal ready: Replace this file with hardware timer implementation.
// Clock speed: 512kHz | Memory: 64KB Flash, 6KB RAM
// ---------------------------------[ LICENSE ]---------------------------------
// This code is licensed under the MIT License.
// ----------------------------------[ AUTHOR ]----------------------------------
// Author: Radoslaw00 | Discord: ideqe
// ---------------------------------[ INCLUDES ]---------------------------------
#include "clock/clock.h"			// Clock module header
// --------------------------------[ PLATFORM DETECTION ]--------------------------------
#ifdef _WIN32
	#include <windows.h>			// Windows API for timing
	static LARGE_INTEGER freq;		// Performance counter frequency
	static LARGE_INTEGER start_time;// Start time for elapsed calculation
#else
	#include <time.h>				// POSIX time functions
	#include <unistd.h>				// POSIX usleep function
	static struct timespec start_time;	// Start time for elapsed calculation
#endif
// --------------------------------[ CLOCK INIT ]--------------------------------
void clock_init(void) {				// Initialize clock subsystem
#ifdef _WIN32
	QueryPerformanceFrequency(&freq);	// Get timer frequency (ticks per second)
	QueryPerformanceCounter(&start_time);	// Record start time
#else
	clock_gettime(CLOCK_MONOTONIC, &start_time);	// Record start time (Linux)
#endif
}										// End of clock_init
// --------------------------------[ GET MILLISECONDS ]--------------------------------
uint32_t clock_get_ms(void) {			// Get elapsed time in milliseconds
#ifdef _WIN32
	LARGE_INTEGER now;					// Current time
	QueryPerformanceCounter(&now);		// Get current tick count
	return (uint32_t)((now.QuadPart - start_time.QuadPart) * 1000 / freq.QuadPart);
										// Convert ticks to milliseconds
#else
	struct timespec now;				// Current time
	clock_gettime(CLOCK_MONOTONIC, &now);	// Get current time (Linux)
	long sec_diff = now.tv_sec - start_time.tv_sec;		// Seconds difference
	long nsec_diff = now.tv_nsec - start_time.tv_nsec;	// Nanoseconds difference
	return (uint32_t)(sec_diff * 1000 + nsec_diff / 1000000);	// Convert to ms
#endif
}										// End of clock_get_ms
// --------------------------------[ SLEEP MILLISECONDS ]--------------------------------
void clock_sleep_ms(uint32_t ms) {		// Sleep for specified milliseconds
#ifdef _WIN32
	Sleep(ms);							// Windows sleep (milliseconds)
#else
	usleep(ms * 1000);					// Linux usleep (microseconds)
#endif
}										// End of clock_sleep_ms
// --------------------------------[ BARE METAL NOTES ]--------------------------------
// For bare metal (e.g., ARM Cortex-M at 512KHz), replace this file with:
//
// #include "clock/clock.h"
// static volatile uint32_t tick_ms = 0;
//
// void SysTick_Handler(void) { tick_ms++; }	// SysTick interrupt - 1ms tick
//
// void clock_init(void) {
//     SysTick->LOAD = 512 - 1;		// 512KHz / 1000 = 512 cycles per ms
//     SysTick->VAL = 0;
//     SysTick->CTRL = 7;				// Enable with interrupt
// }
//
// uint32_t clock_get_ms(void) { return tick_ms; }
// void clock_sleep_ms(uint32_t ms) { uint32_t s = tick_ms; while((tick_ms - s) < ms); }
// ------------------------------[ END OF FILE ]------------------------------
