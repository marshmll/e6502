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
    for (DWORD i = 0; i < MAX_MEM_SIZE; ++i)
        data[i] = 0;
}

const BYTE Memory::read(const WORD &addr)
{
    BYTE data = this->data[addr];

    return data;
}

void Memory::write(const WORD addr, const BYTE data)
{
    this->data[addr] = data;
}
