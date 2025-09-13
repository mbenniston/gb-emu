#ifndef GBEMU_MBC_ROM_ONLY_H
#define GBEMU_MBC_ROM_ONLY_H

#define NO_MBC_ROM_BANK_LENGTH (32 * 1024)

#include <stdint.h>

typedef struct {
  uint8_t *rom_data;
} mbc_rom_only_t;

int mbc_rom_only_create(mbc_rom_only_t *mbc, uint8_t *rom_data,
                        uint32_t rom_length);

uint8_t mbc_rom_only_read(mbc_rom_only_t *mbc, uint16_t address);

void mbc_rom_only_write(mbc_rom_only_t *mbc, uint16_t address, uint8_t data);

#endif
