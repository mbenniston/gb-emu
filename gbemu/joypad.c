#include "joypad.h"

#include <stdio.h>
#include <string.h>

#include "interrupt_controller.h"

void joypad_create(joypad_t *joypad) {
    joypad->state = (joypad_state_t){.select_pressed = 1,
                                     .start_pressed = 1,
                                     .down_pressed = 1,
                                     .up_pressed = 1,
                                     .left_pressed = 1,
                                     .right_pressed = 1,
                                     .a_pressed = 1,
                                     .b_pressed = 1};
    joypad->register_joyp = 0xCF;
}

void joypad_update(joypad_t *joypad, interrupt_controller_t *interrupt_controller, joypad_state_t state) {
    if (memcmp(&joypad->state, &state, sizeof(joypad_state_t)) != 0) {
        interrupt_controller_set_joypad_flag(interrupt_controller);
        joypad->state = state;
    }
}

void joypad_register_write(joypad_t *joypad, uint8_t data) {
    joypad->register_joyp &= ~(JOYPAD_SELECT_BUTTONS | JOYPAD_SELECT_DPAD);
    joypad->register_joyp |= data & (JOYPAD_SELECT_BUTTONS | JOYPAD_SELECT_DPAD);

    int buttons = (data & JOYPAD_SELECT_BUTTONS) == 0;
    int dpad = (data & JOYPAD_SELECT_DPAD) == 0;

    if (buttons) {
        joypad->register_joyp &= 0xF0;
        joypad->register_joyp |= !joypad->state.start_pressed ? JOYPAD_START_DOWN : 0;
        joypad->register_joyp |= !joypad->state.select_pressed ? JOYPAD_SELECT_UP : 0;
        joypad->register_joyp |= !joypad->state.b_pressed ? JOYPAD_B_LEFT : 0;
        joypad->register_joyp |= !joypad->state.a_pressed ? JOYPAD_A_RIGHT : 0;
    }

    if (dpad) {
        joypad->register_joyp &= 0xF0;
        joypad->register_joyp |= !joypad->state.down_pressed ? JOYPAD_START_DOWN : 0;
        joypad->register_joyp |= !joypad->state.up_pressed ? JOYPAD_SELECT_UP : 0;
        joypad->register_joyp |= !joypad->state.left_pressed ? JOYPAD_B_LEFT : 0;
        joypad->register_joyp |= !joypad->state.right_pressed ? JOYPAD_A_RIGHT : 0;
    }

    if (!buttons && !dpad) {
        joypad->register_joyp |= 0xF;
    }
}
