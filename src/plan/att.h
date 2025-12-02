/*Plan orbital maneuvers (Hohmann, plane changes, circularization, deorbit burns)
Compute delta-v, burn timing, fuel requirements
Check maneuver feasibility / constraints
Return structured maneuver plan*/

//Add function prototypes for attitude control and fuel management

#ifndef ATT_H
#define ATT_H

void plan_orbital_maneuver(double r_initial, double r_target, double isp_seconds);
void execute_attitude_update(double pitch_deg, double roll_deg, double yaw_deg);
void update_fuel_mass(double fuel_used);

#endif
