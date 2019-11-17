#ifndef GBEMU_REGISTERS
#define GBEMU_REGISTERS
#include <stdbool.h>

#include "types.h"

typedef struct 
{
    union  { lbyte AF; struct { byte F, A; }; };
    union  { lbyte BC; struct { byte C, B; }; };
    union  { lbyte DE; struct { byte E, D; }; };
    union  { lbyte HL; struct { byte L, H; }; };
    lbyte SP;
    lbyte PC;
} RegisterBank;

void flags_ResetAll(byte* f);

void flags_SetZ(byte* f);
void flags_ResetZ(byte* f);
bool flags_IsZ(byte f);

void flags_SetN(byte* f);
void flags_ResetN(byte* f);
bool flags_IsN(byte f);

void flags_SetH(byte* f);
void flags_ResetH(byte* f);
bool flags_IsH(byte f);

void flags_SetC(byte* f);
void flags_ResetC(byte* f);
bool flags_IsC(byte f);

#endif 