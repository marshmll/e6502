#pragma once

#include "sizes.h"

/* INSTRUCTION OPCODES =========================================================================== */

enum Instructions
{
    LDA_IM = 0xA9, // LOAD ACCUMULATOR IMMEDIATE OPCODE
    LDA_ZP = 0xA5, // LOAD ACCUMULATOR ZERO PAGE
};