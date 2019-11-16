#include "../include/cpu.h"
#include "../include/instructions.h"
#include <string.h>
#include <stdbool.h>

bool cpu_Stopped = false;

lbyte cpu_DebugCurrentInst = 0xFF;

void cpu_Initialise(CPU* cpu)
{
    memset(&cpu->registers, 0, sizeof(RegisterBank));
}

void cpu_Tick(CPU* cpu) 
{
    //read instruction
    lbyte opcode = Memory_Read_byte(&cpu->memory, cpu->registers.PC);   
    Instruction instruction = instruction_set[opcode];

    switch (instruction.numImmediates)
    {
    case 1:
    {
        byte value = Memory_Read_byte(&cpu->memory, ++cpu->registers.PC);
        instruction.handler(cpu, &value);
    }
        break;
    
    default:
        instruction.handler(cpu, NULL);
        break;
    }

    cpu->registers.PC++; 

    cpu_DebugCurrentInst = opcode;
}

static const int Z_bit = 0b10000000; 
static const int N_bit = 0b01000000; 
static const int H_bit = 0b00100000; 
static const int C_bit = 0b00010000; 

void flags_SetZ(byte* f) 
{
    *f |= Z_bit;
}

void flags_ResetZ(byte* f) 
{
    *f &= ~Z_bit;
}

void flags_SetN(byte* f) 
{
    *f |= N_bit;
}

void flags_ResetN(byte* f) 
{
    *f &= ~N_bit;
}

void flags_SetH(byte* f) 
{
    *f |= H_bit;

}

void flags_ResetH(byte* f) 
{
    *f &= ~H_bit;

}

void flags_SetC(byte* f) 
{
    *f |= C_bit;

}

void flags_ResetC(byte* f) 
{
    *f &= ~C_bit;
}

void flags_ResetAll(byte* f)
{
    *f = 0;
}

bool flags_IsZ(byte f) 
{
    return (f & Z_bit) > 0;
}

bool flags_IsN(byte f) 
{
    return (f & N_bit) > 0;
}

bool flags_IsH(byte f) 
{
    return (f & H_bit) > 0;
}

bool flags_IsC(byte f) 
{
    return (f & C_bit) > 0;
}