#include "stdafx.h"
#include "e6502/decode.h"

const E6502::Instructions E6502::decodeInstruction(const Byte &opcode)
{
    // Lookup for unique instructions
    for (auto &ins : uniqueInstructions)
        if (ins == opcode)
            return ins;

    // Lookup for instructions with different addresing modes.
    for (auto &mask : instructionMasks)
        if ((opcode & mask.zerosMask) == 0 && (opcode & mask.onesMask) == mask.onesMask)
            return mask.instruction;

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