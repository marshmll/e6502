#include "stdafx.h"
#include "mem.h"

Memory::Memory()
{
}

Memory::~Memory()
{
}

void Memory::init()
{
    for (DWord i = 0; i < MAX_MEM_SIZE; ++i)
        data[i] = 0;
}

const Byte Memory::read(const Word &addr)
{
    Byte data = this->data[addr];

    return data;
}

void Memory::write(const Word addr, const Byte data)
{
    this->data[addr] = data;
}
