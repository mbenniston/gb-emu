#ifndef GBEMU_INTERRUPT_CONTROLLER_H
#define GBEMU_INTERRUPT_CONTROLLER_H

#include "registers.h"

#define IE_JOYPAD 0b10000
#define IE_SERIAL 0b01000
#define IE_TIMER 0b00100
#define IE_LCD 0b00010
#define IE_VBLANK 0b00001

#define IF_JOYPAD 0b10000
#define IF_SERIAL 0b01000
#define IF_TIMER 0b00100
#define IF_LCD 0b00010
#define IF_VBLANK 0b00001

#define IE_ADDRESS 0xFFFF
#define IF_ADDRESS 0xFF0F

typedef struct {
    uint8_t register_ie;
    uint8_t register_if;
} interrupt_controller_t;

void interrupt_controller_create(interrupt_controller_t *controller);

void interrupt_controller_set_timer_flag(interrupt_controller_t *controller);

void interrupt_controller_set_vblank_flag(interrupt_controller_t *controller);

void interrupt_controller_set_lcd_flag(interrupt_controller_t *controller);

void interrupt_controller_set_joypad_flag(interrupt_controller_t *controller);

#endif
