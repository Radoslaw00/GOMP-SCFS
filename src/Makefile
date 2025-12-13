# GOMP-SCFS Makefile
# Target Platform: Linux (VM) or Windows 10 Pro (Native)

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -I.
LDFLAGS = -lm

# Platform detection
ifeq ($(OS),Windows_NT)
	EXE_EXT = .exe
	RM = del /Q
else
	EXE_EXT =
	RM = rm -f
endif

# Main GOMP-SCFS build
GOMP_TARGET = gomp$(EXE_EXT)
GOMP_SRC = main.c clock/clock.c logic/logic.c sensors/sensors.c sensors/sensor_registers.c math/math.c

# TMR Simulation build
TMR_TARGET = tmr_sim$(EXE_EXT)
TMR_SRC = hardware/tmr_sim.c hardware/tmr.c clock/clock.c

# Default target
all: $(GOMP_TARGET) $(TMR_TARGET)

# Build main GOMP-SCFS
$(GOMP_TARGET): $(GOMP_SRC)
	$(CC) $(CFLAGS) -o $(GOMP_TARGET) $(GOMP_SRC) $(LDFLAGS)

# Build TMR simulation
$(TMR_TARGET): $(TMR_SRC)
	$(CC) $(CFLAGS) -o $(TMR_TARGET) $(TMR_SRC) $(LDFLAGS)

# Clean build artifacts
clean:
	$(RM) $(GOMP_TARGET) $(TMR_TARGET)

# Run main GOMP-SCFS
run: $(GOMP_TARGET)
	./$(GOMP_TARGET)

# Run TMR simulation
run-tmr: $(TMR_TARGET)
	./$(TMR_TARGET)

.PHONY: all clean run run-tmr
