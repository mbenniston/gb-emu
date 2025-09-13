#include "interrupt_controller.h"

void interrupt_controller_create(interrupt_controller_t *controller) {
  controller->register_ie = 0;
  controller->register_if = 0xE1;
}

void interrupt_controller_set_timer_flag(interrupt_controller_t *controller) {
  controller->register_if |= IF_TIMER;
}

void interrupt_controller_set_vblank_flag(interrupt_controller_t *controller) {
  controller->register_if |= IF_VBLANK;
}

void interrupt_controller_set_lcd_flag(interrupt_controller_t *controller) {
  controller->register_if |= IF_LCD;
}

void interrupt_controller_set_joypad_flag(interrupt_controller_t *controller) {
  controller->register_if |= IF_JOYPAD;
}
