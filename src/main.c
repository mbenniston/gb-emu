#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <cfx/cfx.h>

#include "../include/cpu.h"
#include "../include/instructions.h"

extern bool cpu_Stopped;
extern int cpu_DebugCurrentInst;

int main(int argc, char** argv) 
{
    winOpen(800, 600, "GB-EMU");

    CPU cpu;
    cpu_Initialise(&cpu);

    const char* fileName = argv[1];
    FILE* file = fopen(fileName, "rb");
    if(!file) return 1;

    int c, inst = 0;
    while((c = fgetc(file)) != EOF) {
        cpu.memory.ram[inst] = c;
        inst++;
    }

    while(!winGetKey(WIN_KEY_Q)){
        winClear();

        static int rdown = false;
        //free run
        if(winGetKey(WIN_KEY_SPACE))
            cpu_Tick(&cpu);
        else {
            if(winGetKey(WIN_KEY_R) && !rdown && !cpu_Stopped)
            {
                rdown = true;
                cpu_Tick(&cpu);
            } 
            else if(!winGetKey(WIN_KEY_R) && rdown)
            {
                rdown = false;
            }
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


        sprintf(debug_registers, "CI: 0x%X, %s", 
            cpu_DebugCurrentInst, instruction_set[cpu_DebugCurrentInst].name);
        dwDrawString(0, 6 * 8, 2, debug_registers, (Color){255,255,255});

        sprintf(debug_registers, "Z: %d, N: %d, H: %d, C: %d", 
            flags_IsZ(cpu.registers.F), flags_IsN(cpu.registers.F), flags_IsH(cpu.registers.F), flags_IsC(cpu.registers.F));
        dwDrawString(0, 8 * 8, 2, debug_registers, (Color){255,255,255});

        if(cpu_Stopped) {
            dwDrawString(0, 10 * 8, 2, "STOPPED", (Color){255,50,50});
        }

        int immCount = 0;
        for(int i = 0; i < 16; i++) {
            byte b = cpu.memory.ram[i];

            if(immCount > 0) {
                sprintf(debug_registers, "0x%X: #0x%X", i, b);
                immCount--;
            } else {
                if(instruction_set[b].name != NULL) {
                    sprintf(debug_registers, "0x%X: 0x%X, %s", i, b, instruction_set[b].name);
                    immCount += instruction_set[b].numImmediates;
                } 
            }


            dwDrawString(0, (2 * i + 12) * 8, 2, debug_registers, (Color){255,255,255});
            if(cpu.registers.PC == i) { dwDrawString((strlen(debug_registers) * 2 * 8) + 16, (2 * i + 12) * 8, 2, "<-", (Color){50,255,50}); }
        }

        winUpdate();
    }

    winClose();

    return 0;
}