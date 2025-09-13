#ifndef GBEMU_MBC_H
#define GBEMU_MBC_H
#include <stdint.h>

#include "mbcs/mbc3.h"
#include "mbcs/mbc3_ram_battery.h"
#include "mbcs/rom_only.h"

typedef enum {
  ROM_ONLY = 0X00,
  MBC1 = 0X01,
  MBC1_RAM = 0X02,
  MBC1_RAM_BATTERY = 0X03,
  MBC2 = 0X05,
  MBC2_BATTERY = 0X06,
  ROM_RAM = 0X08,
  ROM_RAM_BATTERY = 0X09,
  MMM01 = 0X0B,
  MMM01_RAM = 0X0C,
  MMM01_RAM_BATTERY = 0X0D,
  MBC3_TIMER_BATTERY = 0X0F,
  MBC3_TIMER_RAM_BATTERY = 0X10,
  MBC3 = 0X11,
  MBC3_RAM = 0X12,
  MBC3_RAM_BATTERY = 0X13,
  MBC5 = 0X19,
  MBC5_RAM = 0X1A,
  MBC5_RAM_BATTERY = 0X1B,
  MBC5_RUMBLE = 0X1C,
  MBC5_RUMBLE_RAM = 0X1D,
  MBC5_RUMBLE_RAM_BATTERY = 0X1E,
  MBC6 = 0X20,
  MBC7_SENSOR_RUMBLE_RAM_BATTERY = 0X22,
  POCKET_CAMERA = 0XFC,
  BANDAI_TAMA5 = 0XFD,
  HUC3 = 0XFE,
  HUC1_RAM_BATTERY = 0XFF,
} cartridge_type_e;

#define CARTRIDGE_ROM_START_ADDRESS 0x0000
#define CARTRIDGE_ROM_END_ADDRESS 0x7FFF

#define CARTRIDGE_RAM_START_ADDRESS 0xA000
#define CARTRIDGE_RAM_END_ADDRESS 0xBFFF

typedef union {
  mbc_rom_only_t rom_only;
  mbc_mbc3_t mbc3;
  mbc_mbc3_ram_battery_t mbc3_ram_battery;
} mbc_u;

typedef struct {
  cartridge_type_e type;
  mbc_u mbc;
} mbc_t;

int mbc_create(mbc_t *mbc, cartridge_type_e type, uint8_t *rom_data,
               uint32_t rom_size);

uint8_t mbc_read(mbc_t *mbc, uint16_t address);

void mbc_write(mbc_t *mbc, uint16_t address, uint8_t data);

void mbc_destroy(mbc_t *mbc);

#endif
