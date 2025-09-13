#ifndef GBEMU_EMULATOR_H
#define GBEMU_EMULATOR_H

#include "bus.h"
#include "cpu.h"
#include "interrupt_controller.h"
#include "joypad.h"
#include "lcd.h"

typedef struct {
  cpu_t cpu;
  interrupt_controller_t interrupt_controller;
  timer_controller_t timer_controller;
  lcd_t lcd;
  bus_t bus;
  ppu_t ppu;
  joypad_t joypad;
} emulator_t;

void emulator_create(emulator_t *emu, cartridge_t *cart);

void emulator_step(emulator_t *emu, joypad_state_t state,
                   int *machine_cycles_elapsed);

#endif
