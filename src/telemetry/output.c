#include <stdio.h>
#include "telemetry/telemetry.h"
//CONSOLE OUTPUT OF TELEMETRY DATA
/*
Print nicely formatted output
Optional: ASCII tables, unit labels, warnings
Only reads structured data; does not modify spacecraft state
*/

void inform_console(void) {
	printf("Telemetry data will be displayed here:\n");
}

void output_telemetry_data(void) {
//Output the telemetry data
	printf("Telemetry Data: %s\n", data);
}

//Currently I dont need to work on the output module, so this is just a placeholder.