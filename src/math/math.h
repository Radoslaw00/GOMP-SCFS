// ------------------------------[ math.h ]------------------------------
//  Math module header - orbital mechanics calculations and constants.
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
#ifndef MATH_H
#define MATH_H
// --------------------------------[ EARTH CONSTANTS ]--------------------------------
#define Earth_radius_meters 6371000.0	// Radius of Earth in meters
#define Earth_mu 3.986004418e14			// Standard gravitational parameter (m^3/s^2)
#define Earth_g 9.80665					// Standard gravity at sea level (m/s^2)
// --------------------------------[ FUNCTION PROTOTYPES ]--------------------------------
// Orbit calculations
double orbit_radius(double altitude_meters);		// Calculate orbit radius from altitude
double orbital_velocity(double radius_meters);		// Calculate orbital velocity at radius
double vis_viva_velocity(double radius_meters, double semi_major_axis_meters);
													// Calculate velocity using vis-viva equation
double delta_v_hohmann(double r1_meters, double r2_meters);
													// Calculate delta-v for Hohmann transfer
// Mass/fuel calculations
double mass_fraction(double delta_v, double isp_seconds);		// Tsiolkovsky rocket equation
double fuel_mass_fraction(double delta_v, double isp_seconds);	// Calculate fuel mass fraction
// Angle conversions
double deg_to_rad(double degrees);		// Convert degrees to radians
double rad_to_deg(double radians);		// Convert radians to degrees
// Utility
double clamp(double value, double min, double max);	// Clamp value between min and max
// ---------------------------------[ END HEADER GUARD ]---------------------------------
#endif
// ------------------------------[ END OF FILE ]------------------------------