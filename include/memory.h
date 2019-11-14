#ifndef GBEMU_MEMORY_H
#define GBEMU_MEMORY_H
#include "types.h"

typedef struct {
    byte ram[0xFFFF]; 
} Memory;

#endif