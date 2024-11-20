#pragma once

#include "e6502/cpu.h"
#include "e6502/decode.h"

namespace E6502
{
    using InstructionHandler = std::function<void(E6502::CPU &, const E6502::AddressingModes &)>;

    namespace InstructionHandlers
    {
        /* INSTRUCTION SPECIFIC HANDLERS ========================================================== */

        void LDAHandler(E6502::CPU &cpu, const E6502::AddressingModes &addr_mode);

        void LDXHandler(E6502::CPU &cpu, const E6502::AddressingModes &addr_mode);

        void LDYHandler(E6502::CPU &cpu, const E6502::AddressingModes &addr_mode);

        /* GENERIC HANDLERS ======================================================================= */

        void loadInstructionHandler(E6502::CPU &cpu, const E6502::AddressingModes &addr_mode, E6502::Byte &reg);

        void invalidHandler();
    };

    static std::unordered_map<Instructions, InstructionHandler> handlersTable = {
        {LDA, InstructionHandler(&InstructionHandlers::LDAHandler)},
        {LDX, InstructionHandler(&InstructionHandlers::LDXHandler)},
        {LDY, InstructionHandler(&InstructionHandlers::LDYHandler)}};

};