// ------------------------------[ sensors.c ]------------------------------
//  Sensors module implementation - sensor data acquisition.
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
#include "sensors/sensors.h"			// Sensors module header
#include "sensors/sensor_registers.h"	// Simulated hardware registers
// --------------------------------[ INIT SENSORS ]--------------------------------
void init_sensors(void) {				// Initialize sensors for first-time use
	*TEMP_SENSOR_REG = 177.0;			// Temperature in Celsius (irrelevant, static)
	*RADIO_ALT_REG = 400000.0;			// Altitude in meters (400km)
	*IRS_VEL_REG = 7700.0;				// Velocity in m/s (orbital velocity)
	*FUEL_MASS_REG = 20000.0;			// Fuel in kilograms (20 tonnes)
	*DRY_MASS_REG = 78000.0;			// Dry mass in kilograms (78 tonnes)
}										// End of init_sensors
// --------------------------------[ READ SENSORS ]--------------------------------
void read_sensors(void) {				// Read sensor values from hardware registers
	// In bare metal, this would read from actual hardware registers
	// For simulation, values are already in the registers
}										// End of read_sensors
// --------------------------------[ SENSOR GETTERS ]--------------------------------
double get_temperature(void) {			// Get temperature in Celsius
	return *TEMP_SENSOR_REG;			// Return value from register
}										// End of get_temperature

double get_radio_altitude(void) {		// Get altitude in meters
	return *RADIO_ALT_REG;				// Return value from register
}										// End of get_radio_altitude

double get_velocity(void) {				// Get velocity in m/s
	return *IRS_VEL_REG;				// Return value from register
}										// End of get_velocity

double get_fuel_mass(void) {			// Get fuel mass in kilograms
	return *FUEL_MASS_REG;				// Return value from register
}										// End of get_fuel_mass

double get_dry_mass(void) {				// Get dry mass in kilograms
	return *DRY_MASS_REG;				// Return value from register
}										// End of get_dry_mass
// ------------------------------[ END OF FILE ]------------------------------