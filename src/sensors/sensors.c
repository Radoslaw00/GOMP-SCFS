//SENSORS FILE

/*Generate constant initial values
Update “dynamic” values if input or simulation is added later
Provide structured output for main.c and att.c*/

/*struct constants {
	G = 
};*/

#include "sensors/sensors.h"
#include "sensors/sensor_registers.h"

void init_sensors(void) {
        *TEMP_SENSOR_REG = 177.0;       //Temperature in °C (irrelevant)
        *RADIO_ALT_REG = 400000.0;      //Altitude in meters
		*IRS_VEL_REG = 7700.0;          //Inertial Reference System velocity in m/s
        *FUEL_MASS_REG = 20000.0;       //Fuel in kilograms
    }
  
}

void read_sensors(void) {
	//fake
}

double get_temperature(void) {
    return *TEMP_SENSOR_REG;
}

double get_radio_altitude(void) {
    return *RADIO_ALT_REG;
}

double get_velocity(void) {
    return *IRS_VEL_REG;
}

double get_fuel_mass(void) {
    return *FUEL_MASS_REG;
}