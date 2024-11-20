#pragma once

#include "memory/sizes.h"
#include "e6502/instructions.h"

namespace E6502
{
    enum AddressingModesBitMasks
    {
        ACCUMULATOR_ZEROS_BITMASK = 0b10010101,
        ACCUMULATOR_ONES_BITMASK = 0b00001010,
        IMPLIED_EXCEPTION_1 = 0b00000000,
        IMPLIED_EXCEPTION_2 = 0b01000000,
        IMPLIED_EXCEPTION_3 = 0b01100000,
        IMPLIED_ZEROS_BITMASK_1 = 0b00000111,
        IMPLIED_ZEROS_BITMASK_2 = 0b00000101,
        IMPLIED_ONES_BITMASK_1 = 0b00011000,
        IMPLIED_ONES_BITMASK_2 = 0b10001010,
        RELATIVE_ZEROS_BITMASK = 0b00001111,
        RELATIVE_ONES_BITMASK = 0b00010000,
        IMMEDIATE_ZEROS_BITMASK = 0b00010100,
        ZERO_PAGE_EXCEPTION = 0b01010100,
        ZERO_PAGE_ZEROS_BITMASK = 0b00011000,
        ZERO_PAGE_ONES_BITMASK = 0b00000100,
        ZERO_PAGE_X_ZEROS_BITMASK = 0b00001000,
        ZERO_PAGE_X_ONES_BITMASK = 0b00010100,
        ZERO_PAGE_Y_EXCEPTION_1 = 0b10110110,
        ZERO_PAGE_Y_EXCEPTION_2 = 0b10010110,
        ABSOLUTE_EXCEPTION = 0b00100000,
        ABSOLUTE_ZEROS_BITMASK = 0b00010000,
        ABSOLUTE_ONES_BITMASK = 0b00001100,
        ABSOLUTE_X_ONES_BITMASK = 0b00011100,
        ABSOLUTE_Y_EXCEPTION = 0b10111110,
        ABSOLUTE_Y_ZEROS_BITMASK = 0b00000110,
        ABSOLUTE_Y_ONES_BITMASK = 0b00011000,
        INDIRECT_X_ZEROS_BITMASK = 0b00011110,
        INDIRECT_X_ONES_BITMASK = 0b00000001,
        INDIRECT_Y_ZEROS_BITMASK = 0b00001110,
        INDIRECT_Y_ONES_BITMASK = 0b00010001,
    };

    enum AddressingModes
    {
        NOT_IMPLEMENTED = 0,
        ACCUMULATOR,
        IMPLIED,
        RELATIVE,
        IMMEDIATE,
        ZERO_PAGE,
        ZERO_PAGE_X,
        ZERO_PAGE_Y,
        ABSOLUTE,
        ABSOLUTE_X,
        ABSOLUTE_Y,
        INDIRECT_X,
        INDIRECT_Y,
    };

    struct AddressingModeMask
    {
        Byte zerosMask;
        Byte onesMask;
        AddressingModes mode;
    };

    static const std::unordered_map<Byte, AddressingModes> exceptionModes = {
        {IMPLIED_EXCEPTION_1, IMPLIED},
        {IMPLIED_EXCEPTION_2, IMPLIED},
        {IMPLIED_EXCEPTION_3, IMPLIED},
        {ZERO_PAGE_EXCEPTION, ZERO_PAGE},
        {ZERO_PAGE_Y_EXCEPTION_1, ZERO_PAGE_Y},
        {ZERO_PAGE_Y_EXCEPTION_2, ZERO_PAGE_Y},
        {ABSOLUTE_EXCEPTION, ABSOLUTE},
        {ABSOLUTE_Y_EXCEPTION, ABSOLUTE_Y}};

    static const std::vector<AddressingModeMask> modeMasks = {
        {ACCUMULATOR_ZEROS_BITMASK, ACCUMULATOR_ONES_BITMASK, ACCUMULATOR},
        {RELATIVE_ZEROS_BITMASK, RELATIVE_ONES_BITMASK, RELATIVE},
        {IMPLIED_ZEROS_BITMASK_1, IMPLIED_ONES_BITMASK_1, IMPLIED},
        {IMPLIED_ZEROS_BITMASK_2, IMPLIED_ONES_BITMASK_2, IMPLIED},
        {INDIRECT_X_ZEROS_BITMASK, INDIRECT_X_ONES_BITMASK, INDIRECT_X},
        {INDIRECT_Y_ZEROS_BITMASK, INDIRECT_Y_ONES_BITMASK, INDIRECT_Y},
        {ZERO_PAGE_ZEROS_BITMASK, ZERO_PAGE_ONES_BITMASK, ZERO_PAGE},
        {ZERO_PAGE_X_ZEROS_BITMASK, ZERO_PAGE_X_ONES_BITMASK, ZERO_PAGE_X},
        {IMMEDIATE_ZEROS_BITMASK, 0, IMMEDIATE}, // Immediate only needs a zeros mask
        {ABSOLUTE_ZEROS_BITMASK, ABSOLUTE_ONES_BITMASK, ABSOLUTE},
        {ABSOLUTE_Y_ZEROS_BITMASK, ABSOLUTE_Y_ONES_BITMASK, ABSOLUTE_Y},
        {0, ABSOLUTE_X_ONES_BITMASK, ABSOLUTE_X} // Absolute X only needs ones mask
    };

    enum InstructionsBitMasks
    {
        ADC_ZEROS_BITMASK = 0b10000010,
        ADC_ONES_BITMASK = 0b01100001,
        AND_ZEROS_BITMASK = 0b11000010,
        AND_ONES_BITMASK = 0b00100001,
        ASL_ZEROS_BITMASK = 0b11100001,
        ASL_ONES_BITMASK = 0b00000010,
        BIT_ZEROS_BITMASK = 0b11010011,
        BIT_ONES_BITMASK = 0b00100100,
        CMP_ZEROS_BITMASK = 0b00100010,
        CMP_ONES_BITMASK = 0b11000001,
        CPX_ZEROS_BITMASK = 0b00010011,
        CPX_ONES_BITMASK = 0b11100000,
        CPY_ZEROS_BITMASK = 0b00110011,
        CPY_ONES_BITMASK = 0b11000000,
        DEC_ZEROS_BITMASK = 0b00100001,
        DEC_ONES_BITMASK = 0b11000110,
        EOR_ZEROS_BITMASK = 0b10100010,
        EOR_ONES_BITMASK = 0b01000001,
        INC_ZEROS_BITMASK = 0b00000001,
        INC_ONES_BITMASK = 0b11100110,
        LDA_ZEROS_BITMASK = 0b01000010,
        LDA_ONES_BITMASK = 0b10100001,
        LDX_ZEROS_BITMASK = 0b01000000,
        LDX_ONES_BITMASK = 0b10100000,
        LDY_ZEROS_BITMASK = 0b01000011,
        LDY_ONES_BITMASK = 0b10100000,
        LSR_ZEROS_BITMASK = 0b10100001,
        LSR_ONES_BITMASK = 0b01000110,
        ORA_ZEROS_BITMASK = 0b11100010,
        ORA_ONES_BITMASK = 0b00000001,
        ROL_ZEROS_BITMASK = 0b11000001,
        ROL_ONES_BITMASK = 0b00100110,
        ROR_ZEROS_BITMASK = 0b10000001,
        ROR_ONES_BITMASK = 0b01100110,
        SBC_ZEROS_BITMASK = 0b00000010,
        SBC_ONES_BITMASK = 0b11100001,
        STA_ZEROS_BITMASK = 0b01100010,
        STA_ONES_BITMASK = 0b10000001,
        STX_ZEROS_BITMASK = 0b01100001,
        STX_ONES_BITMASK = 0b10000110,
        STY_ZEROS_BITMASK = 0b01100011,
        STY_ONES_BITMASK = 0b10000100,

        // Unique instructions (exact opcode matches)
        BCC_MASK = 0x90,
        BCS_MASK = 0xB0,
        BEQ_MASK = 0xF0,
        BMI_MASK = 0x30,
        BNE_MASK = 0xD0,
        BPL_MASK = 0x10,
        BRK_MASK = 0x00,
        BVC_MASK = 0x50,
        BVS_MASK = 0x70,
        CLC_MASK = 0x18,
        CLD_MASK = 0xD8,
        CLI_MASK = 0x58,
        CLV_MASK = 0xB8,
        DEX_MASK = 0xCA,
        DEY_MASK = 0x88,
        INX_MASK = 0xE8,
        INY_MASK = 0xC8,
        JMP_MASK = 0x4C,
        JSR_MASK = 0x20,
        NOP_MASK = 0xEA,
        PHA_MASK = 0x48,
        PHP_MASK = 0x08,
        PLA_MASK = 0x68,
        PLP_MASK = 0x28,
        RTI_MASK = 0x40,
        RTS_MASK = 0x60,
        SEC_MASK = 0x38,
        SED_MASK = 0xF8,
        SEI_MASK = 0x78,
        TAX_MASK = 0xAA,
        TAY_MASK = 0xA8,
        TSX_MASK = 0xBA,
        TXA_MASK = 0x8A,
        TXS_MASK = 0x9A,
        TYA_MASK = 0x98
    };

    struct InstructionMask
    {
        Byte zerosMask;
        Byte onesMask;
        Instructions instruction;
    };

    static const std::vector<InstructionMask> instructionMasks = {
        // Instructions with bitmask logic
        {ADC_ZEROS_BITMASK, ADC_ONES_BITMASK, ADC},
        {AND_ZEROS_BITMASK, AND_ONES_BITMASK, AND},
        {ASL_ZEROS_BITMASK, ASL_ONES_BITMASK, ASL},
        {BIT_ZEROS_BITMASK, BIT_ONES_BITMASK, BIT},
        {CMP_ZEROS_BITMASK, CMP_ONES_BITMASK, CMP},
        {CPX_ZEROS_BITMASK, CPX_ONES_BITMASK, CPX},
        {CPY_ZEROS_BITMASK, CPY_ONES_BITMASK, CPY},
        {DEC_ZEROS_BITMASK, DEC_ONES_BITMASK, DEC},
        {EOR_ZEROS_BITMASK, EOR_ONES_BITMASK, EOR},
        {INC_ZEROS_BITMASK, INC_ONES_BITMASK, INC},
        {LDA_ZEROS_BITMASK, LDA_ONES_BITMASK, LDA},
        {LDX_ZEROS_BITMASK, LDX_ONES_BITMASK, LDX},
        {LDY_ZEROS_BITMASK, LDY_ONES_BITMASK, LDY},
        {LSR_ZEROS_BITMASK, LSR_ONES_BITMASK, LSR},
        {ORA_ZEROS_BITMASK, ORA_ONES_BITMASK, ORA},
        {ROL_ZEROS_BITMASK, ROL_ONES_BITMASK, ROL},
        {ROR_ZEROS_BITMASK, ROR_ONES_BITMASK, ROR},
        {SBC_ZEROS_BITMASK, SBC_ONES_BITMASK, SBC},
        {STA_ZEROS_BITMASK, STA_ONES_BITMASK, STA},
        {STX_ZEROS_BITMASK, STX_ONES_BITMASK, STX},
        {STY_ZEROS_BITMASK, STY_ONES_BITMASK, STY},

        // Unique instructions (exact opcode matches)
        {BCC_MASK, BCC_MASK, BCC},
        {BCS_MASK, BCS_MASK, BCS},
        {BEQ_MASK, BEQ_MASK, BEQ},
        {BMI_MASK, BMI_MASK, BMI},
        {BNE_MASK, BNE_MASK, BNE},
        {BPL_MASK, BPL_MASK, BPL},
        {BRK_MASK, BRK_MASK, BRK},
        {BVC_MASK, BVC_MASK, BVC},
        {BVS_MASK, BVS_MASK, BVS},
        {CLC_MASK, CLC_MASK, CLC},
        {CLD_MASK, CLD_MASK, CLD},
        {CLI_MASK, CLI_MASK, CLI},
        {CLV_MASK, CLV_MASK, CLV},
        {DEX_MASK, DEX_MASK, DEX},
        {DEY_MASK, DEY_MASK, DEY},
        {INX_MASK, INX_MASK, INX},
        {INY_MASK, INY_MASK, INY},
        {JMP_MASK, JMP_MASK, JMP},
        {JSR_MASK, JSR_MASK, JSR},
        {NOP_MASK, NOP_MASK, NOP},
        {PHA_MASK, PHA_MASK, PHA},
        {PHP_MASK, PHP_MASK, PHP},
        {PLA_MASK, PLA_MASK, PLA},
        {PLP_MASK, PLP_MASK, PLP},
        {RTI_MASK, RTI_MASK, RTI},
        {RTS_MASK, RTS_MASK, RTS},
        {SEC_MASK, SEC_MASK, SEC},
        {SED_MASK, SED_MASK, SED},
        {SEI_MASK, SEI_MASK, SEI},
        {TAX_MASK, TAX_MASK, TAX},
        {TAY_MASK, TAY_MASK, TAY},
        {TSX_MASK, TSX_MASK, TSX},
        {TXA_MASK, TXA_MASK, TXA},
        {TXS_MASK, TXS_MASK, TXS},
        {TYA_MASK, TYA_MASK, TYA}};

    static std::unordered_map<Byte, AddressingModes> addrLookupTable;

    static std::unordered_map<Byte, Instructions> instructionLookupTable;

    void initLookupTables();

    const Instructions lookupForInstruction(const Byte &opcode);

    const AddressingModes lookupForAddrMode(const Byte &opcode);

    const Instructions decodeInstruction(const Byte &opcode);

    const AddressingModes decodeAddressingMode(const Byte &opcode);
}