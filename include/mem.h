#pragma once

#include "sizes.h"

class Memory
{
private:
    /* MEMORY DATA ================================================================================ */

    Byte data[MAX_MEM_SIZE]; // Memory data (64 KiB)

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
     * @brief Reads a Byte from memory in a given address.
     *
     * @param addr The address to read from in memory.
     *
     * @return const Byte
     */
    const Byte read(const Word &addr);

    /**
     * @brief Writes a Byte into memory in a given address.
     *
     * @param addr The address to write into memory
     * @param data The data to write into memory
     *
     * @return void
     */
    void write(const Word addr, const Byte data);
};