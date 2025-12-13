// ------------------------------[ sensor_registers.c ]------------------------------
//  Sensor registers implementation - simulated hardware register storage.
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
#include "sensors/sensor_registers.h"	// Sensor registers header
// --------------------------------[ SIMULATED REGISTER VALUES ]--------------------------------
// In real hardware, these would be at fixed memory addresses
static double temp_sensor_value = 177.0;	// Temperature in Celsius
static double radio_alt_value = 400000.0;	// Altitude in meters (400km)
static double irs_vel_value = 7700.0;		// Velocity in m/s (orbital velocity)
static double fuel_mass_value = 20000.0;	// Fuel in kilograms (20 tonnes)
static double dry_mass_value = 78000.0;		// Dry mass in kilograms (78 tonnes)
// --------------------------------[ REGISTER POINTERS ]--------------------------------
// Map the extern pointers to internal storage
double* TEMP_SENSOR_REG = &temp_sensor_value;	// Temperature register pointer
double* RADIO_ALT_REG = &radio_alt_value;		// Radio altimeter register pointer
double* IRS_VEL_REG = &irs_vel_value;			// IRS velocity register pointer
double* FUEL_MASS_REG = &fuel_mass_value;		// Fuel mass register pointer
double* DRY_MASS_REG = &dry_mass_value;			// Dry mass register pointer
// ------------------------------[ END OF FILE ]------------------------------
