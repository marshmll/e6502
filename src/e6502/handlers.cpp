#include "stdafx.h"
#include "e6502/handlers.h"

void E6502::InstructionHandlers::ADCHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    const Byte prev_A_value = cpu.A;

    const Byte operand = performOperation(cpu, addr_mode, [&](CPU &cpu, const Byte &operand)
                                          { cpu.A += operand + (cpu.P & CARRY_FLAG); });

    cpu.setADCFlags(operand, prev_A_value);
}

void E6502::InstructionHandlers::ANDHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    performOperation(cpu, addr_mode, [&](CPU &cpu, const Byte &operand)
                     { cpu.A = cpu.A & operand; });

    cpu.setZeroAndNegativeFlags(cpu.A);
}

void E6502::InstructionHandlers::ASLHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    Byte seventh_bit;

    switch (addr_mode)
    {
    case ACCUMULATOR:
    {
        seventh_bit = cpu.A & 0b10000000;
        cpu.A <<= 1;
        cpu.clkCycles++;

        break;
    }
    case ZERO_PAGE:
    {
        const Byte base_pointer = cpu.fetchByte();
        Byte operand = cpu.readByte(base_pointer);
        seventh_bit = operand & 0b10000000;
        operand <<= 1;
        cpu.clkCycles++;
        cpu.writeByte(base_pointer, operand);

        break;
    }
    case ZERO_PAGE_X:
    {
        Byte base_pointer = cpu.fetchByte();
        base_pointer += cpu.X;
        cpu.clkCycles++;
        Byte operand = cpu.readByte(base_pointer);
        seventh_bit = operand & 0b10000000;
        operand <<= 1;
        cpu.clkCycles++;
        cpu.writeByte(base_pointer, operand);

        break;
    }
    case ABSOLUTE:
    {
        const Word addr = cpu.fetchWord();
        Byte operand = cpu.readByte(addr);
        seventh_bit = operand & 0b10000000;
        operand <<= 1;
        cpu.clkCycles++;
        cpu.writeByte(addr, operand);

        break;
    }
    case ABSOLUTE_X:
    {
        Word addr = cpu.fetchWord();
        addr += cpu.X;
        cpu.clkCycles++;
        Byte operand = cpu.readByte(addr);
        seventh_bit = operand & 0b10000000;
        operand <<= 1;
        cpu.clkCycles++;
        cpu.writeByte(addr, operand);

        break;
    }
    default:
        std::cerr << "INVALID ADDRESSING MODE FOR ASL." << "\n";
        return;
    }

    if (seventh_bit == 0 && (cpu.P & CARRY_FLAG) != 0)
        cpu.P ^= CARRY_FLAG;
    else if (seventh_bit != 0)
        cpu.P |= CARRY_FLAG;

    cpu.setZeroAndNegativeFlags(cpu.A);
}

void E6502::InstructionHandlers::LDAHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    performOperation(cpu, addr_mode, [&](CPU &cpu, const Byte &operand)
                     { cpu.A = operand; });

    cpu.setZeroAndNegativeFlags(cpu.A);
}

void E6502::InstructionHandlers::LDXHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    performOperation(cpu, addr_mode, [&](CPU &cpu, const Byte &operand)
                     { cpu.X = operand; });

    cpu.setZeroAndNegativeFlags(cpu.X);
}

void E6502::InstructionHandlers::LDYHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    performOperation(cpu, addr_mode, [&](CPU &cpu, const Byte &operand)
                     { cpu.Y = operand; });

    cpu.setZeroAndNegativeFlags(cpu.Y);
}

void E6502::InstructionHandlers::SBCHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    const Byte prev_A_value = cpu.A;
    const Byte operand = performOperation(cpu, addr_mode, [&](CPU &cpu, const Byte &operand)
                                          { cpu.A += (255 - operand) + (cpu.P & CARRY_FLAG); });

    cpu.setSBCFlags(operand, prev_A_value);
}

const E6502::Byte E6502::InstructionHandlers::getOperand(CPU &cpu, const AddressingModes &addr_mode)
{
    Byte operand;

    switch (addr_mode)
    {
    case IMMEDIATE:
    {
        operand = cpu.fetchByte();
        break;
    }
    case ZERO_PAGE:
    {
        operand = cpu.readByte(cpu.fetchByte());
        break;
    }
    case ZERO_PAGE_X:
    {
        Byte zp_addr = cpu.fetchByte();
        zp_addr += cpu.X;
        operand = cpu.readByte(zp_addr);
        cpu.clkCycles++;
        break;
    }
    case ABSOLUTE:
    {
        Word addr = cpu.fetchWord();
        operand = cpu.readByte(addr);
        break;
    }
    case ABSOLUTE_X:
    {
        Word addr = cpu.fetchWord();
        addr += cpu.X;
        operand = cpu.readByte(addr);
        if (cpu.pageCrossed(addr - cpu.X, addr))
            cpu.clkCycles++;
        break;
    };
    case ABSOLUTE_Y:
    {
        Word addr = cpu.fetchWord();
        addr += cpu.Y;
        operand = cpu.readByte(addr);
        if (cpu.pageCrossed(addr - cpu.Y, addr))
            cpu.clkCycles++;
        break;
    };
    case INDIRECT_X:
    {
        Byte base_pointer = cpu.fetchByte();
        base_pointer += cpu.X;
        Word target_addr = cpu.readWord(base_pointer);
        operand = cpu.readByte(target_addr);
        cpu.clkCycles++;
        break;
    }
    case INDIRECT_Y:
    {
        Byte base_pointer = cpu.fetchByte();
        Word target_addr = cpu.readWord(base_pointer);
        target_addr += cpu.Y;
        operand = cpu.readByte(target_addr);
        if (cpu.pageCrossed(target_addr - cpu.Y, target_addr))
            cpu.clkCycles++;
        break;
    }
    default:
    {
        std::cerr << "WARNING: INVALID ADDRESSING MODE IN GET OPERAND." << "\n";
        return 0;
    }
    };

    return operand;
}

const E6502::Byte E6502::InstructionHandlers::performOperation(CPU &cpu, const AddressingModes &addr_mode, std::function<void(CPU &, const Byte &)> operation)
{
    Byte operand;

    switch (addr_mode)
    {
    case IMMEDIATE:
    {
        operand = cpu.fetchByte();
        break;
    }
    case ZERO_PAGE:
    {
        operand = cpu.readByte(cpu.fetchByte());
        break;
    }
    case ZERO_PAGE_X:
    {
        Byte zp_addr = cpu.fetchByte();
        zp_addr += cpu.X;
        operand = cpu.readByte(zp_addr);
        cpu.clkCycles++;
        break;
    }
    case ABSOLUTE:
    {
        Word addr = cpu.fetchWord();
        operand = cpu.readByte(addr);
        break;
    }
    case ABSOLUTE_X:
    {
        Word addr = cpu.fetchWord();
        addr += cpu.X;
        operand = cpu.readByte(addr);
        if (cpu.pageCrossed(addr - cpu.X, addr))
            cpu.clkCycles++;
        break;
    };
    case ABSOLUTE_Y:
    {
        Word addr = cpu.fetchWord();
        addr += cpu.Y;
        operand = cpu.readByte(addr);
        if (cpu.pageCrossed(addr - cpu.Y, addr))
            cpu.clkCycles++;
        break;
    };
    case INDIRECT_X:
    {
        Byte base_pointer = cpu.fetchByte();
        base_pointer += cpu.X;
        Word target_addr = cpu.readWord(base_pointer);
        operand = cpu.readByte(target_addr);
        cpu.clkCycles++;
        break;
    }
    case INDIRECT_Y:
    {
        Byte base_pointer = cpu.fetchByte();
        Word target_addr = cpu.readWord(base_pointer);
        target_addr += cpu.Y;
        operand = cpu.readByte(target_addr);
        if (cpu.pageCrossed(target_addr - cpu.Y, target_addr))
            cpu.clkCycles++;
        break;
    }
    default:
    {
        std::cerr << "WARNING: INVALID ADDRESSING MODE IN PERFORM OPERATION." << "\n";
        return 0;
    }
    };

    operation(cpu, operand);

    return operand;
}

void E6502::InstructionHandlers::invalidHandler()
{
    std::cerr << "WARNING: INVALID HANDLER EXECUTED." << "\n";
}