#ifndef SENSORS_REGISTERS_H
#define SENSORS_REGISTERS_H

//Fake hardware addresses
#define TEMP_SENSOR_ADDR       0x0004801		//Temperature sensor
#define RADIO_ALT_ADDR         0x0078324		//Radio altimeter
#define IRS_VEL_ADDR           0x0287301		//Inertial Reference System velocity
#define FUEL_MASS_ADDR         0x0740504		//Kilograms of fuel

//Mapped sensor memory
extern double* TEMP_SENSOR_REG;
extern double* RADIO_ALT_REG;
extern double* IRS_VEL_REG;
extern double* FUEL_MASS_REG;

#endif
