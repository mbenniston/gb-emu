#ifndef GBEMU_INSTRUCTIONS_H
#define GBEMU_INSTRUCTIONS_H

#include "types.h"

typedef struct 
{
    const char* name;
    //function pointer to handler
} Instruction;

static const Instruction instruction_set[] = {
    [0x30] = (Instruction){"SWAP B"},
    [0x31] = (Instruction){"SWAP C"}
};  


#endif
