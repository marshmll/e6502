#include "stdafx.h"
#include "cpu.h"

CPU::CPU(Memory &memory) : memory(memory) {}

CPU::~CPU() {}

void CPU::printState()
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

void CPU::reset()
{
    SP = 0x0FF;                    // Initialize Stack Pointer to 0xFF (0x1FF)
    PC = 0xFFFC;                   // Initialize the reset vector address
    C = Z = I = D = B = V = N = 0; // Clear Flags
    A = X = Y = 0;                 // Clear other registers

    memory.init(); // Initialize memory

    memory.write(0xFFFC, JSR);
    memory.write(0xFFFD, 0xBE);
    memory.write(0xFFFE, 0xB0);
    memory.write(0xB0BE, LDA_IM);
    memory.write(0xB0BF, 0x0);
    memory.write(0xB0C0, RTS);
}

void CPU::execute(DWord cycles)
{
    while (cycles > 0)
    {
        Byte ins = fetchByte(cycles);

        switch (ins)
        {
        /* LOAD ACCUMULATOR IMMEDIATE ============================================================= */
        case LDA_IM:
        {
            Byte value = fetchByte(cycles); // Fetch immediate value
            A = value;                      // Copies the value into the accumulator
            setLDAFlags();                  // Set Flags as appropriate

            break;
        }
        /* LOAD ACCUMULATOR ZERO PAGE ============================================================= */
        case LDA_ZP:
        {
            Byte zero_page_addr = fetchByte(cycles); // Fetch zero page address value
            A = readByte(cycles, zero_page_addr);    // Copies the value read from zero page address into A
            setLDAFlags();                           // Set Flags as appropriate

            break;
        }
        /* LOAD ACCUMULATOR ZERO PAGE X =========================================================== */
        case LDA_ZX:
        {
            Byte zero_page_addr = fetchByte(cycles); // Fetch zero page address value
            zero_page_addr += X;                     // Add the value in reg. X into the address.

            cycles--; // Decrement cicle count

            A = readByte(cycles, zero_page_addr); // Copies the value read from the address into A
            setLDAFlags();                        // Set Flags as appropriate

            break;
        }
        /* JUMP TO SUBROUTINE ===================================================================== */
        case JSR:
        {
            Word subroutine_addr = fetchWord(cycles); // Fetch subroutine address value
            SP -= 2;                                  // Increment stack pointer
            writeWord(cycles, SP + 0x100, PC - 1);    // Write PC - 1 into the stack
            PC = subroutine_addr;                     // Change Program Counter to the subroutine address.
            --cycles;                                 // Decrement cycle count

            break;
        }
        /* RETURN FROM SUBROUTINE ================================================================= */
        case RTS:
        {
            Word return_addr = readWord(cycles, SP + 0x100); // Read return address from stack
            SP += 2;                                         // Decrement stack pointer
            PC = return_addr + 1;                            // Add 1 to the return address
            cycles -= 3;                                     // Decrement cycle count

            break;
        }
        default:
        {
            std::cout << "UNKNOWN INSTRUCTION: 0x" << std::hex << static_cast<int>(ins) << " FROM ADDRESS 0x" << std::hex << (int)PC << "\n";
            break;
        }
        }
    }
}

Byte CPU::fetchByte(DWord &cycles)
{
    Byte data = memory.read(PC);

    ++PC;
    --cycles;

    return data;
}

Word CPU::fetchWord(DWord &cycles)
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
#ifdef BIG_ENDIAN_PLATFORM
    swapBytesInWord(data);
#endif

    cycles -= 2;

    return data;
}

Byte CPU::readByte(DWord &cycles, const Word &addr)
{
    Byte data = memory.read(addr);

    --cycles;

    return data;
}

Word CPU::readWord(DWord &cycles, const Word &addr)
{
    /* IMPORTANT: 6502 IS LITTLE ENDIAN! */
    // This means that the order of the bytes is reversed in memory.

    // Read first byte into lower bytes of the variable
    Word data = memory.read(addr);

    // Read last byte into higher part of the variable.
    data |= (memory.read(addr + 1) << 8);

// Check for platform endianness
#ifdef BIG_ENDIAN_PLATFORM
    swapBytesInWord(data);
#endif

    cycles -= 2;

    return data;
}

void CPU::writeWord(DWord &cycles, const Word &addr, const Word data)
{
    memory.write(addr, data & 0x00FF); // Write lower bytes first.
    memory.write(addr + 1, data >> 8); // Write upper bytes last.

    cycles -= 2;
}

void CPU::setLDAFlags()
{
    Z = (Byte)(A == 0);               // Sets zero flag if accumulator is zero.
    N = (Byte)((A & 0b10000000) > 0); // Sets negative flag if seventh bit is 1
}

void CPU::swapBytesInWord(Word &word)
{
    Word tmp = word;
    word << 8;
    word &= 0xFF00;
    word |= (tmp >> 8);
}
