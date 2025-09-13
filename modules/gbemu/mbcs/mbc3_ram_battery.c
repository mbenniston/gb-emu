#include "mbc3_ram_battery.h"

#include <stdio.h>
#include <string.h>

int mbc_mbc3_ram_battery_create(mbc_mbc3_ram_battery_t *mbc, uint8_t *rom_data,
                                uint32_t rom_length) {
  mbc->ram_bank_number = 0;
  mbc->rom_bank_number = 1;
  mbc->rom_data = rom_data;
  memset(mbc->ram_data, 0, 32 * 1024);
  mbc->ram_and_timer_enabled = 0;
  return 1;
}

uint8_t mbc_mbc3_ram_battery_read(mbc_mbc3_ram_battery_t *mbc,
                                  uint16_t address) {
  // bank 0
  if (address <= 0x3FFF)
    return mbc->rom_data[address];

  // ram
  if (address >= 0xA000 && address <= 0xBFFF) {
    if (!mbc->ram_and_timer_enabled)
      return 0xFF;

    return mbc->ram_data[mbc->ram_bank_number * 8 * 1024 + address - 0xA000];
  }

  // bank N
  return mbc->rom_data[mbc->rom_bank_number * 16 * 1024 + (address - 0x4000)];
}

void mbc_mbc3_ram_battery_write(mbc_mbc3_ram_battery_t *mbc, uint16_t address,
                                uint8_t data) {
  if (address <= RAM_AND_TIMER_ENABLE_END_ADDRESS) {
    mbc->ram_and_timer_enabled = (data & 0xF) == 0xA;
    return;
  }

  if (address >= RAM_BANK_NUMBER_START_WRITE_ADDRESS &&
      address <= RAM_BANK_NUMBER_END_WRITE_ADDRESS) {
    mbc->ram_bank_number = data & 0b11;
    return;
  }

  if (address >= ROM_BANK_NUMBER_START_ADDRESS &&
      address <= ROM_BANK_NUMBER_END_ADDRESS) {
    mbc->rom_bank_number = (data == 0 ? 1 : data) & 0x7F;
    return;
  }

  if (address >= 0xA000 && address <= 0xBFFF) {
    if (mbc->ram_and_timer_enabled) {
      mbc->ram_data[mbc->ram_bank_number * 8 * 1024 + (address - 0xA000)] =
          data;
    }
  }
}
