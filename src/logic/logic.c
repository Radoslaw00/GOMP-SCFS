// ------------------------------[ logic.c ]------------------------------
//  Logic module implementation - state machine and control logic.
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
#include "logic/logic.h"			// Logic module header
#include "sensors/sensors.h"		// Sensor interface functions
#include "math/math.h"				// Math helper functions
#include <stdio.h>					// Standard I/O for printf
// --------------------------------[ CONSTANTS ]--------------------------------
#define MIN_SAFE_ALTITUDE_M 200000.0	// 200km minimum safe altitude
#define MAX_SAFE_ALTITUDE_M 500000.0	// 500km maximum target altitude
#define FUEL_RESERVE_KG 500.0			// Keep 500kg fuel reserve
// --------------------------------[ STATE NAME LOOKUP ]--------------------------------
const char* logic_state_name(SystemState state) {	// Convert state enum to string
	switch (state) {								// Switch on state
		case STATE_INIT:		return "INIT";		// Initialization
		case STATE_IDLE:		return "IDLE";		// Idle state
		case STATE_PREP:		return "PREP";		// Preparation state
		case STATE_ALIGN:		return "ALIGN";		// Alignment state
		case STATE_BURN:		return "BURN";		// Burn state
		case STATE_POST_BURN:	return "POST_BURN";	// Post-burn verification
		case STATE_ERROR:		return "ERROR";		// Error state
		default:				return "UNKNOWN";	// Unknown state
	}
}													// End of logic_state_name
// --------------------------------[ LOGIC INIT ]--------------------------------
void logic_init(SpacecraftState* state) {			// Initialize spacecraft state
	state->altitude_m = get_radio_altitude();		// Get initial altitude from sensor
	state->velocity_mps = get_velocity();			// Get initial velocity from sensor
	state->fuel_kg = get_fuel_mass();				// Get initial fuel from sensor
	state->dry_mass_kg = get_dry_mass();			// Get dry mass from sensor
	state->pitch_rad = 0.0;							// Initial pitch angle (level)
	state->yaw_rad = 0.0;							// Initial yaw angle (level)
	state->roll_rad = 0.0;							// Initial roll angle (level)
	state->state = STATE_IDLE;						// Start in IDLE state
	state->state_timer_ms = 0;						// Reset state timer
}													// End of logic_init
// --------------------------------[ SAFETY VALIDATION ]--------------------------------
static int validate_state(SpacecraftState* state) {	// Validate state bounds
	if (state->fuel_kg < 0.0) {						// Check for negative fuel
		printf("ERROR: Negative fuel detected!\n");	// Log error
		state->fuel_kg = 0.0;						// Clamp to zero
		return 0;									// Return failure
	}
	if (state->altitude_m < MIN_SAFE_ALTITUDE_M) {	// Check altitude minimum
		printf("WARNING: Altitude below safe minimum!\n");	// Log warning
	}
	double total_mass = state->dry_mass_kg + state->fuel_kg;	// Calculate total mass
	if (total_mass < state->dry_mass_kg) {			// Check for overflow/error
		printf("ERROR: Mass calculation error!\n");	// Log error
		return 0;									// Return failure
	}
	return 1;										// Return success
}													// End of validate_state
// --------------------------------[ LOGIC RUN CYCLE ]--------------------------------
void logic_run_cycle(SpacecraftState* state, double dt) {	// Run one control cycle
	state->state_timer_ms += (uint32_t)(dt * 1000.0);		// Update state timer

	state->altitude_m = get_radio_altitude();		// Read current altitude
	state->velocity_mps = get_velocity();			// Read current velocity
	state->fuel_kg = get_fuel_mass();				// Read current fuel

	if (!validate_state(state)) {					// Validate state bounds
		state->state = STATE_ERROR;					// Enter error state on failure
	}
// --------------------------------[ STATE MACHINE ]--------------------------------
	switch (state->state) {							// Switch on current state
		case STATE_INIT:							// Initialization state
			state->state = STATE_IDLE;				// Transition to IDLE
			state->state_timer_ms = 0;				// Reset timer
			break;

		case STATE_IDLE:							// Idle state - monitor altitude
			if (state->altitude_m < MIN_SAFE_ALTITUDE_M &&
			    state->fuel_kg > FUEL_RESERVE_KG) {	// If altitude low and fuel available
				printf("TRANSITION: IDLE -> PREP (altitude low)\n");	// Log transition
				state->state = STATE_PREP;			// Transition to PREP
				state->state_timer_ms = 0;			// Reset timer
			}
			break;

		case STATE_PREP:							// Preparation state - calculate maneuver
			if (state->state_timer_ms > 500) {		// After 500ms
				printf("TRANSITION: PREP -> ALIGN\n");	// Log transition
				state->state = STATE_ALIGN;			// Transition to ALIGN
				state->state_timer_ms = 0;			// Reset timer
			}
			break;

		case STATE_ALIGN:							// Alignment state - rotate spacecraft
			if (state->state_timer_ms > 1000) {		// After 1000ms
				printf("TRANSITION: ALIGN -> BURN\n");	// Log transition
				state->state = STATE_BURN;			// Transition to BURN
				state->state_timer_ms = 0;			// Reset timer
			}
			break;

		case STATE_BURN:							// Burn state - engine firing
			if (state->state_timer_ms > 2000) {		// After 2000ms
				printf("TRANSITION: BURN -> POST_BURN\n");	// Log transition
				state->state = STATE_POST_BURN;		// Transition to POST_BURN
				state->state_timer_ms = 0;			// Reset timer
			}
			break;

		case STATE_POST_BURN:						// Post-burn state - verify results
			if (state->state_timer_ms > 500) {		// After 500ms
				printf("TRANSITION: POST_BURN -> IDLE\n");	// Log transition
				state->state = STATE_IDLE;			// Transition back to IDLE
				state->state_timer_ms = 0;			// Reset timer
			}
			break;

		case STATE_ERROR:							// Error state - safe mode
			break;									// Stay in error state
	}
}													// End of logic_run_cycle
// ------------------------------[ END OF FILE ]------------------------------
