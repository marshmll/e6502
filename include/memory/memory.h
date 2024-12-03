#pragma once

#include "memory/sizes.h"
#include "memory/endianness.h"

namespace E6502
{
    class Memory
    {
    private:
        /* MEMORY DATA ================================================================================ */

        Byte data[MAX_MEM_SIZE]; // Memory data (32 KiB)

    public:
        /* CONSTRUCTOR AND DESTRUCTOR ================================================================= */

        Memory();

        virtual ~Memory();

        /**
         * @brief Sets all memory to 0.
         *
         * @return void
         */
        void init();

        /**
         * @brief Reads a binary ROM file into the 
         * memory array.
         * @param rom_fname The name of the ROM binary file.
         * 
         * @return void
         */
        void init(const std::string rom_fname);

        /**
         * @brief Reads a Byte from memory in a given address.
         * @attention Disconsiders most significant bit from the
         * address, in order to assure that the address is in range of the
         * 32KiB of the ROM.
         *
         * @param addr The address to read from in memory.
         *
         * @return const Byte
         */
        const Byte read(const Word &addr);

        /**
         * @brief Writes a Byte into memory in a given address.
         * @attention Disconsiders most significant bit from the
         * address, in order to assure that the address is in range of the
         * 32KiB of the ROM.
         *
         * @param addr The address to write into memory
         * @param data The data to write into memory
         *
         * @return void
         */
        void write(const Word addr, const Byte data);
    };
}
