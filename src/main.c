//The target platform: Embedded system / RAD CPU class computer

/*			!!!		MAIN EVENT LOOP		!!! 		*/

//Include necessary headers
#include "sensors/sensors.h"
#include "output/output.h"
#include "telemetry/telemetry.h"
#include "math/math.h"
#include "sensors/sensor_registers.h"
#include "plan/orbit.h"
#include "plan/att.h"
//#include "folder/header.h"	--add other headers as needed
//no libraries here

//Start the main event loop
int main(void) {
	init_sensors();											//Load sensors
	while (1) {												//Main event loop

		read_sensors();										//Read sensors
		double alttitude = get_radio_altitude();
		double velocity = get_velocity();
		double fuel = get_fuel_mass();
		double temperature = get_temperature();
		double dry_mass = get_dry_mass();
		double total_mass = dry_mass + fuel;
	}

	return 0;
}