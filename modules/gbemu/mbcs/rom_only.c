#include "rom_only.h"

#include <stdlib.h>
#include <string.h>

int mbc_rom_only_create(mbc_rom_only_t *mbc, uint8_t *rom_data,
                        uint32_t rom_length) {
  mbc->rom_data = malloc(32 * 1024);
  memcpy(mbc->rom_data, rom_data,
         rom_length < 32 * 1024 ? rom_length : 32 * 1024);
  return 1;
}

uint8_t mbc_rom_only_read(mbc_rom_only_t *mbc, uint16_t address) {
  if (address <= 0x7FFF)
    return mbc->rom_data[address];
  return 0;
}

void mbc_rom_only_write(mbc_rom_only_t *mbc, uint16_t address, uint8_t data) {}

void mbc_rom_only_destroy(mbc_rom_only_t *mbc) { free(mbc->rom_data); }
