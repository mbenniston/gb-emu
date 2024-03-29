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

int inst_ld_a_abc(CPU* cpu, void* data);
int inst_ld_a_ade(CPU* cpu, void* data);
int inst_ld_a_ann(CPU* cpu, void* data);
int inst_ld_a_ahl(CPU* cpu, void* data);
int inst_ld_b_ahl(CPU* cpu, void* data);
int inst_ld_c_ahl(CPU* cpu, void* data);
int inst_ld_d_ahl(CPU* cpu, void* data);
int inst_ld_e_ahl(CPU* cpu, void* data);
int inst_ld_h_ahl(CPU* cpu, void* data);
int inst_ld_l_ahl(CPU* cpu, void* data);

int inst_ld_abc_a(CPU* cpu, void* data);
int inst_ld_ade_a(CPU* cpu, void* data);
int inst_ld_ann_a(CPU* cpu, void* data);
int inst_ld_ahl_a(CPU* cpu, void* data);
int inst_ld_ahl_b(CPU* cpu, void* data);
int inst_ld_ahl_c(CPU* cpu, void* data);
int inst_ld_ahl_d(CPU* cpu, void* data);
int inst_ld_ahl_e(CPU* cpu, void* data);
int inst_ld_ahl_h(CPU* cpu, void* data);
int inst_ld_ahl_l(CPU* cpu, void* data);
int inst_ld_ahl_ib(CPU* cpu, void* data);

int inst_ld_a_ib(CPU* cpu, void* data);
int inst_ld_b_ib(CPU* cpu, void* data);
int inst_ld_c_ib(CPU* cpu, void* data);
int inst_ld_d_ib(CPU* cpu, void* data);
int inst_ld_e_ib(CPU* cpu, void* data);
int inst_ld_h_ib(CPU* cpu, void* data);
int inst_ld_l_ib(CPU* cpu, void* data);

int inst_ld_ac_a(CPU* cpu, void* data);
int inst_ld_a_ac(CPU* cpu, void* data);

int inst_ld_bc_il(CPU* cpu, void* data);
int inst_ld_de_il(CPU* cpu, void* data);
int inst_ld_hl_il(CPU* cpu, void* data);
int inst_ld_sp_il(CPU* cpu, void* data);

int inst_ldd_ahl_a(CPU* cpu, void* data);
int inst_ldd_a_ahl(CPU* cpu, void* data);

int inst_ldh_aib_a(CPU* cpu, void* data);
int inst_ldh_a_aib (CPU* cpu, void* data);


int inst_adc_a_a(CPU* cpu, void* data);
int inst_adc_a_b(CPU* cpu, void* data);
int inst_adc_a_c(CPU* cpu, void* data);
int inst_adc_a_d(CPU* cpu, void* data);
int inst_adc_a_e(CPU* cpu, void* data);
int inst_adc_a_h(CPU* cpu, void* data);
int inst_adc_a_l(CPU* cpu, void* data);
int inst_adc_a_ahl(CPU* cpu, void* data);
int inst_adc_a_ib(CPU* cpu, void* data);

int inst_inc_a(CPU* cpu, void* data);
int inst_inc_b(CPU* cpu, void* data);
int inst_inc_c(CPU* cpu, void* data);
int inst_inc_d(CPU* cpu, void* data);
int inst_inc_e(CPU* cpu, void* data);
int inst_inc_h(CPU* cpu, void* data);
int inst_inc_l(CPU* cpu, void* data);
int inst_inc_ahl(CPU* cpu, void* data);

int inst_dec_a(CPU* cpu, void* data);
int inst_dec_b(CPU* cpu, void* data);
int inst_dec_c(CPU* cpu, void* data);
int inst_dec_d(CPU* cpu, void* data);
int inst_dec_e(CPU* cpu, void* data);
int inst_dec_h(CPU* cpu, void* data);
int inst_dec_l(CPU* cpu, void* data);
int inst_dec_ahl(CPU* cpu, void* data);

int inst_add_a_b(CPU* cpu, void* data);
int inst_add_a_a(CPU* cpu, void* data);
int inst_add_a_c(CPU* cpu, void* data);
int inst_add_a_d(CPU* cpu, void* data);
int inst_add_a_e(CPU* cpu, void* data);
int inst_add_a_h(CPU* cpu, void* data);
int inst_add_a_l(CPU* cpu, void* data);
int inst_add_a_ahl(CPU* cpu, void* data);
int inst_add_a_ib(CPU* cpu, void* data);

int inst_sub_a(CPU* cpu, void* data);
int inst_sub_b(CPU* cpu, void* data);
int inst_sub_c(CPU* cpu, void* data);
int inst_sub_d(CPU* cpu, void* data);
int inst_sub_e(CPU* cpu, void* data);
int inst_sub_h(CPU* cpu, void* data);
int inst_sub_l(CPU* cpu, void* data);
int inst_sub_ahl(CPU* cpu, void* data);
int inst_sub_ib(CPU* cpu, void* data);


int inst_cp_a(CPU* cpu, void* data);
int inst_cp_b(CPU* cpu, void* data);
int inst_cp_c(CPU* cpu, void* data);
int inst_cp_d(CPU* cpu, void* data);
int inst_cp_e(CPU* cpu, void* data);
int inst_cp_h(CPU* cpu, void* data);
int inst_cp_l(CPU* cpu, void* data);
int inst_cp_ahl(CPU* cpu, void* data);
int inst_cp_ib(CPU* cpu, void* data);

int inst_cpl(CPU* cpu, void* data);
int inst_ccf(CPU* cpu, void* data);
int inst_scf(CPU* cpu, void* data);

int inst_jp_nn(CPU* cpu, void* data);

int inst_jp_fnz_nn(CPU* cpu, void* data);
int inst_jp_fz_nn(CPU* cpu, void* data);
int inst_jp_fnc_nn(CPU* cpu, void* data);
int inst_jp_fc_nn(CPU* cpu, void* data);

int inst_jp_hl(CPU* cpu, void* data);

int inst_jr_fnz_ib(CPU* cpu, void* data);

int inst_push_af(CPU* cpu, void* data);
int inst_push_bc(CPU* cpu, void* data);
int inst_push_de(CPU* cpu, void* data);
int inst_push_hl(CPU* cpu, void* data);

int inst_pop_af(CPU* cpu, void* data);
int inst_pop_bc(CPU* cpu, void* data);
int inst_pop_de(CPU* cpu, void* data);
int inst_pop_hl(CPU* cpu, void* data);

int inst_and_a(CPU* cpu, void* data);
int inst_and_b(CPU* cpu, void* data);
int inst_and_c(CPU* cpu, void* data);
int inst_and_d(CPU* cpu, void* data);
int inst_and_e(CPU* cpu, void* data);
int inst_and_h(CPU* cpu, void* data);
int inst_and_l(CPU* cpu, void* data);
int inst_and_ib(CPU* cpu, void* data);
int inst_and_ahl(CPU* cpu, void* data);

int inst_or_a(CPU* cpu, void* data);
int inst_or_b(CPU* cpu, void* data);
int inst_or_c(CPU* cpu, void* data);
int inst_or_d(CPU* cpu, void* data);
int inst_or_e(CPU* cpu, void* data);
int inst_or_h(CPU* cpu, void* data);
int inst_or_l(CPU* cpu, void* data);
int inst_or_ib(CPU* cpu, void* data);
int inst_or_ahl(CPU* cpu, void* data);

int inst_xor_a(CPU* cpu, void* data);
int inst_xor_b(CPU* cpu, void* data);
int inst_xor_c(CPU* cpu, void* data);
int inst_xor_d(CPU* cpu, void* data);
int inst_xor_e(CPU* cpu, void* data);
int inst_xor_h(CPU* cpu, void* data);
int inst_xor_l(CPU* cpu, void* data);
int inst_xor_ib(CPU* cpu, void* data);
int inst_xor_ahl(CPU* cpu, void* data);

int inst_call_nn(CPU* cpu, void* data);
int inst_ret(CPU* cpu, void* data);

int inst_di(CPU* cpu, void* data);

int inst_rst_00(CPU* cpu, void* data);
int inst_rst_08(CPU* cpu, void* data);
int inst_rst_10(CPU* cpu, void* data);
int inst_rst_18(CPU* cpu, void* data);
int inst_rst_20(CPU* cpu, void* data);
int inst_rst_28(CPU* cpu, void* data);
int inst_rst_30(CPU* cpu, void* data);
int inst_rst_38(CPU* cpu, void* data);

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
    [0x06] = (Instruction){"LD B,#",    inst_ld_b_ib,    1},
    [0x0E] = (Instruction){"LD C,#",    inst_ld_c_ib,    1},
    [0x16] = (Instruction){"LD D,#",    inst_ld_d_ib,    1},
    [0x1E] = (Instruction){"LD E,#",    inst_ld_e_ib,    1},
    [0x26] = (Instruction){"LD H,#",    inst_ld_h_ib,    1},
    [0x2E] = (Instruction){"LD L,#",    inst_ld_l_ib,    1},

    [0x0A] = (Instruction){"LD A,(BC)",    inst_ld_a_abc,    0},
    [0x1A] = (Instruction){"LD A,(DE)",    inst_ld_a_ade,    0},
    [0x7E] = (Instruction){"LD A,(HL)",    inst_ld_a_ahl,    0},
    [0xFA] = (Instruction){"LD A,(nn)",    inst_ld_a_ann,    2},
    [0x46] = (Instruction){"LD B,(HL)",    inst_ld_b_ahl,    0},
    [0x4E] = (Instruction){"LD C,(HL)",    inst_ld_c_ahl,    0},
    [0x56] = (Instruction){"LD D,(HL)",    inst_ld_d_ahl,    0},
    [0x5E] = (Instruction){"LD E,(HL)",    inst_ld_e_ahl,    0},
    [0x66] = (Instruction){"LD H,(HL)",    inst_ld_h_ahl,    0},
    [0x6E] = (Instruction){"LD L,(HL)",    inst_ld_l_ahl,    0},

    [0x02] = (Instruction){"LD (BC),A",    inst_ld_abc_a,    0},
    [0x12] = (Instruction){"LD (DE),A",    inst_ld_ade_a,    0},
    [0x77] = (Instruction){"LD (HL),A",    inst_ld_ahl_a,    0},
    [0xEA] = (Instruction){"LD (nn),A",    inst_ld_ann_a,    2},
    [0x70] = (Instruction){"LD (HL),B",    inst_ld_ahl_b,    0},
    [0x71] = (Instruction){"LD (HL),C",    inst_ld_ahl_c,    0},
    [0x72] = (Instruction){"LD (HL),D",    inst_ld_ahl_d,    0},
    [0x73] = (Instruction){"LD (HL),E",    inst_ld_ahl_e,    0},
    [0x74] = (Instruction){"LD (HL),H",    inst_ld_ahl_h,    0},
    [0x75] = (Instruction){"LD (HL),L",    inst_ld_ahl_l,    0},
    [0x36] = (Instruction){"LD (HL),n",    inst_ld_ahl_ib,    0},

    [0xE2] = (Instruction){"LD (C),A",    inst_ld_ac_a,    0},
    [0xF2] = (Instruction){"LD A,(C)",    inst_ld_a_ac,    0},

    //16 bit immediate loads
    [0x01] = (Instruction){"LD BC,#",    inst_ld_bc_il,    2},
    [0x11] = (Instruction){"LD DE,#",    inst_ld_de_il,    2},
    [0x21] = (Instruction){"LD HL,#",    inst_ld_hl_il,    2},
    [0x31] = (Instruction){"LD SP,#",    inst_ld_sp_il,    2},

    //the same as LD (HL),A; DEC HL
    [0x32] = (Instruction){"LDD (HL),A",    inst_ldd_ahl_a,    0},
    //the same as LD A,(HL); DEC HL
    [0x32] = (Instruction){"LDD A,(HL)",    inst_ldd_a_ahl,    0},

    //relational loads
    [0xE0] = (Instruction){"LDH (#),A",    inst_ldh_aib_a,    1},
    [0xF0] = (Instruction){"LDH A,(#)",    inst_ldh_a_aib,    1},


    //addition

    //increment
    [0x3C] = (Instruction){"INC A",   inst_inc_a,    0},
    [0x04] = (Instruction){"INC B",   inst_inc_b,    0},
    [0x0C] = (Instruction){"INC C",   inst_inc_c,    0},
    [0x14] = (Instruction){"INC D",   inst_inc_d,    0},
    [0x1C] = (Instruction){"INC E",   inst_inc_e,    0},
    [0x24] = (Instruction){"INC H",   inst_inc_h,    0},
    [0x2C] = (Instruction){"INC L",   inst_inc_l,    0},
    [0x34] = (Instruction){"INC (HL)",   inst_inc_ahl,    0},

    //add with carries
    [0x8F] = (Instruction){"ADC A,A",   inst_adc_a_a,    0},
    [0x88] = (Instruction){"ADC A,B",   inst_adc_a_b,    0},
    [0x89] = (Instruction){"ADC A,C",   inst_adc_a_c,    0},
    [0x8A] = (Instruction){"ADC A,D",   inst_adc_a_d,    0},
    [0x8B] = (Instruction){"ADC A,E",   inst_adc_a_e,    0},
    [0x8C] = (Instruction){"ADC A,H",   inst_adc_a_h,    0},
    [0x8D] = (Instruction){"ADC A,L",   inst_adc_a_l,    0},
    [0x8E] = (Instruction){"ADC A,(HL)",   inst_adc_a_ahl,    0},
    [0xCE] = (Instruction){"ADC A,#",   inst_adc_a_ib,    0},

    //adds
    [0x87] = (Instruction){"ADD A,A",    inst_add_a_a,    0},
    [0x80] = (Instruction){"ADD A,B",    inst_add_a_b,    0},
    [0x81] = (Instruction){"ADD A,C",    inst_add_a_c,    0},
    [0x82] = (Instruction){"ADD A,D",    inst_add_a_d,    0},
    [0x83] = (Instruction){"ADD A,E",    inst_add_a_e,    0},
    [0x84] = (Instruction){"ADD A,H",    inst_add_a_h,    0},
    [0x85] = (Instruction){"ADD A,L",    inst_add_a_l,    0},
    [0x86] = (Instruction){"ADD A,(HL)",    inst_add_a_ahl,    0},
    [0xC6] = (Instruction){"ADD A,#",    inst_add_a_ib,    0},

    //subtraction

    //decrement
    [0x3D] = (Instruction){"DEC A",   inst_dec_a,    0},
    [0x05] = (Instruction){"DEC B",   inst_dec_b,    0},
    [0x0D] = (Instruction){"DEC C",   inst_dec_c,    0},
    [0x15] = (Instruction){"DEC D",   inst_dec_d,    0},
    [0x1D] = (Instruction){"DEC E",   inst_dec_e,    0},
    [0x25] = (Instruction){"DEC H",   inst_dec_h,    0},
    [0x2D] = (Instruction){"DEC L",   inst_dec_l,    0},
    [0x35] = (Instruction){"DEC (HL)",   inst_dec_ahl,    0},


    [0x97] = (Instruction){"SUB A",    inst_sub_a,    0},
    [0x90] = (Instruction){"SUB B",    inst_sub_b,    0},
    [0x91] = (Instruction){"SUB C",    inst_sub_c,    0},
    [0x92] = (Instruction){"SUB D",    inst_sub_d,    0},
    [0x93] = (Instruction){"SUB E",    inst_sub_e,    0},
    [0x94] = (Instruction){"SUB H",    inst_sub_h,    0},
    [0x95] = (Instruction){"SUB L",    inst_sub_l,    0},
    [0x96] = (Instruction){"SUB (HL)",    inst_sub_ahl,    0},
    [0xD6] = (Instruction){"SUB #",    inst_sub_ib,    1},

    //compare (with A)

    [0xBF] = (Instruction){"CP A",    inst_cp_a,    0},
    [0xB8] = (Instruction){"CP B",    inst_cp_b,    0},
    [0xB9] = (Instruction){"CP C",    inst_cp_c,    0},
    [0xBA] = (Instruction){"CP D",    inst_cp_d,    0},
    [0xBB] = (Instruction){"CP E",    inst_cp_e,    0},
    [0xBC] = (Instruction){"CP H",    inst_cp_h,    0},
    [0xBD] = (Instruction){"CP L",    inst_cp_l,    0},
    [0xBE] = (Instruction){"CP (HL)",    inst_cp_ahl,    0},
    [0xFE] = (Instruction){"CP #",    inst_cp_ib,    1},

    // [0x30] = (Instruction){"SWAP B",    inst_swap_b,    0},
    // [0x31] = (Instruction){"SWAP C",    inst_swap_c,    0},
    // [0x32] = (Instruction){"SWAP D",    inst_swap_d,    0},

    [0x10] = (Instruction){"STOP",      inst_stop,  0}, //might be extended 0x10 0x00
    [0x2F] = (Instruction){"CPL",      inst_cpl,  0},
    [0x3F] = (Instruction){"CCF",      inst_ccf,  0},
    [0x37] = (Instruction){"SCF",      inst_scf,  0},

    [0xC3] = (Instruction){"JP nn",      inst_jp_nn,  2},
    [0xC2] = (Instruction){"JP NZ,nn",      inst_jp_fnz_nn,  2},
    [0xCA] = (Instruction){"JP Z,nn",      inst_jp_fz_nn,  2},
    [0xD2] = (Instruction){"JP NC,nn",      inst_jp_fnc_nn,  2},
    [0xDA] = (Instruction){"JP C,nn",      inst_jp_fc_nn,  2},
    [0xE9] = (Instruction){"JP HL", inst_jp_hl, 0},

    [0x20] = (Instruction){"JR NZ,#", inst_jr_fnz_ib, 1},


    [0xCD] = (Instruction){"CALL nn",   inst_call_nn,   2},
    [0xC9] = (Instruction){"RET",   inst_ret,   0},

    //push
    [0xF5] = (Instruction){"PUSH AF",      inst_push_af,  0},
    [0xC5] = (Instruction){"PUSH BC",      inst_push_bc,  0},
    [0xD5] = (Instruction){"PUSH DE",      inst_push_de,  0},
    [0xE5] = (Instruction){"PUSH HL",      inst_push_hl,  0},

    //pop
    [0xF1] = (Instruction){"POP AF",      inst_pop_af,  0},
    [0xC1] = (Instruction){"POP BC",      inst_pop_bc,  0},
    [0xD1] = (Instruction){"POP DE",      inst_pop_de,  0},
    [0xE1] = (Instruction){"POP HL",      inst_pop_hl,  0},

    //AND
    [0xA7] = (Instruction){"AND A", inst_and_a, 0},
    [0xA0] = (Instruction){"AND B", inst_and_b, 0},
    [0xA1] = (Instruction){"AND C", inst_and_c, 0},
    [0xA2] = (Instruction){"AND D", inst_and_d, 0},
    [0xA3] = (Instruction){"AND E", inst_and_e, 0},
    [0xA4] = (Instruction){"AND H", inst_and_h, 0},
    [0xA5] = (Instruction){"AND L", inst_and_l, 0},
    [0xA6] = (Instruction){"AND (HL)", inst_and_ahl, 0},
    [0xE6] = (Instruction){"AND #", inst_and_ib, 1},

    //OR
    [0xB7] = (Instruction){"OR A", inst_or_a, 0},
    [0xB0] = (Instruction){"OR B", inst_or_b, 0},
    [0xB1] = (Instruction){"OR C", inst_or_c, 0},
    [0xB2] = (Instruction){"OR D", inst_or_d, 0},
    [0xB3] = (Instruction){"OR E", inst_or_e, 0},
    [0xB4] = (Instruction){"OR H", inst_or_h, 0},
    [0xB5] = (Instruction){"OR L", inst_or_l, 0},
    [0xB6] = (Instruction){"OR (HL)", inst_or_ahl, 0},
    [0xF6] = (Instruction){"OR #", inst_or_ib, 1},


    //XOR
    [0xAF] = (Instruction){"XOR A", inst_xor_a, 0},
    [0xA8] = (Instruction){"XOR B", inst_xor_b, 0},
    [0xA9] = (Instruction){"XOR C", inst_xor_c, 0},
    [0xAA] = (Instruction){"XOR D", inst_xor_d, 0},
    [0xAB] = (Instruction){"XOR E", inst_xor_e, 0},
    [0xAC] = (Instruction){"XOR H", inst_xor_h, 0},
    [0xAD] = (Instruction){"XOR L", inst_xor_l, 0},
    [0xAE] = (Instruction){"XOR (HL)", inst_xor_ahl, 0},
    [0xEE] = (Instruction){"XOR #", inst_xor_ib, 1},


    //INC NN
    [0x03] = (Instruction){"INC BC",    inst_inc_bc,    0},
    [0x13] = (Instruction){"INC DE",    inst_inc_de,    0},
    [0x23] = (Instruction){"INC HL",    inst_inc_hl,    0},
    [0x33] = (Instruction){"INC SP",    inst_inc_sp,    0},

    //DEC NN
    [0x0B] = (Instruction){"DEC BC",    inst_dec_bc,    0},
    [0x1B] = (Instruction){"DEC DE",    inst_dec_de,    0},
    [0x2B] = (Instruction){"DEC HL",    inst_dec_hl,    0},
    [0x3B] = (Instruction){"DEC SP",    inst_dec_sp,    0},

    [0xF3] = (Instruction){"DI",    inst_di,    0},

    //RST
    [0xC7] = (Instruction){"RST 00", inst_rst_00, 0},
    [0xCF] = (Instruction){"RST 08", inst_rst_08, 0},
    [0xD7] = (Instruction){"RST 10", inst_rst_10, 0},
    [0xDF] = (Instruction){"RST 18", inst_rst_18, 0},
    [0xE7] = (Instruction){"RST 20", inst_rst_20, 0},
    [0xEF] = (Instruction){"RST 28", inst_rst_28, 0},
    [0xF7] = (Instruction){"RST 30", inst_rst_30, 0},
    [0xFF] = (Instruction){"RST 38", inst_rst_38, 0}
};


#endif
