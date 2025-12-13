// ------------------------------[ logic.h ]------------------------------
//  Logic module header - state machine and spacecraft state definition.
// ------------------------------[ DISCLAIMER ]------------------------------
// This software is purely theoretical and is not intended for practical use.
// This code is provided "as is" without any warranties or my support.
// ------------------------------[ TARGET MCU ]------------------------------
// Clock speed: 512kHz | Memory: 64KB Flash, 6KB RAM
// ---------------------------------[ LICENSE ]---------------------------------
// This code is licensed under the MIT License.
// ----------------------------------[ AUTHOR ]----------------------------------
// Author: Radoslaw00 | Discord: ideqe
// ---------------------------------[ HEADER GUARD ]---------------------------------
#ifndef LOGIC_H
#define LOGIC_H
// ---------------------------------[ INCLUDES ]---------------------------------
#include <stdint.h>					// Fixed-width integer types (uint32_t)
// --------------------------------[ STATE MACHINE ENUM ]--------------------------------
typedef enum {						// System states for mission phase management
	STATE_INIT = 0,					// System starting up
	STATE_IDLE,						// In stable orbit, no actions planned
	STATE_PREP,						// Calculating burn parameters
	STATE_ALIGN,					// Rotating to correct orientation
	STATE_BURN,						// Engine firing
	STATE_POST_BURN,				// Verifying results
	STATE_ERROR						// Something went wrong, safe mode
} SystemState;
// --------------------------------[ SPACECRAFT STATE STRUCT ]--------------------------------
typedef struct {					// Unified state structure for RAM efficiency
	double altitude_m;				// Current altitude in meters
	double velocity_mps;			// Current velocity in m/s
	double fuel_kg;					// Remaining fuel in kilograms
	double dry_mass_kg;				// Spacecraft dry mass in kilograms
	double pitch_rad;				// Pitch angle in radians
	double yaw_rad;					// Yaw angle in radians
	double roll_rad;				// Roll angle in radians
	SystemState state;				// Current mission state
	uint32_t state_timer_ms;		// Time spent in current state
} SpacecraftState;					// Total: ~56 bytes with double
// --------------------------------[ FUNCTION PROTOTYPES ]--------------------------------
void logic_init(SpacecraftState* state);				// Initialize state machine
void logic_run_cycle(SpacecraftState* state, double dt);// Run one control cycle
const char* logic_state_name(SystemState state);		// Get state name string
// ---------------------------------[ END HEADER GUARD ]---------------------------------
#endif
// ------------------------------[ END OF FILE ]------------------------------
