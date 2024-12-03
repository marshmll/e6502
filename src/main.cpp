#include "stdafx.h"
#include "e6502/cpu.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Modo de uso: " << argv[0] << " <rom>" << "\n";
        exit(EXIT_FAILURE);
    }

    E6502::Memory memory;
    E6502::CPU cpu(memory);

    memory.init(argv[1]); // Initialize memory

    cpu.reset();
    cpu.execute(12);
    cpu.printState();

    return 0;
}