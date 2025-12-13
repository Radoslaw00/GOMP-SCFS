// ------------------------------[ sensors.h ]------------------------------
//  Sensors module header - sensor interface functions.
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
#ifndef SENSORS_H
#define SENSORS_H
// --------------------------------[ FUNCTION PROTOTYPES ]--------------------------------
void init_sensors(void);			// Initialize sensors for first-time use
void read_sensors(void);			// Read sensor values from hardware registers
double get_temperature(void);		// Get temperature in Celsius
double get_radio_altitude(void);	// Get altitude in meters from radio altimeter
double get_velocity(void);			// Get velocity in m/s from IRS
double get_fuel_mass(void);			// Get fuel mass in kilograms
double get_dry_mass(void);			// Get spacecraft dry mass in kilograms
// ---------------------------------[ END HEADER GUARD ]---------------------------------
#endif
// ------------------------------[ END OF FILE ]------------------------------