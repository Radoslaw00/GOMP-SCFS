//main purpose of math.c: provide mathematical functions
//for orbital mechanics calculations
//------------------------------------------------------------//
//	DONE;	Orbit-related math: radius, velocity, vis-viva	  //
//	DONE;	Delta-v formulas								  //
//	DONE;	Fuel/mass fraction formulas						  //
//	DONE;	Trig, sqrt, pow — via math.h					  //
//------------------------------------------------------------//

//INCLUDES
#include <math.h>
#include "math/math.h"

//math.h definitions
//#define EARTH_RADIUS_M 6371000.0      --meters
//#define EARTH_G 9.80665               --m/s^2 at sea level
//#define EARTH_MU 3.986004418e14       --m^3/s^2, standard gravitational parameter

//Functions for orbital mechanics calculations

//Calculate orbit radius from altitude
double orbit_radius(double altitude_meters) {
	return Earth_radius_meters + altitude_meters;
}
//Calculate orbital velocity at given radius
double orbital_velocity(double radius_meters) {
	return sqrt(Earth_mu / radius_meters);
}
//Calculate velocity using vis-viva equation
double vis_viva_velocity(double radius_meters, double semi_major_axis_meters) {
	return sqrt(Earth_mu * ((2.0 / radius_meters) - (1.0 / semi_major_axis_meters)));
}
//Calculate delta-v for Hohmann transfer between two circular orbits
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
//Calculate mass fraction using Tsiolkovsky rocket equation
double mass_fraction(double delta_v, double isp_seconds) {
	const double g0 = Earth_g;
	return 1.0 - exp(-delta_v / (isp_seconds * g0));
}

//Angle conversion functions

//Convert degrees to radians
double deg_to_rad(double degrees) {
	return degrees * (M_PI / 180.0);
}

//Convert radians to degrees
double rad_to_deg(double radians) {
	return radians * (180.0 / M_PI);
}

//Function for fuel/mass calculations
double fuel_mass_fraction(double delta_v, double isp_seconds) {
	const double g0 = Earth_g;
	return 1.0 - exp(-delta_v / (isp_seconds * g0));
}

//Clamp a value between min and max
double clamp(double value, double min, double max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}