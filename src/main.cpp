#include "stdafx.h"
#include "mem.h"
#include "cpu.h"

int main()
{
    Memory memory;
    CPU cpu(memory);

    cpu.reset();
    cpu.run(2);

    return 0;
}