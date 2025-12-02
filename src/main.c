//The target platform: Embedded system / RAD CPU class computer

/*			!!!		MAIN EVENT LOOP		!!! 		*/

//MAIN TODO LIST INCLUDING ALL FILES:
//Refine and check all comments that aren't in use change and do more TODO lists
//Bug and logic fixes in att.c
//Check math.c functions for correctness
//Check main att.c "Current TODOs" list and make fixes, improvements and features based on that
//Check sensors
//Check what to do in header files

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
	//do the math
	//do the orbit math
	//do the att controls
	//get telemetry data
	//output telemetry data
	//goto read_sensors (repeat infiniteley all the steps)
	return 0;
}