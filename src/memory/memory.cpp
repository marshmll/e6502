#include "stdafx.h"
#include "memory/memory.h"
#include "memory.h"

E6502::Memory::Memory() {}

E6502::Memory::~Memory() {}

void E6502::Memory::init()
{
    for (DWord i = 0; i < MAX_MEM_SIZE; ++i)
        data[i] = 0;
}

void E6502::Memory::init(const std::string rom_fname)
{
    std::fstream stream(rom_fname);
    if (!stream.is_open())
    {
        throw std::runtime_error("Error opening ROM file \"" + rom_fname + "\". Aborting.");
        exit(EXIT_FAILURE);
    }

    DWord memsize = 0;
    Byte buf;
    while (stream >> buf)
    {
        data[memsize] = buf;
        memsize++;
    }

    stream.close();
    std::cout << "[MEMORY] > " << memsize << " bytes loaded from " << rom_fname << "\n";

    for (DWord i = memsize; i < MAX_MEM_SIZE; ++i)
        data[i] = 0;
}

const E6502::Byte E6502::Memory::read(const Word &addr)
{
    return this->data[(addr & 0b0111111111111111)];
}

void E6502::Memory::write(const Word addr, const Byte data)
{
    this->data[(addr & 0b0111111111111111)] = data;
}
