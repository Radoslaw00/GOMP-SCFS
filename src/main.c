// ------------------------------[ main.c ]------------------------------
//  This file contains the main event loop for GOMP-SCFS Flight Computer.
// ------------------------------[ DISCLAIMER ]------------------------------
// This software is purely theoretical and is not intended for practical use.
// This code should not be used in any real spacecraft or embedded systems.
// This code is provided "as is" without any warranties or my support.
// Use it at your own risk.
// I am not responsible for any damage or issues caused by this code.
// You are free to modify and distribute this code.
// ------------------------------[ TARGET MCU ]------------------------------
// This code is intended to run on bare metal microcontrollers without an RTOS or any OS.
// Clock speed: 512kHz
// Memory: 64KB Flash, 6KB RAM
// --------------------------------[ PROJECT ]--------------------------------
// GOMP-SCFS: Generic Orbital Maneuver Planner - Shuttle-Class Flight Subsystem
// Controls spacecraft orbital maneuvers based on sensor data.
// Used for Low Earth Orbit (LEO) mission planning and execution.
// ------------------------------[ FILE STRUCTURE ]------------------------------
// Files:	/src/main.c
//			/src/clock/clock.c | h
//			/src/logic/logic.c | h
//			/src/sensors/sensors.c | h
//			/src/sensors/sensor_registers.c | h
//			/src/math/math.c | h
//			/src/plan/orbit.c | h
//			/src/hardware/tmr.c | h | tmr_sim.c
// ---------------------------------[ LICENSE ]---------------------------------
// This code is licensed under the MIT License.
// ----------------------------------[ AUTHOR ]----------------------------------
// Author: Radoslaw00
// Link: https://github.com/Radoslaw00
// Link to GOMP-SCFS project: https://github.com/Radoslaw00/GOMP-SCFS
// Discord: ideqe
// ---------------------------------[ INCLUDES ]---------------------------------
#include <stdio.h>					// Standard input/output for printf
#include <stdint.h>					// Fixed-width integer types (uint32_t)
#include "sensors/sensors.h"		// Sensor interface functions
#include "sensors/sensor_registers.h"	// Simulated hardware registers
#include "math/math.h"				// Orbital mechanics calculations
#include "clock/clock.h"			// Portable timing functions
#include "logic/logic.h"			// State machine and control logic
// --------------------------------[ CONSTANTS ]--------------------------------
#define LOOP_PERIOD_MS 100			// 100ms = 10Hz deterministic loop rate
// ------------------------------[ MAIN FUNCTION ]------------------------------
int main(void) {										// Main entry point
	printf("=== GOMP-SCFS Flight Computer ===\n");		// Print startup message
	printf("Loop period: %dms\n\n", LOOP_PERIOD_MS);	// Print loop period

	clock_init();										// Initialize clock subsystem first
	init_sensors();										// Initialize sensor registers

	SpacecraftState state;								// Create spacecraft state struct
	logic_init(&state);									// Initialize state machine to IDLE

	printf("Initial altitude: %.0f m\n", state.altitude_m);		// Print initial altitude
	printf("Initial velocity: %.1f m/s\n", state.velocity_mps);	// Print initial velocity
	printf("Initial fuel: %.1f kg\n", state.fuel_kg);			// Print initial fuel
	printf("State: %s\n\n", logic_state_name(state.state));		// Print initial state

	uint32_t cycle = 0;									// Cycle counter for display
// ------------------------------[ MAIN EVENT LOOP ]------------------------------
	while (1) {											// Infinite loop - runs forever
		uint32_t start_ms = clock_get_ms();				// Capture start time for timing control

		read_sensors();									// Read sensor data from registers
		logic_run_cycle(&state, 0.1);					// Run one cycle of control logic (dt=100ms)

		if (cycle % 10 == 0) {							// Every 10 cycles (1 second)
			printf("Cycle %4d: Alt=%.0fm, Vel=%.1fm/s, Fuel=%.1fkg, State=%s\n",
				cycle, state.altitude_m, state.velocity_mps,
				state.fuel_kg, logic_state_name(state.state));	// Print status
		}

		cycle++;										// Increment cycle counter

		uint32_t elapsed = clock_get_ms() - start_ms;	// Calculate elapsed time
		if (elapsed < LOOP_PERIOD_MS) {					// If under 100ms
			clock_sleep_ms(LOOP_PERIOD_MS - elapsed);	// Sleep for remainder
		}
		else {											// If over 100ms
			printf("WARNING: Loop overrun! Elapsed: %dms\n", elapsed);	// Log warning
		}
	}													// Go back to beginning of loop
	return 0;											// Never reaches here
	// Note: return 0 is unreachable in this no-os infinite-loop design, but kept
	// for completeness/compiler satisfaction if compiled in a non-embedded environment.
}														// End of 'main' function
// ------------------------------[ END OF FILE ]------------------------------