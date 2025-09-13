#include "mbc.h"

#include <assert.h>

#include "mbcs/rom_only.h"
#include <stdio.h>
int mbc_create(mbc_t *mbc, cartridge_type_e type, uint8_t *rom_data,
               uint32_t rom_size) {
  mbc->type = type;
  switch (type) {
  case ROM_ONLY:
  case MBC1:
    mbc->type = ROM_ONLY;
    return mbc_rom_only_create(&mbc->mbc.rom_only, rom_data, rom_size);
  case MBC3:
    return mbc_mbc3_create(&mbc->mbc.mbc3, rom_data, rom_size);
  case MBC3_TIMER_RAM_BATTERY:
  case MBC3_RAM_BATTERY:
    return mbc_mbc3_ram_battery_create(&mbc->mbc.mbc3_ram_battery, rom_data,
                                       rom_size);
  default:
    return 0;
  }
}

uint8_t mbc_read(mbc_t *mbc, uint16_t address) {
  switch (mbc->type) {
  case ROM_ONLY:
    return mbc_rom_only_read(&mbc->mbc.rom_only, address);
  case MBC3:
    return mbc_mbc3_read(&mbc->mbc.mbc3, address);
  case MBC3_TIMER_RAM_BATTERY:

  case MBC3_RAM_BATTERY:
    return mbc_mbc3_ram_battery_read(&mbc->mbc.mbc3_ram_battery, address);
  default:
    assert(0 && "MBC type not supported");
  }
}

void mbc_write(mbc_t *mbc, uint16_t address, uint8_t data) {
  switch (mbc->type) {
  case ROM_ONLY:
    mbc_rom_only_write(&mbc->mbc.rom_only, address, data);
    break;
  case MBC3:
    mbc_mbc3_write(&mbc->mbc.mbc3, address, data);
    break;
  case MBC3_TIMER_RAM_BATTERY:
  case MBC3_RAM_BATTERY:
    mbc_mbc3_ram_battery_write(&mbc->mbc.mbc3_ram_battery, address, data);
    break;
  default:
    assert(0 && "MBC type not supported");
  }
}

void mbc_destroy(mbc_t *mbc) {}
