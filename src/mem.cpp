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

const BYTE &Memory::read(const WORD &addr)
{
    return data[addr];
}
