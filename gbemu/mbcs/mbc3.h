#ifndef GBEMU_MBC_MBC3_H
#define GBEMU_MBC_MBC3_H

#include <stdint.h>

typedef struct {
    uint8_t *rom_data;
    int selected_bank;
    int mode;
} mbc_mbc3_t;

int mbc_mbc3_create(mbc_mbc3_t *mbc, uint8_t *rom_data, uint32_t rom_length);

uint8_t mbc_mbc3_read(mbc_mbc3_t *mbc, uint16_t address);

void mbc_mbc3_write(mbc_mbc3_t *mbc, uint16_t address, uint8_t data);

#endif
