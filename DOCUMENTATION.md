# 📄 GOMP-SCFS Technical Documentation

> **Generic Orbital Maneuver Planner — Shuttle-Class Flight Subsystem**

## 1. System Overview

GOMP-SCFS is a flight control system designed for **Low Earth Orbit (LEO)** operations. It runs on a deterministic control loop and manages spacecraft state, orbital maneuvers, and telemetry. The architecture is modular, portable, and designed for extreme hardware constraints (512 KHz CPU, 6 KB RAM).

### 1.1 Architecture

The system follows a "Do-Measure-Wait" execution model:

1.  **Read Sensors**: Acquire altitude, velocity, fuel, and mass data.
2.  **Execute Logic**: Update state machine, calculate maneuvers, and issue commands.
3.  **Wait**: Sleep until the 100ms cycle is complete to maintain determinism.

---

## 2. Modules

### 2.1 Core (`src/main.c`)
- **Role**: Entry point and scheduler.
- **Function**: Initializes subsystems and runs the infinite 10Hz control loop.
- **Timing**: Enforces 100ms period using the `clock` module.

### 2.2 Clock (`src/clock/`)
- **Role**: Timing abstraction layer.
- **API**:
  - `clock_init()`: Initialize timer.
  - `clock_get_ms()`: Get uptime in milliseconds.
  - `clock_sleep_ms(ms)`: Blocking delay.
- **Portability**:
  - **Windows**: Uses `QueryPerformanceCounter`.
  - **Linux**: Uses `clock_gettime`.
  - **Embedded**: Designed to wrap hardware timers (e.g., SysTick).

### 2.3 Logic (`src/logic/`)
- **Role**: Decision making and state management.
- **State Machine**:
  - `STATE_IDLE`: Nominal orbit keeping.
  - `STATE_PREP`: Calculating burn parameters.
  - `STATE_ALIGN`: Orienting spacecraft.
  - `STATE_BURN`: Firing thrusters.
  - `STATE_POST_BURN`: Verifying maneuver result.
- **Structs**: `SpacecraftState` (optimized for RAM).

### 2.4 Math (`src/math/`)
- **Role**: Orbital mechanics library.
- **Functions**:
  - `orbit_radius(alt)`: $r = R_E + h$
  - `orbital_velocity(r)`: $v = \sqrt{\mu/r}$
  - `vis_viva_velocity(r, a)`: Vis-viva equation.
  - `delta_v_hohmann(r1, r2)`: Total $\Delta v$ for transfer.
  - `mass_fraction(dv, isp)`: Tsiolkovsky rocket equation.

### 2.5 Sensors (`src/sensors/`)
- **Role**: Hardware abstraction for sensors.
- **Implementation**: Uses memory-mapped style global registers (`sensor_registers.c`) to simulate hardware interaction.
- **Data Points**: Radar Altitude, IRS Velocity, Fuel Mass, Dry Mass.

### 2.6 TMR Hardware (`src/hardware/`)
- **Role**: Fault tolerance simulation.
- **Components**:
  - **TMR_Input**: Sensor data passed to instances.
  - **TMR_Output**: Commands returned by instances.
  - **Voter**: Compares 3 outputs and selects the majority.
  - **Fault Injection**: Deliberately corrupts data to test resilience.

---

## 3. Triple Modular Redundancy (TMR)

The system includes a simulation of **Triple Modular Redundancy** to demonstrate reliability in high-radiation environments.

### 3.1 Concept
Three identical instances of the GOMP logic (`Instance A`, `Instance B`, `Instance C`) run in parallel. Their outputs are fed into a **Voter**, which determines the final command.

### 3.2 Fault Scenario
The simulation (`tmr_sim.c`) runs for 100 cycles. On **Cycle 50**, a fault is injected into **Instance B**:
- Input altitude is corrupted.
- Output command becomes nonsensical (`999.0` delta-v).
- **Result**: The Voter detects the discrepancy (`A=IDLE, B=BURN, C=IDLE`) and correctly chooses `IDLE` (A/C).

---

## 4. Building and Running

### 4.1 Prerequisites
- GCC Compiler
- Make (optional)

### 4.2 Build Commands

**Main Flight Computer:**
```bash
gcc -Wall -Wextra -I. main.c clock/clock.c logic/logic.c sensors/sensors.c sensors/sensor_registers.c math/math.c -lm -o gomp
```

**TMR Simulation:**
```bash
gcc -Wall -Wextra -I. hardware/tmr_sim.c hardware/tmr.c clock/clock.c -o tmr_sim
```

### 4.3 Execution

Run the flight computer:
```bash
./gomp
```

Run the TMR simulation:
```bash
./tmr_sim
```

---

## 5. Coding Standards

- **Language**: C99
- **Comments**: High density. Every line explains its purpose.
- **Headers**: Box style for file sections (`// ---[ SECTION ]---`).
- **Safety**: Explicit bounds checking (no negative fuel, min altitude).
- **Constraints**: 512kHz CPU / 6KB RAM target. Avoid dynamic allocation (`malloc`).

---

> *Documentation generated for GOMP-SCFS v1.0*