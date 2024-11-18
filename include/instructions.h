#pragma once

#include "sizes.h"

/* INSTRUCTION OPCODES =========================================================================== */

enum Instructions
{
    LDA_IM = 0xA9, // LOAD ACCUMULATOR IMMEDIATE
    LDA_ZP = 0xA5, // LOAD ACCUMULATOR ZERO PAGE
    LDA_ZX = 0xB5, // LOAD ACCUMULATOR ZERO PAGE X
    LDA_AB = 0xAD, // LOAD ACCUMULATOR ABSOLUTE
    LDA_AX = 0xBD, // LOAD ACCUMULATOR ABSOLUTE X
    LDA_AY = 0xB9, // LOAD ACCUMULATOR ABSOLUTE y
    JSR    = 0x20, // JUMP TO SUBROUTINE
    RTS    = 0x60, // RETURN FROM SUBROUTINE
};