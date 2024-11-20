#pragma once

namespace E6502
{
    enum Instructions
    {
        UNK = 0, // unkown instructon
        ADC,     // add with carry
        AND,     // and (with accumulator)
        ASL,     // arithmetic shift left
        BCC,     // branch on carry clear
        BCS,     // branch on carry set
        BEQ,     // branch on equal (zero set)
        BIT,     // bit test
        BMI,     // branch on minus (negative set)
        BNE,     // branch on not equal (zero clear)
        BPL,     // branch on plus (negative clear)
        BRK,     // break / interrupt
        BVC,     // branch on overflow clear
        BVS,     // branch on overflow set
        CLC,     // clear carry
        CLD,     // clear decimal
        CLI,     // clear interrupt disable
        CLV,     // clear overflow
        CMP,     // compare (with accumulator)
        CPX,     // compare with X
        CPY,     // compare with Y
        DEC,     // decrement
        DEX,     // decrement X
        DEY,     // decrement Y
        EOR,     // exclusive or (with accumulator)
        INC,     // increment
        INX,     // increment X
        INY,     // increment Y
        JMP,     // jump
        JSR,     // jump subroutine
        LDA,     // load accumulator
        LDX,     // load X
        LDY,     // load Y
        LSR,     // logical shift right
        NOP,     // no operation
        ORA,     // or with accumulator
        PHA,     // push accumulator
        PHP,     // push processor status (SR)
        PLA,     // pull accumulator
        PLP,     // pull processor status (SR)
        ROL,     // rotate left
        ROR,     // rotate right
        RTI,     // return from interrupt
        RTS,     // return from subroutine
        SBC,     // subtract with carry
        SEC,     // set carry
        SED,     // set decimal
        SEI,     // set interrupt disable
        STA,     // store accumulator
        STX,     // store X
        STY,     // store Y
        TAX,     // transfer accumulator to X
        TAY,     // transfer accumulator to Y
        TSX,     // transfer stack pointer to X
        TXA,     // transfer X to accumulator
        TXS,     // transfer X to stack pointer
        TYA,     // transfer Y to accumulator
    };

    enum Opcodes
    {
        // ADC (Add with Carry)
        ADC_IMMEDIATE = 0x69,
        ADC_ZERO_PAGE = 0x65,
        ADC_ZERO_PAGE_X = 0x75,
        ADC_ABSOLUTE = 0x6D,
        ADC_ABSOLUTE_X = 0x7D,
        ADC_ABSOLUTE_Y = 0x79,
        ADC_INDIRECT_X = 0x61,
        ADC_INDIRECT_Y = 0x71,

        // AND (Logical AND)
        AND_IMMEDIATE = 0x29,
        AND_ZERO_PAGE = 0x25,
        AND_ZERO_PAGE_X = 0x35,
        AND_ABSOLUTE = 0x2D,
        AND_ABSOLUTE_X = 0x3D,
        AND_ABSOLUTE_Y = 0x39,
        AND_INDIRECT_X = 0x21,
        AND_INDIRECT_Y = 0x31,

        // ASL (Arithmetic Shift Left)
        ASL_ACCUMULATOR = 0x0A,
        ASL_ZERO_PAGE = 0x06,
        ASL_ZERO_PAGE_X = 0x16,
        ASL_ABSOLUTE = 0x0E,
        ASL_ABSOLUTE_X = 0x1E,

        // BCC (Branch if Carry Clear)
        BCC_RELATIVE = 0x90,

        // BCS (Branch if Carry Set)
        BCS_RELATIVE = 0xB0,

        // BEQ (Branch if Equal)
        BEQ_RELATIVE = 0xF0,

        // BIT (Bit Test)
        BIT_ZERO_PAGE = 0x24,
        BIT_ABSOLUTE = 0x2C,

        // BMI (Branch if Minus)
        BMI_RELATIVE = 0x30,

        // BNE (Branch if Not Equal)
        BNE_RELATIVE = 0xD0,

        // BPL (Branch if Positive)
        BPL_RELATIVE = 0x10,

        // BRK (Force Interrupt)
        BRK_IMPLIED = 0x00,

        // BVC (Branch if Overflow Clear)
        BVC_RELATIVE = 0x50,

        // BVS (Branch if Overflow Set)
        BVS_RELATIVE = 0x70,

        // CLC (Clear Carry Flag)
        CLC_IMPLIED = 0x18,

        // CLD (Clear Decimal Mode)
        CLD_IMPLIED = 0xD8,

        // CLI (Clear Interrupt Disable)
        CLI_IMPLIED = 0x58,

        // CLV (Clear Overflow Flag)
        CLV_IMPLIED = 0xB8,

        // CMP (Compare)
        CMP_IMMEDIATE = 0xC9,
        CMP_ZERO_PAGE = 0xC5,
        CMP_ZERO_PAGE_X = 0xD5,
        CMP_ABSOLUTE = 0xCD,
        CMP_ABSOLUTE_X = 0xDD,
        CMP_ABSOLUTE_Y = 0xD9,
        CMP_INDIRECT_X = 0xC1,
        CMP_INDIRECT_Y = 0xD1,

        // CPX (Compare X Register)
        CPX_IMMEDIATE = 0xE0,
        CPX_ZERO_PAGE = 0xE4,
        CPX_ABSOLUTE = 0xEC,

        // CPY (Compare Y Register)
        CPY_IMMEDIATE = 0xC0,
        CPY_ZERO_PAGE = 0xC4,
        CPY_ABSOLUTE = 0xCC,

        // DEC (Decrement Memory)
        DEC_ZERO_PAGE = 0xC6,
        DEC_ZERO_PAGE_X = 0xD6,
        DEC_ABSOLUTE = 0xCE,
        DEC_ABSOLUTE_X = 0xDE,

        // DEX (Decrement X Register)
        DEX_IMPLIED = 0xCA,

        // DEY (Decrement Y Register)
        DEY_IMPLIED = 0x88,

        // EOR (Exclusive OR)
        EOR_IMMEDIATE = 0x49,
        EOR_ZERO_PAGE = 0x45,
        EOR_ZERO_PAGE_X = 0x55,
        EOR_ABSOLUTE = 0x4D,
        EOR_ABSOLUTE_X = 0x5D,
        EOR_ABSOLUTE_Y = 0x59,
        EOR_INDIRECT_X = 0x41,
        EOR_INDIRECT_Y = 0x51,

        // INC (Increment Memory)
        INC_ZERO_PAGE = 0xE6,
        INC_ZERO_PAGE_X = 0xF6,
        INC_ABSOLUTE = 0xEE,
        INC_ABSOLUTE_X = 0xFE,

        // INX (Increment X Register)
        INX_IMPLIED = 0xE8,

        // INY (Increment Y Register)
        INY_IMPLIED = 0xC8,

        // JMP (Jump)
        JMP_ABSOLUTE = 0x4C,
        JMP_INDIRECT = 0x6C,

        // JSR (Jump to Subroutine)
        JSR_ABSOLUTE = 0x20,

        // LDA (Load Accumulator)
        LDA_IMMEDIATE = 0xA9,
        LDA_ZERO_PAGE = 0xA5,
        LDA_ZERO_PAGE_X = 0xB5,
        LDA_ABSOLUTE = 0xAD,
        LDA_ABSOLUTE_X = 0xBD,
        LDA_ABSOLUTE_Y = 0xB9,
        LDA_INDIRECT_X = 0xA1,
        LDA_INDIRECT_Y = 0xB1,

        // LDX (Load X Register)
        LDX_IMMEDIATE = 0xA2,
        LDX_ZERO_PAGE = 0xA6,
        LDX_ZERO_PAGE_Y = 0xB6,
        LDX_ABSOLUTE = 0xAE,
        LDX_ABSOLUTE_Y = 0xBE,

        // LDY (Load Y Register)
        LDY_IMMEDIATE = 0xA0,
        LDY_ZERO_PAGE = 0xA4,
        LDY_ZERO_PAGE_X = 0xB4,
        LDY_ABSOLUTE = 0xAC,
        LDY_ABSOLUTE_X = 0xBC,

        // LSR (Logical Shift Right)
        LSR_ACCUMULATOR = 0x4A,
        LSR_ZERO_PAGE = 0x46,
        LSR_ZERO_PAGE_X = 0x56,
        LSR_ABSOLUTE = 0x4E,
        LSR_ABSOLUTE_X = 0x5E,

        // NOP (No Operation)
        NOP_IMPLIED = 0xEA,

        // ORA (Logical Inclusive OR)
        ORA_IMMEDIATE = 0x09,
        ORA_ZERO_PAGE = 0x05,
        ORA_ZERO_PAGE_X = 0x15,
        ORA_ABSOLUTE = 0x0D,
        ORA_ABSOLUTE_X = 0x1D,
        ORA_ABSOLUTE_Y = 0x19,
        ORA_INDIRECT_X = 0x01,
        ORA_INDIRECT_Y = 0x11,

        // PHA (Push Accumulator)
        PHA_IMPLIED = 0x48,

        // PHP (Push Processor Status)
        PHP_IMPLIED = 0x08,

        // PLA (Pull Accumulator)
        PLA_IMPLIED = 0x68,

        // PLP (Pull Processor Status)
        PLP_IMPLIED = 0x28,

        // ROL (Rotate Left)
        ROL_ACCUMULATOR = 0x2A,
        ROL_ZERO_PAGE = 0x26,
        ROL_ZERO_PAGE_X = 0x36,
        ROL_ABSOLUTE = 0x2E,
        ROL_ABSOLUTE_X = 0x3E,

        // ROR (Rotate Right)
        ROR_ACCUMULATOR = 0x6A,
        ROR_ZERO_PAGE = 0x66,
        ROR_ZERO_PAGE_X = 0x76,
        ROR_ABSOLUTE = 0x6E,
        ROR_ABSOLUTE_X = 0x7E,

        // RTI (Return from Interrupt)
        RTI_IMPLIED = 0x40,

        // RTS (Return from Subroutine)
        RTS_IMPLIED = 0x60,

        // SBC (Subtract with Borrow)
        SBC_IMMEDIATE = 0xE9,
        SBC_ZERO_PAGE = 0xE5,
        SBC_ZERO_PAGE_X = 0xF5,
        SBC_ABSOLUTE = 0xED,
        SBC_ABSOLUTE_X = 0xFD,
        SBC_ABSOLUTE_Y = 0xF9,
        SBC_INDIRECT_X = 0xE1,
        SBC_INDIRECT_Y = 0xF1,

        // SEC (Set Carry Flag)
        SEC_IMPLIED = 0x38,

        // SED (Set Decimal Flag)
        SED_IMPLIED = 0xF8,

        // SEI (Set Interrupt Disable)
        SEI_IMPLIED = 0x78,

        // STA (Store Accumulator)
        STA_ZERO_PAGE = 0x85,
        STA_ZERO_PAGE_X = 0x95,
        STA_ABSOLUTE = 0x8D,
        STA_ABSOLUTE_X = 0x9D,
        STA_ABSOLUTE_Y = 0x99,
        STA_INDIRECT_X = 0x81,
        STA_INDIRECT_Y = 0x91,

        // STX (Store X Register)
        STX_ZERO_PAGE = 0x86,
        STX_ZERO_PAGE_Y = 0x96,
        STX_ABSOLUTE = 0x8E,

        // STY (Store Y Register)
        STY_ZERO_PAGE = 0x84,
        STY_ZERO_PAGE_X = 0x94,
        STY_ABSOLUTE = 0x8C,

        // TAX (Transfer Accumulator to X)
        TAX_IMPLIED = 0xAA,

        // TAY (Transfer Accumulator to Y)
        TAY_IMPLIED = 0xA8,

        // TSX (Transfer Stack Pointer to X)
        TSX_IMPLIED = 0xBA,

        // TXA (Transfer X to Accumulator)
        TXA_IMPLIED = 0x8A,

        // TXS (Transfer X to Stack Pointer)
        TXS_IMPLIED = 0x9A,

        // TYA (Transfer Y to Accumulator)
        TYA_IMPLIED = 0x98
    };

}