#include "stdafx.h"
#include "e6502/cpu.h"

E6502::CPU::CPU(Memory &memory) : memory(memory) {}

E6502::CPU::~CPU() {}

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
    std::cout << "│ " << static_cast<int>(N) << " │ " << static_cast<int>(V) << " │ - │ " << static_cast<int>(B) << " │ " << static_cast<int>(D) << " │ " << static_cast<int>(I) << " │ " << static_cast<int>(Z) << " │ " << static_cast<int>(C) << " │\n";
    std::cout << "└───┴───┴───┴───┴───┴───┴───┴───┘\n";
}

void E6502::CPU::reset()
{
    std::cout << "RESETTING..." << "\n";

    SP = 0x0FF;                    // Initialize Stack Pointer to 0xFF (0x1FF)
    PC = 0xFFFC;                   // Initialize the reset vector address
    C = Z = I = D = B = V = N = 0; // Clear Flags
    A = X = Y = 0;                 // Clear other registers

    memory.init(); // Initialize memory

    memory.write(0xFFFC, LDA_IM);
}

E6502::Byte E6502::CPU::fetchByte(int &cycles)
{
    Byte data = memory.read(PC);

    ++PC;
    --cycles;

    return data;
}

E6502::Word E6502::CPU::fetchWord(int &cycles)
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
    if (BIG_ENDIAN_PLATFORM)
        swapBytesInWord(data);

    cycles -= 2;

    return data;
}

E6502::Byte E6502::CPU::readByte(int &cycles, const Word &addr)
{
    Byte data = memory.read(addr);

    --cycles;

    return data;
}

E6502::Word E6502::CPU::readWord(int &cycles, const Word &addr)
{
    /* IMPORTANT: 6502 IS LITTLE ENDIAN! */
    // This means that the order of the bytes is reversed in memory.

    // Read first byte into lower bytes of the variable
    Word data = memory.read(addr);

    // Read last byte into higher part of the variable.
    data |= (memory.read(addr + 1) << 8);

    // Check for platform endianness
    if (BIG_ENDIAN_PLATFORM)
        swapBytesInWord(data);

    cycles -= 2;

    return data;
}

void E6502::CPU::writeWord(int &cycles, const Word &addr, const Word data)
{
    memory.write(addr, data & 0x00FF); // Write lower bytes first.
    memory.write(addr + 1, data >> 8); // Write upper bytes last.

    cycles -= 2;
}

void E6502::CPU::setLoadFlags()
{
    Z = (Byte)(A == 0);               // Sets zero flag if accumulator is zero.
    N = (Byte)((A & 0b10000000) > 0); // Sets negative flag if seventh bit is 1
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
    return previous_page < current_page;
}
