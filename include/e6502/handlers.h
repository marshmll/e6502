#pragma once

#include "e6502/cpu.h"
#include "e6502/decode.h"

namespace E6502
{
    using InstructionHandler = std::function<void(CPU &, const AddressingModes &)>;

    namespace InstructionHandlers
    {
        /* INSTRUCTION SPECIFIC HANDLERS ========================================================== */

        void ADCHandler(CPU &cpu, const AddressingModes &addr_mode);

        void ANDHandler(CPU &cpu, const AddressingModes &addr_mode);

        void ASLHandler(CPU &cpu, const AddressingModes &addr_mode);

        void BCCHandler(CPU &cpu, const AddressingModes &addr_mode);

        void LDAHandler(CPU &cpu, const AddressingModes &addr_mode);

        void LDXHandler(CPU &cpu, const AddressingModes &addr_mode);

        void LDYHandler(CPU &cpu, const AddressingModes &addr_mode);

        void SBCHandler(CPU &cpu, const AddressingModes &addr_mode);

        /* GENERIC HANDLERS ======================================================================= */

        const Byte getOperand(CPU &cpu, const AddressingModes &addr_mode);

        const Byte performOperation(CPU &cpu, const AddressingModes &addr_mode, std::function<void(CPU &, const Byte &)> operation);

        void invalidHandler();
    };

    static std::unordered_map<Instructions, InstructionHandler> handlersTable = {
        {ADC, InstructionHandler(&InstructionHandlers::ADCHandler)},
        {AND, InstructionHandler(&InstructionHandlers::ANDHandler)},
        {ASL, InstructionHandler(&InstructionHandlers::ASLHandler)},
        {BCC, InstructionHandler(&InstructionHandlers::BCCHandler)},
        {LDA, InstructionHandler(&InstructionHandlers::LDAHandler)},
        {LDX, InstructionHandler(&InstructionHandlers::LDXHandler)},
        {LDY, InstructionHandler(&InstructionHandlers::LDYHandler)},
        {SBC, InstructionHandler(&InstructionHandlers::SBCHandler)},
    };

};