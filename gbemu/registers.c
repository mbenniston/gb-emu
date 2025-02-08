#include "registers.h"


void flags_set_z(uint8_t *f) {
    *f |= Z_BIT;
}

void flags_reset_z(uint8_t *f) {
    *f &= ~Z_BIT;
}

void flags_set_n(uint8_t *f) {
    *f |= N_BIT;
}

void flags_reset_n(uint8_t *f) {
    *f &= ~N_BIT;
}

void flags_set_h(uint8_t *f) {
    *f |= H_BIT;
}

void flags_reset_h(uint8_t *f) {
    *f &= ~H_BIT;
}

void flags_set_c(uint8_t *f) {
    *f |= C_BIT;
}

void flags_reset_c(uint8_t *f) {
    *f &= ~C_BIT;
}

void flags_reset_all(uint8_t *f) {
    *f = 0;
}

int flags_is_z(uint8_t f) {
    return (f & Z_BIT) > 0;
}

int flags_is_n(uint8_t f) {
    return (f & N_BIT) > 0;
}

int flags_is_h(uint8_t f) {
    return (f & H_BIT) > 0;
}

int flags_is_c(uint8_t f) {
    return (f & C_BIT) > 0;
}
