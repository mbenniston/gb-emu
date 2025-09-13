#ifndef GBEMU_REGISTERS
#define GBEMU_REGISTERS

#include <stdint.h>
#define Z_BIT (1 << 7)
#define N_BIT (1 << 6)
#define H_BIT (1 << 5)
#define C_BIT (1 << 4)

typedef struct {
  union {
    uint16_t AF;

    struct {
      uint8_t F, A;
    };
  };

  union {
    uint16_t BC;

    struct {
      uint8_t C, B;
    };
  };

  union {
    uint16_t DE;

    struct {
      uint8_t E, D;
    };
  };

  union {
    uint16_t HL;

    struct {
      uint8_t L, H;
    };
  };

  uint16_t SP;
  uint16_t PC;
} registers_t;

void flags_reset_all(uint8_t *f);

void flags_set_z(uint8_t *f);

void flags_reset_z(uint8_t *f);

int flags_is_z(uint8_t f);

void flags_set_n(uint8_t *f);

void flags_reset_n(uint8_t *f);

int flags_is_n(uint8_t f);

void flags_set_h(uint8_t *f);

void flags_reset_h(uint8_t *f);

int flags_is_h(uint8_t f);

void flags_set_c(uint8_t *f);

void flags_reset_c(uint8_t *f);

int flags_is_c(uint8_t f);

#endif
