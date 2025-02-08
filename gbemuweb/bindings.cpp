#include "bindings.hpp"
#include <algorithm>
#include <iostream>
#include <string.h>

#include "gbemu.hpp"
static const int SCREEN_PALETTE[5][3] = {
    {0, 0, 0}, {15, 56, 15}, {48, 98, 48}, {139, 172, 15}, {155, 188, 15},
};

DebugInstruction::~DebugInstruction() {
    delete[] mnemonic;
}

DebugInstructionTable::~DebugInstructionTable() {
    for (int i = 0; i < instructions_length; i++)
        delete instructions[i];
    for (int i = 0; i < extended_instructions_length; i++)
        delete extended_instructions[i];
    delete[] instructions;
    delete[] extended_instructions;
}

DebugMemoryDump::~DebugMemoryDump() {
    delete[] data;
}

DebugBreakpoints::DebugBreakpoints(int length) : breakpoints_length(length) {
    breakpoints = new int[length];
}

DebugBreakpoints::~DebugBreakpoints() {
    delete[] breakpoints;
}

Emulator::Emulator(char *data, int data_length) {
    cartridge_load(&cartridge, reinterpret_cast<uint8_t *>(data), data_length);
    emulator_create(&emulator, &cartridge);
    std::cout << "created emulator " << cartridge.title << std::endl;
}

void Emulator::tick(JoypadState *joypadState) {
    joypad_state_t joypad_state;
    joypad_state.select_pressed = joypadState->selectPressed;
    joypad_state.start_pressed = joypadState->startPressed;
    joypad_state.down_pressed = joypadState->downPressed;
    joypad_state.up_pressed = joypadState->upPressed;
    joypad_state.left_pressed = joypadState->leftPressed;
    joypad_state.right_pressed = joypadState->rightPressed;
    joypad_state.a_pressed = joypadState->aPressed;
    joypad_state.b_pressed = joypadState->bPressed;

    for (int i = 0; i < 70224 / 4;) {
        int cycles_elapsed;
        emulator_step(&emulator, joypad_state, &cycles_elapsed);
        i += cycles_elapsed;
    }
    lcd_update_framebuffer(&emulator.lcd, &emulator.ppu);
}

int Emulator::debug_tick(JoypadState *joypadState) {
    joypad_state_t joypad_state;
    joypad_state.select_pressed = joypadState->selectPressed;
    joypad_state.start_pressed = joypadState->startPressed;
    joypad_state.down_pressed = joypadState->downPressed;
    joypad_state.up_pressed = joypadState->upPressed;
    joypad_state.left_pressed = joypadState->leftPressed;
    joypad_state.right_pressed = joypadState->rightPressed;
    joypad_state.a_pressed = joypadState->aPressed;
    joypad_state.b_pressed = joypadState->bPressed;

    bool hit_breakpoint = false;
    int total_cycles_elapsed = 0;

    // for (int i = 0; i < 70224 / 4;) {
    int i = 0;
    for (;;) {
        if (i > 0 &&
            std::find(breakpoints.begin(), breakpoints.end(), emulator.cpu.registers.PC) != breakpoints.end()) {
            hit_breakpoint = true;
            break;
        }
        int cycles_elapsed;
        emulator_step(&emulator, joypad_state, &cycles_elapsed);
        i += cycles_elapsed;
        total_cycles_elapsed += cycles_elapsed;
        if (emulator.lcd.frame_ready)
            break;
    }

    lcd_update_framebuffer(&emulator.lcd, &emulator.ppu);

    return hit_breakpoint;
}

void Emulator::tick_single() {
    joypad_state_t joypad_state = {0};
    int cycles_elapsed;
    emulator_step(&emulator, joypad_state, &cycles_elapsed);
    lcd_update_framebuffer(&emulator.lcd, &emulator.ppu);
}

void *Emulator::get_framebuffer_ptr() {
    return emulator.lcd.framebuffer;
}

int Emulator::get_framebuffer_width() {
    return FB_WIDTH;
}

int Emulator::get_framebuffer_height() {
    return FB_HEIGHT;
}

int Emulator::get_framebuffer_channels() {
    return FB_CHANNELS;
}

DebugCPUState *Emulator::get_debug_cpu_state() {
    auto *state = new DebugCPUState;
    state->AF = emulator.cpu.registers.AF;
    state->BC = emulator.cpu.registers.BC;
    state->DE = emulator.cpu.registers.DE;
    state->HL = emulator.cpu.registers.HL;
    state->PC = emulator.cpu.registers.PC;
    state->SP = emulator.cpu.registers.SP;
    return state;
}

DebugTimerControllerState *Emulator::get_debug_timer_controller_state() {
    auto *state = new DebugTimerControllerState;
    state->div = emulator.timer_controller.register_div;
    state->tac = emulator.timer_controller.register_tac;
    state->tac_enabled = (emulator.timer_controller.register_tac & TAC_ENABLED_BIT) != 0;
    state->tac_increment = emulator.timer_controller.register_tac & 3;
    state->tima = emulator.timer_controller.register_tima;
    state->tma = emulator.timer_controller.register_tma;

    return state;
}

DebugInterruptsState *Emulator::get_debug_interrupts_state() {
    auto *state = new DebugInterruptsState;
    state->ime = emulator.cpu.ime;
    state->register_if = emulator.interrupt_controller.register_if;
    state->register_ie = emulator.interrupt_controller.register_ie;
    state->joypad_requested = emulator.interrupt_controller.register_if & IF_JOYPAD;
    state->serial_requested = emulator.interrupt_controller.register_if & IF_SERIAL;
    state->timer_requested = emulator.interrupt_controller.register_if & IF_TIMER;
    state->lcd_requested = emulator.interrupt_controller.register_if & IF_LCD;
    state->vblank_requested = emulator.interrupt_controller.register_if & IF_VBLANK;
    state->joypad_enabled = emulator.interrupt_controller.register_ie & IE_JOYPAD;
    state->serial_enabled = emulator.interrupt_controller.register_ie & IE_SERIAL;
    state->timer_enabled = emulator.interrupt_controller.register_ie & IE_TIMER;
    state->lcd_enabled = emulator.interrupt_controller.register_ie & IE_LCD;
    state->vblank_enabled = emulator.interrupt_controller.register_ie & IE_VBLANK;

    return state;
}

DebugInstructionTable *Emulator::get_debug_instruction_table() {
    auto *table = new DebugInstructionTable;
    table->instructions = new DebugInstruction *[256];

    for (int i = 0; i < 256; i++) {
        instruction_t instruction = instructions[i];
        size_t name_length = strlen(instruction.name);
        table->instructions[i] = new DebugInstruction;
        table->instructions[i]->mnemonic = new char[name_length + 1];
        strncpy(table->instructions[i]->mnemonic, instruction.name, name_length);
        table->instructions[i]->mnemonic[name_length] = 0;

        table->instructions[i]->opcode = i;
        table->instructions[i]->isPrefix = i == 0xCB;
    }
    table->instructions_length = 256;

    table->extended_instructions = new DebugInstruction *[256];

    for (int i = 0; i < 256; i++) {
        instruction_t instruction = extended_instructions[i];
        size_t name_length = strlen(instruction.name);
        table->extended_instructions[i] = new DebugInstruction;
        table->extended_instructions[i]->mnemonic = new char[name_length + 1];
        strncpy(table->extended_instructions[i]->mnemonic, instruction.name, name_length);
        table->extended_instructions[i]->mnemonic[name_length] = 0;
        table->extended_instructions[i]->opcode = i;
        table->instructions[i]->isPrefix = false;
    }
    table->extended_instructions_length = 256;

    return table;
}

int Emulator::get_debug_memory_max() {
    return BUS_MAX_ADDRESS;
}

DebugMemoryDump *Emulator::get_debug_dump_memory_range(long range_start, long range_length) {
    auto *dump = new DebugMemoryDump;
    dump->data = new char[range_length];
    dump->data_length = range_length;

    for (int i = 0; i < range_length; i++) {
        dump->data[i] = bus_read(&emulator.bus, range_start + i);
    }

    return dump;
}

DebugBreakpoints *Emulator::get_debug_breakpoints() {
    auto *debug_breakpoints = new DebugBreakpoints(breakpoints.size());

    for (int i = 0; i < breakpoints.size(); i++) {
        debug_breakpoints->breakpoints[i] = breakpoints[i];
    }
    return debug_breakpoints;
}

void Emulator::set_debug_breakpoints(DebugBreakpoints *debug_breakpoints) {
    breakpoints.resize(debug_breakpoints->breakpoints_length);
    for (int i = 0; i < breakpoints.size(); i++) {
        breakpoints[i] = debug_breakpoints->breakpoints[i];
    }
}

DebugTileSetDump::DebugTileSetDump() {
}

DebugTileSetDump *Emulator::get_debug_dump_tileset() {
    auto *dump = new DebugTileSetDump;
    const int NUM_TILES_X = 16;
    const int NUM_TILES_Y = 24;
    dump->width = NUM_TILES_X * 8;
    dump->height = NUM_TILES_Y * 8;
    dump->channels = 4;
    dump->data_length = dump->width * dump->height * dump->channels;
    dump->data = new char[dump->data_length];

    // dump serialize
    for (int i = 0; i < NUM_TILES_X; i++) {
        for (int j = 0; j < NUM_TILES_Y; j++) {
            uint16_t tile_address = 0x8000 + (i + j * NUM_TILES_X) * 16;

            // draw individual tile
            for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                    int row_index = tile_address + y * 2;
                    int low_value = (emulator.ppu.vram[row_index - VRAM_ADDRESS] >> (7 - x)) & 0b1;
                    int high_value = (emulator.ppu.vram[row_index + 1 - VRAM_ADDRESS] >> (7 - x)) & 0b1;
                    int palette_index = (low_value | high_value << 1) & 0b11;

                    int px = i * 8 + x;
                    int py = j * 8 + y;
                    int fb_index = (px + py * dump->width) * 4;

                    dump->data[fb_index] = SCREEN_PALETTE[palette_index][0];
                    dump->data[fb_index + 1] = SCREEN_PALETTE[palette_index][1];
                    dump->data[fb_index + 2] = SCREEN_PALETTE[palette_index][2];
                    dump->data[fb_index + 3] = 255;
                }
            }
        }
    }

    return dump;
}

DebugTileSetDump::~DebugTileSetDump() {
    delete[] data;
}
