# GOMP-SCFS
Generic Orbital Maneuver Planner - Shuttle-Class Flight Subsystem

!!!     This is a documentation file of GOMP-SCFS     !!!

# Main idea
GOMP-SCFS is a C-based project that aims to create a generic orbital maneuver planner inspired by the Shuttle-Class Flight Subsystem.
The project focuses on developing a modular and extensible codebase that can be used for orbital maneuvers for LEO spacecraft.

# Project Structure
GOMP-SCFS/
    /src
        main.c
            /math
                math.c
                math.h
            /sensors
                sensors.c
                sensors.h
                sensors_register.c
                sensors_register.h
            /telemetry
                telemetry.c
                telemetry.h
                output.c
                output.h
            /plan
                att.c
                att.h
                orbit.c
                orbit.h

# C files functions

main.c ->                               loop / orchestrator
att.c ->                        maneuver & attitude planner
math.c ->                                 pure math helpers
sensors.c ->                         spacecraft state input
telemetry.c ->                      gather data for logging
orbit.c ->                      orbit-specific calculations
sensors_register.c ->                      mock sensor data
output.c ->                         display data to console
                                                          
# Header files functions                                  
math.h ->                          math helpers declarations
att.h ->            maneuver & attitude planner declarations
sensors.h ->             spacecraft state input declarations
telemetry.h ->                        telemetry declarations
orbit.h ->          orbit-specific calculations declarations
sensors_register.h ->          mock sensor data declarations
output.h ->             display data to console declarations