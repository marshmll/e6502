#pragma once

#include "sizes.h"
#include "mem.h"
#include "instructions.h"
#include "endianness.h"

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

    Word PC; // Program Counter Register
    Byte SP; // Stack Pointer Register

    Byte A; // Accumulator Register
    Byte X; // Index Register X
    Byte Y; // Index Register Y

    Byte C : 1; // Carry Flag
    Byte Z : 1; // Zero Flag
    Byte I : 1; // Interrupt Disable
    Byte D : 1; // Decimal Mode
    Byte B : 1; // Break Command
    Byte V : 1; // Overflow Flag
    Byte N : 1; // Negative Flag
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

    void execute(DWord cycles);

    /**
     * @brief Fetches ONE Byte from the memory pointed by the Program Counter
     * and increments it by 1. Also decrements the cycle count by 1.
     *
     * @param cycles The cycles variable reference.
     *
     * @return Byte
     */
    Byte fetchByte(DWord &cycles);

    /**
     * @brief Fetches ONE Word (two Bytes) from the memory pointed by the Program
     * Counter and increments it by 2. Also decrements the cycle count by 2.
     *
     * @param cycles The cycles variable reference.
     *
     * @return Byte
     */
    Word fetchWord(DWord &cycles);

    /**
     * @brief Reads ONE Byte from a given memory address.
     * Decrements the cycle count by 1, but DOES NOT INCREMENT PROGRAM COUNTER.
     *
     * @param cycles The cycles variable reference.
     *
     * @return Byte
     */
    Byte readByte(DWord &cycles, const Word &addr);

    /**
     * @brief Reads ONE Word (two Bytes) from a given memory address.
     * Decrements the cycle count by 2, but DOES NOT INCREMENT PROGRAM COUNTER.
     *
     * @param cycles The cycles variable reference.
     * @param addr The memory address to read from
     *
     * @return Word
     */
    Word readWord(DWord &cycles, const Word &addr);

    /**
     * @brief Writes ONE Word (two Bytes) of data on a given address
     * in memory. Decrements cycle count by 2.
     *
     * @param cycles The cycles variable reference.
     * @param addr The memory address to write into.
     * @param data The data to write into memory.
     *
     * @return void
     */
    void writeWord(DWord &cycles, const Word &addr, const Word data);

    void setLDAFlags();

    void swapBytesInWord(Word &word);
};