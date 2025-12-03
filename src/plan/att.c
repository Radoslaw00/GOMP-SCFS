/*Plan orbital maneuvers (Hohmann, plane changes, circularization, deorbit burns)
Compute delta-v, burn timing, fuel requirements
Check maneuver feasibility / constraints
Return structured maneuver plan*/

//Current TODOs:
// TODO: handle insufficient fuel case						--just will send telemetry
// TODO: add telemetry packet when maneuver is computed
// TODO: implement plane change delta-v calculations
// TODO: add circularization maneuver support
// TODO: refine attitude update execution logic
// TODO: start working on telemetry output

//INCLUDES
#include "plan/att.h"
#include "sensors/sensors.h"
#include "math/math.h"
#include "plan/orbit.h"
#include "telemetry/telemetry.h"  // include telemetry

void plan_orbital_maneuver(double r_initial, double r_target, double isp_seconds) {
    double dry_mass = get_dry_mass();
    double fuel_mass = get_fuel_mass();
    double total_mass = dry_mass + fuel_mass;

    double current_velocity = get_velocity();
    double current_altitude = get_radio_altitude();

    double delta_v_need = delta_v_hohmann(r_initial, r_target);
    double fraction_required = mass_fraction(delta_v_need, isp_seconds);
    double fuel_required = fraction_required * total_mass;

    //Check feasibility
    double fuel_used = fuel_required;
    if (fuel_used > fuel_mass) {
        fuel_used = fuel_mass; // limit to available fuel
        // TODO: handle insufficient fuel, just send telemetry
    }

    execute_attitude_update(0.0, 10.0, 0.0);
    update_fuel_mass(fuel_used);

    collect_telemetry_data(delta_v_need, fuel_used, current_altitude, current_velocity);
}

// --- Functions moved outside ---
void execute_attitude_update(double pitch_degrees, double roll_degrees, double yaw_degrees) {
    double pitch_radians = deg_to_rad(pitch_degrees);
    double roll_radians = deg_to_rad(roll_degrees);
    double yaw_radians = deg_to_rad(yaw_degrees);
    // TODO: implement real attitude update
}

void update_fuel_mass(double fuel_used) {
    double current_fuel = get_fuel_mass();
    double new_fuel_mass;
    if (fuel_used > current_fuel) {
        new_fuel_mass = 0;
    }
    else {
        new_fuel_mass = current_fuel - fuel_used;
    }
    *FUEL_MASS_REG = new_fuel_mass;
}
