#include "stdafx.h"
#include "e6502/cpu.h"

/* CONSTRUCTOR AND DESTRUCTOR ===================================================================== */

E6502::CPU::CPU(Memory &memory) : memory(memory), clkCycles(0) { initLookupTables(); }

E6502::CPU::~CPU() {}

/* DEBUG FUNCTIONS ================================================================================ */

void E6502::CPU::printState()
{
    std::cout << "╔═══════════════════════════════╗" << "\n";
    std::cout << "║           MOS E6502           ║" << "\n";
    std::cout << "╚═══════════════════════════════╝" << "\n";
    std::cout << "┌────────────────┬──────────────┐\n";
    std::cout << "│    Register    │    Value     │\n";
    std::cout << "├────────────────┼──────────────┤\n";
    std::cout << std::hex << std::uppercase;
    std::cout << "│       PC       │     0x" << std::setw(4) << std::setfill('0') << PC << "   │\n";
    std::cout << "│       SP       │     0x" << std::setw(2) << std::setfill('0') << static_cast<int>(SP) << "     │\n";
    std::cout << "│       A        │     0x" << std::setw(2) << static_cast<int>(A) << "     │\n";
    std::cout << "│       X        │     0x" << std::setw(2) << static_cast<int>(X) << "     │\n";
    std::cout << "│       Y        │     0x" << std::setw(2) << static_cast<int>(Y) << "     │\n";
    std::cout << "├────────────────┴──────────────┤\n";
    std::cout << "│             FLAGS             │\n";
    std::cout << "├───┬───┬───┬───┬───┬───┬───┬───┤\n";
    std::cout << "│ N │ V │ - │ B │ D │ I │ Z │ C │\n";
    std::cout << "├───┼───┼───┼───┼───┼───┼───┼───┤\n";
    std::cout << "│ " << static_cast<int>((P & NEGATIVE_FLAG) == NEGATIVE_FLAG) << " │ " << static_cast<int>((P & OVERFLOW_FLAG) == OVERFLOW_FLAG) << " │ - │ " << static_cast<int>((P & BREAK_FLAG) == BREAK_FLAG) << " │ " << static_cast<int>((P & DECIMAL_FLAG) == DECIMAL_FLAG) << " │ " << static_cast<int>((P & INTERRUPT_FLAG) == INTERRUPT_FLAG) << " │ " << static_cast<int>((P & ZERO_FLAG) == ZERO_FLAG) << " │ " << static_cast<int>((P & CARRY_FLAG) == CARRY_FLAG) << " │\n";
    std::cout << "└───┴───┴───┴───┴───┴───┴───┴───┘\n";
}
/* EXECUTION FUNCTIONS ============================================================================ */

void E6502::CPU::reset()
{
    std::cout << "RESETTING..." << "\n";

    SP = 0x0FF;    // Initialize Stack Pointer to 0xFF (0x1FF)
    PC = 0xFFFC;   // Initialize the reset vector address
    P &= 0;        // Clear Flags
    A = X = Y = 0; // Clear other registers

    memory.init(); // Initialize memory

    memory.write(0xFFFC, BCC_RELATIVE);
    memory.write(0xFFFD, 0xFE);
}

/* INSTRUCTION FETCH FUNCTIONS ==================================================================== */

E6502::Byte E6502::CPU::fetchByte()
{
    Byte data = memory.read(PC);

    ++PC;
    ++clkCycles;

    return data;
}

E6502::Word E6502::CPU::fetchWord()
{
    /* IMPORTANT: 6502 IS LITTLE ENDIAN! */
    // This means that the order of the bytes is reversed in memory.

    // Read first byte into lower bytes of the variable
    Word data = memory.read(PC);
    ++PC;

    // Read last byte into higher part of the variable.
    data |= (memory.read(PC) << 8);
    ++PC;

    // Check for platform endianness
    if (IS_BIG_ENDIAN_PLATFORM)
        swapBytesInWord(data);

    clkCycles += 2;

    return data;
}

/* MEMORY I/O FUNCTIONS =========================================================================== */

E6502::Byte E6502::CPU::readByte(const Word &addr)
{
    Byte data = memory.read(addr);

    ++clkCycles;

    return data;
}

void E6502::CPU::writeByte(const Word &addr, const Byte data)
{
    memory.write(addr, data);
    ++clkCycles;
}

E6502::Word E6502::CPU::readWord(const Word &addr)
{
    /* IMPORTANT: 6502 IS LITTLE ENDIAN! */
    // This means that the order of the bytes is reversed in memory.

    // Read first byte into lower bytes of the variable
    Word data = memory.read(addr);

    // Read last byte into higher part of the variable.
    data |= (memory.read(addr + 1) << 8);

    // Check for platform endianness
    if (IS_BIG_ENDIAN_PLATFORM)
        swapBytesInWord(data);

    clkCycles += 2;

    return data;
}

void E6502::CPU::writeWord(const Word &addr, const Word data)
{
    memory.write(addr, data & 0x00FF); // Write lower bytes first.
    memory.write(addr + 1, data >> 8); // Write upper bytes last.

    clkCycles += 2;
}

void E6502::CPU::swapBytesInWord(Word &word)
{
    Word tmp = word;
    word << 8;
    word &= 0xFF00;
    word |= (tmp >> 8);
}

const bool E6502::CPU::pageCrossed(const Word &prev_addr, const Word &curr_addr)
{
    Byte previous_page = static_cast<Byte>(prev_addr >> 8); // Save the previous page
    Byte current_page = static_cast<Byte>(curr_addr >> 8);  // Save the current page
    return previous_page != current_page;
}

/* FLAGS FUNCTIONS ================================================================================ */

void E6502::CPU::setADCFlags(const Byte &operand, const Byte &previous_A_value)
{
    // If result is bigger than a Byte, set carry flag.
    if ((previous_A_value + operand + (P & CARRY_FLAG)) > 255)
        P |= CARRY_FLAG; // Set carry flag to 1.
    else if ((P & CARRY_FLAG))
        P ^= CARRY_FLAG; // Toggle carry flag.

    // If the result is zero, set carry flag.
    if (A == 0)
        P |= ZERO_FLAG;
    else if ((P & ZERO_FLAG))
        P ^= ZERO_FLAG;

    // If the result has 7th bit set, set negative flag.
    if ((A & NEGATIVE_FLAG))
        P |= NEGATIVE_FLAG;
    else if ((P & NEGATIVE_FLAG))
        P ^= NEGATIVE_FLAG;

    // If the addition of two numbers with same signal result in a number
    // with the opposite sign, set overflow flag
    if (((operand & NEGATIVE_FLAG) == 0 && (previous_A_value & NEGATIVE_FLAG) == 0 && (A & NEGATIVE_FLAG) != 0) ||
        ((operand & NEGATIVE_FLAG) != 0 && (previous_A_value & NEGATIVE_FLAG) != 0 && (A & NEGATIVE_FLAG) == 0))
        P |= OVERFLOW_FLAG;
    else if ((P & OVERFLOW_FLAG))
        P ^= OVERFLOW_FLAG;
}

void E6502::CPU::setZeroAndNegativeFlags(const Byte &reg)
{
    if (reg == 0)
        P |= ZERO_FLAG; // Sets zero flag if accumulator is zero.
    else if ((P & ZERO_FLAG))
        P ^= ZERO_FLAG;

    if (reg & NEGATIVE_FLAG) // Sets negative flag if seventh bit is 1
        P |= NEGATIVE_FLAG;
    else if ((P & NEGATIVE_FLAG))
        P ^= NEGATIVE_FLAG;
}

void E6502::CPU::setSBCFlags(const Byte &operand, const Byte &previous_A_value)
{
    // If result is greater or equal 0, set carry flag.
    if ((previous_A_value - operand - (P & CARRY_FLAG)) >= 0)
        P |= CARRY_FLAG; // Set carry flag to 1.
    else if ((P & CARRY_FLAG))
        P ^= CARRY_FLAG; // Clear carry flag.

    // If the result is zero, set zero flag.
    if (A == 0)
        P |= ZERO_FLAG;
    else if ((P & ZERO_FLAG))
        P ^= ZERO_FLAG;

    // If the result has 7th bit set, set negative flag.
    if ((A & NEGATIVE_FLAG))
        P |= NEGATIVE_FLAG;
    else if ((P & NEGATIVE_FLAG))
        P ^= NEGATIVE_FLAG;

    // If the subtraction of a negative minus a positive equais a positive or
    // a positive minus a negative equais a negative, set overflow flag.
    if (((previous_A_value & NEGATIVE_FLAG) != 0 && (operand & NEGATIVE_FLAG) == 0 && (A & NEGATIVE_FLAG) == 0) ||
        ((previous_A_value & NEGATIVE_FLAG) == 0 && (operand & NEGATIVE_FLAG) != 0 && (A & NEGATIVE_FLAG) != 0))
        P |= OVERFLOW_FLAG;
    else if ((P & OVERFLOW_FLAG))
        P ^= OVERFLOW_FLAG;
}