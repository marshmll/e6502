#include "stdafx.h"
#include "e6502/handlers.h"

void E6502::InstructionHandlers::LDAHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    loadInstructionHandler(cpu, addr_mode, cpu.A);
}

void E6502::InstructionHandlers::LDXHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    loadInstructionHandler(cpu, addr_mode, cpu.X);
}

void E6502::InstructionHandlers::LDYHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    loadInstructionHandler(cpu, addr_mode, cpu.Y);
}

void E6502::InstructionHandlers::loadInstructionHandler(CPU &cpu, const AddressingModes &addr_mode, Byte &reg)
{
    switch (addr_mode)
    {
    case IMMEDIATE:
    {
        reg = cpu.fetchByte();
        break;
    }
    case ZERO_PAGE:
    {
        reg = cpu.readByte(cpu.fetchByte());
        break;
    }
    case ZERO_PAGE_X:
    {
        Byte zp = cpu.fetchByte();
        zp += cpu.X;
        cpu.clkCycles++;
        reg = cpu.readByte(zp);
        break;
    }
    case ZERO_PAGE_Y:
    {
        Byte zp = cpu.fetchByte();
        zp += cpu.Y;
        cpu.clkCycles++;
        reg = cpu.readByte(zp);
        break;
    };
    case ABSOLUTE:
    {
        reg = cpu.readByte(cpu.fetchWord());
        break;
    }
    case ABSOLUTE_X:
    {
        Word addr = cpu.fetchWord();
        addr += cpu.X;
        reg = cpu.readByte(addr);
        if (cpu.pageCrossed(addr - cpu.X, addr))
            cpu.clkCycles++;
        break;
    };
    case ABSOLUTE_Y:
    {
        Word addr = cpu.fetchWord();
        addr += cpu.Y;
        reg = cpu.readByte(addr);
        if (cpu.pageCrossed(addr - cpu.X, addr))
            cpu.clkCycles++;
        break;
    };
    case INDIRECT_X:
    {
        Byte base_pointer = cpu.fetchByte();
        base_pointer += cpu.X;
        Word target_addr = cpu.readWord(base_pointer);
        reg = cpu.readByte(target_addr);
        cpu.clkCycles++;
        break;
    }
    case INDIRECT_Y:
    {
        Byte base_pointer = cpu.fetchByte();
        Word target_addr = cpu.readWord(base_pointer);
        target_addr += cpu.Y;
        reg = cpu.readByte(target_addr);
        if (cpu.pageCrossed(target_addr - cpu.Y, target_addr))
            cpu.clkCycles++;
        break;
    }
    default:
    {
        std::cerr << "WARNING: INVALID ADDRESSING MODE." << "\n";
        return;
    }
    };

    cpu.setLoadFlags(reg);
}
void E6502::InstructionHandlers::invalidHandler()
{
    std::cerr << "WARNING: INVALID HANDLER EXECUTED." << "\n";
}