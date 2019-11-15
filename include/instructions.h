#ifndef GBEMU_INSTRUCTIONS_H
#define GBEMU_INSTRUCTIONS_H

#include "types.h"
#include "cpu.h"

typedef struct 
{
    const char* name;
    int(*handler)(CPU*, void*);
    //function pointer to handler
} Instruction;

int inst_swap_b(CPU* cpu, void* data);
int inst_swap_c(CPU* cpu, void* data);
int inst_swap_d(CPU* cpu, void* data);
int inst_stop(CPU* cpu, void* data);
int inst_nop(CPU* cpu, void* data);

int inst_inc_bc(CPU* cpu, void* data);
int inst_inc_de(CPU* cpu, void* data);
int inst_inc_hl(CPU* cpu, void* data);
int inst_inc_sp(CPU* cpu, void* data);
int inst_dec_bc(CPU* cpu, void* data);
int inst_dec_de(CPU* cpu, void* data);
int inst_dec_hl(CPU* cpu, void* data);
int inst_dec_sp(CPU* cpu, void* data);

static const Instruction instruction_set[] = {
    [0x00] = (Instruction){"NOP",       inst_nop},
    
    [0x30] = (Instruction){"SWAP B",    inst_swap_b},
    [0x31] = (Instruction){"SWAP C",    inst_swap_c},
    [0x32] = (Instruction){"SWAP D",    inst_swap_d},
    
    [0x10] = (Instruction){"STOP",      inst_stop}, //might be extended 0x10 0x00
    
    //INC NN
    [0x03] = (Instruction){"INC BC",    inst_inc_bc},
    [0x13] = (Instruction){"INC DE",    inst_inc_de},
    [0x23] = (Instruction){"INC HL",    inst_inc_hl},
    [0x33] = (Instruction){"INC SP",    inst_inc_sp},


    //DEC NN
    [0x0B] = (Instruction){"DEC BC",    inst_dec_bc},
    [0x1B] = (Instruction){"DEC DE",    inst_dec_de},
    [0x2B] = (Instruction){"DEC HL",    inst_dec_hl},
    [0x3B] = (Instruction){"DEC SP",    inst_dec_sp}    
};  


#endif
