#include "instructions.h"

#include <assert.h>

void push_uint16(cpu_t *cpu, bus_t *bus, uint16_t value) {
  bus_write(bus, --cpu->registers.SP, value >> 8);
  bus_write(bus, --cpu->registers.SP, value & 0xFF);
}

void push_uint8(cpu_t *cpu, bus_t *bus, uint8_t value) {
  bus_write(bus, --cpu->registers.SP, value);
}

uint8_t pop_uint8(cpu_t *cpu, bus_t *bus) {
  return bus_read(bus, cpu->registers.SP++);
}

uint16_t pop_uint16(cpu_t *cpu, bus_t *bus) {
  return bus_read(bus, cpu->registers.SP++) | bus_read(bus, cpu->registers.SP++)
                                                  << 8;
}

int add_has_overflow_uint8(uint8_t left, uint8_t right) {
  return (uint16_t)left + (uint16_t)right > 0xFF;
}

int add_has_overflow_with_carry_uint8(uint8_t left, uint8_t right,
                                      uint8_t carry) {
  return (uint16_t)left + (uint16_t)right + (uint16_t)carry > 0xFF;
}

int add_has_half_overflow_uint8(uint8_t left, uint8_t right) {
  return (left & 0xF) + (right & 0xF) > 0xF;
}

int add_has_half_overflow_with_carry_uint8(uint8_t left, uint8_t right,
                                           uint8_t carry) {
  return (left & 0xF) + (right & 0xF) + carry > 0xF;
}

int add_has_overflow_uint16(uint16_t left, uint16_t right) {
  return (uint32_t)left + (uint32_t)right > 0xFFFF;
}

int add_has_half_overflow_uint16(uint16_t left, uint16_t right) {
  return (left & 0xFFF) + (right & 0xFFF) > 0xFFF;
}

int sub_has_half_borrow_uint8(uint8_t left, uint8_t right) {
  return (int16_t)(left & 0xF) - (int16_t)(right & 0xF) < 0;
}

int sub_has_half_borrow_with_carry_uint8(uint8_t left, uint8_t right,
                                         uint8_t carry) {
  return (int16_t)(left & 0xF) - ((int16_t)(right & 0xF) + carry) < 0;
}

int sub_has_borrow_with_carry_uint8(uint8_t left, uint8_t right,
                                    uint8_t carry) {
  return (uint16_t)right + (uint16_t)carry > left;
}

uint8_t swap_uint8_with_flags(uint8_t input, uint8_t *flags_register) {
  uint8_t result = (input & 0xF) << 4 | (input & 0xF0) >> 4;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_reset_h(flags_register);
  flags_reset_c(flags_register);

  return result;
}

uint8_t and_uint8_with_flags(uint8_t left, uint8_t right,
                             uint8_t *flags_register) {
  uint8_t result = left & right;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_set_h(flags_register);
  flags_reset_c(flags_register);

  return result;
}

uint8_t or_uint8_with_flags(uint8_t left, uint8_t right,
                            uint8_t *flags_register) {
  uint8_t result = left | right;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_reset_h(flags_register);
  flags_reset_c(flags_register);

  return result;
}

uint8_t xor_uint8_with_flags(uint8_t left, uint8_t right,
                             uint8_t *flags_register) {
  uint8_t result = left ^ right;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_reset_h(flags_register);
  flags_reset_c(flags_register);

  return result;
}

uint8_t bit_with_flags(uint8_t value, int bit_index, uint8_t *flag_register) {
  uint8_t result = (value & 1 << bit_index) >> bit_index;

  if (result == 0)
    flags_set_z(flag_register);
  else
    flags_reset_z(flag_register);

  flags_reset_n(flag_register);
  flags_set_h(flag_register);

  return result;
}

uint8_t set_with_flags(uint8_t value, int bit_index, uint8_t *flag_register) {
  return value | 1 << bit_index;
}

uint8_t reset_with_flags(uint8_t value, int bit_index, uint8_t *flag_register) {
  return value & ~(1 << bit_index);
}

uint8_t inc_uint8_with_flags(uint8_t left, uint8_t *flags_register) {
  uint8_t result = left + 1;

  // Zero result
  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  // Half overflow
  if (add_has_half_overflow_uint8(left, 1))
    flags_set_h(flags_register);
  else
    flags_reset_h(flags_register);

  // Not a subtraction
  flags_reset_n(flags_register);

  return result;
}

uint8_t srl_uint8_with_flags(uint8_t input, uint8_t *flags_register) {
  uint8_t result = input >> 1;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_reset_h(flags_register);

  if ((input & 0x1) > 0)
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  return result;
}

uint8_t sl_uint8_with_flags(uint8_t input, uint8_t *flags_register) {
  uint8_t result = input << 1;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_reset_h(flags_register);

  if ((input & 0x80) > 0)
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  return result;
}

uint8_t sr_uint8_with_flags(uint8_t input, uint8_t *flags_register) {
  uint8_t result = input >> 1;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_reset_h(flags_register);

  if (input & 0x1)
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  return result;
}

uint8_t sra_uint8_with_flags(uint8_t input, uint8_t *flags_register) {
  uint8_t result = input & 0x80 ? input >> 1 | input & 0x80 : input >> 1;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_reset_h(flags_register);

  if (input & 0x1)
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  return result;
}

uint8_t rrc_uint8_with_flags(uint8_t input, uint8_t *flags_register) {
  uint8_t result = input & 0x1 ? input >> 1 | 0x80 : input >> 1;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_reset_h(flags_register);

  if ((input & 0x1) > 0)
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  return result;
}

uint8_t rr_uint8_with_flags(uint8_t input, uint8_t *flags_register) {
  uint8_t result = flags_is_c(*flags_register) ? input >> 1 | 0x80 : input >> 1;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_reset_h(flags_register);

  if (input & 0x1)
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  return result;
}

uint8_t rlc_uint8_with_flags(uint8_t input, uint8_t *flags_register) {
  uint8_t result = input & 0x80 ? input << 1 | 0x1 : input << 1;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_reset_h(flags_register);

  if ((input & 0x80) > 0)
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  return result;
}

uint8_t rl_uint8_with_flags(uint8_t input, uint8_t *flags_register) {
  uint8_t result = flags_is_c(*flags_register) ? input << 1 | 0x1 : input << 1;

  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  flags_reset_n(flags_register);
  flags_reset_h(flags_register);

  if (input & 0x80)
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  return result;
}

uint8_t dec_uint8_with_flags(uint8_t left, uint8_t *flags_register) {
  uint8_t result = left - 1;

  // Zero result
  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  // Half overflow
  if (sub_has_half_borrow_uint8(left, 1))
    flags_set_h(flags_register);
  else
    flags_reset_h(flags_register);

  // Is a subtraction
  flags_set_n(flags_register);

  return (result);
}

uint16_t add_uint16_with_flags(uint16_t left, uint16_t right,
                               uint8_t *flags_register) {
  uint16_t result = left + right;

  // Half overflow
  if (add_has_half_overflow_uint16(left, right))
    flags_set_h(flags_register);
  else
    flags_reset_h(flags_register);

  // Full overflow
  if (add_has_overflow_uint16(left, right))
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  // Not a subtraction
  flags_reset_n(flags_register);

  return result;
}

uint8_t add_uint8_with_flags(uint8_t left, uint8_t right,
                             uint8_t *flags_register) {
  uint8_t result = left + right;

  // Zero result
  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  // Half overflow
  if (add_has_half_overflow_uint8(left, right))
    flags_set_h(flags_register);
  else
    flags_reset_h(flags_register);

  // Full overflow
  if (add_has_overflow_uint8(left, right))
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  // Not a subtraction
  flags_reset_n(flags_register);

  return result;
}

uint8_t adc_uint8_with_flags(uint8_t left, uint8_t right,
                             uint8_t *flags_register) {
  uint8_t rightWithCarry = flags_is_c(*flags_register) ? right + 1 : right;
  uint8_t result = left + rightWithCarry;

  // Zero result
  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  // Half overflow
  if (add_has_half_overflow_with_carry_uint8(left, right,
                                             flags_is_c(*flags_register)))
    flags_set_h(flags_register);
  else
    flags_reset_h(flags_register);

  // Full overflow
  if (add_has_overflow_with_carry_uint8(left, right,
                                        flags_is_c(*flags_register)))
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  // Not a subtraction
  flags_reset_n(flags_register);

  return result;
}

uint8_t sub_uint8_with_flags(uint8_t left, uint8_t right,
                             uint8_t *flags_register) {
  uint8_t result = left - right;

  // Zero result
  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  // Half overflow
  if (sub_has_half_borrow_uint8(left, right))
    flags_set_h(flags_register);
  else
    flags_reset_h(flags_register);

  // Full overflow
  if (right > left)
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  // Is a subtraction
  flags_set_n(flags_register);

  return result;
}

uint8_t sbc_uint8_with_flags(uint8_t left, uint8_t right,
                             uint8_t *flags_register) {
  uint8_t rightWithCarry = flags_is_c(*flags_register) ? right + 1 : right;
  uint8_t result = left - rightWithCarry;

  // Zero result
  if (result == 0)
    flags_set_z(flags_register);
  else
    flags_reset_z(flags_register);

  // Half overflow
  if (sub_has_half_borrow_with_carry_uint8(left, right,
                                           flags_is_c(*flags_register)))
    flags_set_h(flags_register);
  else
    flags_reset_h(flags_register);

  // Full overflow
  if (sub_has_borrow_with_carry_uint8(left, right, flags_is_c(*flags_register)))
    flags_set_c(flags_register);
  else
    flags_reset_c(flags_register);

  // Is a subtraction
  flags_set_n(flags_register);

  return result;
}

/**
 * Convert twos complement signed int8 to int16, extending sign if negative.
 */
uint16_t uint8_sign_extend_uint16(uint8_t value) {
  if (value & 0x80)
    return (uint16_t)0xFF00 | (uint16_t)value;
  return value;
}

const instruction_t instructions[256] = {
    [0x00] = (instruction_t){"NOP", instruction_nop},
    [0x01] = (instruction_t){"LD BC, n16", instruction_ld_bc_n16},
    [0x02] = (instruction_t){"LD (BC), A", instruction_ld_deref_bc_a},
    [0x03] = (instruction_t){"INC BC", instruction_inc_bc},
    [0x04] = (instruction_t){"INC B", instruction_inc_b},
    [0x05] = (instruction_t){"DEC B", instruction_dec_b},
    [0x06] = (instruction_t){"LD B, n8", instruction_ld_b_n8},
    [0x07] = (instruction_t){"RLCA", instruction_rlca},
    [0x08] = (instruction_t){"LD (a16), SP", instruction_ld_deref_a16_sp},
    [0x09] = (instruction_t){"ADD HL, BC", instruction_add_hl_bc},
    [0x0A] = (instruction_t){"LD A, (BC)", instruction_ld_a_deref_bc},
    [0x0B] = (instruction_t){"DEC BC", instruction_dec_bc},
    [0x0C] = (instruction_t){"INC C", instruction_inc_c},
    [0x0D] = (instruction_t){"DEC C", instruction_dec_c},
    [0x0E] = (instruction_t){"LD C, n8", instruction_ld_c_n8},
    [0x0F] = (instruction_t){"RRCA", instruction_rrca},
    [0x10] = (instruction_t){"STOP n8", instruction_stop_n8},
    [0x11] = (instruction_t){"LD DE, n16", instruction_ld_de_n16},
    [0x12] = (instruction_t){"LD (DE), A", instruction_ld_deref_de_a},
    [0x13] = (instruction_t){"INC DE", instruction_inc_de},
    [0x14] = (instruction_t){"INC D", instruction_inc_d},
    [0x15] = (instruction_t){"DEC D", instruction_dec_d},
    [0x16] = (instruction_t){"LD D, n8", instruction_ld_d_n8},
    [0x17] = (instruction_t){"RLA", instruction_rla},
    [0x18] = (instruction_t){"JR e8", instruction_jr_e8},
    [0x19] = (instruction_t){"ADD HL, DE", instruction_add_hl_de},
    [0x1A] = (instruction_t){"LD A, (DE)", instruction_ld_a_deref_de},
    [0x1B] = (instruction_t){"DEC DE", instruction_dec_de},
    [0x1C] = (instruction_t){"INC E", instruction_inc_e},
    [0x1D] = (instruction_t){"DEC E", instruction_dec_e},
    [0x1E] = (instruction_t){"LD E, n8", instruction_ld_e_n8},
    [0x1F] = (instruction_t){"RRA", instruction_rra},
    [0x20] = (instruction_t){"JR NZ, e8", instruction_jr_nz_e8},
    [0x21] = (instruction_t){"LD HL, n16", instruction_ld_hl_n16},
    [0x22] = (instruction_t){"LD (HL+), A", instruction_ld_inc_deref_hl_a},
    [0x23] = (instruction_t){"INC HL", instruction_inc_hl},
    [0x24] = (instruction_t){"INC H", instruction_inc_h},
    [0x25] = (instruction_t){"DEC H", instruction_dec_h},
    [0x26] = (instruction_t){"LD H, n8", instruction_ld_h_n8},
    [0x27] = (instruction_t){"DAA", instruction_daa},
    [0x28] = (instruction_t){"JR Z, e8", instruction_jr_z_e8},
    [0x29] = (instruction_t){"ADD HL, HL", instruction_add_hl_hl},
    [0x2A] = (instruction_t){"LD A, (HL+)", instruction_ld_a_inc_deref_hl},
    [0x2B] = (instruction_t){"DEC HL", instruction_dec_hl},
    [0x2C] = (instruction_t){"INC L", instruction_inc_l},
    [0x2D] = (instruction_t){"DEC L", instruction_dec_l},
    [0x2E] = (instruction_t){"LD L, n8", instruction_ld_l_n8},
    [0x2F] = (instruction_t){"CPL", instruction_cpl},
    [0x30] = (instruction_t){"JR NC, e8", instruction_jr_nc_e8},
    [0x31] = (instruction_t){"LD SP, n16", instruction_ld_sp_n16},
    [0x32] = (instruction_t){"LD (HL-), A", instruction_ld_dec_deref_hl_a},
    [0x33] = (instruction_t){"INC SP", instruction_inc_sp},
    [0x34] = (instruction_t){"INC (HL)", instruction_inc_deref_hl},
    [0x35] = (instruction_t){"DEC (HL)", instruction_dec_deref_hl},
    [0x36] = (instruction_t){"LD (HL), n8", instruction_ld_deref_hl_n8},
    [0x37] = (instruction_t){"SCF", instruction_scf},
    [0x38] = (instruction_t){"JR C, e8", instruction_jr_c_e8},
    [0x39] = (instruction_t){"ADD HL, SP", instruction_add_hl_sp},
    [0x3A] = (instruction_t){"LD A, (HL-)", instruction_ld_a_dec_deref_hl},
    [0x3B] = (instruction_t){"DEC SP", instruction_dec_sp},
    [0x3C] = (instruction_t){"INC A", instruction_inc_a},
    [0x3D] = (instruction_t){"DEC A", instruction_dec_a},
    [0x3E] = (instruction_t){"LD A, n8", instruction_ld_a_n8},
    [0x3F] = (instruction_t){"CCF", instruction_ccf},
    [0x40] = (instruction_t){"LD B, B", instruction_ld_b_b},
    [0x41] = (instruction_t){"LD B, C", instruction_ld_b_c},
    [0x42] = (instruction_t){"LD B, D", instruction_ld_b_d},
    [0x43] = (instruction_t){"LD B, E", instruction_ld_b_e},
    [0x44] = (instruction_t){"LD B, H", instruction_ld_b_h},
    [0x45] = (instruction_t){"LD B, L", instruction_ld_b_l},
    [0x46] = (instruction_t){"LD B, (HL)", instruction_ld_b_deref_hl},
    [0x47] = (instruction_t){"LD B, A", instruction_ld_b_a},
    [0x48] = (instruction_t){"LD C, B", instruction_ld_c_b},
    [0x49] = (instruction_t){"LD C, C", instruction_ld_c_c},
    [0x4A] = (instruction_t){"LD C, D", instruction_ld_c_d},
    [0x4B] = (instruction_t){"LD C, E", instruction_ld_c_e},
    [0x4C] = (instruction_t){"LD C, H", instruction_ld_c_h},
    [0x4D] = (instruction_t){"LD C, L", instruction_ld_c_l},
    [0x4E] = (instruction_t){"LD C, (HL)", instruction_ld_c_deref_hl},
    [0x4F] = (instruction_t){"LD C, A", instruction_ld_c_a},
    [0x50] = (instruction_t){"LD D, B", instruction_ld_d_b},
    [0x51] = (instruction_t){"LD D, C", instruction_ld_d_c},
    [0x52] = (instruction_t){"LD D, D", instruction_ld_d_d},
    [0x53] = (instruction_t){"LD D, E", instruction_ld_d_e},
    [0x54] = (instruction_t){"LD D, H", instruction_ld_d_h},
    [0x55] = (instruction_t){"LD D, L", instruction_ld_d_l},
    [0x56] = (instruction_t){"LD D, (HL)", instruction_ld_d_deref_hl},
    [0x57] = (instruction_t){"LD D, A", instruction_ld_d_a},
    [0x58] = (instruction_t){"LD E, B", instruction_ld_e_b},
    [0x59] = (instruction_t){"LD E, C", instruction_ld_e_c},
    [0x5A] = (instruction_t){"LD E, D", instruction_ld_e_d},
    [0x5B] = (instruction_t){"LD E, E", instruction_ld_e_e},
    [0x5C] = (instruction_t){"LD E, H", instruction_ld_e_h},
    [0x5D] = (instruction_t){"LD E, L", instruction_ld_e_l},
    [0x5E] = (instruction_t){"LD E, (HL)", instruction_ld_e_deref_hl},
    [0x5F] = (instruction_t){"LD E, A", instruction_ld_e_a},
    [0x60] = (instruction_t){"LD H, B", instruction_ld_h_b},
    [0x61] = (instruction_t){"LD H, C", instruction_ld_h_c},
    [0x62] = (instruction_t){"LD H, D", instruction_ld_h_d},
    [0x63] = (instruction_t){"LD H, E", instruction_ld_h_e},
    [0x64] = (instruction_t){"LD H, H", instruction_ld_h_h},
    [0x65] = (instruction_t){"LD H, L", instruction_ld_h_l},
    [0x66] = (instruction_t){"LD H, (HL)", instruction_ld_h_deref_hl},
    [0x67] = (instruction_t){"LD H, A", instruction_ld_h_a},
    [0x68] = (instruction_t){"LD L, B", instruction_ld_l_b},
    [0x69] = (instruction_t){"LD L, C", instruction_ld_l_c},
    [0x6A] = (instruction_t){"LD L, D", instruction_ld_l_d},
    [0x6B] = (instruction_t){"LD L, E", instruction_ld_l_e},
    [0x6C] = (instruction_t){"LD L, H", instruction_ld_l_h},
    [0x6D] = (instruction_t){"LD L, L", instruction_ld_l_l},
    [0x6E] = (instruction_t){"LD L, (HL)", instruction_ld_l_deref_hl},
    [0x6F] = (instruction_t){"LD L, A", instruction_ld_l_a},
    [0x70] = (instruction_t){"LD (HL), B", instruction_ld_deref_hl_b},
    [0x71] = (instruction_t){"LD (HL), C", instruction_ld_deref_hl_c},
    [0x72] = (instruction_t){"LD (HL), D", instruction_ld_deref_hl_d},
    [0x73] = (instruction_t){"LD (HL), E", instruction_ld_deref_hl_e},
    [0x74] = (instruction_t){"LD (HL), H", instruction_ld_deref_hl_h},
    [0x75] = (instruction_t){"LD (HL), L", instruction_ld_deref_hl_l},
    [0x76] = (instruction_t){"HALT", instruction_halt},
    [0x77] = (instruction_t){"LD (HL), A", instruction_ld_deref_hl_a},
    [0x78] = (instruction_t){"LD A, B", instruction_ld_a_b},
    [0x79] = (instruction_t){"LD A, C", instruction_ld_a_c},
    [0x7A] = (instruction_t){"LD A, D", instruction_ld_a_d},
    [0x7B] = (instruction_t){"LD A, E", instruction_ld_a_e},
    [0x7C] = (instruction_t){"LD A, H", instruction_ld_a_h},
    [0x7D] = (instruction_t){"LD A, L", instruction_ld_a_l},
    [0x7E] = (instruction_t){"LD A, (HL)", instruction_ld_a_deref_hl},
    [0x7F] = (instruction_t){"LD A, A", instruction_ld_a_a},
    [0x80] = (instruction_t){"ADD A, B", instruction_add_a_b},
    [0x81] = (instruction_t){"ADD A, C", instruction_add_a_c},
    [0x82] = (instruction_t){"ADD A, D", instruction_add_a_d},
    [0x83] = (instruction_t){"ADD A, E", instruction_add_a_e},
    [0x84] = (instruction_t){"ADD A, H", instruction_add_a_h},
    [0x85] = (instruction_t){"ADD A, L", instruction_add_a_l},
    [0x86] = (instruction_t){"ADD A, (HL)", instruction_add_a_deref_hl},
    [0x87] = (instruction_t){"ADD A, A", instruction_add_a_a},
    [0x88] = (instruction_t){"ADC A, B", instruction_adc_a_b},
    [0x89] = (instruction_t){"ADC A, C", instruction_adc_a_c},
    [0x8A] = (instruction_t){"ADC A, D", instruction_adc_a_d},
    [0x8B] = (instruction_t){"ADC A, E", instruction_adc_a_e},
    [0x8C] = (instruction_t){"ADC A, H", instruction_adc_a_h},
    [0x8D] = (instruction_t){"ADC A, L", instruction_adc_a_l},
    [0x8E] = (instruction_t){"ADC A, (HL)", instruction_adc_a_deref_hl},
    [0x8F] = (instruction_t){"ADC A, A", instruction_adc_a_a},
    [0x90] = (instruction_t){"SUB A, B", instruction_sub_a_b},
    [0x91] = (instruction_t){"SUB A, C", instruction_sub_a_c},
    [0x92] = (instruction_t){"SUB A, D", instruction_sub_a_d},
    [0x93] = (instruction_t){"SUB A, E", instruction_sub_a_e},
    [0x94] = (instruction_t){"SUB A, H", instruction_sub_a_h},
    [0x95] = (instruction_t){"SUB A, L", instruction_sub_a_l},
    [0x96] = (instruction_t){"SUB A, (HL)", instruction_sub_a_deref_hl},
    [0x97] = (instruction_t){"SUB A, A", instruction_sub_a_a},
    [0x98] = (instruction_t){"SBC A, B", instruction_sbc_a_b},
    [0x99] = (instruction_t){"SBC A, C", instruction_sbc_a_c},
    [0x9A] = (instruction_t){"SBC A, D", instruction_sbc_a_d},
    [0x9B] = (instruction_t){"SBC A, E", instruction_sbc_a_e},
    [0x9C] = (instruction_t){"SBC A, H", instruction_sbc_a_h},
    [0x9D] = (instruction_t){"SBC A, L", instruction_sbc_a_l},
    [0x9E] = (instruction_t){"SBC A, (HL)", instruction_sbc_a_deref_hl},
    [0x9F] = (instruction_t){"SBC A, A", instruction_sbc_a_a},
    [0xA0] = (instruction_t){"AND A, B", instruction_and_a_b},
    [0xA1] = (instruction_t){"AND A, C", instruction_and_a_c},
    [0xA2] = (instruction_t){"AND A, D", instruction_and_a_d},
    [0xA3] = (instruction_t){"AND A, E", instruction_and_a_e},
    [0xA4] = (instruction_t){"AND A, H", instruction_and_a_h},
    [0xA5] = (instruction_t){"AND A, L", instruction_and_a_l},
    [0xA6] = (instruction_t){"AND A, (HL)", instruction_and_a_deref_hl},
    [0xA7] = (instruction_t){"AND A, A", instruction_and_a_a},
    [0xA8] = (instruction_t){"XOR A, B", instruction_xor_a_b},
    [0xA9] = (instruction_t){"XOR A, C", instruction_xor_a_c},
    [0xAA] = (instruction_t){"XOR A, D", instruction_xor_a_d},
    [0xAB] = (instruction_t){"XOR A, E", instruction_xor_a_e},
    [0xAC] = (instruction_t){"XOR A, H", instruction_xor_a_h},
    [0xAD] = (instruction_t){"XOR A, L", instruction_xor_a_l},
    [0xAE] = (instruction_t){"XOR A, (HL)", instruction_xor_a_deref_hl},
    [0xAF] = (instruction_t){"XOR A, A", instruction_xor_a_a},
    [0xB0] = (instruction_t){"OR A, B", instruction_or_a_b},
    [0xB1] = (instruction_t){"OR A, C", instruction_or_a_c},
    [0xB2] = (instruction_t){"OR A, D", instruction_or_a_d},
    [0xB3] = (instruction_t){"OR A, E", instruction_or_a_e},
    [0xB4] = (instruction_t){"OR A, H", instruction_or_a_h},
    [0xB5] = (instruction_t){"OR A, L", instruction_or_a_l},
    [0xB6] = (instruction_t){"OR A, (HL)", instruction_or_a_deref_hl},
    [0xB7] = (instruction_t){"OR A, A", instruction_or_a_a},
    [0xB8] = (instruction_t){"CP A, B", instruction_cp_a_b},
    [0xB9] = (instruction_t){"CP A, C", instruction_cp_a_c},
    [0xBA] = (instruction_t){"CP A, D", instruction_cp_a_d},
    [0xBB] = (instruction_t){"CP A, E", instruction_cp_a_e},
    [0xBC] = (instruction_t){"CP A, H", instruction_cp_a_h},
    [0xBD] = (instruction_t){"CP A, L", instruction_cp_a_l},
    [0xBE] = (instruction_t){"CP A, (HL)", instruction_cp_a_deref_hl},
    [0xBF] = (instruction_t){"CP A, A", instruction_cp_a_a},
    [0xC0] = (instruction_t){"RET NZ", instruction_ret_nz},
    [0xC1] = (instruction_t){"POP BC", instruction_pop_bc},
    [0xC2] = (instruction_t){"JP NZ, a16", instruction_jp_nz_a16},
    [0xC3] = (instruction_t){"JP a16", instruction_jp_a16},
    [0xC4] = (instruction_t){"CALL NZ, a16", instruction_call_nz_a16},
    [0xC5] = (instruction_t){"PUSH BC", instruction_push_bc},
    [0xC6] = (instruction_t){"ADD A, n8", instruction_add_a_n8},
    [0xC7] = (instruction_t){"RST $00", instruction_rst_00},
    [0xC8] = (instruction_t){"RET Z", instruction_ret_z},
    [0xC9] = (instruction_t){"RET", instruction_ret},
    [0xCA] = (instruction_t){"JP Z, a16", instruction_jp_z_a16},
    [0xCB] = (instruction_t){"PREFIX", instruction_prefix},
    [0xCC] = (instruction_t){"CALL Z, a16", instruction_call_z_a16},
    [0xCD] = (instruction_t){"CALL a16", instruction_call_a16},
    [0xCE] = (instruction_t){"ADC A, n8", instruction_adc_a_n8},
    [0xCF] = (instruction_t){"RST $08", instruction_rst_08},
    [0xD0] = (instruction_t){"RET NC", instruction_ret_nc},
    [0xD1] = (instruction_t){"POP DE", instruction_pop_de},
    [0xD2] = (instruction_t){"JP NC, a16", instruction_jp_nc_a16},
    [0xD3] = (instruction_t){"ILLEGAL_D3", instruction_illegal_d3},
    [0xD4] = (instruction_t){"CALL NC, a16", instruction_call_nc_a16},
    [0xD5] = (instruction_t){"PUSH DE", instruction_push_de},
    [0xD6] = (instruction_t){"SUB A, n8", instruction_sub_a_n8},
    [0xD7] = (instruction_t){"RST $10", instruction_rst_10},
    [0xD8] = (instruction_t){"RET C", instruction_ret_c},
    [0xD9] = (instruction_t){"RETI", instruction_reti},
    [0xDA] = (instruction_t){"JP C, a16", instruction_jp_c_a16},
    [0xDB] = (instruction_t){"ILLEGAL_DB", instruction_illegal_db},
    [0xDC] = (instruction_t){"CALL C, a16", instruction_call_c_a16},
    [0xDD] = (instruction_t){"ILLEGAL_DD", instruction_illegal_dd},
    [0xDE] = (instruction_t){"SBC A, n8", instruction_sbc_a_n8},
    [0xDF] = (instruction_t){"RST $18", instruction_rst_18},
    [0xE0] = (instruction_t){"LDH (a8), A", instruction_ldh_deref_a8_a},
    [0xE1] = (instruction_t){"POP HL", instruction_pop_hl},
    [0xE2] = (instruction_t){"LDH (C), A", instruction_ldh_deref_c_a},
    [0xE3] = (instruction_t){"ILLEGAL_E3", instruction_illegal_e3},
    [0xE4] = (instruction_t){"ILLEGAL_E4", instruction_illegal_e4},
    [0xE5] = (instruction_t){"PUSH HL", instruction_push_hl},
    [0xE6] = (instruction_t){"AND A, n8", instruction_and_a_n8},
    [0xE7] = (instruction_t){"RST $20", instruction_rst_20},
    [0xE8] = (instruction_t){"ADD SP, e8", instruction_add_sp_e8},
    [0xE9] = (instruction_t){"JP HL", instruction_jp_hl},
    [0xEA] = (instruction_t){"LD (a16), A", instruction_ld_deref_a16_a},
    [0xEB] = (instruction_t){"ILLEGAL_EB", instruction_illegal_eb},
    [0xEC] = (instruction_t){"ILLEGAL_EC", instruction_illegal_ec},
    [0xED] = (instruction_t){"ILLEGAL_ED", instruction_illegal_ed},
    [0xEE] = (instruction_t){"XOR A, n8", instruction_xor_a_n8},
    [0xEF] = (instruction_t){"RST $28", instruction_rst_28},
    [0xF0] = (instruction_t){"LDH A, (a8)", instruction_ldh_a_deref_a8},
    [0xF1] = (instruction_t){"POP AF", instruction_pop_af},
    [0xF2] = (instruction_t){"LDH A, (C)", instruction_ldh_a_deref_c},
    [0xF3] = (instruction_t){"DI", instruction_di},
    [0xF4] = (instruction_t){"ILLEGAL_F4", instruction_illegal_f4},
    [0xF5] = (instruction_t){"PUSH AF", instruction_push_af},
    [0xF6] = (instruction_t){"OR A, n8", instruction_or_a_n8},
    [0xF7] = (instruction_t){"RST $30", instruction_rst_30},
    [0xF8] = (instruction_t){"LD HL, SP+, e8", instruction_ld_hl_inc_sp_e8},
    [0xF9] = (instruction_t){"LD SP, HL", instruction_ld_sp_hl},
    [0xFA] = (instruction_t){"LD A, (a16)", instruction_ld_a_deref_a16},
    [0xFB] = (instruction_t){"EI", instruction_ei},
    [0xFC] = (instruction_t){"ILLEGAL_FC", instruction_illegal_fc},
    [0xFD] = (instruction_t){"ILLEGAL_FD", instruction_illegal_fd},
    [0xFE] = (instruction_t){"CP A, n8", instruction_cp_a_n8},
    [0xFF] = (instruction_t){"RST $38", instruction_rst_38},
};

const instruction_t extended_instructions[256] = {
    [0x00] = (instruction_t){"RLC B", instruction_rlc_b},
    [0x01] = (instruction_t){"RLC C", instruction_rlc_c},
    [0x02] = (instruction_t){"RLC D", instruction_rlc_d},
    [0x03] = (instruction_t){"RLC E", instruction_rlc_e},
    [0x04] = (instruction_t){"RLC H", instruction_rlc_h},
    [0x05] = (instruction_t){"RLC L", instruction_rlc_l},
    [0x06] = (instruction_t){"RLC (HL)", instruction_rlc_deref_hl},
    [0x07] = (instruction_t){"RLC A", instruction_rlc_a},
    [0x08] = (instruction_t){"RRC B", instruction_rrc_b},
    [0x09] = (instruction_t){"RRC C", instruction_rrc_c},
    [0x0A] = (instruction_t){"RRC D", instruction_rrc_d},
    [0x0B] = (instruction_t){"RRC E", instruction_rrc_e},
    [0x0C] = (instruction_t){"RRC H", instruction_rrc_h},
    [0x0D] = (instruction_t){"RRC L", instruction_rrc_l},
    [0x0E] = (instruction_t){"RRC (HL)", instruction_rrc_deref_hl},
    [0x0F] = (instruction_t){"RRC A", instruction_rrc_a},
    [0x10] = (instruction_t){"RL B", instruction_rl_b},
    [0x11] = (instruction_t){"RL C", instruction_rl_c},
    [0x12] = (instruction_t){"RL D", instruction_rl_d},
    [0x13] = (instruction_t){"RL E", instruction_rl_e},
    [0x14] = (instruction_t){"RL H", instruction_rl_h},
    [0x15] = (instruction_t){"RL L", instruction_rl_l},
    [0x16] = (instruction_t){"RL (HL)", instruction_rl_deref_hl},
    [0x17] = (instruction_t){"RL A", instruction_rl_a},
    [0x18] = (instruction_t){"RR B", instruction_rr_b},
    [0x19] = (instruction_t){"RR C", instruction_rr_c},
    [0x1A] = (instruction_t){"RR D", instruction_rr_d},
    [0x1B] = (instruction_t){"RR E", instruction_rr_e},
    [0x1C] = (instruction_t){"RR H", instruction_rr_h},
    [0x1D] = (instruction_t){"RR L", instruction_rr_l},
    [0x1E] = (instruction_t){"RR (HL)", instruction_rr_deref_hl},
    [0x1F] = (instruction_t){"RR A", instruction_rr_a},
    [0x20] = (instruction_t){"SLA B", instruction_sla_b},
    [0x21] = (instruction_t){"SLA C", instruction_sla_c},
    [0x22] = (instruction_t){"SLA D", instruction_sla_d},
    [0x23] = (instruction_t){"SLA E", instruction_sla_e},
    [0x24] = (instruction_t){"SLA H", instruction_sla_h},
    [0x25] = (instruction_t){"SLA L", instruction_sla_l},
    [0x26] = (instruction_t){"SLA (HL)", instruction_sla_deref_hl},
    [0x27] = (instruction_t){"SLA A", instruction_sla_a},
    [0x28] = (instruction_t){"SRA B", instruction_sra_b},
    [0x29] = (instruction_t){"SRA C", instruction_sra_c},
    [0x2A] = (instruction_t){"SRA D", instruction_sra_d},
    [0x2B] = (instruction_t){"SRA E", instruction_sra_e},
    [0x2C] = (instruction_t){"SRA H", instruction_sra_h},
    [0x2D] = (instruction_t){"SRA L", instruction_sra_l},
    [0x2E] = (instruction_t){"SRA (HL)", instruction_sra_deref_hl},
    [0x2F] = (instruction_t){"SRA A", instruction_sra_a},
    [0x30] = (instruction_t){"SWAP B", instruction_swap_b},
    [0x31] = (instruction_t){"SWAP C", instruction_swap_c},
    [0x32] = (instruction_t){"SWAP D", instruction_swap_d},
    [0x33] = (instruction_t){"SWAP E", instruction_swap_e},
    [0x34] = (instruction_t){"SWAP H", instruction_swap_h},
    [0x35] = (instruction_t){"SWAP L", instruction_swap_l},
    [0x36] = (instruction_t){"SWAP (HL)", instruction_swap_deref_hl},
    [0x37] = (instruction_t){"SWAP A", instruction_swap_a},
    [0x38] = (instruction_t){"SRL B", instruction_srl_b},
    [0x39] = (instruction_t){"SRL C", instruction_srl_c},
    [0x3A] = (instruction_t){"SRL D", instruction_srl_d},
    [0x3B] = (instruction_t){"SRL E", instruction_srl_e},
    [0x3C] = (instruction_t){"SRL H", instruction_srl_h},
    [0x3D] = (instruction_t){"SRL L", instruction_srl_l},
    [0x3E] = (instruction_t){"SRL (HL)", instruction_srl_deref_hl},
    [0x3F] = (instruction_t){"SRL A", instruction_srl_a},
    [0x40] = (instruction_t){"BIT 0, B", instruction_bit_0_b},
    [0x41] = (instruction_t){"BIT 0, C", instruction_bit_0_c},
    [0x42] = (instruction_t){"BIT 0, D", instruction_bit_0_d},
    [0x43] = (instruction_t){"BIT 0, E", instruction_bit_0_e},
    [0x44] = (instruction_t){"BIT 0, H", instruction_bit_0_h},
    [0x45] = (instruction_t){"BIT 0, L", instruction_bit_0_l},
    [0x46] = (instruction_t){"BIT 0, (HL)", instruction_bit_0_deref_hl},
    [0x47] = (instruction_t){"BIT 0, A", instruction_bit_0_a},
    [0x48] = (instruction_t){"BIT 1, B", instruction_bit_1_b},
    [0x49] = (instruction_t){"BIT 1, C", instruction_bit_1_c},
    [0x4A] = (instruction_t){"BIT 1, D", instruction_bit_1_d},
    [0x4B] = (instruction_t){"BIT 1, E", instruction_bit_1_e},
    [0x4C] = (instruction_t){"BIT 1, H", instruction_bit_1_h},
    [0x4D] = (instruction_t){"BIT 1, L", instruction_bit_1_l},
    [0x4E] = (instruction_t){"BIT 1, (HL)", instruction_bit_1_deref_hl},
    [0x4F] = (instruction_t){"BIT 1, A", instruction_bit_1_a},
    [0x50] = (instruction_t){"BIT 2, B", instruction_bit_2_b},
    [0x51] = (instruction_t){"BIT 2, C", instruction_bit_2_c},
    [0x52] = (instruction_t){"BIT 2, D", instruction_bit_2_d},
    [0x53] = (instruction_t){"BIT 2, E", instruction_bit_2_e},
    [0x54] = (instruction_t){"BIT 2, H", instruction_bit_2_h},
    [0x55] = (instruction_t){"BIT 2, L", instruction_bit_2_l},
    [0x56] = (instruction_t){"BIT 2, (HL)", instruction_bit_2_deref_hl},
    [0x57] = (instruction_t){"BIT 2, A", instruction_bit_2_a},
    [0x58] = (instruction_t){"BIT 3, B", instruction_bit_3_b},
    [0x59] = (instruction_t){"BIT 3, C", instruction_bit_3_c},
    [0x5A] = (instruction_t){"BIT 3, D", instruction_bit_3_d},
    [0x5B] = (instruction_t){"BIT 3, E", instruction_bit_3_e},
    [0x5C] = (instruction_t){"BIT 3, H", instruction_bit_3_h},
    [0x5D] = (instruction_t){"BIT 3, L", instruction_bit_3_l},
    [0x5E] = (instruction_t){"BIT 3, (HL)", instruction_bit_3_deref_hl},
    [0x5F] = (instruction_t){"BIT 3, A", instruction_bit_3_a},
    [0x60] = (instruction_t){"BIT 4, B", instruction_bit_4_b},
    [0x61] = (instruction_t){"BIT 4, C", instruction_bit_4_c},
    [0x62] = (instruction_t){"BIT 4, D", instruction_bit_4_d},
    [0x63] = (instruction_t){"BIT 4, E", instruction_bit_4_e},
    [0x64] = (instruction_t){"BIT 4, H", instruction_bit_4_h},
    [0x65] = (instruction_t){"BIT 4, L", instruction_bit_4_l},
    [0x66] = (instruction_t){"BIT 4, (HL)", instruction_bit_4_deref_hl},
    [0x67] = (instruction_t){"BIT 4, A", instruction_bit_4_a},
    [0x68] = (instruction_t){"BIT 5, B", instruction_bit_5_b},
    [0x69] = (instruction_t){"BIT 5, C", instruction_bit_5_c},
    [0x6A] = (instruction_t){"BIT 5, D", instruction_bit_5_d},
    [0x6B] = (instruction_t){"BIT 5, E", instruction_bit_5_e},
    [0x6C] = (instruction_t){"BIT 5, H", instruction_bit_5_h},
    [0x6D] = (instruction_t){"BIT 5, L", instruction_bit_5_l},
    [0x6E] = (instruction_t){"BIT 5, (HL)", instruction_bit_5_deref_hl},
    [0x6F] = (instruction_t){"BIT 5, A", instruction_bit_5_a},
    [0x70] = (instruction_t){"BIT 6, B", instruction_bit_6_b},
    [0x71] = (instruction_t){"BIT 6, C", instruction_bit_6_c},
    [0x72] = (instruction_t){"BIT 6, D", instruction_bit_6_d},
    [0x73] = (instruction_t){"BIT 6, E", instruction_bit_6_e},
    [0x74] = (instruction_t){"BIT 6, H", instruction_bit_6_h},
    [0x75] = (instruction_t){"BIT 6, L", instruction_bit_6_l},
    [0x76] = (instruction_t){"BIT 6, (HL)", instruction_bit_6_deref_hl},
    [0x77] = (instruction_t){"BIT 6, A", instruction_bit_6_a},
    [0x78] = (instruction_t){"BIT 7, B", instruction_bit_7_b},
    [0x79] = (instruction_t){"BIT 7, C", instruction_bit_7_c},
    [0x7A] = (instruction_t){"BIT 7, D", instruction_bit_7_d},
    [0x7B] = (instruction_t){"BIT 7, E", instruction_bit_7_e},
    [0x7C] = (instruction_t){"BIT 7, H", instruction_bit_7_h},
    [0x7D] = (instruction_t){"BIT 7, L", instruction_bit_7_l},
    [0x7E] = (instruction_t){"BIT 7, (HL)", instruction_bit_7_deref_hl},
    [0x7F] = (instruction_t){"BIT 7, A", instruction_bit_7_a},
    [0x80] = (instruction_t){"RES 0, B", instruction_res_0_b},
    [0x81] = (instruction_t){"RES 0, C", instruction_res_0_c},
    [0x82] = (instruction_t){"RES 0, D", instruction_res_0_d},
    [0x83] = (instruction_t){"RES 0, E", instruction_res_0_e},
    [0x84] = (instruction_t){"RES 0, H", instruction_res_0_h},
    [0x85] = (instruction_t){"RES 0, L", instruction_res_0_l},
    [0x86] = (instruction_t){"RES 0, (HL)", instruction_res_0_deref_hl},
    [0x87] = (instruction_t){"RES 0, A", instruction_res_0_a},
    [0x88] = (instruction_t){"RES 1, B", instruction_res_1_b},
    [0x89] = (instruction_t){"RES 1, C", instruction_res_1_c},
    [0x8A] = (instruction_t){"RES 1, D", instruction_res_1_d},
    [0x8B] = (instruction_t){"RES 1, E", instruction_res_1_e},
    [0x8C] = (instruction_t){"RES 1, H", instruction_res_1_h},
    [0x8D] = (instruction_t){"RES 1, L", instruction_res_1_l},
    [0x8E] = (instruction_t){"RES 1, (HL)", instruction_res_1_deref_hl},
    [0x8F] = (instruction_t){"RES 1, A", instruction_res_1_a},
    [0x90] = (instruction_t){"RES 2, B", instruction_res_2_b},
    [0x91] = (instruction_t){"RES 2, C", instruction_res_2_c},
    [0x92] = (instruction_t){"RES 2, D", instruction_res_2_d},
    [0x93] = (instruction_t){"RES 2, E", instruction_res_2_e},
    [0x94] = (instruction_t){"RES 2, H", instruction_res_2_h},
    [0x95] = (instruction_t){"RES 2, L", instruction_res_2_l},
    [0x96] = (instruction_t){"RES 2, (HL)", instruction_res_2_deref_hl},
    [0x97] = (instruction_t){"RES 2, A", instruction_res_2_a},
    [0x98] = (instruction_t){"RES 3, B", instruction_res_3_b},
    [0x99] = (instruction_t){"RES 3, C", instruction_res_3_c},
    [0x9A] = (instruction_t){"RES 3, D", instruction_res_3_d},
    [0x9B] = (instruction_t){"RES 3, E", instruction_res_3_e},
    [0x9C] = (instruction_t){"RES 3, H", instruction_res_3_h},
    [0x9D] = (instruction_t){"RES 3, L", instruction_res_3_l},
    [0x9E] = (instruction_t){"RES 3, (HL)", instruction_res_3_deref_hl},
    [0x9F] = (instruction_t){"RES 3, A", instruction_res_3_a},
    [0xA0] = (instruction_t){"RES 4, B", instruction_res_4_b},
    [0xA1] = (instruction_t){"RES 4, C", instruction_res_4_c},
    [0xA2] = (instruction_t){"RES 4, D", instruction_res_4_d},
    [0xA3] = (instruction_t){"RES 4, E", instruction_res_4_e},
    [0xA4] = (instruction_t){"RES 4, H", instruction_res_4_h},
    [0xA5] = (instruction_t){"RES 4, L", instruction_res_4_l},
    [0xA6] = (instruction_t){"RES 4, (HL)", instruction_res_4_deref_hl},
    [0xA7] = (instruction_t){"RES 4, A", instruction_res_4_a},
    [0xA8] = (instruction_t){"RES 5, B", instruction_res_5_b},
    [0xA9] = (instruction_t){"RES 5, C", instruction_res_5_c},
    [0xAA] = (instruction_t){"RES 5, D", instruction_res_5_d},
    [0xAB] = (instruction_t){"RES 5, E", instruction_res_5_e},
    [0xAC] = (instruction_t){"RES 5, H", instruction_res_5_h},
    [0xAD] = (instruction_t){"RES 5, L", instruction_res_5_l},
    [0xAE] = (instruction_t){"RES 5, (HL)", instruction_res_5_deref_hl},
    [0xAF] = (instruction_t){"RES 5, A", instruction_res_5_a},
    [0xB0] = (instruction_t){"RES 6, B", instruction_res_6_b},
    [0xB1] = (instruction_t){"RES 6, C", instruction_res_6_c},
    [0xB2] = (instruction_t){"RES 6, D", instruction_res_6_d},
    [0xB3] = (instruction_t){"RES 6, E", instruction_res_6_e},
    [0xB4] = (instruction_t){"RES 6, H", instruction_res_6_h},
    [0xB5] = (instruction_t){"RES 6, L", instruction_res_6_l},
    [0xB6] = (instruction_t){"RES 6, (HL)", instruction_res_6_deref_hl},
    [0xB7] = (instruction_t){"RES 6, A", instruction_res_6_a},
    [0xB8] = (instruction_t){"RES 7, B", instruction_res_7_b},
    [0xB9] = (instruction_t){"RES 7, C", instruction_res_7_c},
    [0xBA] = (instruction_t){"RES 7, D", instruction_res_7_d},
    [0xBB] = (instruction_t){"RES 7, E", instruction_res_7_e},
    [0xBC] = (instruction_t){"RES 7, H", instruction_res_7_h},
    [0xBD] = (instruction_t){"RES 7, L", instruction_res_7_l},
    [0xBE] = (instruction_t){"RES 7, (HL)", instruction_res_7_deref_hl},
    [0xBF] = (instruction_t){"RES 7, A", instruction_res_7_a},
    [0xC0] = (instruction_t){"SET 0, B", instruction_set_0_b},
    [0xC1] = (instruction_t){"SET 0, C", instruction_set_0_c},
    [0xC2] = (instruction_t){"SET 0, D", instruction_set_0_d},
    [0xC3] = (instruction_t){"SET 0, E", instruction_set_0_e},
    [0xC4] = (instruction_t){"SET 0, H", instruction_set_0_h},
    [0xC5] = (instruction_t){"SET 0, L", instruction_set_0_l},
    [0xC6] = (instruction_t){"SET 0, (HL)", instruction_set_0_deref_hl},
    [0xC7] = (instruction_t){"SET 0, A", instruction_set_0_a},
    [0xC8] = (instruction_t){"SET 1, B", instruction_set_1_b},
    [0xC9] = (instruction_t){"SET 1, C", instruction_set_1_c},
    [0xCA] = (instruction_t){"SET 1, D", instruction_set_1_d},
    [0xCB] = (instruction_t){"SET 1, E", instruction_set_1_e},
    [0xCC] = (instruction_t){"SET 1, H", instruction_set_1_h},
    [0xCD] = (instruction_t){"SET 1, L", instruction_set_1_l},
    [0xCE] = (instruction_t){"SET 1, (HL)", instruction_set_1_deref_hl},
    [0xCF] = (instruction_t){"SET 1, A", instruction_set_1_a},
    [0xD0] = (instruction_t){"SET 2, B", instruction_set_2_b},
    [0xD1] = (instruction_t){"SET 2, C", instruction_set_2_c},
    [0xD2] = (instruction_t){"SET 2, D", instruction_set_2_d},
    [0xD3] = (instruction_t){"SET 2, E", instruction_set_2_e},
    [0xD4] = (instruction_t){"SET 2, H", instruction_set_2_h},
    [0xD5] = (instruction_t){"SET 2, L", instruction_set_2_l},
    [0xD6] = (instruction_t){"SET 2, (HL)", instruction_set_2_deref_hl},
    [0xD7] = (instruction_t){"SET 2, A", instruction_set_2_a},
    [0xD8] = (instruction_t){"SET 3, B", instruction_set_3_b},
    [0xD9] = (instruction_t){"SET 3, C", instruction_set_3_c},
    [0xDA] = (instruction_t){"SET 3, D", instruction_set_3_d},
    [0xDB] = (instruction_t){"SET 3, E", instruction_set_3_e},
    [0xDC] = (instruction_t){"SET 3, H", instruction_set_3_h},
    [0xDD] = (instruction_t){"SET 3, L", instruction_set_3_l},
    [0xDE] = (instruction_t){"SET 3, (HL)", instruction_set_3_deref_hl},
    [0xDF] = (instruction_t){"SET 3, A", instruction_set_3_a},
    [0xE0] = (instruction_t){"SET 4, B", instruction_set_4_b},
    [0xE1] = (instruction_t){"SET 4, C", instruction_set_4_c},
    [0xE2] = (instruction_t){"SET 4, D", instruction_set_4_d},
    [0xE3] = (instruction_t){"SET 4, E", instruction_set_4_e},
    [0xE4] = (instruction_t){"SET 4, H", instruction_set_4_h},
    [0xE5] = (instruction_t){"SET 4, L", instruction_set_4_l},
    [0xE6] = (instruction_t){"SET 4, (HL)", instruction_set_4_deref_hl},
    [0xE7] = (instruction_t){"SET 4, A", instruction_set_4_a},
    [0xE8] = (instruction_t){"SET 5, B", instruction_set_5_b},
    [0xE9] = (instruction_t){"SET 5, C", instruction_set_5_c},
    [0xEA] = (instruction_t){"SET 5, D", instruction_set_5_d},
    [0xEB] = (instruction_t){"SET 5, E", instruction_set_5_e},
    [0xEC] = (instruction_t){"SET 5, H", instruction_set_5_h},
    [0xED] = (instruction_t){"SET 5, L", instruction_set_5_l},
    [0xEE] = (instruction_t){"SET 5, (HL)", instruction_set_5_deref_hl},
    [0xEF] = (instruction_t){"SET 5, A", instruction_set_5_a},
    [0xF0] = (instruction_t){"SET 6, B", instruction_set_6_b},
    [0xF1] = (instruction_t){"SET 6, C", instruction_set_6_c},
    [0xF2] = (instruction_t){"SET 6, D", instruction_set_6_d},
    [0xF3] = (instruction_t){"SET 6, E", instruction_set_6_e},
    [0xF4] = (instruction_t){"SET 6, H", instruction_set_6_h},
    [0xF5] = (instruction_t){"SET 6, L", instruction_set_6_l},
    [0xF6] = (instruction_t){"SET 6, (HL)", instruction_set_6_deref_hl},
    [0xF7] = (instruction_t){"SET 6, A", instruction_set_6_a},
    [0xF8] = (instruction_t){"SET 7, B", instruction_set_7_b},
    [0xF9] = (instruction_t){"SET 7, C", instruction_set_7_c},
    [0xFA] = (instruction_t){"SET 7, D", instruction_set_7_d},
    [0xFB] = (instruction_t){"SET 7, E", instruction_set_7_e},
    [0xFC] = (instruction_t){"SET 7, H", instruction_set_7_h},
    [0xFD] = (instruction_t){"SET 7, L", instruction_set_7_l},
    [0xFE] = (instruction_t){"SET 7, (HL)", instruction_set_7_deref_hl},
    [0xFF] = (instruction_t){"SET 7, A", instruction_set_7_a},
};

instruction_result_t instruction_bit_0_a(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.A, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_0_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = reset_with_flags(cpu->registers.A, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_0_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = set_with_flags(cpu->registers.A, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_0_b(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.B, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_0_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = reset_with_flags(cpu->registers.B, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_0_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = set_with_flags(cpu->registers.B, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_0_c(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.C, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_0_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = reset_with_flags(cpu->registers.C, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_0_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = set_with_flags(cpu->registers.C, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_0_d(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.D, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_0_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = reset_with_flags(cpu->registers.D, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_0_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = set_with_flags(cpu->registers.D, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_0_e(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.E, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_0_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = reset_with_flags(cpu->registers.E, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_0_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = set_with_flags(cpu->registers.E, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_0_f(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.F, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_0_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = reset_with_flags(cpu->registers.F, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_0_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = set_with_flags(cpu->registers.F, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_0_h(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.H, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_0_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = reset_with_flags(cpu->registers.H, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_0_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = set_with_flags(cpu->registers.H, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_0_l(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.L, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_0_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = reset_with_flags(cpu->registers.L, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_0_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = set_with_flags(cpu->registers.L, 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_1_a(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.A, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_1_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = reset_with_flags(cpu->registers.A, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_1_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = set_with_flags(cpu->registers.A, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_1_b(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.B, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_1_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = reset_with_flags(cpu->registers.B, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_1_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = set_with_flags(cpu->registers.B, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_1_c(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.C, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_1_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = reset_with_flags(cpu->registers.C, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_1_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = set_with_flags(cpu->registers.C, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_1_d(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.D, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_1_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = reset_with_flags(cpu->registers.D, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_1_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = set_with_flags(cpu->registers.D, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_1_e(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.E, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_1_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = reset_with_flags(cpu->registers.E, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_1_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = set_with_flags(cpu->registers.E, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_1_f(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.F, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_1_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = reset_with_flags(cpu->registers.F, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_1_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = set_with_flags(cpu->registers.F, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_1_h(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.H, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_1_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = reset_with_flags(cpu->registers.H, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_1_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = set_with_flags(cpu->registers.H, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_1_l(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.L, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_1_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = reset_with_flags(cpu->registers.L, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_1_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = set_with_flags(cpu->registers.L, 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_2_a(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.A, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_2_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = reset_with_flags(cpu->registers.A, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_2_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = set_with_flags(cpu->registers.A, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_2_b(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.B, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_2_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = reset_with_flags(cpu->registers.B, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_2_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = set_with_flags(cpu->registers.B, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_2_c(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.C, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_2_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = reset_with_flags(cpu->registers.C, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_2_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = set_with_flags(cpu->registers.C, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_2_d(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.D, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_2_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = reset_with_flags(cpu->registers.D, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_2_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = set_with_flags(cpu->registers.D, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_2_e(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.E, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_2_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = reset_with_flags(cpu->registers.E, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_2_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = set_with_flags(cpu->registers.E, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_2_f(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.F, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_2_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = reset_with_flags(cpu->registers.F, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_2_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = set_with_flags(cpu->registers.F, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_2_h(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.H, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_2_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = reset_with_flags(cpu->registers.H, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_2_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = set_with_flags(cpu->registers.H, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_2_l(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.L, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_2_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = reset_with_flags(cpu->registers.L, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_2_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = set_with_flags(cpu->registers.L, 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_3_a(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.A, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_3_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = reset_with_flags(cpu->registers.A, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_3_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = set_with_flags(cpu->registers.A, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_3_b(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.B, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_3_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = reset_with_flags(cpu->registers.B, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_3_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = set_with_flags(cpu->registers.B, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_3_c(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.C, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_3_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = reset_with_flags(cpu->registers.C, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_3_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = set_with_flags(cpu->registers.C, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_3_d(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.D, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_3_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = reset_with_flags(cpu->registers.D, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_3_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = set_with_flags(cpu->registers.D, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_3_e(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.E, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_3_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = reset_with_flags(cpu->registers.E, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_3_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = set_with_flags(cpu->registers.E, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_3_f(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.F, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_3_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = reset_with_flags(cpu->registers.F, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_3_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = set_with_flags(cpu->registers.F, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_3_h(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.H, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_3_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = reset_with_flags(cpu->registers.H, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_3_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = set_with_flags(cpu->registers.H, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_3_l(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.L, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_3_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = reset_with_flags(cpu->registers.L, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_3_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = set_with_flags(cpu->registers.L, 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_4_a(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.A, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_4_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = reset_with_flags(cpu->registers.A, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_4_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = set_with_flags(cpu->registers.A, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_4_b(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.B, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_4_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = reset_with_flags(cpu->registers.B, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_4_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = set_with_flags(cpu->registers.B, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_4_c(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.C, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_4_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = reset_with_flags(cpu->registers.C, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_4_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = set_with_flags(cpu->registers.C, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_4_d(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.D, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_4_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = reset_with_flags(cpu->registers.D, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_4_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = set_with_flags(cpu->registers.D, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_4_e(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.E, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_4_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = reset_with_flags(cpu->registers.E, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_4_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = set_with_flags(cpu->registers.E, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_4_f(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.F, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_4_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = reset_with_flags(cpu->registers.F, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_4_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = set_with_flags(cpu->registers.F, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_4_h(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.H, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_4_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = reset_with_flags(cpu->registers.H, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_4_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = set_with_flags(cpu->registers.H, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_4_l(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.L, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_4_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = reset_with_flags(cpu->registers.L, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_4_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = set_with_flags(cpu->registers.L, 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_5_a(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.A, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_5_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = reset_with_flags(cpu->registers.A, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_5_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = set_with_flags(cpu->registers.A, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_5_b(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.B, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_5_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = reset_with_flags(cpu->registers.B, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_5_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = set_with_flags(cpu->registers.B, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_5_c(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.C, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_5_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = reset_with_flags(cpu->registers.C, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_5_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = set_with_flags(cpu->registers.C, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_5_d(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.D, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_5_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = reset_with_flags(cpu->registers.D, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_5_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = set_with_flags(cpu->registers.D, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_5_e(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.E, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_5_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = reset_with_flags(cpu->registers.E, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_5_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = set_with_flags(cpu->registers.E, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_5_f(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.F, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_5_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = reset_with_flags(cpu->registers.F, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_5_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = set_with_flags(cpu->registers.F, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_5_h(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.H, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_5_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = reset_with_flags(cpu->registers.H, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_5_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = set_with_flags(cpu->registers.H, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_5_l(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.L, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_5_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = reset_with_flags(cpu->registers.L, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_5_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = set_with_flags(cpu->registers.L, 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_6_a(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.A, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_6_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = reset_with_flags(cpu->registers.A, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_6_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = set_with_flags(cpu->registers.A, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_6_b(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.B, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_6_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = reset_with_flags(cpu->registers.B, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_6_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = set_with_flags(cpu->registers.B, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_6_c(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.C, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_6_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = reset_with_flags(cpu->registers.C, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_6_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = set_with_flags(cpu->registers.C, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_6_d(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.D, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_6_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = reset_with_flags(cpu->registers.D, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_6_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = set_with_flags(cpu->registers.D, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_6_e(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.E, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_6_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = reset_with_flags(cpu->registers.E, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_6_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = set_with_flags(cpu->registers.E, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_6_f(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.F, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_6_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = reset_with_flags(cpu->registers.F, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_6_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = set_with_flags(cpu->registers.F, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_6_h(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.H, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_6_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = reset_with_flags(cpu->registers.H, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_6_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = set_with_flags(cpu->registers.H, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_6_l(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.L, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_6_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = reset_with_flags(cpu->registers.L, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_6_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = set_with_flags(cpu->registers.L, 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_7_a(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.A, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_7_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = reset_with_flags(cpu->registers.A, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_7_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = set_with_flags(cpu->registers.A, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_7_b(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.B, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_7_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = reset_with_flags(cpu->registers.B, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_7_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = set_with_flags(cpu->registers.B, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_7_c(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.C, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_7_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = reset_with_flags(cpu->registers.C, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_7_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = set_with_flags(cpu->registers.C, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_7_d(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.D, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_7_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = reset_with_flags(cpu->registers.D, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_7_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = set_with_flags(cpu->registers.D, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_7_e(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.E, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_7_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = reset_with_flags(cpu->registers.E, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_7_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = set_with_flags(cpu->registers.E, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_7_f(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.F, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_7_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = reset_with_flags(cpu->registers.F, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_7_f(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F = set_with_flags(cpu->registers.F, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_7_h(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.H, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_7_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = reset_with_flags(cpu->registers.H, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_7_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = set_with_flags(cpu->registers.H, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_7_l(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(cpu->registers.L, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_res_7_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = reset_with_flags(cpu->registers.L, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_set_7_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = set_with_flags(cpu->registers.L, 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

uint16_t read_immediate_u16(cpu_t *cpu, bus_t *bus) {
  return bus_read(bus, cpu->registers.PC++) | bus_read(bus, cpu->registers.PC++)
                                                  << 8;
}

uint8_t read_immediate_u8(cpu_t *cpu, bus_t *bus) {
  return bus_read(bus, cpu->registers.PC++);
}

instruction_result_t instruction_nop(cpu_t *cpu, bus_t *bus) {
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_bc_n16(cpu_t *cpu, bus_t *bus) {
  cpu->registers.BC = read_immediate_u16(cpu, bus);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_ld_deref_bc_a(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.BC, cpu->registers.A);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_bc(cpu_t *cpu, bus_t *bus) {
  cpu->registers.BC++;
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = inc_uint8_with_flags(cpu->registers.B, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_dec_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = dec_uint8_with_flags(cpu->registers.B, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_b_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = read_immediate_u8(cpu, bus);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rlca(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = rlc_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  flags_reset_z(&cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_deref_a16_sp(cpu_t *cpu, bus_t *bus) {
  uint16_t address = read_immediate_u16(cpu, bus);
  bus_write(bus, address, cpu->registers.SP & 0xFF);
  bus_write(bus, address + 1, cpu->registers.SP >> 8);
  return (instruction_result_t){.cycle_count = 5};
}

instruction_result_t instruction_add_hl_bc(cpu_t *cpu, bus_t *bus) {
  cpu->registers.HL = add_uint16_with_flags(
      cpu->registers.HL, cpu->registers.BC, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_a_deref_bc(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = bus_read(bus, cpu->registers.BC);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_dec_bc(cpu_t *cpu, bus_t *bus) {
  cpu->registers.BC--;
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = inc_uint8_with_flags(cpu->registers.C, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_dec_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = dec_uint8_with_flags(cpu->registers.C, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_c_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = read_immediate_u8(cpu, bus);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rrca(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = rrc_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  flags_reset_z(&cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_stop_n8(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0x10\" / \"instruction_stop_n8\" not implemented.");
}

instruction_result_t instruction_ld_de_n16(cpu_t *cpu, bus_t *bus) {
  cpu->registers.DE = read_immediate_u16(cpu, bus);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_ld_deref_de_a(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.DE, cpu->registers.A);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_de(cpu_t *cpu, bus_t *bus) {
  cpu->registers.DE++;
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = inc_uint8_with_flags(cpu->registers.D, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_dec_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = dec_uint8_with_flags(cpu->registers.D, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_d_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = read_immediate_u8(cpu, bus);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rla(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = rl_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  flags_reset_z(&cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_jr_e8(cpu_t *cpu, bus_t *bus) {
  uint8_t signed_offset = read_immediate_u8(cpu, bus);
  cpu->registers.PC += uint8_sign_extend_uint16(signed_offset);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_add_hl_de(cpu_t *cpu, bus_t *bus) {
  cpu->registers.HL = add_uint16_with_flags(
      cpu->registers.HL, cpu->registers.DE, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_a_deref_de(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = bus_read(bus, cpu->registers.DE);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_dec_de(cpu_t *cpu, bus_t *bus) {
  cpu->registers.DE--;
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = inc_uint8_with_flags(cpu->registers.E, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_dec_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = dec_uint8_with_flags(cpu->registers.E, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_e_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = read_immediate_u8(cpu, bus);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rra(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = rr_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  flags_reset_z(&cpu->registers.F);

  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_jr_nz_e8(cpu_t *cpu, bus_t *bus) {
  uint8_t signed_offset = read_immediate_u8(cpu, bus);

  if (!flags_is_z(cpu->registers.F)) {
    cpu->registers.PC += uint8_sign_extend_uint16(signed_offset);
    return (instruction_result_t){.cycle_count = 3};
  }

  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_hl_n16(cpu_t *cpu, bus_t *bus) {
  cpu->registers.HL = read_immediate_u16(cpu, bus);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_ld_inc_deref_hl_a(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.HL++, cpu->registers.A);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.HL++;
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = inc_uint8_with_flags(cpu->registers.H, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_dec_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = dec_uint8_with_flags(cpu->registers.H, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_h_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = read_immediate_u8(cpu, bus);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_daa(cpu_t *cpu, bus_t *bus) {
  int tmp = cpu->registers.A;

  if (!(cpu->registers.F & N_BIT)) {
    if ((cpu->registers.F & H_BIT) || (tmp & 0x0F) > 9)
      tmp += 6;
    if ((cpu->registers.F & C_BIT) || tmp > 0x9F)
      tmp += 0x60;
  } else {
    if (cpu->registers.F & H_BIT) {
      tmp -= 6;
      if (!(cpu->registers.F & C_BIT))
        tmp &= 0xFF;
    }
    if (cpu->registers.F & C_BIT)
      tmp -= 0x60;
  }
  cpu->registers.F &= ~(H_BIT | Z_BIT);
  if (tmp & 0x100)
    cpu->registers.F |= C_BIT;

  cpu->registers.A = tmp & 0xFF;
  if (!cpu->registers.A)
    cpu->registers.F |= Z_BIT;

  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_jr_z_e8(cpu_t *cpu, bus_t *bus) {
  uint8_t signed_offset = read_immediate_u8(cpu, bus);

  if (flags_is_z(cpu->registers.F)) {
    cpu->registers.PC += uint8_sign_extend_uint16(signed_offset);
    return (instruction_result_t){.cycle_count = 3};
  }
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_add_hl_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.HL = add_uint16_with_flags(
      cpu->registers.HL, cpu->registers.HL, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_a_inc_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = bus_read(bus, cpu->registers.HL++);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_dec_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.HL--;
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = inc_uint8_with_flags(cpu->registers.L, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_dec_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = dec_uint8_with_flags(cpu->registers.L, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_l_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = read_immediate_u8(cpu, bus);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_cpl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = ~cpu->registers.A;
  flags_set_h(&cpu->registers.F);
  flags_set_n(&cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_jr_nc_e8(cpu_t *cpu, bus_t *bus) {
  uint8_t signed_offset = read_immediate_u8(cpu, bus);

  if (!flags_is_c(cpu->registers.F)) {
    cpu->registers.PC += uint8_sign_extend_uint16(signed_offset);
    return (instruction_result_t){.cycle_count = 3};
  }

  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_sp_n16(cpu_t *cpu, bus_t *bus) {
  cpu->registers.SP = read_immediate_u16(cpu, bus);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_ld_dec_deref_hl_a(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.HL--, cpu->registers.A);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_sp(cpu_t *cpu, bus_t *bus) {
  cpu->registers.SP++;
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_deref_hl(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.HL,
            inc_uint8_with_flags(bus_read(bus, cpu->registers.HL),
                                 &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_dec_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            dec_uint8_with_flags(bus_read(bus, cpu->registers.HL),
                                 &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_ld_deref_hl_n8(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.HL, read_immediate_u8(cpu, bus));
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_scf(cpu_t *cpu, bus_t *bus) {
  flags_reset_n(&cpu->registers.F);
  flags_reset_h(&cpu->registers.F);
  flags_set_c(&cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_jr_c_e8(cpu_t *cpu, bus_t *bus) {
  uint8_t signed_offset = read_immediate_u8(cpu, bus);

  if (flags_is_c(cpu->registers.F)) {
    cpu->registers.PC += uint8_sign_extend_uint16(signed_offset);
    return (instruction_result_t){.cycle_count = 3};
  }

  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_add_hl_sp(cpu_t *cpu, bus_t *bus) {
  cpu->registers.HL = add_uint16_with_flags(
      cpu->registers.HL, cpu->registers.SP, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_a_dec_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = bus_read(bus, cpu->registers.HL--);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_dec_sp(cpu_t *cpu, bus_t *bus) {
  cpu->registers.SP--;
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_inc_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = inc_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_dec_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = dec_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_a_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = read_immediate_u8(cpu, bus);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ccf(cpu_t *cpu, bus_t *bus) {
  flags_reset_n(&cpu->registers.F);
  flags_reset_h(&cpu->registers.F);

  if (flags_is_c(cpu->registers.F))
    flags_reset_c(&cpu->registers.F);
  else
    flags_set_c(&cpu->registers.F);

  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_b_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = cpu->registers.B;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_b_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = cpu->registers.C;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_b_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = cpu->registers.D;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_b_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = cpu->registers.E;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_b_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = cpu->registers.H;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_b_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = cpu->registers.L;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_b_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = bus_read(bus, cpu->registers.HL);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_b_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = cpu->registers.A;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_c_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = cpu->registers.B;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_c_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = cpu->registers.C;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_c_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = cpu->registers.D;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_c_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = cpu->registers.E;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_c_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = cpu->registers.H;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_c_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = cpu->registers.L;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_c_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = bus_read(bus, cpu->registers.HL);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_c_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = cpu->registers.A;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_d_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = cpu->registers.B;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_d_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = cpu->registers.C;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_d_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = cpu->registers.D;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_d_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = cpu->registers.E;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_d_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = cpu->registers.H;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_d_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = cpu->registers.L;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_d_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = bus_read(bus, cpu->registers.HL);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_d_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = cpu->registers.A;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_e_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = cpu->registers.B;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_e_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = cpu->registers.C;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_e_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = cpu->registers.D;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_e_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = cpu->registers.E;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_e_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = cpu->registers.H;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_e_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = cpu->registers.L;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_e_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = bus_read(bus, cpu->registers.HL);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_e_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = cpu->registers.A;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_h_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = cpu->registers.B;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_h_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = cpu->registers.C;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_h_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = cpu->registers.D;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_h_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = cpu->registers.E;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_h_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = cpu->registers.H;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_h_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = cpu->registers.L;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_h_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = bus_read(bus, cpu->registers.HL);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_h_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = cpu->registers.A;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_l_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = cpu->registers.B;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_l_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = cpu->registers.C;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_l_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = cpu->registers.D;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_l_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = cpu->registers.E;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_l_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = cpu->registers.H;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_l_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = cpu->registers.L;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_l_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = bus_read(bus, cpu->registers.HL);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_l_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = cpu->registers.A;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_deref_hl_b(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.HL, cpu->registers.B);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_deref_hl_c(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.HL, cpu->registers.C);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_deref_hl_d(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.HL, cpu->registers.D);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_deref_hl_e(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.HL, cpu->registers.E);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_deref_hl_h(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.HL, cpu->registers.H);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_deref_hl_l(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.HL, cpu->registers.L);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_halt(cpu_t *cpu, bus_t *bus) {
  cpu->halted = 1;
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_deref_hl_a(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, cpu->registers.HL, cpu->registers.A);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_a_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = cpu->registers.B;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_a_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = cpu->registers.C;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_a_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = cpu->registers.D;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_a_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = cpu->registers.E;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_a_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = cpu->registers.H;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_a_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = cpu->registers.L;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_a_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = bus_read(bus, cpu->registers.HL);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_a_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = cpu->registers.A;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_add_a_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = add_uint8_with_flags(cpu->registers.A, cpu->registers.B,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_add_a_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = add_uint8_with_flags(cpu->registers.A, cpu->registers.C,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_add_a_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = add_uint8_with_flags(cpu->registers.A, cpu->registers.D,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_add_a_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = add_uint8_with_flags(cpu->registers.A, cpu->registers.E,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_add_a_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = add_uint8_with_flags(cpu->registers.A, cpu->registers.H,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_add_a_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = add_uint8_with_flags(cpu->registers.A, cpu->registers.L,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_add_a_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = add_uint8_with_flags(
      cpu->registers.A, bus_read(bus, cpu->registers.HL), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_add_a_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = add_uint8_with_flags(cpu->registers.A, cpu->registers.A,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_adc_a_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = adc_uint8_with_flags(cpu->registers.A, cpu->registers.B,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_adc_a_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = adc_uint8_with_flags(cpu->registers.A, cpu->registers.C,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_adc_a_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = adc_uint8_with_flags(cpu->registers.A, cpu->registers.D,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_adc_a_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = adc_uint8_with_flags(cpu->registers.A, cpu->registers.E,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_adc_a_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = adc_uint8_with_flags(cpu->registers.A, cpu->registers.H,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_adc_a_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = adc_uint8_with_flags(cpu->registers.A, cpu->registers.L,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_adc_a_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = adc_uint8_with_flags(
      cpu->registers.A, bus_read(bus, cpu->registers.HL), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_adc_a_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = adc_uint8_with_flags(cpu->registers.A, cpu->registers.A,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_sub_a_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sub_uint8_with_flags(cpu->registers.A, cpu->registers.B,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_sub_a_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sub_uint8_with_flags(cpu->registers.A, cpu->registers.C,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_sub_a_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sub_uint8_with_flags(cpu->registers.A, cpu->registers.D,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_sub_a_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sub_uint8_with_flags(cpu->registers.A, cpu->registers.E,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_sub_a_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sub_uint8_with_flags(cpu->registers.A, cpu->registers.H,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
  ;
}

instruction_result_t instruction_sub_a_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sub_uint8_with_flags(cpu->registers.A, cpu->registers.L,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_sub_a_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sub_uint8_with_flags(
      cpu->registers.A, bus_read(bus, cpu->registers.HL), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sub_a_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sub_uint8_with_flags(cpu->registers.A, cpu->registers.A,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_sbc_a_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sbc_uint8_with_flags(cpu->registers.A, cpu->registers.B,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_sbc_a_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sbc_uint8_with_flags(cpu->registers.A, cpu->registers.C,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_sbc_a_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sbc_uint8_with_flags(cpu->registers.A, cpu->registers.D,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
  ;
}

instruction_result_t instruction_sbc_a_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sbc_uint8_with_flags(cpu->registers.A, cpu->registers.E,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
  ;
}

instruction_result_t instruction_sbc_a_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sbc_uint8_with_flags(cpu->registers.A, cpu->registers.H,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_sbc_a_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sbc_uint8_with_flags(cpu->registers.A, cpu->registers.L,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_sbc_a_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sbc_uint8_with_flags(
      cpu->registers.A, bus_read(bus, cpu->registers.HL), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sbc_a_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sbc_uint8_with_flags(cpu->registers.A, cpu->registers.A,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_and_a_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = and_uint8_with_flags(cpu->registers.A, cpu->registers.B,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_and_a_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = and_uint8_with_flags(cpu->registers.A, cpu->registers.C,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_and_a_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = and_uint8_with_flags(cpu->registers.A, cpu->registers.D,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_and_a_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = and_uint8_with_flags(cpu->registers.A, cpu->registers.E,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_and_a_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = and_uint8_with_flags(cpu->registers.A, cpu->registers.H,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_and_a_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = and_uint8_with_flags(cpu->registers.A, cpu->registers.L,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_and_a_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = and_uint8_with_flags(
      cpu->registers.A, bus_read(bus, cpu->registers.HL), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_and_a_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = and_uint8_with_flags(cpu->registers.A, cpu->registers.A,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_xor_a_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = xor_uint8_with_flags(cpu->registers.A, cpu->registers.B,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_xor_a_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = xor_uint8_with_flags(cpu->registers.A, cpu->registers.C,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_xor_a_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = xor_uint8_with_flags(cpu->registers.A, cpu->registers.D,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_xor_a_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = xor_uint8_with_flags(cpu->registers.A, cpu->registers.E,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_xor_a_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = xor_uint8_with_flags(cpu->registers.A, cpu->registers.H,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_xor_a_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = xor_uint8_with_flags(cpu->registers.A, cpu->registers.L,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_xor_a_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = xor_uint8_with_flags(
      cpu->registers.A, bus_read(bus, cpu->registers.HL), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_xor_a_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = xor_uint8_with_flags(cpu->registers.A, cpu->registers.A,
                                          &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_or_a_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = or_uint8_with_flags(cpu->registers.A, cpu->registers.B,
                                         &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_or_a_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = or_uint8_with_flags(cpu->registers.A, cpu->registers.C,
                                         &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_or_a_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = or_uint8_with_flags(cpu->registers.A, cpu->registers.D,
                                         &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_or_a_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = or_uint8_with_flags(cpu->registers.A, cpu->registers.E,
                                         &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_or_a_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = or_uint8_with_flags(cpu->registers.A, cpu->registers.H,
                                         &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_or_a_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = or_uint8_with_flags(cpu->registers.A, cpu->registers.L,
                                         &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_or_a_deref_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = or_uint8_with_flags(
      cpu->registers.A, bus_read(bus, cpu->registers.HL), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_or_a_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = or_uint8_with_flags(cpu->registers.A, cpu->registers.A,
                                         &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_cp_a_b(cpu_t *cpu, bus_t *bus) {
  sub_uint8_with_flags(cpu->registers.A, cpu->registers.B, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_cp_a_c(cpu_t *cpu, bus_t *bus) {
  sub_uint8_with_flags(cpu->registers.A, cpu->registers.C, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_cp_a_d(cpu_t *cpu, bus_t *bus) {
  sub_uint8_with_flags(cpu->registers.A, cpu->registers.D, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_cp_a_e(cpu_t *cpu, bus_t *bus) {
  sub_uint8_with_flags(cpu->registers.A, cpu->registers.E, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_cp_a_h(cpu_t *cpu, bus_t *bus) {
  sub_uint8_with_flags(cpu->registers.A, cpu->registers.H, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_cp_a_l(cpu_t *cpu, bus_t *bus) {
  sub_uint8_with_flags(cpu->registers.A, cpu->registers.L, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_cp_a_deref_hl(cpu_t *cpu, bus_t *bus) {
  sub_uint8_with_flags(cpu->registers.A, bus_read(bus, cpu->registers.HL),
                       &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_cp_a_a(cpu_t *cpu, bus_t *bus) {
  sub_uint8_with_flags(cpu->registers.A, cpu->registers.A, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ret_nz(cpu_t *cpu, bus_t *bus) {
  if (!flags_is_z(cpu->registers.F)) {
    cpu->registers.PC = pop_uint16(cpu, bus);
    return (instruction_result_t){.cycle_count = 5};
  }

  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_pop_bc(cpu_t *cpu, bus_t *bus) {
  cpu->registers.BC = pop_uint16(cpu, bus);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_jp_nz_a16(cpu_t *cpu, bus_t *bus) {
  uint16_t address = read_immediate_u16(cpu, bus);

  if (!flags_is_z(cpu->registers.F)) {
    cpu->registers.PC = address;
    return (instruction_result_t){.cycle_count = 4};
  }

  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_jp_a16(cpu_t *cpu, bus_t *bus) {
  cpu->registers.PC = read_immediate_u16(cpu, bus);
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_call_nz_a16(cpu_t *cpu, bus_t *bus) {
  uint16_t address = read_immediate_u16(cpu, bus);

  if (!flags_is_z(cpu->registers.F)) {
    push_uint16(cpu, bus, cpu->registers.PC);
    cpu->registers.PC = address;
    return (instruction_result_t){.cycle_count = 6};
  }

  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_push_bc(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.BC);
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_add_a_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = add_uint8_with_flags(
      cpu->registers.A, read_immediate_u8(cpu, bus), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rst_00(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.PC);
  cpu->registers.PC = 0x00;
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_ret_z(cpu_t *cpu, bus_t *bus) {
  if (flags_is_z(cpu->registers.F)) {
    cpu->registers.PC = pop_uint16(cpu, bus);
    return (instruction_result_t){.cycle_count = 5};
  }

  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ret(cpu_t *cpu, bus_t *bus) {
  cpu->registers.PC = pop_uint16(cpu, bus);
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_jp_z_a16(cpu_t *cpu, bus_t *bus) {
  uint16_t address = read_immediate_u16(cpu, bus);

  if (flags_is_z(cpu->registers.F)) {
    cpu->registers.PC = address;
    return (instruction_result_t){.cycle_count = 4};
  }

  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_prefix(cpu_t *cpu, bus_t *bus) {
  uint8_t next_opcode = bus_read(bus, cpu->registers.PC++);
  instruction_t instruction = extended_instructions[next_opcode];
  return instruction.handler(cpu, bus);
}

instruction_result_t instruction_call_z_a16(cpu_t *cpu, bus_t *bus) {
  uint16_t address = read_immediate_u16(cpu, bus);

  if (flags_is_z(cpu->registers.F)) {
    push_uint16(cpu, bus, cpu->registers.PC);
    cpu->registers.PC = address;
    return (instruction_result_t){.cycle_count = 6};
  }

  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_call_a16(cpu_t *cpu, bus_t *bus) {
  uint16_t address = read_immediate_u16(cpu, bus);
  push_uint16(cpu, bus, cpu->registers.PC);
  cpu->registers.PC = address;
  return (instruction_result_t){.cycle_count = 6};
}

instruction_result_t instruction_adc_a_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = adc_uint8_with_flags(
      cpu->registers.A, read_immediate_u8(cpu, bus), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_rst_08(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.PC);
  cpu->registers.PC = 0x08;
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_ret_nc(cpu_t *cpu, bus_t *bus) {
  if (!flags_is_c(cpu->registers.F)) {
    cpu->registers.PC = pop_uint16(cpu, bus);
    return (instruction_result_t){.cycle_count = 5};
  }

  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_pop_de(cpu_t *cpu, bus_t *bus) {
  cpu->registers.DE = pop_uint16(cpu, bus);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_jp_nc_a16(cpu_t *cpu, bus_t *bus) {
  uint16_t address = read_immediate_u16(cpu, bus);

  if (!flags_is_c(cpu->registers.F)) {
    cpu->registers.PC = address;
    return (instruction_result_t){.cycle_count = 4};
  }

  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_illegal_d3(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0xD3\" / \"instruction_illegal_d3\" not implemented.");
}

instruction_result_t instruction_call_nc_a16(cpu_t *cpu, bus_t *bus) {
  uint16_t address = read_immediate_u16(cpu, bus);

  if (!flags_is_c(cpu->registers.F)) {
    push_uint16(cpu, bus, cpu->registers.PC);
    cpu->registers.PC = address;
    return (instruction_result_t){.cycle_count = 6};
  }

  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_push_de(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.DE);
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_sub_a_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sub_uint8_with_flags(
      cpu->registers.A, read_immediate_u8(cpu, bus), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rst_10(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.PC);
  cpu->registers.PC = 0x10;
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_ret_c(cpu_t *cpu, bus_t *bus) {
  if (flags_is_c(cpu->registers.F)) {
    cpu->registers.PC = pop_uint16(cpu, bus);
    return (instruction_result_t){.cycle_count = 5};
  }

  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_reti(cpu_t *cpu, bus_t *bus) {
  cpu->ime = 1;
  cpu->registers.PC = pop_uint16(cpu, bus);
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_jp_c_a16(cpu_t *cpu, bus_t *bus) {
  uint16_t address = read_immediate_u16(cpu, bus);

  if (flags_is_c(cpu->registers.F)) {
    cpu->registers.PC = address;
    return (instruction_result_t){.cycle_count = 4};
  }

  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_illegal_db(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0xDB\" / \"instruction_illegal_db\" not implemented.");
}

instruction_result_t instruction_call_c_a16(cpu_t *cpu, bus_t *bus) {
  uint16_t address = read_immediate_u16(cpu, bus);

  if (flags_is_c(cpu->registers.F)) {
    push_uint16(cpu, bus, cpu->registers.PC);
    cpu->registers.PC = address;
    return (instruction_result_t){.cycle_count = 6};
  }

  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_illegal_dd(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0xDD\" / \"instruction_illegal_dd\" not implemented.");
}

instruction_result_t instruction_sbc_a_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sbc_uint8_with_flags(
      cpu->registers.A, read_immediate_u8(cpu, bus), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rst_18(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.PC);
  cpu->registers.PC = 0x18;
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_ldh_deref_a8_a(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, 0xFF00 + read_immediate_u8(cpu, bus), cpu->registers.A);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_pop_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.HL = pop_uint16(cpu, bus);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_ldh_deref_c_a(cpu_t *cpu, bus_t *bus) {
  bus_write(bus, 0xFF00 + cpu->registers.C, cpu->registers.A);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_illegal_e3(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0xE3\" / \"instruction_illegal_e3\" not implemented.");
}

instruction_result_t instruction_illegal_e4(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0xE4\" / \"instruction_illegal_e4\" not implemented.");
}

instruction_result_t instruction_push_hl(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.HL);
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_and_a_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = and_uint8_with_flags(
      cpu->registers.A, read_immediate_u8(cpu, bus), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rst_20(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.PC);
  cpu->registers.PC = 0x20;
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_add_sp_e8(cpu_t *cpu, bus_t *bus) {
  uint16_t left = cpu->registers.SP;
  uint16_t right = uint8_sign_extend_uint16(read_immediate_u8(cpu, bus));
  cpu->registers.SP = left + right;

  flags_reset_z(&cpu->registers.F);
  flags_reset_n(&cpu->registers.F);

  if (add_has_half_overflow_uint8(left, right))
    flags_set_h(&cpu->registers.F);
  else
    flags_reset_h(&cpu->registers.F);

  if (add_has_overflow_uint8(left, right))
    flags_set_c(&cpu->registers.F);
  else
    flags_reset_c(&cpu->registers.F);

  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_jp_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.PC = cpu->registers.HL;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_ld_deref_a16_a(cpu_t *cpu, bus_t *bus) {
  uint16_t address = read_immediate_u16(cpu, bus);
  bus_write(bus, address, cpu->registers.A);
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_illegal_eb(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0xEB\" / \"instruction_illegal_eb\" not implemented.");
}

instruction_result_t instruction_illegal_ec(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0xEC\" / \"instruction_illegal_ec\" not implemented.");
}

instruction_result_t instruction_illegal_ed(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0xED\" / \"instruction_illegal_ed\" not implemented.");
}

instruction_result_t instruction_xor_a_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = xor_uint8_with_flags(
      cpu->registers.A, read_immediate_u8(cpu, bus), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rst_28(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.PC);
  cpu->registers.PC = 0x28;
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_ldh_a_deref_a8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = bus_read(bus, 0xFF00 + read_immediate_u8(cpu, bus));
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_pop_af(cpu_t *cpu, bus_t *bus) {
  cpu->registers.F =
      pop_uint8(cpu, bus) & 0xF0; // Only read bits needed for flags
  cpu->registers.A = pop_uint8(cpu, bus);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_ldh_a_deref_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = bus_read(bus, 0xFF00 + cpu->registers.C);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_di(cpu_t *cpu, bus_t *bus) {
  cpu->ime = 0;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_illegal_f4(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0xF4\" / \"instruction_illegal_f4\" not implemented.");
}

instruction_result_t instruction_push_af(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.AF);
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_or_a_n8(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = or_uint8_with_flags(
      cpu->registers.A, read_immediate_u8(cpu, bus), &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rst_30(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.PC);
  cpu->registers.PC = 0x30;
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_ld_hl_inc_sp_e8(cpu_t *cpu, bus_t *bus) {
  uint16_t left = cpu->registers.SP;
  uint16_t right = uint8_sign_extend_uint16(read_immediate_u8(cpu, bus));
  cpu->registers.HL = left + right;

  flags_reset_z(&cpu->registers.F);
  flags_reset_n(&cpu->registers.F);

  if (add_has_half_overflow_uint8(left, right))
    flags_set_h(&cpu->registers.F);
  else
    flags_reset_h(&cpu->registers.F);

  if (add_has_overflow_uint8(left, right))
    flags_set_c(&cpu->registers.F);
  else
    flags_reset_c(&cpu->registers.F);

  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_ld_sp_hl(cpu_t *cpu, bus_t *bus) {
  cpu->registers.SP = cpu->registers.HL;
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_ld_a_deref_a16(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = bus_read(bus, read_immediate_u16(cpu, bus));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_ei(cpu_t *cpu, bus_t *bus) {
  cpu->ime = 1;
  return (instruction_result_t){.cycle_count = 1};
}

instruction_result_t instruction_illegal_fc(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0xFC\" / \"instruction_illegal_fc\" not implemented.");
}

instruction_result_t instruction_illegal_fd(cpu_t *cpu, bus_t *bus) {
  assert(0 && "0xFD\" / \"instruction_illegal_fd\" not implemented.");
}

instruction_result_t instruction_cp_a_n8(cpu_t *cpu, bus_t *bus) {
  sub_uint8_with_flags(cpu->registers.A, read_immediate_u8(cpu, bus),
                       &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rst_38(cpu_t *cpu, bus_t *bus) {
  push_uint16(cpu, bus, cpu->registers.PC);
  cpu->registers.PC = 0x38;
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_rlc_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = rlc_uint8_with_flags(cpu->registers.B, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rlc_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = rlc_uint8_with_flags(cpu->registers.C, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rlc_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = rlc_uint8_with_flags(cpu->registers.D, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rlc_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = rlc_uint8_with_flags(cpu->registers.E, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rlc_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = rlc_uint8_with_flags(cpu->registers.H, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rlc_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = rlc_uint8_with_flags(cpu->registers.L, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rlc_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            rlc_uint8_with_flags(bus_read(bus, cpu->registers.HL),
                                 &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_rlc_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = rlc_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rrc_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = rrc_uint8_with_flags(cpu->registers.B, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rrc_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = rrc_uint8_with_flags(cpu->registers.C, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rrc_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = rrc_uint8_with_flags(cpu->registers.D, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rrc_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = rrc_uint8_with_flags(cpu->registers.E, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rrc_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = rrc_uint8_with_flags(cpu->registers.H, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rrc_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = rrc_uint8_with_flags(cpu->registers.L, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rrc_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            rrc_uint8_with_flags(bus_read(bus, cpu->registers.HL),
                                 &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_rrc_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = rrc_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rl_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = rl_uint8_with_flags(cpu->registers.B, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rl_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = rl_uint8_with_flags(cpu->registers.C, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rl_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = rl_uint8_with_flags(cpu->registers.D, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rl_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = rl_uint8_with_flags(cpu->registers.E, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rl_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = rl_uint8_with_flags(cpu->registers.H, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rl_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = rl_uint8_with_flags(cpu->registers.L, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rl_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(
      bus, address,
      rl_uint8_with_flags(bus_read(bus, cpu->registers.HL), &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_rl_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = rl_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rr_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = rr_uint8_with_flags(cpu->registers.B, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rr_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = rr_uint8_with_flags(cpu->registers.C, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rr_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = rr_uint8_with_flags(cpu->registers.D, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rr_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = rr_uint8_with_flags(cpu->registers.E, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rr_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = rr_uint8_with_flags(cpu->registers.H, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rr_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = rr_uint8_with_flags(cpu->registers.L, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_rr_deref_hl(cpu_t *cpu, bus_t *bus) {
  bus_write(
      bus, cpu->registers.HL,
      rr_uint8_with_flags(bus_read(bus, cpu->registers.HL), &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_rr_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = rr_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sla_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = sl_uint8_with_flags(cpu->registers.B, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sla_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = sl_uint8_with_flags(cpu->registers.C, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sla_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = sl_uint8_with_flags(cpu->registers.D, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sla_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = sl_uint8_with_flags(cpu->registers.E, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sla_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = sl_uint8_with_flags(cpu->registers.H, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sla_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = sl_uint8_with_flags(cpu->registers.L, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sla_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(
      bus, address,
      sl_uint8_with_flags(bus_read(bus, cpu->registers.HL), &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_sla_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sl_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sra_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = sra_uint8_with_flags(cpu->registers.B, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sra_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = sra_uint8_with_flags(cpu->registers.C, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sra_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = sra_uint8_with_flags(cpu->registers.D, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sra_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = sra_uint8_with_flags(cpu->registers.E, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sra_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = sra_uint8_with_flags(cpu->registers.H, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sra_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = sra_uint8_with_flags(cpu->registers.L, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_sra_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            sra_uint8_with_flags(bus_read(bus, cpu->registers.HL),
                                 &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_sra_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = sra_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_swap_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = swap_uint8_with_flags(cpu->registers.B, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_swap_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = swap_uint8_with_flags(cpu->registers.C, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_swap_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = swap_uint8_with_flags(cpu->registers.D, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_swap_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = swap_uint8_with_flags(cpu->registers.E, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_swap_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = swap_uint8_with_flags(cpu->registers.H, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_swap_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = swap_uint8_with_flags(cpu->registers.L, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_swap_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            swap_uint8_with_flags(bus_read(bus, cpu->registers.HL),
                                  &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_swap_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = swap_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_srl_b(cpu_t *cpu, bus_t *bus) {
  cpu->registers.B = srl_uint8_with_flags(cpu->registers.B, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_srl_c(cpu_t *cpu, bus_t *bus) {
  cpu->registers.C = srl_uint8_with_flags(cpu->registers.C, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_srl_d(cpu_t *cpu, bus_t *bus) {
  cpu->registers.D = srl_uint8_with_flags(cpu->registers.D, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_srl_e(cpu_t *cpu, bus_t *bus) {
  cpu->registers.E = srl_uint8_with_flags(cpu->registers.E, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_srl_h(cpu_t *cpu, bus_t *bus) {
  cpu->registers.H = srl_uint8_with_flags(cpu->registers.H, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_srl_l(cpu_t *cpu, bus_t *bus) {
  cpu->registers.L = srl_uint8_with_flags(cpu->registers.L, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_srl_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            srl_uint8_with_flags(bus_read(bus, cpu->registers.HL),
                                 &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_srl_a(cpu_t *cpu, bus_t *bus) {
  cpu->registers.A = srl_uint8_with_flags(cpu->registers.A, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 2};
}

instruction_result_t instruction_bit_0_deref_hl(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(bus_read(bus, cpu->registers.HL), 0, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_bit_2_deref_hl(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(bus_read(bus, cpu->registers.HL), 2, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_bit_1_deref_hl(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(bus_read(bus, cpu->registers.HL), 1, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_bit_3_deref_hl(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(bus_read(bus, cpu->registers.HL), 3, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_bit_4_deref_hl(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(bus_read(bus, cpu->registers.HL), 4, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_bit_5_deref_hl(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(bus_read(bus, cpu->registers.HL), 5, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_bit_6_deref_hl(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(bus_read(bus, cpu->registers.HL), 6, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_bit_7_deref_hl(cpu_t *cpu, bus_t *bus) {
  bit_with_flags(bus_read(bus, cpu->registers.HL), 7, &cpu->registers.F);
  return (instruction_result_t){.cycle_count = 3};
}

instruction_result_t instruction_res_0_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            reset_with_flags(bus_read(bus, address), 0, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_res_1_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            reset_with_flags(bus_read(bus, address), 1, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_res_2_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            reset_with_flags(bus_read(bus, address), 2, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_res_3_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            reset_with_flags(bus_read(bus, address), 3, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_res_4_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            reset_with_flags(bus_read(bus, address), 4, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_res_5_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            reset_with_flags(bus_read(bus, address), 5, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_res_6_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            reset_with_flags(bus_read(bus, address), 6, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_res_7_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            reset_with_flags(bus_read(bus, address), 7, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_set_0_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            set_with_flags(bus_read(bus, address), 0, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_set_1_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            set_with_flags(bus_read(bus, address), 1, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_set_2_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            set_with_flags(bus_read(bus, address), 2, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_set_3_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            set_with_flags(bus_read(bus, address), 3, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_set_4_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            set_with_flags(bus_read(bus, address), 4, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_set_5_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            set_with_flags(bus_read(bus, address), 5, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_set_6_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            set_with_flags(bus_read(bus, address), 6, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}

instruction_result_t instruction_set_7_deref_hl(cpu_t *cpu, bus_t *bus) {
  uint16_t address = cpu->registers.HL;
  bus_write(bus, address,
            set_with_flags(bus_read(bus, address), 7, &cpu->registers.F));
  return (instruction_result_t){.cycle_count = 4};
}
