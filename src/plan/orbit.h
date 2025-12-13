// ------------------------------[ orbit.h ]------------------------------
//  Orbit module header - orbit prediction and propagation.
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
#ifndef ORBIT_H
#define ORBIT_H
// --------------------------------[ FUNCTION PROTOTYPES ]--------------------------------
// Placeholder for future orbital propagation logic
// Currently, math.c handles the core mechanics (radius, velocity, etc.)
// This module will handle state vector propagation over time.
void propagate_orbit(double dt);	// Advance orbit state by dt seconds
// ---------------------------------[ END HEADER GUARD ]---------------------------------
#endif
// ------------------------------[ END OF FILE ]------------------------------
