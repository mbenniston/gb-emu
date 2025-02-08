#include "cpu.h"

#include <assert.h>
#include <stdio.h>

#include "instructions/instruction.h"
#include "instructions/instructions.h"

void cpu_create(cpu_t *cpu) {
    cpu->ime = 1;
    cpu->registers.A = 0x01;
    cpu->registers.F = 0xB0;
    cpu->registers.B = 0x00;
    cpu->registers.C = 0x13;
    cpu->registers.D = 0x00;
    cpu->registers.E = 0xD8;
    cpu->registers.H = 0x01;
    cpu->registers.L = 0x4D;
    cpu->registers.PC = 0x100;
    cpu->registers.SP = 0xFFFE;
    cpu->halted = 0;
}

void cpu_tick(cpu_t *cpu, bus_t *bus, int *machine_cycles_elapsed) {
    int total_cycles_elapsed = 0;
    int interrupt_executed = 0;

    // check for halt exit
    if (cpu->halted) {
        uint8_t register_if = bus_read(bus, IF_ADDRESS);
        uint8_t register_ie = bus_read(bus, IE_ADDRESS);
        uint8_t interrupts = register_if & register_ie;

        if (interrupts > 0) {
            cpu->halted = 0;
        } else {
            *machine_cycles_elapsed = 1;
            return;
        }
    }

    // check for interrupts
    if (cpu->ime) {
        uint8_t register_if = bus_read(bus, IF_ADDRESS);
        uint8_t register_ie = bus_read(bus, IE_ADDRESS);
        uint8_t interrupts = register_if & register_ie;

        if (interrupts > 0) {
            uint16_t jump_address = 0;
            if (interrupts & IE_VBLANK) {
                jump_address = 0x40;
                register_if &= ~IE_VBLANK;
            } else if (interrupts & IE_LCD) {
                jump_address = 0x48;
                register_if &= ~IE_LCD;
            } else if (interrupts & IE_TIMER) {
                jump_address = 0x50;
                register_if &= ~IE_TIMER;
            } else if (interrupts & IE_SERIAL) {
                jump_address = 0x58;
                register_if &= ~IE_SERIAL;
            } else if (interrupts & IE_JOYPAD) {
                jump_address = 0x60;
                register_if &= ~IE_JOYPAD;
            } else {
                assert(0 && "Interrupt does not exist");
            }

            // Reset interrupt flag
            bus_write(bus, IF_ADDRESS, register_if);

            // Disable interrupts
            cpu->ime = 0;

            // Push Return address to stack
            bus_write(bus, --cpu->registers.SP, cpu->registers.PC >> 8);
            bus_write(bus, --cpu->registers.SP, cpu->registers.PC & 0xFF);

            // Jump to vector
            cpu->registers.PC = jump_address;

            total_cycles_elapsed += 5;
            interrupt_executed = 1;
        }
    }

    if (!interrupt_executed) {
        uint8_t opcode = bus_read(bus, cpu->registers.PC++);
        instruction_t instruction = instructions[opcode];
        instruction_result_t result = instruction.handler(cpu, bus);
        total_cycles_elapsed += result.cycle_count;
    }


    *machine_cycles_elapsed = total_cycles_elapsed;
}


void cpu_print(cpu_t *cpu) {
    printf("CPU REGISTERS:\n");
    printf("AF: %04X\n", cpu->registers.AF);
    printf("BC: %04X\n", cpu->registers.BC);
    printf("DE: %04X\n", cpu->registers.DE);
    printf("HL: %04X\n", cpu->registers.HL);
    printf("PC: %04X\n", cpu->registers.PC);
    printf("SP: %04X\n", cpu->registers.SP);
}
