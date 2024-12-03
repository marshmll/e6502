#include "stdafx.h"
#include "e6502/execute.h"

void E6502::CPU::execute(int cycles)
{
    unsigned long previous_clk = clkCycles;
    system("clear");
    while (true)
    {
        if (previous_clk >= clkCycles)
        {
            Byte opcode = fetchByte();
            handleInstruction(opcode, *this);
        }

        std::cout << "[CLOCK]: " << std::dec << previous_clk << "\n";
        printState();

        usleep(100000);
        system("clear");
        previous_clk++;
    }
}

void E6502::handleInstruction(const Byte &opcode, CPU &cpu)
{
    Instructions instruction = lookupForInstruction(opcode);
    AddressingModes addr_mode = lookupForAddrMode(opcode);

    // std::cout << "instruction: " << std::dec << static_cast<int>(instruction) << "\n"
    //           << "addressing mode: " << static_cast<int>(addr_mode) << "\n";

    try
    {
        InstructionHandler handler = handlersTable.at(instruction);
        handler(cpu, addr_mode);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Invalid handler for opcode " << std::hex << static_cast<int>(opcode) << ": " << e.what() << '\n';
    }
}