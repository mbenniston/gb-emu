#include "timer_controller.h"

static int clock_increment_table[] = {
    [0b00] = 256,
    [0b01] = 4,
    [0b10] = 16,
    [0b11] = 64,
};

void timer_controller_create(timer_controller_t *controller) {
  controller->register_div = 0xABCC;
  controller->register_tima = 0;
  controller->register_tma = 0;
  controller->register_tac = 0xF8;
  controller->machine_cycles_since_last_increment = 0;
}

void timer_controller_tick(timer_controller_t *controller,
                           int machine_cycles_elapsed,
                           int *timer_interrupt_requested) {
  controller->register_div += 4 * machine_cycles_elapsed;
  controller->machine_cycles_since_last_increment += machine_cycles_elapsed;

  int increment = clock_increment_table[controller->register_tac & 0b11];
  int amount_to_increment_tima = 0;
  if (controller->machine_cycles_since_last_increment > increment) {
    amount_to_increment_tima =
        controller->machine_cycles_since_last_increment / increment;
    uint16_t left_over_cycles =
        controller->machine_cycles_since_last_increment % increment;
    controller->machine_cycles_since_last_increment = left_over_cycles;
  }

  if (controller->register_tac & TAC_ENABLED_BIT) {
    int tima_will_overflow =
        controller->register_tima + amount_to_increment_tima > 0xFF;
    *timer_interrupt_requested = tima_will_overflow;
    if (tima_will_overflow) {
      controller->register_tima = controller->register_tma;
    } else {
      controller->register_tima += amount_to_increment_tima;
    }
  }
}
