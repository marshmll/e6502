#pragma once

#include "memory/memory.h"
#include "e6502/decode.h"
#include "e6502/instructions.h"

namespace E6502
{
    /* PROCESSOR STATUS FLAGS BITMASKS */
    constexpr Byte NEGATIVE_FLAG            = 0b10000000,
                   OVERFLOW_FLAG            = 0b01000000,
                   BREAK_FLAG               = 0b00010000,
                   DECIMAL_FLAG             = 0b00001000,
                   INTERRUPT_DISABLE_FLAG   = 0b00000100,
                   ZERO_FLAG                = 0b00000010,
                   CARRY_FLAG               = 0b00000001;

    /* RESET AND INTERRRUPT VECTORS */
    constexpr Word RESET_VECTOR     = 0xFFFC,
                   INTERRUPT_VECTOR = 0xFFFE;

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
         * and increments it by 1. Also increments the cycle count by 1.
         *
         * @return Byte
         */
        Byte fetchByte();

        /**
         * @brief Fetches ONE Word (two Bytes) from the memory pointed by the Program
         * Counter and increments it by 2. Also increments the cycle count by 2.
         *
         * @return Word
         */
        Word fetchWord();

        /* MEMORY I/O FUNCTIONS =================================================================== */

        /**
         * @brief Reads ONE Byte from a given memory address.
         * Increments the cycle count by 1, but DOES NOT INCREMENT PROGRAM COUNTER.
         *
         * @return Byte
         */
        Byte readByte(const Word &addr);

        /**
         * @brief Writes ONE Byte of data on a given address
         * in memory. Increments cycle count by 1.
         *
         * @param addr The memory address to write into.
         * @param data The data to write into memory.
         *
         * @return void
         */
        void writeByte(const Word &addr, const Byte data);

        /**
         * @brief Reads ONE Word (two Bytes) from a given memory address.
         * Increments the cycle count by 2, but DOES NOT INCREMENT PROGRAM COUNTER.
         * @param addr The memory address to read from
         *
         * @return Word
         */
        Word readWord(const Word &addr);

        /**
         * @brief Writes ONE Word (two Bytes) of data on a given address
         * in memory. Increments cycle count by 2.
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

        /**
         * @brief Pushes data onto the top of the stack, then decrement SP.
         * Does not change cycle count.
         *
         * @param data The data to push onto the stack.
         *
         * @return void
         */
        void pushByte(const Byte data);

        /**
         * @brief Pushes data onto the top of the stack, then decrement SP by 2.
         * Does not change cycle count.
         *
         * @param data The data to push onto the stack.
         *
         * @return void
         */
        void pushWord(const Word data);

        /**
         * @brief Pops data from the top of the stack. Increments SP first.
         * Does not change cycle count.
         *
         * @return const Byte.
         */
        const Byte popByte();

        /**
         * @brief Pops data from the top of the stack. Increments SP by 2 first.
         * Does not change cycle count.
         *
         * @return const Word
         */
        const Word popWord();

        /* FLAG FUNCTIONS ========================================================================= */

        void setFlag(const Byte &flag, const bool &value);

        const bool isFlagSet(const Byte &flag) const;

        void updateADCFlags(const Byte &operand, const Byte &previous_A_value);

        /**
         * @brief Updates Z (zero) and N (negative) flags when loading
         * values into a register.
         * @attention Sets Z to 1 when loaded a zero value.
         * @attention Sets N to 1 when the seventh bit of the value
         * is 1.
         *
         * @param val The register or value to check.
         *
         * @return void
         */
        void updateZeroAndNegativeFlags(const Byte &val);

        void updateSBCFlags(const Byte &operand, const Byte &previous_A_value);

        void updateCompareFlags(const Byte &operand, const Byte &val);
    };
}
