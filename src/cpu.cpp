#include "stdafx.h"
#include "cpu.h"

CPU::CPU(Memory &memory)
    : memory(memory)
{
}

CPU::~CPU()
{
}

void CPU::reset()
{
    SP = 0;                        // Initialize Stack Pointer to 0x000 (0x100)
    PC = 0xFFFC;                   // Initialize the reset vector address
    C = Z = I = D = B = V = N = 0; // Clear Flags
    A = X = Y = 0;                 // Clear other registers

    memory.init(); // Initialize memory
}

void CPU::run(DWORD cicles)
{
    while (cicles > 0)
    {
        BYTE ins = fetch(cicles);
    }
}

const BYTE CPU::fetch(DWORD &cicles)
{
    BYTE data = memory.read(PC);

    ++PC;
    --cicles;

    return data;
}
