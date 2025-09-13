#include "emulator.h"

#include <stdio.h>

#include "instructions/instruction.h"

void emulator_create(emulator_t *emu, cartridge_t *cart) {
  cpu_create(&emu->cpu);
  interrupt_controller_create(&emu->interrupt_controller);
  lcd_create(&emu->lcd);
  ppu_create(&emu->ppu);
  bus_create(&emu->bus, &emu->interrupt_controller, &emu->timer_controller,
             &emu->lcd, &emu->ppu, &emu->joypad, cart);
}

void emulator_step(emulator_t *emu, joypad_state_t joypad_state,
                   int *machine_cycles_elapsed) {
  // tick cpu
  cpu_tick(&emu->cpu, &emu->bus, machine_cycles_elapsed);

  // tick timer
  int timer_interrupt_requested = 0;
  timer_controller_tick(&emu->timer_controller, *machine_cycles_elapsed,
                        &timer_interrupt_requested);
  if (timer_interrupt_requested) {
    interrupt_controller_set_timer_flag(&emu->interrupt_controller);
  }

  // tick ppu
  ppu_tick(&emu->ppu, &emu->lcd, &emu->bus, &emu->interrupt_controller,
           *machine_cycles_elapsed);

  // update joypad
  joypad_update(&emu->joypad, &emu->interrupt_controller, joypad_state);
}
