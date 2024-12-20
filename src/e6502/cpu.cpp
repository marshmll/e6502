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
    std::cout << "│ " << static_cast<int>((P & NEGATIVE_FLAG) == NEGATIVE_FLAG) << " │ " << static_cast<int>((P & OVERFLOW_FLAG) == OVERFLOW_FLAG) << " │ - │ " << static_cast<int>((P & BREAK_FLAG) == BREAK_FLAG) << " │ " << static_cast<int>((P & DECIMAL_FLAG) == DECIMAL_FLAG) << " │ " << static_cast<int>((P & INTERRUPT_DISABLE_FLAG) == INTERRUPT_DISABLE_FLAG) << " │ " << static_cast<int>((P & ZERO_FLAG) == ZERO_FLAG) << " │ " << static_cast<int>((P & CARRY_FLAG) == CARRY_FLAG) << " │\n";
    std::cout << "└───┴───┴───┴───┴───┴───┴───┴───┘\n";
}
/* EXECUTION FUNCTIONS ============================================================================ */

void E6502::CPU::reset()
{
    SP = 0x0FF;                            // Initialize Stack Pointer to 0xFF (0x1FF)
    setFlag(INTERRUPT_DISABLE_FLAG, true); // Disable interrupts
    setFlag(DECIMAL_FLAG, false);          // Clear decimal flag
    setFlag(BREAK_FLAG, true);             // Set break flag
    A = X = Y = 0;                         // Clear other registers
    clkCycles = 7;                         // RESET takes 7 clock cycles.
    PC = readWord(RESET_VECTOR);           // Read the program counter from RESET VECTOR

    std::cout << "RESETTING TO ADDRESS 0x" << std::hex << PC << "\n";
}

/* INSTRUCTION FETCH FUNCTIONS ==================================================================== */

E6502::Byte E6502::CPU::fetchByte()
{
    Byte data = memory.read(PC);

    ++PC;
    clkCycles++;

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

    clkCycles++;

    return data;
}

void E6502::CPU::writeByte(const Word &addr, const Byte data)
{
    memory.write(addr, data);
    clkCycles++;
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
    Word actual_data = data;

    // Check for platform endianness
    if (IS_BIG_ENDIAN_PLATFORM)
        swapBytesInWord(actual_data);

    memory.write(addr, actual_data & 0x00FF); // Write lower bytes first.
    memory.write(addr + 1, actual_data >> 8); // Write upper bytes last.

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

void E6502::CPU::pushByte(const Byte data)
{
    memory.write(SP + 0x100, data);
    SP--;
}

void E6502::CPU::pushWord(const Word data)
{
    pushByte(data >> 8);
    pushByte(data & 0xFF);
}

const E6502::Byte E6502::CPU::popByte()
{
    SP++;
    return memory.read(SP + 0x100);
}

const E6502::Word E6502::CPU::popWord()
{
    Word data = popByte();
    data |= (popByte() << 8);

    return data;
}

/* FLAGS FUNCTIONS ================================================================================ */

void E6502::CPU::setFlag(const Byte &flag, const bool &value)
{
    if (value)
        P |= flag;
    else if (!value && (P & flag) != 0)
        P ^= flag;
}

const bool E6502::CPU::isFlagSet(const Byte &flag) const
{
    return (P & flag) != 0;
}

void E6502::CPU::updateADCFlags(const Byte &operand, const Byte &previous_A_value)
{
    // If result is bigger than a Byte, set carry flag.
    setFlag(CARRY_FLAG, (previous_A_value + operand + (P & CARRY_FLAG)) > 255); // Set carry flag to 1.

    // If the result is zero, set zero flag.
    setFlag(ZERO_FLAG, A == 0);

    // If the result has 7th bit set, set negative flag.
    setFlag(NEGATIVE_FLAG, (A & NEGATIVE_FLAG) != 0);

    // If the addition of two numbers with same signal result in a number
    // with the opposite sign, set overflow flag
    setFlag(OVERFLOW_FLAG,
            ((operand & NEGATIVE_FLAG) == 0 && (previous_A_value & NEGATIVE_FLAG) == 0 && (A & NEGATIVE_FLAG) != 0) ||
                ((operand & NEGATIVE_FLAG) != 0 && (previous_A_value & NEGATIVE_FLAG) != 0 && (A & NEGATIVE_FLAG) == 0));
}

void E6502::CPU::updateZeroAndNegativeFlags(const Byte &val)
{
    setFlag(ZERO_FLAG, val == 0); // Sets zero flag if accumulator is zero.

    setFlag(NEGATIVE_FLAG, (val & NEGATIVE_FLAG) != 0); // Sets negative flag if seventh bit is 1
}

void E6502::CPU::updateSBCFlags(const Byte &operand, const Byte &previous_A_value)
{
    // If result is greater or equal 0, set carry flag.
    setFlag(CARRY_FLAG, (previous_A_value - operand - (P & CARRY_FLAG)) >= 0);

    // If the result is zero, set zero flag.
    setFlag(ZERO_FLAG, A == 0);

    // If the result has 7th bit set, set negative flag.
    setFlag(NEGATIVE_FLAG, (A & NEGATIVE_FLAG) != 0);

    // If the subtraction of a negative minus a positive equais a positive or
    // a positive minus a negative equais a negative, set overflow flag.
    setFlag(OVERFLOW_FLAG, ((previous_A_value & NEGATIVE_FLAG) != 0 && (operand & NEGATIVE_FLAG) == 0 && (A & NEGATIVE_FLAG) == 0) ||
                               ((previous_A_value & NEGATIVE_FLAG) == 0 && (operand & NEGATIVE_FLAG) != 0 && (A & NEGATIVE_FLAG) != 0));
}
void E6502::CPU::updateCompareFlags(const Byte &operand, const Byte &val)
{
    const Byte result = val - operand;

    setFlag(ZERO_FLAG, operand == val);
    setFlag(NEGATIVE_FLAG, (result & NEGATIVE_FLAG) != 0);
    setFlag(CARRY_FLAG, operand <= val);
}