// ------------------------------[ tmr.c ]------------------------------
//  TMR (Triple Modular Redundancy) simulation logic and voter.
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
#include "hardware/tmr.h"			// TMR header
#include <string.h>					// Memset
// --------------------------------[ CONSTANTS ]--------------------------------
#define FAULT_CYCLE 50				// Cycle to inject fault
#define FAULT_INSTANCE 1			// Instance ID to fault (0=A, 1=B, 2=C)
// --------------------------------[ STATE INIT ]--------------------------------
void gomp_state_init(GOMP_State* state) {	// Initialize GOMP state
	state->position_m = 6771000.0;	// Initial radius (400km alt)
	state->velocity_mps = 7700.0;	// Initial velocity
	state->fuel_kg = 20000.0;		// Initial fuel
	state->state = 0;				// Initial state (IDLE)
}									// End of gomp_state_init
// --------------------------------[ GOMP STEP ]--------------------------------
TMR_Output gomp_step(GOMP_State* state, const TMR_Input* input) {
	TMR_Output output;				// Output structure
	memset(&output, 0, sizeof(TMR_Output));	// Clear output

	state->fuel_kg = input->fuel_kg;// Update internal fuel state

	// Simple logic for simulation purposes:
	if (input->altitude_m < 350000.0 && state->fuel_kg > 100.0) {
		output.command = CMD_BURN;			// Burn to raise orbit
		output.delta_v_mps = 5.0;			// Small delta-v
		output.thruster_duration_s = 10.0;	// 10s burn
		output.fuel_used_kg = 50.0;			// 50kg fuel
	}
	else if (input->altitude_m > 450000.0 && state->fuel_kg > 100.0) {
		output.command = CMD_BURN;			// Burn to lower orbit
		output.delta_v_mps = -5.0;			// Retrograde burn
		output.thruster_duration_s = 10.0;	// 10s burn
		output.fuel_used_kg = 50.0;			// 50kg fuel
	}
	else {
		output.command = CMD_IDLE;			// Nominal state
		output.delta_v_mps = 0.0;
		output.thruster_duration_s = 0.0;
		output.fuel_used_kg = 0.0;
	}
	return output;							// Return control output
}											// End of gomp_step
// --------------------------------[ VOTER HELPERS ]--------------------------------
static int outputs_equal(const TMR_Output* a, const TMR_Output* b) {
	if (a->command != b->command) return 0;	// Check command
	if (a->thruster_duration_s != b->thruster_duration_s) return 0; // Check duration
	double diff = a->delta_v_mps - b->delta_v_mps;	// Check delta-v
	if (diff < -0.001 || diff > 0.001) return 0;	// Tolerance for float
	return 1;								// Outputs match
}
// --------------------------------[ VOTER LOGIC ]--------------------------------
TMR_Output vote(const TMR_Output* outA, const TMR_Output* outB, const TMR_Output* outC) {
	if (outputs_equal(outA, outB)) return *outA;	// A == B -> A wins
	if (outputs_equal(outA, outC)) return *outA;	// A == C -> A wins
	if (outputs_equal(outB, outC)) return *outB;	// B == C -> B wins
	return *outA;									// Default to A if all disagree
}											// End of vote
// --------------------------------[ FAULT INJECTION ]--------------------------------
void inject_fault_input(TMR_Input* input, uint8_t instance_id, uint32_t cycle) {
	if (cycle == FAULT_CYCLE && instance_id == FAULT_INSTANCE) {
		input->altitude_m = 100000.0;		// Corrupt altitude input
	}
}

void inject_fault_output(TMR_Output* output, uint8_t instance_id, uint32_t cycle) {
	if (cycle == FAULT_CYCLE && instance_id == FAULT_INSTANCE) {
		output->command = CMD_BURN;			// Corrupt Output command
		output->delta_v_mps = 999.0;		// Absurd delta-v
		output->thruster_duration_s = 999.0;// Absurd duration
	}
}
// ------------------------------[ END OF FILE ]------------------------------
