#include "stdafx.h"
#include "mem.h"
#include "cpu.h"

int main()
{
    Memory memory;

    CPU cpu(memory);

    cpu.reset();
    cpu.execute(2);

    cpu.printState();

    return 0;
}