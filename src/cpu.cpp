#include "stdafx.h"
#include "cpu.h"

CPU::CPU(Memory &memory) : memory(memory) {}

CPU::~CPU() {}

void CPU::printState()
{
    std::cout << "***** CPU STATE *****" << "\n"
              << "> PC: 0x" << std::hex << PC << "\n"
              << "> SP: 0x" << std::hex << static_cast<int>(SP) << "\n"
              << "> A: 0x" << std::hex << static_cast<int>(A) << "\n"
              << "> X: 0x" << std::hex << static_cast<int>(X) << "\n"
              << "> Y: 0x" << std::hex << static_cast<int>(Y) << "\n"
              << "> C: 0x" << std::hex << static_cast<int>(C) << "\n"
              << "> Z: 0x" << std::hex << static_cast<int>(Z) << "\n"
              << "> I: 0x" << std::hex << static_cast<int>(I) << "\n"
              << "> D: 0x" << std::hex << static_cast<int>(D) << "\n"
              << "> B: 0x" << std::hex << static_cast<int>(B) << "\n"
              << "> V: 0x" << std::hex << static_cast<int>(V) << "\n"
              << "> N: 0x" << std::hex << static_cast<int>(N) << "\n";
}

void CPU::reset()
{
    SP = 0;                        // Initialize Stack Pointer to 0x000 (0x100)
    PC = 0xFFFC;                   // Initialize the reset vector address
    C = Z = I = D = B = V = N = 0; // Clear Flags
    A = X = Y = 0;                 // Clear other registers

    memory.init(); // Initialize memory

    memory.write(0xFFFC, LDA_IM);
    memory.write(0xFFFD, 0x69);
}

void CPU::execute(DWORD cicles)
{
    while (cicles > 0)
    {
        BYTE ins = fetch(cicles);

        switch (ins)
        {
        /* LOAD ACCUMULATOR IMMEDIATE ============================================================= */
        case LDA_IM:
        {
            const BYTE value = fetch(cicles); // Fetch immediate value
            A = value;                        // Copies the value into the accumulator
            Z = (BYTE)(A == 0);               // Sets zero flag if accumulator is zero.
            N = (BYTE)((A & 0b10000000) > 0); // Sets negative flag if seventh bit is 1.
            break;
        }
        default:
        {
            std::cout << "UNKNOWN INSTRUCTION: 0x" << std::hex << static_cast<int>(ins) << "\n";
            break;
        }
        }
    }
}

BYTE CPU::fetch(DWORD &cicles)
{
    BYTE data = memory.read(PC);

    ++PC;
    --cicles;

    return data;
}
