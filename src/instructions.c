#include "../include/instructions.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

extern bool cpu_Stopped;

const Instruction* const Instruction_GetFromName(const char* name) 
{
    for(int i = 0; i < sizeof(instruction_set) / sizeof(Instruction); i++) {
        if(instruction_set[i].name != NULL && strncmp(instruction_set[i].name, name, strlen(instruction_set[i].name)) == 0) { 
            return &instruction_set[i]; 
        }
    }

    return NULL;
}


void swap_r(CPU* cpu, byte* b) 
{
    byte htemp = *b & 0xF0;
    *b <<= 4;
    *b |= htemp >> 4;

    flags_ResetAll(&cpu->registers.F);

    if(*b == 0) flags_SetZ(&cpu->registers.F);
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

int inst_ld_a_b(CPU* cpu, void* data) { cpu->registers.A = cpu->registers.B; return 4; }
int inst_ld_a_c(CPU* cpu, void* data) { cpu->registers.A = cpu->registers.C; return 4; }
int inst_ld_a_d(CPU* cpu, void* data) { cpu->registers.A = cpu->registers.D; return 4; }
int inst_ld_a_e(CPU* cpu, void* data) { cpu->registers.A = cpu->registers.E; return 4; }
int inst_ld_a_h(CPU* cpu, void* data) { cpu->registers.A = cpu->registers.H; return 4; }
int inst_ld_a_l(CPU* cpu, void* data) { cpu->registers.A = cpu->registers.L; return 4; }

int inst_ld_b_a(CPU* cpu, void* data) { cpu->registers.B = cpu->registers.A; return 4; }
int inst_ld_b_c(CPU* cpu, void* data) { cpu->registers.B = cpu->registers.C; return 4; }
int inst_ld_b_d(CPU* cpu, void* data) { cpu->registers.B = cpu->registers.D; return 4; }
int inst_ld_b_e(CPU* cpu, void* data) { cpu->registers.B = cpu->registers.E; return 4; }
int inst_ld_b_h(CPU* cpu, void* data) { cpu->registers.B = cpu->registers.H; return 4; }
int inst_ld_b_l(CPU* cpu, void* data) { cpu->registers.B = cpu->registers.L; return 4; }

int inst_ld_c_a(CPU* cpu, void* data) { cpu->registers.C = cpu->registers.A; return 4; }
int inst_ld_c_b(CPU* cpu, void* data) { cpu->registers.C = cpu->registers.B; return 4; }
int inst_ld_c_d(CPU* cpu, void* data) { cpu->registers.C = cpu->registers.D; return 4; }
int inst_ld_c_e(CPU* cpu, void* data) { cpu->registers.C = cpu->registers.E; return 4; }
int inst_ld_c_h(CPU* cpu, void* data) { cpu->registers.C = cpu->registers.H; return 4; }
int inst_ld_c_l(CPU* cpu, void* data) { cpu->registers.C = cpu->registers.L; return 4; }

int inst_ld_d_a(CPU* cpu, void* data) { cpu->registers.D = cpu->registers.A; return 4; }
int inst_ld_d_b(CPU* cpu, void* data) { cpu->registers.D = cpu->registers.B; return 4; }
int inst_ld_d_c(CPU* cpu, void* data) { cpu->registers.D = cpu->registers.C; return 4; }
int inst_ld_d_e(CPU* cpu, void* data) { cpu->registers.D = cpu->registers.E; return 4; }
int inst_ld_d_h(CPU* cpu, void* data) { cpu->registers.D = cpu->registers.H; return 4; }
int inst_ld_d_l(CPU* cpu, void* data) { cpu->registers.D = cpu->registers.L; return 4; }

int inst_ld_e_a(CPU* cpu, void* data) { cpu->registers.E = cpu->registers.A; return 4; }
int inst_ld_e_b(CPU* cpu, void* data) { cpu->registers.E = cpu->registers.B; return 4; }
int inst_ld_e_c(CPU* cpu, void* data) { cpu->registers.E = cpu->registers.C; return 4; }
int inst_ld_e_d(CPU* cpu, void* data) { cpu->registers.E = cpu->registers.D; return 4; }
int inst_ld_e_h(CPU* cpu, void* data) { cpu->registers.E = cpu->registers.H; return 4; }
int inst_ld_e_l(CPU* cpu, void* data) { cpu->registers.E = cpu->registers.L; return 4; }

int inst_ld_h_a(CPU* cpu, void* data) { cpu->registers.H = cpu->registers.A; return 4; }
int inst_ld_h_b(CPU* cpu, void* data) { cpu->registers.H = cpu->registers.B; return 4; }
int inst_ld_h_c(CPU* cpu, void* data) { cpu->registers.H = cpu->registers.C; return 4; }
int inst_ld_h_d(CPU* cpu, void* data) { cpu->registers.H = cpu->registers.D; return 4; }
int inst_ld_h_e(CPU* cpu, void* data) { cpu->registers.H = cpu->registers.E; return 4; }
int inst_ld_h_l(CPU* cpu, void* data) { cpu->registers.H = cpu->registers.L; return 4; }

int inst_ld_l_a(CPU* cpu, void* data) { cpu->registers.L = cpu->registers.A; return 4; }
int inst_ld_l_b(CPU* cpu, void* data) { cpu->registers.L = cpu->registers.B; return 4; }
int inst_ld_l_c(CPU* cpu, void* data) { cpu->registers.L = cpu->registers.C; return 4; }
int inst_ld_l_d(CPU* cpu, void* data) { cpu->registers.L = cpu->registers.D; return 4; }
int inst_ld_l_e(CPU* cpu, void* data) { cpu->registers.L = cpu->registers.E; return 4; }
int inst_ld_l_h(CPU* cpu, void* data) { cpu->registers.L = cpu->registers.H; return 4; }

int inst_add_a_a(CPU* cpu, void* data) 
{
    cpu->registers.A += cpu->registers.A;
    //set flags
    return 4;
}

int inst_add_a_b(CPU* cpu, void* data) 
{
    cpu->registers.A += cpu->registers.B;
    //set flags
    return 4;
}

int inst_ld_a_ib(CPU* cpu, void* data)
{
    byte ib = *(byte*)data;
    cpu->registers.A = ib;
    return 4;
}

int inst_nop(CPU* cpu, void* data)
{
    return 4;    
}

int inst_stop(CPU* cpu, void* data) 
{
    cpu_Stopped = true;
    return 4;
}
