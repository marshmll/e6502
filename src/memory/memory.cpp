#include "stdafx.h"
#include "memory/memory.h"

E6502::Memory::Memory() {}

E6502::Memory::~Memory() {}

void E6502::Memory::init()
{
    for (DWord i = 0; i < MAX_MEM_SIZE; ++i)
        data[i] = 0;
}

const E6502::Byte E6502::Memory::read(const Word &addr)
{
    Byte data = this->data[addr];

    return data;
}

void E6502::Memory::write(const Word addr, const Byte data)
{
    this->data[addr] = data;
}
