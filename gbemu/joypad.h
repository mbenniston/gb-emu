#ifndef GBEMU_JOYPAD_H
#define GBEMU_JOYPAD_H

#include <stdint.h>

#include "interrupt_controller.h"

#define JOYPAD_ADDRESS 0xFF00
#define JOYPAD_SELECT_BUTTONS   0b100000
#define JOYPAD_SELECT_DPAD      0b10000
#define JOYPAD_START_DOWN 0b01000
#define JOYPAD_SELECT_UP 0b100
#define JOYPAD_B_LEFT 0b10
#define JOYPAD_A_RIGHT 0b1

typedef struct {
    int select_pressed;
    int start_pressed;
    int down_pressed;
    int up_pressed;
    int left_pressed;
    int right_pressed;

    int a_pressed;
    int b_pressed;
} joypad_state_t;

typedef struct {
    uint8_t register_joyp;
    joypad_state_t state;
} joypad_t;

void joypad_create(joypad_t *joypad);

void joypad_update(joypad_t *joypad,
                   interrupt_controller_t *interrupt_controller,
                   joypad_state_t state
);

void joypad_register_write(joypad_t *joypad, uint8_t data);

#endif
