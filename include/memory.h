#ifndef GBEMU_MEMORY_H
#define GBEMU_MEMORY_H
#include "types.h"

typedef struct {
    byte ram[0xFFFF]; 
} Memory;

void Memory_Write_byte(Memory* memory, lbyte address, byte data);
byte Memory_Read_byte(Memory* memory, lbyte address);
lbyte Memory_Read_lbyte(Memory* memory, lbyte address);

#endif