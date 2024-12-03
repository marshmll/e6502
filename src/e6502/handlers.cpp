#include "stdafx.h"
#include "e6502/handlers.h"

void E6502::InstructionHandlers::ADCHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    const Byte prev_A_value = cpu.A;
    auto [addr, operand] = getOperand(cpu, addr_mode);
    cpu.A += operand + (cpu.P & CARRY_FLAG);
    cpu.updateADCFlags(operand, prev_A_value);
}

void E6502::InstructionHandlers::ANDHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [addr, operand] = getOperand(cpu, addr_mode);
    cpu.A &= operand;
    cpu.updateZeroAndNegativeFlags(cpu.A);
}

void E6502::InstructionHandlers::ASLHandler(CPU &cpu, const AddressingModes &addr_mode)
{

    if (addr_mode == ACCUMULATOR)
    {
        cpu.setFlag(CARRY_FLAG, (cpu.A & 0b10000000) != 0);
        cpu.A <<= 1;
        cpu.clkCycles++;
        cpu.setFlag(NEGATIVE_FLAG, (cpu.A & 0b10000000) != 0);
        cpu.setFlag(ZERO_FLAG, cpu.A == 0);
    }

    auto [addr, operand] = getOperandWithoutPageCrossingCycle(cpu, addr_mode);

    cpu.setFlag(CARRY_FLAG, (operand & 0b10000000) != 0);
    operand <<= 1;
    cpu.clkCycles++;

    cpu.writeByte(addr, operand);

    cpu.setFlag(NEGATIVE_FLAG, (operand & 0b10000000) != 0);
    cpu.setFlag(ZERO_FLAG, operand == 0);
}

void E6502::InstructionHandlers::BCCHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    if (!cpu.isFlagSet(CARRY_FLAG))
        branchHandler(cpu, addr_mode);
}

void E6502::InstructionHandlers::BCSHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    if (cpu.isFlagSet(CARRY_FLAG))
        branchHandler(cpu, addr_mode);
}

void E6502::InstructionHandlers::BEQHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    if (cpu.isFlagSet(ZERO_FLAG))
        branchHandler(cpu, addr_mode);
}

void E6502::InstructionHandlers::BITHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [addr, operand] = getOperand(cpu, addr_mode);

    Byte negative_flag = (operand & 0b10000000);
    Byte overflow_flag = (operand & 0b01000000);
    Byte result = cpu.A & operand;

    cpu.setFlag(NEGATIVE_FLAG, negative_flag != 0);
    cpu.setFlag(OVERFLOW_FLAG, overflow_flag != 0);
    cpu.setFlag(ZERO_FLAG, result == 0);
}

void E6502::InstructionHandlers::BMIHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    if (cpu.isFlagSet(NEGATIVE_FLAG))
        branchHandler(cpu, addr_mode);
}

void E6502::InstructionHandlers::BNEHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    if (!cpu.isFlagSet(ZERO_FLAG))
        branchHandler(cpu, addr_mode);
}

void E6502::InstructionHandlers::BPLHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    if (!cpu.isFlagSet(NEGATIVE_FLAG))
        branchHandler(cpu, addr_mode);
}

void E6502::InstructionHandlers::BRKHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.PC++;
    cpu.clkCycles++;

    cpu.pushWord(cpu.PC);
    cpu.clkCycles += 2;

    Byte processor_status = cpu.P;
    processor_status |= BREAK_FLAG;

    cpu.pushByte(processor_status);
    cpu.clkCycles++;

    cpu.setFlag(INTERRUPT_DISABLE_FLAG, true);
    cpu.setFlag(BREAK_FLAG, false);

    Word interrupt_handler_addr = cpu.readWord(INTERRUPT_VECTOR);
    cpu.PC = interrupt_handler_addr;
}

void E6502::InstructionHandlers::BVCHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    if (!cpu.isFlagSet(OVERFLOW_FLAG))
        branchHandler(cpu, addr_mode);
}

void E6502::InstructionHandlers::BVSHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    if (cpu.isFlagSet(OVERFLOW_FLAG))
        branchHandler(cpu, addr_mode);
}

void E6502::InstructionHandlers::CLCHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.setFlag(CARRY_FLAG, false);
    cpu.clkCycles++;
}

void E6502::InstructionHandlers::CLDHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.setFlag(DECIMAL_FLAG, false);
    cpu.clkCycles++;
}

void E6502::InstructionHandlers::CLIHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.setFlag(INTERRUPT_DISABLE_FLAG, false);
    cpu.clkCycles++;
}

void E6502::InstructionHandlers::CLVHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.setFlag(OVERFLOW_FLAG, false);
    cpu.clkCycles++;
}

void E6502::InstructionHandlers::CMPHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [_, operand] = getOperand(cpu, addr_mode);
    cpu.updateCompareFlags(operand, cpu.A);
}

void E6502::InstructionHandlers::CPXHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [_, operand] = getOperand(cpu, addr_mode);
    cpu.updateCompareFlags(operand, cpu.X);
}

void E6502::InstructionHandlers::CPYHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [_, operand] = getOperand(cpu, addr_mode);
    cpu.updateCompareFlags(operand, cpu.Y);
}

void E6502::InstructionHandlers::DECHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [addr, operand] = getOperandWithoutPageCrossingCycle(cpu, addr_mode);
    operand--;
    cpu.clkCycles++;
    cpu.writeByte(addr, operand);
    cpu.updateZeroAndNegativeFlags(operand);
}

void E6502::InstructionHandlers::DEXHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.X--;
    cpu.clkCycles++;
    cpu.updateZeroAndNegativeFlags(cpu.X);
}

void E6502::InstructionHandlers::DEYHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.Y--;
    cpu.clkCycles++;
    cpu.updateZeroAndNegativeFlags(cpu.Y);
}

void E6502::InstructionHandlers::EORHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [_, operand] = getOperand(cpu, addr_mode);
    cpu.A ^= operand;
    cpu.updateZeroAndNegativeFlags(cpu.A);
}

void E6502::InstructionHandlers::INCHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [addr, operand] = getOperandWithoutPageCrossingCycle(cpu, addr_mode);
    operand++;
    cpu.clkCycles++;
    cpu.writeByte(addr, operand);
    cpu.updateZeroAndNegativeFlags(operand);
}

void E6502::InstructionHandlers::INXHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.X++;
    cpu.clkCycles++;
    cpu.updateZeroAndNegativeFlags(cpu.X);
}

void E6502::InstructionHandlers::INYHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.Y++;
    cpu.clkCycles++;
    cpu.updateZeroAndNegativeFlags(cpu.Y);
}

void E6502::InstructionHandlers::JMPHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    switch (addr_mode)
    {
    case ABSOLUTE:
    {
        Word addr = cpu.fetchWord();
        cpu.PC = addr;

        break;
    }
    case INDIRECT:
    {
        Word addr = cpu.fetchWord();
        Word target_addr = cpu.readWord(addr);
        cpu.PC = target_addr;

        break;
    }
    };
}

void E6502::InstructionHandlers::JSRHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    Word addr = cpu.fetchWord();
    Word ret_addr = cpu.PC - 1;
    cpu.clkCycles++;

    cpu.pushWord(ret_addr);
    cpu.clkCycles += 2;
    cpu.PC = addr;
}

void E6502::InstructionHandlers::LDAHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [_, operand] = getOperand(cpu, addr_mode);
    cpu.A = operand;
    cpu.updateZeroAndNegativeFlags(cpu.A);
}

void E6502::InstructionHandlers::LDXHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [_, operand] = getOperand(cpu, addr_mode);
    cpu.X = operand;
    cpu.updateZeroAndNegativeFlags(cpu.X);
}

void E6502::InstructionHandlers::LDYHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [_, operand] = getOperand(cpu, addr_mode);
    cpu.Y = operand;
    cpu.updateZeroAndNegativeFlags(cpu.Y);
}

void E6502::InstructionHandlers::LSRHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    if (addr_mode == ACCUMULATOR)
    {
        cpu.setFlag(CARRY_FLAG, (cpu.A & 0b00000001) != 0);
        cpu.A >>= 1;
        cpu.clkCycles++;
        cpu.setFlag(NEGATIVE_FLAG, false);
        cpu.setFlag(ZERO_FLAG, cpu.A == 0);

        return;
    }

    auto [addr, operand] = getOperandWithoutPageCrossingCycle(cpu, addr_mode);

    cpu.setFlag(CARRY_FLAG, (operand & 0b00000001) != 0);
    operand >>= 1;
    cpu.clkCycles++;
    cpu.writeByte(addr, operand);
    cpu.setFlag(NEGATIVE_FLAG, false);
    cpu.setFlag(ZERO_FLAG, operand == 0);
}

void E6502::InstructionHandlers::NOPHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.clkCycles++;
}

void E6502::InstructionHandlers::ORAHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [_, operand] = getOperand(cpu, addr_mode);

    cpu.A |= operand;
    cpu.updateZeroAndNegativeFlags(cpu.A);
}

void E6502::InstructionHandlers::PHAHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.pushByte(cpu.A);
    cpu.clkCycles += 2;
}

void E6502::InstructionHandlers::PHPHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.pushByte(cpu.P);
    cpu.clkCycles += 2;
}

void E6502::InstructionHandlers::PLAHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.A = cpu.popByte();
    cpu.updateZeroAndNegativeFlags(cpu.A);
    cpu.clkCycles -= 3;
}

void E6502::InstructionHandlers::PLPHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.P = cpu.popByte();
    cpu.clkCycles -= 3;
}

void E6502::InstructionHandlers::ROLHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    if (addr_mode == ACCUMULATOR)
    {
        Byte new_carry = cpu.A & 0b10000000;
        new_carry >>= 7;

        cpu.A <<= 1;
        cpu.A |= (cpu.P & CARRY_FLAG);

        cpu.setFlag(CARRY_FLAG, false);
        cpu.P |= new_carry;

        cpu.updateZeroAndNegativeFlags(cpu.A);
        cpu.clkCycles++;

        return;
    }
    auto [addr, operand] = getOperandWithoutPageCrossingCycle(cpu, addr_mode);

    Byte new_carry = operand & 0b10000000;
    new_carry >>= 7;

    operand <<= 1;
    operand |= (cpu.P & CARRY_FLAG);
    cpu.clkCycles++;

    cpu.setFlag(CARRY_FLAG, false);
    cpu.P |= new_carry;

    cpu.updateZeroAndNegativeFlags(operand);
    cpu.writeByte(addr, operand);
}

void E6502::InstructionHandlers::RORHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    if (addr_mode == ACCUMULATOR)
    {
        Byte new_carry = cpu.A & 0b00000001;

        cpu.A >>= 1;
        cpu.A |= ((cpu.P & CARRY_FLAG) << 7);

        cpu.setFlag(CARRY_FLAG, false);
        cpu.P |= new_carry;

        cpu.updateZeroAndNegativeFlags(cpu.A);
        cpu.clkCycles++;

        return;
    }

    auto [addr, operand] = getOperandWithoutPageCrossingCycle(cpu, addr_mode);

    Byte new_carry = operand & 0b00000001;

    operand >>= 1;
    operand |= ((cpu.P & CARRY_FLAG) << 7);
    cpu.clkCycles++;

    cpu.setFlag(CARRY_FLAG, false);
    cpu.P |= new_carry;

    cpu.updateZeroAndNegativeFlags(operand);
    cpu.writeByte(addr, operand);
}

void E6502::InstructionHandlers::RTIHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.P = cpu.popByte();
    cpu.PC = cpu.popWord();
    cpu.clkCycles += 5;
}

void E6502::InstructionHandlers::RTSHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.PC = cpu.popWord();
    cpu.PC++;
    cpu.clkCycles += 5;
}

void E6502::InstructionHandlers::SBCHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    const Byte prev_A_value = cpu.A;
    auto [addr, operand] = getOperand(cpu, addr_mode);
    cpu.A += (255 - operand) + (cpu.P & CARRY_FLAG);
    cpu.updateSBCFlags(operand, prev_A_value);
}

void E6502::InstructionHandlers::SECHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.setFlag(CARRY_FLAG, true);
    cpu.clkCycles++;
}

void E6502::InstructionHandlers::SEDHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.setFlag(DECIMAL_FLAG, true);
    cpu.clkCycles++;
}

void E6502::InstructionHandlers::SEIHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.setFlag(INTERRUPT_DISABLE_FLAG, true);
    cpu.clkCycles++;
}

void E6502::InstructionHandlers::STAHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    const Word addr = getEffectiveAddress(cpu, addr_mode);
    cpu.writeByte(addr, cpu.A);
}

void E6502::InstructionHandlers::STXHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    const Word addr = getEffectiveAddress(cpu, addr_mode);
    cpu.writeByte(addr, cpu.X);
}

void E6502::InstructionHandlers::STYHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    const Word addr = getEffectiveAddress(cpu, addr_mode);
    cpu.writeByte(addr, cpu.Y);
}

void E6502::InstructionHandlers::TAXHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.X = cpu.A;
    cpu.clkCycles++;
    cpu.updateZeroAndNegativeFlags(cpu.X);
}

void E6502::InstructionHandlers::TAYHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.Y = cpu.A;
    cpu.clkCycles++;
    cpu.updateZeroAndNegativeFlags(cpu.Y);
}

void E6502::InstructionHandlers::TSXHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.X = cpu.SP;
    cpu.clkCycles++;
    cpu.updateZeroAndNegativeFlags(cpu.X);
}

void E6502::InstructionHandlers::TXAHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.A = cpu.X;
    cpu.clkCycles++;
    cpu.updateZeroAndNegativeFlags(cpu.A);
}

void E6502::InstructionHandlers::TXSHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.SP = cpu.X;
    cpu.clkCycles++;
}

void E6502::InstructionHandlers::TYAHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    cpu.A = cpu.Y;
    cpu.clkCycles++;
    cpu.updateZeroAndNegativeFlags(cpu.A);
}

const E6502::OperandPair E6502::InstructionHandlers::getOperand(CPU &cpu, const AddressingModes &addr_mode)
{
    Byte operand;
    Word address;

    switch (addr_mode)
    {
    case RELATIVE:
    {
        address = cpu.PC;
        operand = cpu.fetchByte();
        break;
    }
    case IMMEDIATE:
    {
        address = cpu.PC;
        operand = cpu.fetchByte();
        break;
    }
    case ZERO_PAGE:
    {
        address = cpu.fetchByte();
        operand = cpu.readByte(address);
        break;
    }
    case ZERO_PAGE_Y:
    {
        address = cpu.fetchByte();
        address += cpu.Y;
        operand = cpu.readByte(address);
        cpu.clkCycles++;
        break;
    }
    case ZERO_PAGE_X:
    {
        address = cpu.fetchByte();
        address += cpu.X;
        operand = cpu.readByte(address);
        cpu.clkCycles++;
        break;
    }
    case ABSOLUTE:
    {
        address = cpu.fetchWord();
        operand = cpu.readByte(address);
        break;
    }
    case ABSOLUTE_X:
    {
        address = cpu.fetchWord();
        address += cpu.X;
        operand = cpu.readByte(address);
        if (cpu.pageCrossed(address - cpu.X, address))
            cpu.clkCycles++;
        break;
    };
    case ABSOLUTE_Y:
    {
        address = cpu.fetchWord();
        address += cpu.Y;
        operand = cpu.readByte(address);
        if (cpu.pageCrossed(address - cpu.Y, address))
            cpu.clkCycles++;
        break;
    };
    case INDIRECT_X:
    {
        Byte base_pointer = cpu.fetchByte();
        base_pointer += cpu.X;
        address = cpu.readWord(base_pointer);
        operand = cpu.readByte(address);
        cpu.clkCycles++;
        break;
    }
    case INDIRECT_Y:
    {
        Byte base_pointer = cpu.fetchByte();
        address = cpu.readWord(base_pointer);
        address += cpu.Y;
        operand = cpu.readByte(address);
        if (cpu.pageCrossed(address - cpu.Y, address))
            cpu.clkCycles++;
        break;
    }
    default:
    {
        std::cerr << "WARNING: INVALID ADDRESSING MODE IN GET OPERAND." << "\n";
        return std::pair<const E6502::AddressingModes, const E6502::Byte>();
    }
    };

    return std::make_pair(address, operand);
}

const E6502::OperandPair E6502::InstructionHandlers::getOperandWithoutPageCrossingCycle(CPU &cpu, const AddressingModes &addr_mode)
{
    Word addr;
    Byte operand;

    switch (addr_mode)
    {
    case ABSOLUTE:
    {
        addr = cpu.fetchWord();
        operand = cpu.readByte(addr);

        break;
    }
    case ABSOLUTE_X:
    {
        addr = cpu.fetchWord();
        addr += cpu.X;
        cpu.clkCycles++;
        operand = cpu.readByte(addr);

        break;
    }
    case ABSOLUTE_Y:
    {
        addr = cpu.fetchWord();
        addr += cpu.Y;
        cpu.clkCycles++;
        operand = cpu.readByte(addr);

        break;
    }
    case ZERO_PAGE:
    {
        addr = cpu.fetchByte();
        operand = cpu.readByte(addr);

        break;
    }
    case ZERO_PAGE_X:
    {
        addr = cpu.fetchByte();
        addr += cpu.X;
        cpu.clkCycles++;
        operand = cpu.readByte(addr);

        break;
    }
    case INDIRECT_X:
    {
        Byte base_pointer = cpu.fetchByte();
        base_pointer += cpu.X;
        cpu.clkCycles++;
        addr = cpu.readWord(base_pointer);
        operand = cpu.readByte(addr);

        break;
    }
    case INDIRECT_Y:
    {
        Byte base_pointer = cpu.fetchByte();
        addr = cpu.readWord(base_pointer);
        addr += cpu.Y;
        cpu.clkCycles++;
        operand = cpu.readByte(addr);

        break;
    }
    };

    return std::make_pair(addr, operand);
}

const E6502::Word E6502::InstructionHandlers::getEffectiveAddress(CPU &cpu, const AddressingModes &addr_mode)
{
    Word addr;

    switch (addr_mode)
    {
    case ABSOLUTE:
    {
        addr = cpu.fetchWord();

        break;
    }
    case ABSOLUTE_X:
    {
        addr = cpu.fetchWord();
        addr += cpu.X;
        cpu.clkCycles++;

        break;
    }
    case ABSOLUTE_Y:
    {
        addr = cpu.fetchWord();
        addr += cpu.Y;
        cpu.clkCycles++;

        break;
    }
    case ZERO_PAGE:
    {
        addr = cpu.fetchByte();

        break;
    }
    case ZERO_PAGE_X:
    {
        addr = cpu.fetchByte();
        addr += cpu.X;
        cpu.clkCycles++;

        break;
    }
    case INDIRECT_X:
    {
        Byte base_pointer = cpu.fetchByte();
        base_pointer += cpu.X;
        cpu.clkCycles++;
        addr = cpu.readWord(base_pointer);

        break;
    }
    case INDIRECT_Y:
    {
        Byte base_pointer = cpu.fetchByte();
        addr = cpu.readWord(base_pointer);
        addr += cpu.Y;
        cpu.clkCycles++;

        break;
    }
    };

    return addr;
}

void E6502::InstructionHandlers::branchHandler(CPU &cpu, const AddressingModes &addr_mode)
{
    auto [_, offset] = getOperand(cpu, addr_mode);

    std::cout << "offset: 0x" << std::hex << static_cast<int>(offset) << "\n";

    cpu.clkCycles++;

    if ((offset & 0b10000000) != 0)
    {
        // Take the two's complement.
        offset = ~offset;
        offset += 0b00000001;

        if (cpu.pageCrossed(cpu.PC, cpu.PC - offset))
            cpu.clkCycles++;

        cpu.PC -= offset;
    }
    else
    {
        if (cpu.pageCrossed(cpu.PC, cpu.PC + offset))
            cpu.clkCycles++;

        cpu.PC += offset;
    }
}