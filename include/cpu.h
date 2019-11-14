#ifndef GBEMU_CPU_H
#define GBEMU_CPU_H
#include "memory.h"
#include "registers.h"

typedef struct {
    RegisterBank registers;
    Memory memory;
} CPU;

#endif
