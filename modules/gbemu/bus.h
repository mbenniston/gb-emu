#ifndef GBEMU_BUS_H
#define GBEMU_BUS_H

#include <stdint.h>

#include "cartridge.h"
#include "interrupt_controller.h"
#include "joypad.h"
#include "lcd.h"
#include "ppu.h"
#include "timer_controller.h"

typedef void (*bus_write_callback)(void *user_data, uint16_t address,
                                   uint8_t data);

typedef struct bus {
  uint8_t memory[0x10000];
  interrupt_controller_t *interrupt_controller;
  timer_controller_t *timer_controller;
  lcd_t *lcd;
  ppu_t *ppu;
  joypad_t *joypad;
  cartridge_t *cartridge;
  bus_write_callback user_write_callback;
  void *user_data;
} bus_t;

#define WORK_RAM_START_ADDRESS 0xC000
#define WORK_RAM_END_ADDRESS 0xDFFF

#define ECHO_WORK_RAM_START_ADDRESS 0xE000
#define ECHO_WORK_RAM_END_ADDRESS 0xFDFF

#define HIGH_RAM_START_ADDRESS 0xFF80
#define HIGH_RAM_END_ADDRESS 0xFFFE

#define BUS_MAX_ADDRESS 0xFFFF

void bus_create(bus_t *bus, interrupt_controller_t *interrupt_controller,
                timer_controller_t *timer_controller, lcd_t *lcd, ppu_t *ppu,
                joypad_t *joypad, cartridge_t *cartridge);

void bus_write(bus_t *bus, uint16_t address, uint8_t data);

uint8_t bus_read(bus_t *bus, uint16_t address);

#endif
