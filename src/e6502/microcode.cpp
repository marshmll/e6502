#include "stdafx.h"
#include "e6502/microcode.h"

void E6502::CPU::execute(int cycles)
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
            setLoadFlags();                 // Set Flags as appropriate

            std::cout << "LDA #$" << std::hex << std::uppercase << value << "\n";

            break;
        }
        /* LOAD ACCUMULATOR ZERO PAGE ============================================================= */
        case LDA_ZP:
        {
            Byte base_pointer = fetchByte(cycles); // Fetch base pointer
            Word zero_page_addr = 0;               // Set lower byte of zero page address as the base pointer
            zero_page_addr |= base_pointer;
            A = readByte(cycles, zero_page_addr); // Copies the value read from zero page address into A
            setLoadFlags();                       // Set Flags as appropriate

            std::cout << "LDA $" << std::hex << std::uppercase << base_pointer << "\n";

            break;
        }
        /* LOAD ACCUMULATOR ZERO PAGE X =========================================================== */
        case LDA_ZX:
        {
            Byte base_pointer = fetchByte(cycles); // Fetch base pointer
            base_pointer += X;                     // Add the contents of X into the base pointer
            Word zero_page_addr = 0;               // Set lower byte of zero page address as the
            zero_page_addr |= base_pointer;        // base pointer
            cycles--;                              // Decrement cicle count
            A = readByte(cycles, zero_page_addr);  // Copies the value read from the address into A
            setLoadFlags();                        // Set Flags as appropriate

            std::cout << "LDA $" << std::hex << std::uppercase << base_pointer << ", X" << "\n";

            break;
        }
        /* LOAD ACCUMULATOR ABSOLUTE ============================================================== */
        case LDA_AB:
        {
            Word abs_addr = fetchWord(cycles); // Fetch the 16 bit absolute address
            A = readByte(cycles, abs_addr);    // Read the value at the address into A
            setLoadFlags();                    // Set Flags as appropriate

            std::cout << "LDA $" << std::hex << std::uppercase << abs_addr << "\n";

            break;
        }
        /* LOAD ACCUMULATOR ABSOLUTE X ============================================================ */
        case LDA_AX:
        {
            Word abs_addr = fetchWord(cycles);       // Fetch the 16 bit absolute address
            abs_addr += X;                           // Add the contents of X into the address
            A = readByte(cycles, abs_addr);          // Store the value at the address into A
            if (pageCrossed(abs_addr - X, abs_addr)) // If page crossed, i.e, changed the highest bit in the
                --cycles;                            // address
            setLoadFlags();                          // Set Flags as appropriate

            std::cout << "LDA $" << std::hex << std::uppercase << abs_addr << ", X" << "\n";

            break;
        }
        /* LOAD ACCUMULATOR ABSOLUTE y ============================================================ */
        case LDA_AY:
        {
            Word abs_addr = fetchWord(cycles);    // Fetch the 16 bit absolute address
            Word prev_addr = abs_addr;            // Save the original address
            abs_addr += Y;                        // Add the contents of Y into the address
            A = readByte(cycles, abs_addr);       // Store the value at the address into A
            if (pageCrossed(prev_addr, abs_addr)) // If page crossed, i.e, changed the highest bit in the
                --cycles;                         // address
            setLoadFlags();                       // Set Flags as appropriate

            std::cout << "LDA $" << std::hex << std::uppercase << abs_addr << ", Y" << "\n";

            break;
        }
        /* LOAD ACCUMULATOR INDIRECT X ============================================================ */
        case LDA_IX:
        {
            Byte base_pointer = fetchByte(cycles);               // Fetch the base pointer
            base_pointer += X;                                   // Add the contents of X into the base pointer
            Word zero_page_addr = 0;                             // Set the low bytes of the address as the
            zero_page_addr |= base_pointer;                      // base pointer.
            Word target_addr = readWord(cycles, zero_page_addr); // Read the target address from zero page address
            A = readByte(cycles, target_addr);                   // Store the contents in memory at the address into A.
            --cycles;                                            // Decrement cycle count
            setLoadFlags();                                      // Set Flags as appropriate

            std::cout << "LDA ($" << std::hex << std::uppercase << base_pointer - X << ", X)" << "\n";

            break;
        }
        /* LOAD ACCUMULATOR INDIRECT y ============================================================ */
        case LDA_IY:
        {
            Byte base_pointer = fetchByte(cycles);               // Fetch the base pointer
            Word zero_page_addr = 0;                             // Set the low bytes of the address as the
            zero_page_addr |= base_pointer;                      // base pointer
            Word target_addr = readWord(cycles, zero_page_addr); // Read the target address from zero page address
            target_addr += Y;                                    // Add the Y register to the target address
            A = readByte(cycles, target_addr);                   // Load the contents in memory at the address into A
            if (pageCrossed(target_addr - Y, target_addr))       // Add carry cycle if target adress page crossed
                --cycles;
            setLoadFlags(); // Set Flags as appropriate

            std::cout << "LDA ($" << std::hex << std::uppercase << base_pointer - Y << "), Y" << "\n";

            break;
        }
        /* LOAD INDEX REGISTER X IMMEDIATE ======================================================== */
        case LDX_IM:
        {
            Byte imm_value = fetchByte(cycles); // Fetch the immediate value
            X = imm_value;                      // Copy the value into X
            setLoadFlags();                     // Set flags as appropriate

            std::cout << "LDX #$" << std::hex << std::uppercase << imm_value << "\n";

            break;
        }
        /* LOAD INDEX REGISTER X ZERO PAGE ======================================================== */
        case LDX_ZP:
        {
            Byte base_pointer = fetchByte(cycles); // Fetch base pointer
            Word zero_page_addr = 0;               // Set lower byte of zero page address as the base pointer
            zero_page_addr |= base_pointer;
            A = readByte(cycles, zero_page_addr); // Copies the value read from zero page address into X
            setLoadFlags();                       // Set Flags as appropriate

            std::cout << "LDX $" << std::hex << std::uppercase << base_pointer << "\n";

            break;
        }
        /* LOAD INDEX REGISTER X ZERO PAGE Y ====================================================== */
        case LDX_ZY:
        {
            Byte base_pointer = fetchByte(cycles); // Fetch base pointer
            base_pointer += Y;                     // Add the contents of Y into the base pointer
            Word zero_page_addr = 0;               // Set lower byte of zero page address as the
            zero_page_addr |= base_pointer;        // base pointer
            cycles--;                              // Decrement cicle count
            X = readByte(cycles, zero_page_addr);  // Copies the value read from the address into X
            setLoadFlags();                        // Set Flags as appropriate

            std::cout << "LDX $" << std::hex << std::uppercase << base_pointer << ", Y" << "\n";

            break;
        }
        /* LOAD INDEX REGISTER X ABSOLUTE ========================================================= */
        case LDX_AB:
        {
            Word abs_addr = fetchWord(cycles); // Fetch the 16 bit absolute address
            X = readByte(cycles, abs_addr);    // Read the value at the address into X
            setLoadFlags();                    // Set Flags as appropriate

            std::cout << "LDX $" << std::hex << std::uppercase << abs_addr << "\n";

            break;
        }
        /* LOAD INDEX REGISTER X ABSOLUTE Y ======================================================= */
        case LDX_AY:
        {
            Word abs_addr = fetchWord(cycles);    // Fetch the 16 bit absolute address
            Word prev_addr = abs_addr;            // Save the original address
            abs_addr += Y;                        // Add the contents of Y into the address
            X = readByte(cycles, abs_addr);       // Store the value at the address into X
            if (pageCrossed(prev_addr, abs_addr)) // If page crossed, i.e, changed the highest bit in the
                --cycles;                         // address
            setLoadFlags();                       // Set Flags as appropriate

            std::cout << "LDX $" << std::hex << std::uppercase << abs_addr << ", Y" << "\n";

            break;
        }
        /* LOAD INDEX REGISTER Y IMMEDIATE ======================================================== */
        case LDY_IM:
        {
            Byte imm_value = fetchByte(cycles); // Fetch the immediate value
            Y = imm_value;                      // Copy the value into Y
            setLoadFlags();                     // Set flags as appropriate

            std::cout << "LDY #$" << std::hex << std::uppercase << imm_value << "\n";

            break;
        }
        /* LOAD INDEX REGISTER Y ZERO PAGE ======================================================== */
        case LDY_ZP:
        {
            Byte base_pointer = fetchByte(cycles); // Fetch base pointer
            Word zero_page_addr = 0;               // Set lower byte of zero page address as the base pointer
            zero_page_addr |= base_pointer;
            Y = readByte(cycles, zero_page_addr); // Copies the value read from zero page address into Y
            setLoadFlags();                       // Set Flags as appropriate

            std::cout << "LDY $" << std::hex << std::uppercase << base_pointer << "\n";

            break;
        }
        /* LOAD INDEX REGISTER Y ZERO PAGE X ====================================================== */
        case LDY_ZX:
        {
            Byte base_pointer = fetchByte(cycles); // Fetch base pointer
            base_pointer += X;                     // Add the contents of X into the base pointer
            Word zero_page_addr = 0;               // Set lower byte of zero page address as the
            zero_page_addr |= base_pointer;        // base pointer
            cycles--;                              // Decrement cicle count
            Y = readByte(cycles, zero_page_addr);  // Copies the value read from the address into Y
            setLoadFlags();                        // Set Flags as appropriate

            std::cout << "LDY $" << std::hex << std::uppercase << base_pointer << ", X" << "\n";

            break;
        }
        /* LOAD INDEX REGISTER Y ABSOLUTE ========================================================= */
        case LDY_AB:
        {
            Word abs_addr = fetchWord(cycles); // Fetch the 16 bit absolute address
            Y = readByte(cycles, abs_addr);    // Read the value at the address into Y
            setLoadFlags();                    // Set Flags as appropriate

            std::cout << "LDY $" << std::hex << std::uppercase << abs_addr << "\n";

            break;
        }
        /* LOAD INDEX REGISTER Y ABSOLUTE X ======================================================= */
        case LDY_AX:
        {
            Word abs_addr = fetchWord(cycles);    // Fetch the 16 bit absolute address
            Word prev_addr = abs_addr;            // Save the original address
            abs_addr += X;                        // Add the contents of X into the address
            Y = readByte(cycles, abs_addr);       // Store the value at the address into Y
            if (pageCrossed(prev_addr, abs_addr)) // If page crossed, i.e, changed the highest bit in the
                --cycles;                         // address
            setLoadFlags();                       // Set Flags as appropriate

            std::cout << "LDY $" << std::hex << std::uppercase << abs_addr << ", X" << "\n";

            break;
        }
        /* JUMP ABSOLUTE ========================================================================== */
        case JMP_AB:
        {
            Word jmp_addr = fetchWord(cycles); // Fetch the jump address
            PC = jmp_addr;                     // Transfer program counter to the address

            std::cout << "JMP $" << std::hex << std::uppercase << jmp_addr << "\n";

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

            std::cout << "JSR $" << std::hex << std::uppercase << subroutine_addr << "\n";

            break;
        }
        /* RETURN FROM SUBROUTINE ================================================================= */
        case RTS:
        {
            Word return_addr = readWord(cycles, SP + 0x100); // Read return address from stack
            SP += 2;                                         // Decrement stack pointer
            PC = return_addr + 1;                            // Add 1 to the return address
            cycles -= 3;                                     // Decrement cycle count

            std::cout << "RTS" << "\n";

            break;
        }
        default:
        {
            std::cout << "UNKNOWN INSTRUCTION: 0x" << std::hex << static_cast<int>(ins) << " FROM ADDRESS 0x" << std::hex << (int)PC << "\n";
            std::cout << "ABORTING WITH " << std::dec << cycles << " REMAINING." << "\n";
            return;
        }
        }
    }
}