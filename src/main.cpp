#include "stdafx.h"
#include "e6502/cpu.h"

int main()
{
    E6502::Memory memory;
    E6502::CPU cpu(memory);

    cpu.reset();
    cpu.execute(6);
    cpu.printState();

    return 0;
}