#pragma once

#include "memory/sizes.h"

namespace E6502
{
    enum AddressingModesBitMasks
    {
        IMPLIED_EXCEPTION         = 0b00000000,
        IMPLIED_UNSET_BITMASK     = 0b00000111,
        IMPLIED_SET_BITMASK       = 0b00011000,
        IMMEDIATE_UNSET_BITMASK   = 0b00010100,
        ZERO_PAGE_EXCEPTION       = 0b01010100,
        ZERO_PAGE_UNSET_BITMASK   = 0b00011000,
        ZERO_PAGE_SET_BITMASK     = 0b00000100,
        ZERO_PAGE_X_UNSET_BITMASK = 0b00001000,
        ZERO_PAGE_X_SET_BITMASK   = 0b00010100,
        ZERO_PAGE_Y_EXCEPTION_1   = 0b10110110,
        ZERO_PAGE_Y_EXCEPTION_2   = 0b10010110,
        ABSOLUTE_EXCEPTION        = 0b00100000,
        ABSOLUTE_UNSET_BITMASK    = 0b00010000,
        ABSOLUTE_SET_BITMASK      = 0b00001100,
        ABSOLUTE_X_SET_BITMASK    = 0b00011100,
        ABSOLUTE_Y_EXCEPTION      = 0b10111110,
        ABSOLUTE_Y_UNSET_BITMASK  = 0b00000110,
        ABSOLUTE_Y_SET_BITMASK    = 0b00011000,
        INDIRECT_X_UNSET_BITMASK  = 0b00011110,
        INDIRECT_X_SET_BITMASK    = 0b00000001,
        INDIRECT_Y_UNSET_BITMASK  = 0b00001110,
        INDIRECT_Y_SET_BITMASK    = 0b00010001,
    };

    enum AddressingModes
    {
        NOT_IMPLEMENTED = 0,
        IMPLIED,
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

    const AddressingModes decodeAddressingMode(Byte instruction);
}