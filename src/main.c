//The target platform: Embedded system with limited resources
//MAIN EVENT LOOP

//Include necessary headers
#include <sensors.h>
/*
#include
#include
#include
#include
*/

int main(void) {
//	Load sensors
	sensors();
	while (1) {
//		Read sensors
		read_sensors();
	}

	return 0;
}