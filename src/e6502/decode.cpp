#include "stdafx.h"
#include "e6502/decode.h"

void E6502::initLookupTables()
{
    for (int opcode = 0; opcode < 256; ++opcode)
    {
        Instructions instruction = decodeInstruction(static_cast<Byte>(opcode));
        AddressingModes addr_mode = decodeAddressingMode(static_cast<Byte>(opcode));

        instructionLookupTable[static_cast<Byte>(opcode)] = instruction;
        addrLookupTable[static_cast<Byte>(opcode)] = addr_mode;
    }
}

const E6502::Instructions E6502::lookupForInstruction(const Byte &opcode)
{
    return instructionLookupTable.at(opcode);
}

const E6502::AddressingModes E6502::lookupForAddrMode(const Byte &opcode)
{
    return addrLookupTable.at(opcode);
}

const E6502::Instructions E6502::decodeInstruction(const Byte &opcode)
{
    for (auto &mask : instructionMasks)
    {
        if (mask.zerosMask == mask.onesMask && mask.onesMask == opcode)
        {
            return mask.instruction;
        }
        else if ((opcode & mask.zerosMask) == 0 && (opcode & mask.onesMask) == mask.onesMask)
        {
            return mask.instruction;
        }
    }

    // Instruction not found
    return UNK;
}

const E6502::AddressingModes E6502::decodeAddressingMode(const Byte &opcode)
{
    /* Handle instructions that are exceptions in the bitmasking */
    for (auto &[op, mode] : exceptionModes)
        if (op == opcode)
            return mode;

    /* Bitmasking tests */
    for (auto &mode_mask : modeMasks)
        if ((opcode & mode_mask.zerosMask) == 0 && (opcode & mode_mask.onesMask) == mode_mask.onesMask)
            return mode_mask.mode;

    // Addressing mode not found.
    return NOT_IMPLEMENTED;
}