#include "sensors_registers.h"

//Simulated values
static double temp_sensor_value = 177.0;		//Temperature in Celsius (irrelevant)
static double radio_alt_value = 400000.0;		//Radio Altimeter Altitude in meters
static double irs_vel_value = 7700.0;			//Inertial Reference System velocity in m/s
static double fuel_mass_value = 20000.0;		//Kilograms

//Map the addresses to these internal values
double* TEMP_SENSOR_REG = &temp_sensor_value;
double* RADIO_ALT_REG = &radio_alt_value;
double* IRS_VEL_REG = &irs_vel_value;
double* FUEL_MASS_REG = &fuel_mass_value;
