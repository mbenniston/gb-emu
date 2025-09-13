#ifndef GBEMU_TIMER_CONTROLLER_H
#define GBEMU_TIMER_CONTROLLER_H

#include <stdint.h>

#define DIV_ADDRESS 0xFF04
#define TIMA_ADDRESS 0xFF05
#define TMA_ADDRESS 0xFF06
#define TAC_ADDRESS 0xFF07

#define TAC_ENABLED_BIT 0b100

typedef struct {
  uint16_t register_div;
  uint8_t register_tima;
  uint8_t register_tma;
  uint8_t register_tac;
  uint16_t machine_cycles_since_last_increment;
} timer_controller_t;

void timer_controller_create(timer_controller_t *controller);

void timer_controller_tick(timer_controller_t *controller,
                           int machine_cycles_elapsed,
                           int *timer_interrupt_requested);

#endif
