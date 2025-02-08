#ifndef GBEMU_MBC_MBC3_RAM_BATTERY_H
#define GBEMU_MBC_MBC3_RAM_BATTERY_H

#include <stdint.h>

typedef struct {
    uint8_t *rom_data;
    uint8_t ram_data[32 * 1024];
    uint8_t rom_bank_number;
    uint8_t ram_bank_number;
    int ram_and_timer_enabled;
} mbc_mbc3_ram_battery_t;

#define RAM_AND_TIMER_ENABLE_START_ADDRESS 0x0000
#define RAM_AND_TIMER_ENABLE_END_ADDRESS 0x1FFF


#define ROM_BANK_NUMBER_START_ADDRESS 0x2000
#define ROM_BANK_NUMBER_END_ADDRESS 0x3FFF

#define RAM_BANK_NUMBER_START_WRITE_ADDRESS 0x4000
#define RAM_BANK_NUMBER_END_WRITE_ADDRESS 0x5FFF


int mbc_mbc3_ram_battery_create(mbc_mbc3_ram_battery_t *mbc, uint8_t *rom_data, uint32_t rom_length);

uint8_t mbc_mbc3_ram_battery_read(mbc_mbc3_ram_battery_t *mbc, uint16_t address);

void mbc_mbc3_ram_battery_write(mbc_mbc3_ram_battery_t *mbc, uint16_t address, uint8_t data);

#endif
