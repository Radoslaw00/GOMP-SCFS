// ------------------------------[ tmr_sim.c ]------------------------------
//  TMR Simulation Main - Demonstrates fault tolerance in GOMP-SCFS.
// ------------------------------[ DISCLAIMER ]------------------------------
// This software is purely theoretical and is not intended for practical use.
// This code is provided "as is" without any warranties or my support.
// ------------------------------[ TARGET MCU ]------------------------------
// Clock speed: 512kHz | Memory: 64KB Flash, 6KB RAM
// ---------------------------------[ LICENSE ]---------------------------------
// This code is licensed under the MIT License.
// ----------------------------------[ AUTHOR ]----------------------------------
// Author: Radoslaw00 | Discord: ideqe
// ---------------------------------[ INCLUDES ]---------------------------------
#include <stdio.h>					// Standard I/O
#include <stdint.h>					// Fixed-width integers
#include "hardware/tmr.h"			// TMR simulation header
#include "clock/clock.h"			// Clock module header
// --------------------------------[ CONSTANTS ]--------------------------------
#define SIM_CYCLES 100				// Run 100 simulation cycles
#define LOOP_PERIOD_MS 100			// 100ms deterministic loop
// ------------------------------[ MAIN FUNCTION ]------------------------------
int main(void) {					// Simulation entry point
	printf("=== GOMP-SCFS TMR Simulation ===\n");
	printf("Running %d cycles at %dms period\n\n", SIM_CYCLES, LOOP_PERIOD_MS);

	clock_init();					// Initialize clock

	GOMP_State stateA, stateB, stateC;	// Create 3 independent states
	gomp_state_init(&stateA);		// Init state A
	gomp_state_init(&stateB);		// Init state B
	gomp_state_init(&stateC);		// Init state C

	double sim_altitude = 400000.0;	// Simulation altitude
	double sim_velocity = 7700.0;	// Simulation velocity
	double sim_fuel = 20000.0;		// Simulation fuel

// ---------------------------[ SIMULATION LOOP ]---------------------------
	for (uint32_t cycle = 0; cycle < SIM_CYCLES; cycle++) {
		uint32_t start_ms = clock_get_ms();		// Mark start time

		TMR_Input input;			// Create input structure
		input.altitude_m = sim_altitude;
		input.velocity_mps = sim_velocity;
		input.fuel_kg = sim_fuel;
		input.dry_mass_kg = 78000.0;
		input.cycle_count = cycle;

		TMR_Input inputA = input;	// Copy input for A
		TMR_Input inputB = input;	// Copy input for B
		TMR_Input inputC = input;	// Copy input for C

		inject_fault_input(&inputB, 1, cycle);	// Inject input fault to B if scheduled

		TMR_Output outA = gomp_step(&stateA, &inputA);	// Run instance A
		TMR_Output outB = gomp_step(&stateB, &inputB);	// Run instance B
		TMR_Output outC = gomp_step(&stateC, &inputC);	// Run instance C

		inject_fault_output(&outB, 1, cycle);	// Inject output fault to B if scheduled

		TMR_Output final = vote(&outA, &outB, &outC);	// Perform majority vote

		if (final.command == CMD_BURN) {		// Apply voted command
			sim_velocity += final.delta_v_mps;	// Update velocity
			sim_fuel -= final.fuel_used_kg;		// Consume fuel
			if (sim_fuel < 0) sim_fuel = 0;		// Clamp fuel
		}

		if (cycle % 10 == 0 || cycle == 50) {	// Print status
			printf("Cycle %3d: Alt=%.0fm, Vel=%.1fm/s, Fuel=%.1fkg, Cmd=%d\n",
				cycle, sim_altitude, sim_velocity, sim_fuel, final.command);

			if (outA.command != outB.command || outB.command != outC.command) {
				printf("  >>> FAULT DETECTED: A=%d, B=%d, C=%d -> Voted=%d\n",
					outA.command, outB.command, outC.command, final.command);
			}
		}

		uint32_t elapsed = clock_get_ms() - start_ms;	// Calculate elapsed time
		if (elapsed < LOOP_PERIOD_MS) {
			clock_sleep_ms(LOOP_PERIOD_MS - elapsed);	// Maintain loop rate
		}
	}								// End of loop

	printf("\n=== Simulation Complete ===\n");
	printf("Final: Alt=%.0fm, Vel=%.1fm/s, Fuel=%.1fkg\n",
		sim_altitude, sim_velocity, sim_fuel);

	return 0;						// Exit success
}									// End of main
// ------------------------------[ END OF FILE ]------------------------------
