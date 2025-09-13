#ifndef GBEMU_ROM_H
#define GBEMU_ROM_H

#include <stdint.h>

#include "mbc.h"

#define CARTRIDGE_TITLE_ADDRESS 0x0134
#define CARTRIDGE_TITLE_LENGTH 16

#define CARTRIDGE_TYPE_ADDRESS 0x0147

#define CARTRIDGE_MIN_LENGTH (32 * 1024)

typedef struct {
  uint8_t *data;
  uint32_t data_length;
  char title[CARTRIDGE_TITLE_LENGTH + 1];
  mbc_t mbc;
} cartridge_t;

cartridge_type_e cartridge_type(cartridge_t *rom);

int cartridge_load(cartridge_t *rom, uint8_t *data, uint32_t data_length);

void cartridge_destroy(cartridge_t *rom);

uint8_t cartridge_read(cartridge_t *rom, uint16_t address);

void cartridge_write(cartridge_t *rom, uint16_t address, uint8_t data);

#endif
