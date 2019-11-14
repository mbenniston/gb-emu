#ifndef GBEMU_REGISTERS
#define GBEMU_REGISTERS

#include "types.h"

typedef struct 
{
    union  { lbyte AF; struct { byte A, F; }; };
    union  { lbyte BC; struct { byte B, C; }; };
    union  { lbyte DE; struct { byte D, E; }; };
    union  { lbyte HL; struct { byte H, L; }; };
    lbyte SP;
    lbyte PC;
} RegisterBank;


#endif 