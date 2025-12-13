<p align="center">
  <h1 align="center">🚀 GOMP-SCFS</h1>
  <p align="center">
    <strong>Generic Orbital Maneuver Planner — Shuttle-Class Flight Subsystem</strong>
  </p>
  <p align="center">
    A modular, embedded C flight control system for LEO spacecraft
  </p>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=flat-square" alt="Language">
  <img src="https://img.shields.io/badge/Platform-Embedded-green?style=flat-square" alt="Platform">
  <img src="https://img.shields.io/badge/Status-In%20Development-orange?style=flat-square" alt="Status">
  <img src="https://img.shields.io/badge/License-MIT-lightgrey?style=flat-square" alt="License">
</p>

---

## 📖 Overview

GOMP-SCFS is a flight control subsystem designed for **low Earth orbit (LEO) spacecraft**. Built entirely in C, it targets resource-constrained embedded systems and implements deterministic control loops, orbital mechanics calculations, and a Triple Modular Redundancy (TMR) simulation for fault tolerance.

> *Inspired by the Space Shuttle Orbiter — technology that remains relevant decades later.*

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🕐 **Deterministic Loop** | 100ms fixed-rate control cycle (10 Hz) |
| 🧮 **Orbital Mechanics** | Hohmann transfers, vis-viva equation, Tsiolkovsky rocket equation |
| 🛡️ **TMR Simulation** | Triple Modular Redundancy with external voter and fault injection |
| 🔧 **Bare Metal Ready** | Portable clock module adaptable to MCU hardware timers |
| 📊 **State Machine** | Mission phases: `IDLE` → `PREP` → `ALIGN` → `BURN` → `POST_BURN` |

---

## 🏗️ Project Structure

```
GOMP-SCFS/
├── src/
│   ├── main.c              # Entry point & deterministic loop
│   ├── clock/              # Portable timing (Windows/Linux/Bare Metal)
│   ├── logic/              # State machine & control logic
│   ├── hardware/           # TMR simulation & fault injection
│   ├── math/               # Orbital mechanics calculations
│   ├── sensors/            # Sensor hardware abstraction
│   ├── plan/               # Orbit-specific computations
│   └── telemetry/          # Data logging (WIP)
├── README.md
├── DOCUMENTATION.md
└── LICENSE
```

---

## 🚀 Quick Start

### Prerequisites

- GCC compiler (MinGW on Windows, GCC on Linux)
- Make (optional)

### Build & Run

```bash
cd src
gcc -Wall -Wextra -I. main.c clock/clock.c logic/logic.c sensors/sensors.c sensors/sensor_registers.c math/math.c -lm -o gomp
./gomp
```

### Expected Output

```
=== GOMP-SCFS Flight Computer ===
Loop period: 100ms

Initial altitude: 400000 m
Initial velocity: 7700.0 m/s
Initial fuel: 20000.0 kg
State: IDLE

Cycle    0: Alt=400000m, Vel=7700.0m/s, Fuel=20000.0kg, State=IDLE
Cycle   10: Alt=400000m, Vel=7700.0m/s, Fuel=20000.0kg, State=IDLE
```

---

## 🛡️ TMR Simulation

Run the fault-tolerant Triple Modular Redundancy demonstration:

```bash
cd src
gcc -Wall -Wextra -I. hardware/tmr_sim.c hardware/tmr.c clock/clock.c -o tmr_sim
./tmr_sim
```

Fault injection on cycle 50 demonstrates the voter correctly identifying and discarding corrupted data.

---

## 🎯 Target Hardware

| Specification | Value |
|---------------|-------|
| **CPU** | 512 KHz |
| **RAM** | 6 KB |
| **Storage** | 64 KB |

The codebase is designed with extreme resource constraints in mind, suitable for radiation-hardened processors.

---

## 📚 Documentation

See [`DOCUMENTATION.md`](DOCUMENTATION.md) for detailed module descriptions and API reference.

---

## 🤝 Contributing

This is a personal learning project, but suggestions and feedback are welcome! Feel free to open an issue or submit a pull request.

---

## 📜 License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

---

<p align="center">
  <sub>Built with ❤️ and a passion for aerospace</sub>
</p>