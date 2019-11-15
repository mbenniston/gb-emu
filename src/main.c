#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <cfx/cfx.h>

#include "../include/cpu.h"

extern bool cpu_Stopped;

int main(int argc, char** argv) 
{
    winOpen(800, 600, "GB-EMU");

    CPU cpu;
    cpu_Initialise(&cpu);

    cpu.registers.BC = 0xFF;

    cpu.memory.ram[0] = 0x0B;
    cpu.memory.ram[1] = 0x0B;
    cpu.memory.ram[2] = 0x0B;
    cpu.memory.ram[3] = 0x10;

    while(!winGetKey(WIN_KEY_Q)){
        winClear();

        static int rdown = false;
        if(winGetKey(WIN_KEY_R) && !rdown)
        {
            rdown = true;
            cpu_Tick(&cpu);
        } 
        else if(!winGetKey(WIN_KEY_R) && rdown)
        {
            rdown = false;
        }
        //debug

        char debug_registers[1024];
        sprintf(debug_registers, "PC:%X SP:%X", 
            cpu.registers.PC, cpu.registers.SP);
        dwDrawString(0, 0, 2, debug_registers, (Color){255,255,255});

        sprintf(debug_registers, "A:%X B:%X C:%X D:%X E:%X H:%X L:%X", 
            cpu.registers.A, cpu.registers.B, cpu.registers.C, cpu.registers.D, cpu.registers.E, cpu.registers.H,
            cpu.registers.L);
        dwDrawString(0, 2 * 8, 2, debug_registers, (Color){255,255,255});

        sprintf(debug_registers, "BC:%X DE:%X HL:%X", 
            cpu.registers.BC, cpu.registers.DE, cpu.registers.HL);
        dwDrawString(0, 4 * 8, 2, debug_registers, (Color){255,255,255});


        if(cpu_Stopped) {
            dwDrawString(0, 6 * 8, 2, "STOPPED", (Color){255,50,50});
        }

        winUpdate();
    }

    winClose();

    return 0;
}