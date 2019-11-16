#ifndef GBEMU_INSTRUCTIONS_H
#define GBEMU_INSTRUCTIONS_H

#include "types.h"
#include "cpu.h"

typedef struct 
{
    const char* name;
    int(*handler)(CPU*, void*);
    int numImmediates; //defaults to 0 
    //function pointer to handler
} Instruction;

const Instruction* const Instruction_GetFromName(const char* name);

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

int inst_ld_a_b(CPU* cpu, void* data);
int inst_ld_a_c(CPU* cpu, void* data);
int inst_ld_a_d(CPU* cpu, void* data);
int inst_ld_a_e(CPU* cpu, void* data);
int inst_ld_a_h(CPU* cpu, void* data);
int inst_ld_a_l(CPU* cpu, void* data);

int inst_ld_b_a(CPU* cpu, void* data);
int inst_ld_b_c(CPU* cpu, void* data);
int inst_ld_b_d(CPU* cpu, void* data);
int inst_ld_b_e(CPU* cpu, void* data);
int inst_ld_b_h(CPU* cpu, void* data);
int inst_ld_b_l(CPU* cpu, void* data);

int inst_ld_c_a(CPU* cpu, void* data);
int inst_ld_c_b(CPU* cpu, void* data);
int inst_ld_c_d(CPU* cpu, void* data);
int inst_ld_c_e(CPU* cpu, void* data);
int inst_ld_c_h(CPU* cpu, void* data);
int inst_ld_c_l(CPU* cpu, void* data);

int inst_ld_d_a(CPU* cpu, void* data);
int inst_ld_d_b(CPU* cpu, void* data);
int inst_ld_d_c(CPU* cpu, void* data);
int inst_ld_d_e(CPU* cpu, void* data);
int inst_ld_d_h(CPU* cpu, void* data);
int inst_ld_d_l(CPU* cpu, void* data);

int inst_ld_e_a(CPU* cpu, void* data);
int inst_ld_e_b(CPU* cpu, void* data);
int inst_ld_e_c(CPU* cpu, void* data);
int inst_ld_e_d(CPU* cpu, void* data);
int inst_ld_e_h(CPU* cpu, void* data);
int inst_ld_e_l(CPU* cpu, void* data);

int inst_ld_h_a(CPU* cpu, void* data);
int inst_ld_h_b(CPU* cpu, void* data);
int inst_ld_h_c(CPU* cpu, void* data);
int inst_ld_h_d(CPU* cpu, void* data);
int inst_ld_h_e(CPU* cpu, void* data);
int inst_ld_h_l(CPU* cpu, void* data);

int inst_ld_l_a(CPU* cpu, void* data);
int inst_ld_l_b(CPU* cpu, void* data);
int inst_ld_l_c(CPU* cpu, void* data);
int inst_ld_l_d(CPU* cpu, void* data);
int inst_ld_l_e(CPU* cpu, void* data);
int inst_ld_l_h(CPU* cpu, void* data);

int inst_ld_a_ib(CPU* cpu, void* data);

int inst_add_a_b(CPU* cpu, void* data);
int inst_add_a_a(CPU* cpu, void* data);

static const Instruction instruction_set[] = {
    [0x00] = (Instruction){"NOP",       inst_nop,   0},


    //ld r, r'
    [0x7F] = (Instruction){"LD A,A",    inst_nop,   0},
    [0x78] = (Instruction){"LD A,B",    inst_ld_a_b,    0},
    [0x79] = (Instruction){"LD A,C",    inst_ld_a_c,    0},
    [0x7A] = (Instruction){"LD A,D",    inst_ld_a_d,    0},
    [0x7B] = (Instruction){"LD A,E",    inst_ld_a_e,    0},
    [0x7C] = (Instruction){"LD A,H",    inst_ld_a_h,    0},
    [0x7D] = (Instruction){"LD A,L",    inst_ld_a_l,    0},
    [0x47] = (Instruction){"LD B,A",    inst_ld_b_a,   0},
    [0x40] = (Instruction){"LD B,B",    inst_nop,   0},
    [0x41] = (Instruction){"LD B,C",    inst_ld_b_c,    0},
    [0x42] = (Instruction){"LD B,D",    inst_ld_b_d,    0},
    [0x43] = (Instruction){"LD B,E",    inst_ld_b_e,    0},
    [0x44] = (Instruction){"LD B,H",    inst_ld_b_h,    0},
    [0x45] = (Instruction){"LD B,L",    inst_ld_b_l,    0},
    [0x4F] = (Instruction){"LD C,A",    inst_ld_c_a,   0},
    [0x48] = (Instruction){"LD C,B",    inst_ld_c_b,   0},
    [0x49] = (Instruction){"LD C,C",    inst_nop,   0},
    [0x4A] = (Instruction){"LD C,D",    inst_ld_c_d,    0},
    [0x4B] = (Instruction){"LD C,E",    inst_ld_c_e,    0},
    [0x4C] = (Instruction){"LD C,H",    inst_ld_c_h,    0},
    [0x4D] = (Instruction){"LD C,L",    inst_ld_c_l,    0},
    [0x57] = (Instruction){"LD D,A",    inst_ld_d_a,    0},
    [0x51] = (Instruction){"LD D,C",    inst_ld_d_c,   0},
    [0x50] = (Instruction){"LD D,B",    inst_ld_d_b,   0},
    [0x52] = (Instruction){"LD D,D",    inst_nop,   0},
    [0x53] = (Instruction){"LD D,E",    inst_ld_d_e,    0},
    [0x54] = (Instruction){"LD D,H",    inst_ld_d_h,    0},
    [0x55] = (Instruction){"LD D,L",    inst_ld_d_l,    0},
    [0x5F] = (Instruction){"LD E,A",    inst_ld_e_a,    0},
    [0x58] = (Instruction){"LD E,B",    inst_ld_e_b,   0},
    [0x59] = (Instruction){"LD E,C",    inst_ld_e_c,   0},
    [0x5A] = (Instruction){"LD E,D",    inst_ld_e_d,   0},
    [0x5B] = (Instruction){"LD E,E",    inst_nop,   0},
    [0x5C] = (Instruction){"LD E,H",    inst_ld_e_h,    0},
    [0x5D] = (Instruction){"LD E,L",    inst_ld_e_l,    0},
    [0x67] = (Instruction){"LD H,A",    inst_ld_h_a,   0},
    [0x60] = (Instruction){"LD H,B",    inst_ld_h_b,   0},
    [0x61] = (Instruction){"LD H,C",    inst_ld_h_c,   0},
    [0x62] = (Instruction){"LD H,D",    inst_ld_h_d,   0},
    [0x63] = (Instruction){"LD H,E",    inst_ld_h_e,    0},
    [0x64] = (Instruction){"LD H,H",    inst_nop,   0},
    [0x65] = (Instruction){"LD H,L",    inst_ld_h_l,    0},
    [0x6F] = (Instruction){"LD L,A",    inst_ld_l_a,   0},
    [0x68] = (Instruction){"LD L,B",    inst_ld_l_b,   0},
    [0x69] = (Instruction){"LD L,C",    inst_ld_l_c,   0},
    [0x6A] = (Instruction){"LD L,D",    inst_ld_l_d,   0},
    [0x6B] = (Instruction){"LD L,E",    inst_ld_l_e,    0},
    [0x6C] = (Instruction){"LD L,L",    inst_nop,   0},
    [0x6D] = (Instruction){"LD L,H",    inst_ld_l_h,    0},

    [0x3E] = (Instruction){"LD A,#",    inst_ld_a_ib,    1},

    [0x87] = (Instruction){"ADD A,A",    inst_add_a_a,    0},
    [0x80] = (Instruction){"ADD A,B",    inst_add_a_b,    0},

    [0x30] = (Instruction){"SWAP B",    inst_swap_b,    0},
    [0x31] = (Instruction){"SWAP C",    inst_swap_c,    0},
    [0x32] = (Instruction){"SWAP D",    inst_swap_d,    0},
    
    [0x10] = (Instruction){"STOP",      inst_stop,  0}, //might be extended 0x10 0x00
    
    //INC NN
    [0x03] = (Instruction){"INC BC",    inst_inc_bc,    0},
    [0x13] = (Instruction){"INC DE",    inst_inc_de,    0},
    [0x23] = (Instruction){"INC HL",    inst_inc_hl,    0},
    [0x33] = (Instruction){"INC SP",    inst_inc_sp,    0},

    //DEC NN
    [0x0B] = (Instruction){"DEC BC",    inst_dec_bc,    0},
    [0x1B] = (Instruction){"DEC DE",    inst_dec_de,    0},
    [0x2B] = (Instruction){"DEC HL",    inst_dec_hl,    0},
    [0x3B] = (Instruction){"DEC SP",    inst_dec_sp,    0}    
};  


#endif
