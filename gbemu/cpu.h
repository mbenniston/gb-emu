#ifndef GBEMU_CPU_H
#define GBEMU_CPU_H

#include "bus.h"
#include "registers.h"

typedef struct {
  registers_t registers;
  int ime;
  int halted;
} cpu_t;

void cpu_create(cpu_t *cpu);

void cpu_tick(cpu_t *cpu, bus_t *bus, int *machine_cycles_elapsed);

void cpu_print(cpu_t *cpu);

#endif
