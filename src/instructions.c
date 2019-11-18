#include "../include/instructions.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
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

int inst_ld_a_ahl(CPU* cpu, void* data) { cpu->registers.A = Memory_Read_byte(&cpu->memory, cpu->registers.HL); return 8; }
int inst_ld_b_ahl(CPU* cpu, void* data) { cpu->registers.B = Memory_Read_byte(&cpu->memory, cpu->registers.HL); return 8; }
int inst_ld_c_ahl(CPU* cpu, void* data) { cpu->registers.C = Memory_Read_byte(&cpu->memory, cpu->registers.HL); return 8; }
int inst_ld_d_ahl(CPU* cpu, void* data) { cpu->registers.D = Memory_Read_byte(&cpu->memory, cpu->registers.HL); return 8; }
int inst_ld_e_ahl(CPU* cpu, void* data) { cpu->registers.E = Memory_Read_byte(&cpu->memory, cpu->registers.HL); return 8; }
int inst_ld_h_ahl(CPU* cpu, void* data) { cpu->registers.H = Memory_Read_byte(&cpu->memory, cpu->registers.HL); return 8; }
int inst_ld_l_ahl(CPU* cpu, void* data) { cpu->registers.L = Memory_Read_byte(&cpu->memory, cpu->registers.HL); return 8; }

int inst_ld_a_abc(CPU* cpu, void* data) { cpu->registers.A = Memory_Read_byte(&cpu->memory, cpu->registers.BC); return 8; }
int inst_ld_a_ade(CPU* cpu, void* data) { cpu->registers.A = Memory_Read_byte(&cpu->memory, cpu->registers.DE); return 8; }
int inst_ld_a_ann(CPU* cpu, void* data) { cpu->registers.A = Memory_Read_byte(&cpu->memory, *(lbyte*)data); return 16; }


int inst_ld_abc_a(CPU* cpu, void* data) { Memory_Write_byte(&cpu->memory, cpu->registers.BC, cpu->registers.A); return 8; } 
int inst_ld_ade_a(CPU* cpu, void* data) { Memory_Write_byte(&cpu->memory, cpu->registers.DE, cpu->registers.A); return 8; } 
int inst_ld_ann_a(CPU* cpu, void* data) { Memory_Write_byte(&cpu->memory, *(lbyte*)data, cpu->registers.A); return 16; } 
int inst_ld_ahl_a(CPU* cpu, void* data) { Memory_Write_byte(&cpu->memory, cpu->registers.HL, cpu->registers.A); return 8;} 
int inst_ld_ahl_b(CPU* cpu, void* data) { Memory_Write_byte(&cpu->memory, cpu->registers.HL, cpu->registers.B); return 8;} 
int inst_ld_ahl_c(CPU* cpu, void* data) { Memory_Write_byte(&cpu->memory, cpu->registers.HL, cpu->registers.C); return 8;} 
int inst_ld_ahl_d(CPU* cpu, void* data) { Memory_Write_byte(&cpu->memory, cpu->registers.HL, cpu->registers.D); return 8;} 
int inst_ld_ahl_e(CPU* cpu, void* data) { Memory_Write_byte(&cpu->memory, cpu->registers.HL, cpu->registers.E); return 8;} 
int inst_ld_ahl_h(CPU* cpu, void* data) { Memory_Write_byte(&cpu->memory, cpu->registers.HL, cpu->registers.H); return 8;} 
int inst_ld_ahl_l(CPU* cpu, void* data) { Memory_Write_byte(&cpu->memory, cpu->registers.HL, cpu->registers.L); return 8;} 
int inst_ld_ahl_ib(CPU* cpu, void* data) { Memory_Write_byte(&cpu->memory, cpu->registers.HL, *(byte*)data); return 12;} 

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
    return 8;
}

int inst_ld_b_ib(CPU* cpu, void* data) {cpu->registers.B = *(byte*)data; return 8; } 
int inst_ld_c_ib(CPU* cpu, void* data) {cpu->registers.C = *(byte*)data; return 8; } 
int inst_ld_d_ib(CPU* cpu, void* data) {cpu->registers.D = *(byte*)data; return 8; } 
int inst_ld_e_ib(CPU* cpu, void* data) {cpu->registers.E = *(byte*)data; return 8; } 
int inst_ld_h_ib(CPU* cpu, void* data) {cpu->registers.H = *(byte*)data; return 8; } 
int inst_ld_l_ib(CPU* cpu, void* data) {cpu->registers.L = *(byte*)data; return 8; } 

int inst_nop(CPU* cpu, void* data)
{
    return 4;    
}

int inst_stop(CPU* cpu, void* data) 
{
    cpu_Stopped = true;
    return 4;
}

int inst_cpl(CPU* cpu, void* data)
{
    cpu->registers.A = ~cpu->registers.A;
    flags_SetN(&cpu->registers.F);
    flags_SetH(&cpu->registers.F);
    return 4;
}

int inst_ccf(CPU* cpu, void* data)
{
    cpu->registers.A = ~cpu->registers.A;
    if(flags_IsC(cpu->registers.F)) 
        flags_ResetC(&cpu->registers.F);
    else 
        flags_SetC(&cpu->registers.F);
    
    flags_ResetH(&cpu->registers.F);
    flags_ResetN(&cpu->registers.F);

    return 4;
}

int inst_scf(CPU* cpu, void* data)
{
    flags_ResetH(&cpu->registers.F);
    flags_ResetN(&cpu->registers.F);
    flags_SetC(&cpu->registers.F);

    return 4;
}

int inst_jp_nn(CPU* cpu, void* data)
{
    cpu->registers.PC = *(lbyte*)data;
    return 12;
}

void stack_push(CPU* cpu, lbyte data)
{
    byte low_byte = data & 0xFF, high_byte = data >> 8;
    cpu->registers.SP--;
    Memory_Write_byte(&cpu->memory, cpu->registers.SP, low_byte);
    cpu->registers.SP--;
    Memory_Write_byte(&cpu->memory, cpu->registers.SP, high_byte);
}

lbyte stack_pop(CPU* cpu)
{
    byte low_byte, high_byte;
    high_byte = Memory_Read_byte(&cpu->memory, cpu->registers.SP);
    cpu->registers.SP++;
    low_byte = Memory_Read_byte(&cpu->memory, cpu->registers.SP);
    cpu->registers.SP++;
    return low_byte + (high_byte << 8);
}

int inst_push_af(CPU* cpu, void* data) { stack_push(cpu, cpu->registers.AF); return 16; }
int inst_push_bc(CPU* cpu, void* data) { stack_push(cpu, cpu->registers.BC); return 16; }
int inst_push_de(CPU* cpu, void* data) { stack_push(cpu, cpu->registers.DE); return 16; }
int inst_push_hl(CPU* cpu, void* data) { stack_push(cpu, cpu->registers.HL); return 16; }

int inst_pop_af(CPU* cpu, void* data) { cpu->registers.AF = stack_pop(cpu); return 12; }
int inst_pop_bc(CPU* cpu, void* data) { cpu->registers.BC = stack_pop(cpu); return 12; }
int inst_pop_de(CPU* cpu, void* data) { cpu->registers.DE = stack_pop(cpu); return 12; }
int inst_pop_hl(CPU* cpu, void* data) { cpu->registers.HL = stack_pop(cpu); return 12; }

void and_a(CPU* cpu, byte b)
{
    cpu->registers.A &= b;
    if(cpu->registers.A == 0) flags_SetZ(&cpu->registers.F); else flags_ResetZ(&cpu->registers.F);
    flags_ResetN(&cpu->registers.F);
    flags_SetH(&cpu->registers.F);
    flags_ResetC(&cpu->registers.F);
}

int inst_and_a(CPU* cpu, void* data) { and_a(cpu, cpu->registers.A); return 4; }
int inst_and_b(CPU* cpu, void* data) { and_a(cpu, cpu->registers.B); return 4; }
int inst_and_c(CPU* cpu, void* data) { and_a(cpu, cpu->registers.C); return 4; }
int inst_and_d(CPU* cpu, void* data) { and_a(cpu, cpu->registers.D); return 4; }
int inst_and_e(CPU* cpu, void* data) { and_a(cpu, cpu->registers.E); return 4; }
int inst_and_h(CPU* cpu, void* data) { and_a(cpu, cpu->registers.H); return 4; }
int inst_and_l(CPU* cpu, void* data) { and_a(cpu, cpu->registers.L); return 4; }
int inst_and_ahl(CPU* cpu, void* data) { and_a(cpu, Memory_Read_byte(&cpu->memory, cpu->registers.HL)); return 8; }
int inst_and_ib(CPU* cpu, void* data) { and_a(cpu, *(byte*)data); return 8; }


void or_a(CPU* cpu, byte b)
{
    cpu->registers.A |= b;
    if(cpu->registers.A == 0) flags_SetZ(&cpu->registers.F); else flags_ResetZ(&cpu->registers.F);
    flags_ResetN(&cpu->registers.F);
    flags_ResetH(&cpu->registers.F);
    flags_ResetC(&cpu->registers.F);
}

int inst_or_a(CPU* cpu, void* data) { or_a(cpu, cpu->registers.A); return 4; }
int inst_or_b(CPU* cpu, void* data) { or_a(cpu, cpu->registers.B); return 4; }
int inst_or_c(CPU* cpu, void* data) { or_a(cpu, cpu->registers.C); return 4; }
int inst_or_d(CPU* cpu, void* data) { or_a(cpu, cpu->registers.D); return 4; }
int inst_or_e(CPU* cpu, void* data) { or_a(cpu, cpu->registers.E); return 4; }
int inst_or_h(CPU* cpu, void* data) { or_a(cpu, cpu->registers.H); return 4; }
int inst_or_l(CPU* cpu, void* data) { or_a(cpu, cpu->registers.L); return 4; }
int inst_or_ahl(CPU* cpu, void* data) { or_a(cpu, Memory_Read_byte(&cpu->memory, cpu->registers.HL)); return 8; }
int inst_or_ib(CPU* cpu, void* data) { or_a(cpu, *(byte*)data); return 8; }

void xor_a(CPU* cpu, byte b)
{
    cpu->registers.A ^= b;
    if(cpu->registers.A == 0) flags_SetZ(&cpu->registers.F); else flags_ResetZ(&cpu->registers.F);
    flags_ResetN(&cpu->registers.F);
    flags_ResetH(&cpu->registers.F);
    flags_ResetC(&cpu->registers.F);
}

int inst_xor_a(CPU* cpu, void* data) { xor_a(cpu, cpu->registers.A); return 4; }
int inst_xor_b(CPU* cpu, void* data) { xor_a(cpu, cpu->registers.B); return 4; }
int inst_xor_c(CPU* cpu, void* data) { xor_a(cpu, cpu->registers.C); return 4; }
int inst_xor_d(CPU* cpu, void* data) { xor_a(cpu, cpu->registers.D); return 4; }
int inst_xor_e(CPU* cpu, void* data) { xor_a(cpu, cpu->registers.E); return 4; }
int inst_xor_h(CPU* cpu, void* data) { xor_a(cpu, cpu->registers.H); return 4; }
int inst_xor_l(CPU* cpu, void* data) { xor_a(cpu, cpu->registers.L); return 4; }
int inst_xor_ahl(CPU* cpu, void* data) { xor_a(cpu, Memory_Read_byte(&cpu->memory, cpu->registers.HL)); return 8; }
int inst_xor_ib(CPU* cpu, void* data) { xor_a(cpu, *(byte*)data); return 8; }