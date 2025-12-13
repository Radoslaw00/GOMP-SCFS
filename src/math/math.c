// ------------------------------[ math.c ]------------------------------
//  Math module implementation - orbital mechanics calculations.
// ------------------------------[ DISCLAIMER ]------------------------------
// This software is purely theoretical and is not intended for practical use.
// This code is provided as is without any warranties or my support.
// ------------------------------[ TARGET MCU ]------------------------------
// Clock speed: 512kHz | Memory: 64KB Flash, 6KB RAM
// ---------------------------------[ LICENSE ]---------------------------------
// This code is licensed under the MIT License.
// ----------------------------------[ AUTHOR ]----------------------------------
// Author: Radoslaw00 | Discord: ideqe
// ---------------------------------[ INCLUDES ]---------------------------------
#include <math.h>
#include "math/math.h"
// --------------------------------[ ORBIT RADIUS ]--------------------------------
double orbit_radius(double altitude_meters) {
	return Earth_radius_meters + altitude_meters;
}
// --------------------------------[ ORBITAL VELOCITY ]--------------------------------
double orbital_velocity(double radius_meters) {
	return sqrt(Earth_mu / radius_meters);
}
// --------------------------------[ VIS-VIVA EQUATION ]--------------------------------
double vis_viva_velocity(double radius_meters, double semi_major_axis_meters) {
	return sqrt(Earth_mu * ((2.0 / radius_meters) - (1.0 / semi_major_axis_meters)));
}
// --------------------------------[ HOHMANN TRANSFER ]--------------------------------
double delta_v_hohmann(double r1_meters, double r2_meters) {
	double a_transfer = (r1_meters + r2_meters) / 2.0;
	double v1_initial = orbital_velocity(r1_meters);
	double v1_transfer = vis_viva_velocity(r1_meters, a_transfer);
	double v2_transfer = vis_viva_velocity(r2_meters, a_transfer);
	double v2_final = orbital_velocity(r2_meters);
	double delta_v1 = fabs(v1_transfer - v1_initial);
	double delta_v2 = fabs(v2_final - v2_transfer);
	return delta_v1 + delta_v2;
}
// --------------------------------[ MASS FRACTION ]--------------------------------
double mass_fraction(double delta_v, double isp_seconds) {
	const double g0 = Earth_g;
	return 1.0 - exp(-delta_v / (isp_seconds * g0));
}
// --------------------------------[ ANGLE CONVERSIONS ]--------------------------------
double deg_to_rad(double degrees) {
	return degrees * (M_PI / 180.0);
}
double rad_to_deg(double radians) {
	return radians * (180.0 / M_PI);
}
// --------------------------------[ FUEL MASS FRACTION ]--------------------------------
double fuel_mass_fraction(double delta_v, double isp_seconds) {
	const double g0 = Earth_g;
	return 1.0 - exp(-delta_v / (isp_seconds * g0));
}
// --------------------------------[ CLAMP ]--------------------------------
double clamp(double value, double min, double max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}
// ------------------------------[ END OF FILE ]------------------------------
