#include "../include/instructions.h"
#include <stdbool.h>

extern bool cpu_Stopped;

void swap_r(CPU* cpu, byte* b) 
{
    byte htemp = *b & 0xF0;
    *b <<= 4;
    *b |= htemp >> 4;

    //update flags
}

void inc_rl(lbyte* b) 
{
    (*b)++;
    //no flags affected
} 

void dec_rl(lbyte* b) 
{
    (*b)--;
    //no flags affected
} 

int inst_swap_b(CPU* cpu, void* data) { swap_r(cpu, &cpu->registers.B); return 4; }
int inst_swap_c(CPU* cpu, void* data) { swap_r(cpu, &cpu->registers.C); return 4; }
int inst_swap_d(CPU* cpu, void* data) { swap_r(cpu, &cpu->registers.D); return 4; }
int inst_swap_e(CPU* cpu, void* data) { swap_r(cpu, &cpu->registers.E); return 4; }

int inst_inc_bc(CPU* cpu, void* data) { inc_rl(&cpu->registers.BC); return 8; }
int inst_inc_de(CPU* cpu, void* data) { inc_rl(&cpu->registers.DE); return 8; }
int inst_inc_hl(CPU* cpu, void* data) { inc_rl(&cpu->registers.HL); return 8; }
int inst_inc_sp(CPU* cpu, void* data) { inc_rl(&cpu->registers.SP); return 8; }

int inst_dec_bc(CPU* cpu, void* data) { dec_rl(&cpu->registers.BC); return 8; }
int inst_dec_de(CPU* cpu, void* data) { dec_rl(&cpu->registers.DE); return 8; }
int inst_dec_hl(CPU* cpu, void* data) { dec_rl(&cpu->registers.HL); return 8; }
int inst_dec_sp(CPU* cpu, void* data) { dec_rl(&cpu->registers.SP); return 8; }

int inst_nop(CPU* cpu, void* data)
{
    return 4;    
}

int inst_stop(CPU* cpu, void* data) 
{
    cpu_Stopped = true;
    return 4;
}
