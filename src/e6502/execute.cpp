#include "stdafx.h"
#include "e6502/execute.h"

void E6502::CPU::execute(int cycles)
{
    while (clkCycles < cycles)
    {
        Byte opcode = fetchByte();

        std::cout << "opcode: 0x" << std::hex << static_cast<int>(opcode) << "\n";

        handleInstruction(opcode, *this);
    }
}

void E6502::handleInstruction(const Byte &opcode, CPU &cpu)
{
    Instructions instruction = lookupForInstruction(opcode);
    AddressingModes addr_mode = lookupForAddrMode(opcode);

    std::cout << "instruction: " << std::dec << static_cast<int>(instruction) << "\n"
              << "addressing mode: " << static_cast<int>(addr_mode) << "\n";

    try
    {
        InstructionHandler handler = handlersTable.at(instruction);
        handler(cpu, addr_mode);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Invalid handler: " << e.what() << '\n';
    }
}