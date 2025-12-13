// ------------------------------[ sensor_registers.h ]------------------------------
//  Sensor registers header - simulated hardware memory-mapped registers.
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
#ifndef SENSORS_REGISTERS_H
#define SENSORS_REGISTERS_H
// --------------------------------[ FAKE HARDWARE ADDRESSES ]--------------------------------
// In real embedded systems, these would be actual hardware memory addresses
#define TEMP_SENSOR_ADDR       0x0004801	// Temperature sensor address
#define RADIO_ALT_ADDR         0x0078324	// Radio altimeter address
#define IRS_VEL_ADDR           0x0287301	// Inertial Reference System velocity address
#define FUEL_MASS_ADDR         0x0740504	// Fuel mass sensor address
#define DRY_MASS_ADDR          0x0740600	// Dry mass configuration address
// --------------------------------[ MAPPED SENSOR MEMORY ]--------------------------------
// Extern pointers to simulated hardware registers
extern double* TEMP_SENSOR_REG;				// Temperature sensor register
extern double* RADIO_ALT_REG;				// Radio altimeter register
extern double* IRS_VEL_REG;					// IRS velocity register
extern double* FUEL_MASS_REG;				// Fuel mass register
extern double* DRY_MASS_REG;				// Dry mass register
// ---------------------------------[ END HEADER GUARD ]---------------------------------
#endif
// ------------------------------[ END OF FILE ]------------------------------
