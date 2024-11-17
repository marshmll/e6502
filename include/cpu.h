#pragma once

#include "sizes.h"
#include "mem.h"
#include "instructions.h"

/**
 * @class CPU
 *
 * @brief The 6502 CPU class representation.
 */
class CPU
{
private:
    Memory &memory;

    /* REGISTERS ================================================================================== */

    WORD PC; // Program Counter Register
    BYTE SP; // Stack Pointer Register

    BYTE A; // Accumulator Register
    BYTE X; // Index Register X
    BYTE Y; // Index Register Y

    BYTE C : 1; // Carry Flag
    BYTE Z : 1; // Zero Flag
    BYTE I : 1; // Interrupt Disable
    BYTE D : 1; // Decimal Mode
    BYTE B : 1; // Break Command
    BYTE V : 1; // Overflow Flag
    BYTE N : 1; // Negative Flag
public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================= */

    CPU(Memory &memory);

    virtual ~CPU();

    /* FUNCTIONS ================================================================================== */

    void printState();

    /**
     * @brief Sets all register to 0, sets all memory to 0,
     * Set Program counter to 0xFFFC.
     *
     * @return void
     */
    void reset();

    void execute(DWORD cicles);

    /**
     * @brief Fetches ONE BYTE from the memory pointed by the Program Counter
     * and increments it. Also decrements the cicle count.
     *
     * @param cicles The cicles variable reference.
     *
     * @return BYTE
     */
    BYTE fetch(DWORD &cicles);
};