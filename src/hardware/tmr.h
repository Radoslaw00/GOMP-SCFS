// ------------------------------[ tmr.h ]------------------------------
//  TMR (Triple Modular Redundancy) simulation header.
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
#ifndef TMR_H
#define TMR_H
// ---------------------------------[ INCLUDES ]---------------------------------
#include <stdint.h>					// Fixed-width integer types
// --------------------------------[ COMMAND ENUM ]--------------------------------
typedef enum {						// Command types from flight software
	CMD_NONE = 0,					// No command
	CMD_BURN,						// Execute burn
	CMD_ALIGN,						// Align attitude
	CMD_IDLE						// Idle mode
} CommandType;
// --------------------------------[ INPUT STRUCT ]--------------------------------
typedef struct {					// Input data for GOMP instances
	double altitude_m;				// Altitude in meters
	double velocity_mps;			// Velocity in m/s
	double fuel_kg;					// Fuel mass in kg
	double dry_mass_kg;				// Dry mass in kg
	uint32_t cycle_count;			// Simulation cycle counter
} TMR_Input;
// --------------------------------[ OUTPUT STRUCT ]--------------------------------
typedef struct {					// Output control commands
	CommandType command;			// Requested command
	double thruster_duration_s;		// Thruster firing duration
	double delta_v_mps;				// Requested delta-v
	double fuel_used_kg;			// Fuel consumed
} TMR_Output;
// --------------------------------[ STATE STRUCT ]--------------------------------
typedef struct {					// Internal state of GOMP instance
	double position_m;				// Current position/altitude
	double velocity_mps;			// Current velocity
	double fuel_kg;					// Remaining fuel
	uint8_t state;					// State machine state
} GOMP_State;
// --------------------------------[ FUNCTION PROTOTYPES ]--------------------------------
TMR_Output gomp_step(GOMP_State* state, const TMR_Input* input);
									// Run one simulation step
void gomp_state_init(GOMP_State* state);	// Initialize state
TMR_Output vote(const TMR_Output* outA, const TMR_Output* outB, const TMR_Output* outC);
									// Perform majority voting
void inject_fault_input(TMR_Input* input, uint8_t instance_id, uint32_t cycle);
									// Inject input fault
void inject_fault_output(TMR_Output* output, uint8_t instance_id, uint32_t cycle);
									// Inject output fault
// ---------------------------------[ END HEADER GUARD ]---------------------------------
#endif
// ------------------------------[ END OF FILE ]------------------------------
