#pragma once

/* INSTRUCTION OPCODES =========================================================================== */

namespace E6502
{
    enum Instructions
    {
        NOP = 0xEA,    // NO OPERATION
        LDA_IM = 0xA9, // LOAD ACCUMULATOR IMMEDIATE
        LDA_ZP = 0xA5, // LOAD ACCUMULATOR ZERO PAGE
        LDA_ZX = 0xB5, // LOAD ACCUMULATOR ZERO PAGE X
        LDA_AB = 0xAD, // LOAD ACCUMULATOR ABSOLUTE
        LDA_AX = 0xBD, // LOAD ACCUMULATOR ABSOLUTE X
        LDA_AY = 0xB9, // LOAD ACCUMULATOR ABSOLUTE y
        LDA_IX = 0xA1, // LOAD ACCUMULATOR INDIRECTED X
        LDA_IY = 0xB1, // LOAD ACCUMULATOR INDIRECTED Y
        JMP_AB = 0x4C, // JUMP ABSOLUTE
        JSR = 0x20,    // JUMP TO SUBROUTINE
        RTS = 0x60,    // RETURN FROM SUBROUTINE
    };
}
