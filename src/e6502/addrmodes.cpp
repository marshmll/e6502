#include "stdafx.h"
#include "e6502/addrmodes.h"

const E6502::AddressingModes E6502::decodeAddressingMode(Byte instruction)
{
    AddressingModes mode = NOT_IMPLEMENTED;

    /* Handle instructions that are exceptions in the bitmasking */
    if (instruction == IMPLIED_EXCEPTION)
    {
        std::cout << "Implied mode found!" << "\n";
        mode = IMPLIED;
    }
    else if (instruction == ZERO_PAGE_EXCEPTION)
    {
        std::cout << "Zero Page mode found!" << "\n";
        mode = ZERO_PAGE;
    }
    else if (instruction == ZERO_PAGE_Y_EXCEPTION_1 || instruction == ZERO_PAGE_Y_EXCEPTION_2)
    {
        std::cout << "Zero Page Y mode found!" << "\n";
        mode = ZERO_PAGE_Y;
    }
    else if (instruction == ABSOLUTE_EXCEPTION)
    {
        std::cout << "Absolute mode found!" << "\n";
        mode = ABSOLUTE;
    }
    else if (instruction == ABSOLUTE_Y_EXCEPTION)
    {
        std::cout << "Absolute Y mode found!" << "\n";
        mode = ABSOLUTE_Y;
    }

    /* Bitmasking tests */
    else if ((instruction & IMPLIED_UNSET_BITMASK) == 0 && (instruction & IMPLIED_SET_BITMASK) > 0)
    {
        std::cout << "Implied mode found!" << "\n";
        mode = IMPLIED;
    }
    else if ((instruction & INDIRECT_X_UNSET_BITMASK) == 0 && (instruction & INDIRECT_X_SET_BITMASK) > 0)
    {
        std::cout << "Indirect X mode found!" << "\n";
        mode = INDIRECT_X;
    }
    else if ((instruction & INDIRECT_Y_UNSET_BITMASK) == 0 && (instruction & INDIRECT_Y_SET_BITMASK) > 0)
    {
        std::cout << "Indirect Y mode found!" << "\n";
        mode = INDIRECT_Y;
    }

    else if (((instruction & ZERO_PAGE_UNSET_BITMASK) == 0) && (instruction & ZERO_PAGE_SET_BITMASK) > 0)
    {
        std::cout << "Zero Page mode found!" << "\n";
        mode = ZERO_PAGE;
    }
    else if ((instruction & ZERO_PAGE_X_UNSET_BITMASK) == 0 && (instruction & ZERO_PAGE_X_SET_BITMASK) > 0)
    {
        std::cout << "Zero Page X mode found!" << "\n";
        mode = ZERO_PAGE_X;
    }
    else if ((instruction & IMMEDIATE_UNSET_BITMASK) == 0)
    {
        std::cout << "Immediate mode found!" << "\n";
        mode = IMMEDIATE;
    }
    else if (((instruction & ABSOLUTE_UNSET_BITMASK) == 0) && (instruction & ABSOLUTE_SET_BITMASK) > 0)
    {
        std::cout << "Absolute mode found!" << "\n";
        mode = ABSOLUTE;
    }
    else if ((instruction & ABSOLUTE_Y_UNSET_BITMASK) == 0 && (instruction & ABSOLUTE_Y_SET_BITMASK) > 0)
    {
        std::cout << "Absolute Y mode found!" << "\n";
        mode = ABSOLUTE_Y;
    }
    else if ((instruction & ABSOLUTE_X_SET_BITMASK) > 0)
    {
        std::cout << "Absolute X mode found!" << "\n";
        mode = ABSOLUTE_X;
    }

    return mode;
}