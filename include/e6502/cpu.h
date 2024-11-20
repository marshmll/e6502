#pragma once

#include "memory/memory.h"
#include "e6502/decode.h"
#include "e6502/instructions.h"

namespace E6502
{
    /**
     * @class CPU
     *
     * @brief The 6502 CPU class representation.
     */
    class CPU
    {
    public:
        /* MEMORY BUS ============================================================================= */

        Memory &memory;

        /* CLOCK ================================================================================== */

        long unsigned int clkCycles;

        /* REGISTERS ============================================================================== */

        Word PC; // Program Counter Register
        Byte SP; // Stack Pointer Register

        Byte A; // Accumulator Register
        Byte X; // Index Register X
        Byte Y; // Index Register Y
        Byte P; // Processor Status Register (+) | N | V | - | B | D | I | Z | C | (-)

        /* CONSTRUCTOR AND DESTRUCTOR ============================================================= */

        CPU(Memory &memory);

        virtual ~CPU();

        /* DEBUG FUNCTIONS ======================================================================== */

        void printState();

        /* EXECUTION FUNCTIONS ==================================================================== */

        /**
         * @brief Sets all register to 0, sets all memory to 0,
         * Set Program counter to 0xFFFC.
         *
         * @return void
         */
        void reset();

        /**
         * @brief Runs instructions pointed by Program Counter for a
         * given amount of cycles.
         *
         * @attention Implementation is in microcode.cpp file.
         *
         *
         * @return void
         */
        void execute(int cycles);

        /* INSTRUCTION FETCH FUNCTIONS ============================================================ */

        /**
         * @brief Fetches ONE Byte from the memory pointed by the Program Counter
         * and increments it by 1. Also decrements the cycle count by 1.
         *
         * @return Byte
         */
        Byte fetchByte();

        /**
         * @brief Fetches ONE Word (two Bytes) from the memory pointed by the Program
         * Counter and increments it by 2. Also decrements the cycle count by 2.
         *
         * @return Word
         */
        Word fetchWord();

        /* MEMORY I/O FUNCTIONS =================================================================== */

        /**
         * @brief Reads ONE Byte from a given memory address.
         * Decrements the cycle count by 1, but DOES NOT INCREMENT PROGRAM COUNTER.
         *
         * @return Byte
         */
        Byte readByte(const Word &addr);

        /**
         * @brief Reads ONE Word (two Bytes) from a given memory address.
         * Decrements the cycle count by 2, but DOES NOT INCREMENT PROGRAM COUNTER.
         * @param addr The memory address to read from
         *
         * @return Word
         */
        Word readWord(const Word &addr);

        /**
         * @brief Writes ONE Word (two Bytes) of data on a given address
         * in memory. Decrements cycle count by 2.
         *
         * @param addr The memory address to write into.
         * @param data The data to write into memory.
         *
         * @return void
         */
        void writeWord(const Word &addr, const Word data);

        /**
         * @brief Swaps the upper and lower bytes in a Word.
         *
         * @param word A word reference.
         *
         * @return void.
         */
        void swapBytesInWord(Word &word);

        /**
         * @brief Check if the upper byte (page) has changed. If so,
         * then the page has crossed.
         *
         * @param prev_addr The previous address to compare if page crossed
         * @param curr_addr The current address to compare if page crossed
         *
         * @return const bool
         */
        const bool pageCrossed(const Word &prev_addr, const Word &curr_addr);

        /* FLAG FUNCTIONS ========================================================================= */

        /**
         * @brief Sets Z (zero) and N (negative) flags when loading
         * values into a register.
         * @attention Sets Z to 1 when loaded a zero value.
         * @attention Sets N to 1 when the seventh bit of the value
         * is 1.
         *
         * @param reg The register to check.
         *
         * @return void
         */
        void setLoadFlags(const Byte &reg);
    };
}
