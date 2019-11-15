#include "../include/cpu.h"
#include "../include/instructions.h"
#include <string.h>
#include <stdbool.h>

bool cpu_Stopped = false;

void cpu_Initialise(CPU* cpu)
{
    memset(&cpu->registers, 0, sizeof(RegisterBank));
}

void cpu_Tick(CPU* cpu) 
{
    //read instruction
    lbyte opcode = Memory_Read_byte(&cpu->memory, cpu->registers.PC);   
    Instruction instruction = instruction_set[opcode];
    instruction.handler(cpu, NULL);
    cpu->registers.PC++; 
}
