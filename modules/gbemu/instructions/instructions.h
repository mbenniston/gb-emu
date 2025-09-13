#ifndef GBEMU_INSTRUCTIONS_H
#define GBEMU_INSTRUCTIONS_H

#include "instruction.h"

uint16_t uint8_sign_extend_uint16(uint8_t value);

instruction_result_t instruction_nop(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_bc_n16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_bc_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_bc(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_b_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rlca(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_a16_sp(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_hl_bc(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_deref_bc(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_bc(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_c_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rrca(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_stop_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_de_n16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_de_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_de(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_d_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rla(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_jr_e8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_hl_de(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_deref_de(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_de(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_e_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rra(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_jr_nz_e8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_hl_n16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_inc_deref_hl_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_h_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_daa(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_jr_z_e8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_hl_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_inc_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_l_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_cpl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_jr_nc_e8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_sp_n16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_dec_deref_hl_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_sp(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_hl_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_scf(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_jr_c_e8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_hl_sp(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_dec_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_sp(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_inc_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_dec_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ccf(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_b_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_b_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_b_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_b_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_b_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_b_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_b_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_b_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_c_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_c_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_c_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_c_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_c_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_c_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_c_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_c_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_d_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_d_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_d_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_d_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_d_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_d_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_d_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_d_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_e_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_e_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_e_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_e_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_e_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_e_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_e_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_e_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_h_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_h_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_h_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_h_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_h_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_h_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_h_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_h_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_l_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_l_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_l_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_l_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_l_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_l_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_l_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_l_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_hl_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_hl_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_hl_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_hl_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_hl_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_hl_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_halt(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_hl_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_a_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_a_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_a_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_a_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_a_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_a_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_a_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_a_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_adc_a_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_adc_a_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_adc_a_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_adc_a_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_adc_a_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_adc_a_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_adc_a_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_adc_a_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sub_a_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sub_a_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sub_a_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sub_a_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sub_a_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sub_a_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sub_a_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sub_a_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sbc_a_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sbc_a_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sbc_a_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sbc_a_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sbc_a_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sbc_a_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sbc_a_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sbc_a_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_and_a_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_and_a_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_and_a_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_and_a_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_and_a_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_and_a_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_and_a_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_and_a_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_xor_a_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_xor_a_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_xor_a_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_xor_a_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_xor_a_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_xor_a_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_xor_a_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_xor_a_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_or_a_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_or_a_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_or_a_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_or_a_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_or_a_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_or_a_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_or_a_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_or_a_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_cp_a_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_cp_a_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_cp_a_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_cp_a_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_cp_a_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_cp_a_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_cp_a_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_cp_a_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ret_nz(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_pop_bc(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_jp_nz_a16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_jp_a16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_call_nz_a16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_push_bc(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_a_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rst_00(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ret_z(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ret(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_jp_z_a16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_prefix(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_call_z_a16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_call_a16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_adc_a_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rst_08(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ret_nc(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_pop_de(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_jp_nc_a16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_illegal_d3(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_call_nc_a16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_push_de(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sub_a_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rst_10(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ret_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_reti(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_jp_c_a16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_illegal_db(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_call_c_a16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_illegal_dd(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sbc_a_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rst_18(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ldh_deref_a8_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_pop_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ldh_deref_c_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_illegal_e3(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_illegal_e4(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_push_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_and_a_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rst_20(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_add_sp_e8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_jp_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_deref_a16_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_illegal_eb(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_illegal_ec(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_illegal_ed(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_xor_a_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rst_28(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ldh_a_deref_a8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_pop_af(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ldh_a_deref_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_di(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_illegal_f4(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_push_af(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_or_a_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rst_30(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_hl_inc_sp_e8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_sp_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ld_a_deref_a16(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_ei(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_illegal_fc(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_illegal_fd(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_cp_a_n8(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rst_38(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rlc_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rlc_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rlc_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rlc_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rlc_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rlc_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rlc_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rlc_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rrc_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rrc_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rrc_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rrc_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rrc_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rrc_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rrc_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rrc_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rl_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rl_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rl_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rl_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rl_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rl_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rl_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rl_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rr_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rr_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rr_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rr_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rr_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rr_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rr_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_rr_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sla_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sla_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sla_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sla_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sla_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sla_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sla_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sla_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sra_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sra_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sra_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sra_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sra_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sra_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sra_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_sra_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_swap_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_swap_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_swap_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_swap_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_swap_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_swap_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_swap_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_swap_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_srl_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_srl_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_srl_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_srl_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_srl_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_srl_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_srl_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_srl_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_0_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_0_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_0_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_0_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_0_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_0_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_0_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_0_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_1_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_1_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_1_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_1_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_1_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_1_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_1_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_1_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_2_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_2_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_2_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_2_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_2_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_2_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_2_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_2_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_3_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_3_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_3_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_3_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_3_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_3_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_3_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_3_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_4_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_4_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_4_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_4_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_4_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_4_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_4_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_4_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_5_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_5_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_5_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_5_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_5_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_5_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_5_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_5_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_6_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_6_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_6_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_6_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_6_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_6_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_6_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_6_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_7_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_7_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_7_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_7_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_7_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_7_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_7_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_bit_7_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_0_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_0_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_0_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_0_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_0_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_0_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_0_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_0_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_1_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_1_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_1_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_1_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_1_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_1_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_1_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_1_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_2_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_2_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_2_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_2_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_2_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_2_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_2_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_2_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_3_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_3_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_3_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_3_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_3_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_3_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_3_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_3_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_4_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_4_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_4_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_4_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_4_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_4_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_4_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_4_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_5_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_5_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_5_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_5_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_5_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_5_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_5_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_5_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_6_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_6_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_6_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_6_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_6_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_6_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_6_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_6_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_7_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_7_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_7_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_7_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_7_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_7_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_7_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_res_7_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_0_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_0_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_0_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_0_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_0_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_0_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_0_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_0_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_1_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_1_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_1_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_1_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_1_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_1_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_1_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_1_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_2_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_2_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_2_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_2_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_2_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_2_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_2_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_2_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_3_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_3_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_3_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_3_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_3_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_3_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_3_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_3_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_4_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_4_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_4_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_4_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_4_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_4_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_4_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_4_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_5_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_5_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_5_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_5_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_5_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_5_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_5_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_5_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_6_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_6_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_6_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_6_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_6_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_6_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_6_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_6_a(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_7_b(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_7_c(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_7_d(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_7_e(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_7_h(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_7_l(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_7_deref_hl(cpu_t *cpu, bus_t *bus);

instruction_result_t instruction_set_7_a(cpu_t *cpu, bus_t *bus);

extern const instruction_t instructions[];
extern const instruction_t extended_instructions[];

#endif
