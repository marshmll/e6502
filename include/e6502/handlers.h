#pragma once

#include "e6502/cpu.h"
#include "e6502/decode.h"

namespace E6502
{
    using OperandPair = std::pair<E6502::Word, E6502::Byte>;
    using InstructionHandler = std::function<void(CPU &, const AddressingModes &)>;

    namespace InstructionHandlers
    {
        /* INSTRUCTION SPECIFIC HANDLERS ========================================================== */

        void ADCHandler(CPU &cpu, const AddressingModes &addr_mode);

        void ANDHandler(CPU &cpu, const AddressingModes &addr_mode);

        void ASLHandler(CPU &cpu, const AddressingModes &addr_mode);

        void BCCHandler(CPU &cpu, const AddressingModes &addr_mode);

        void BCSHandler(CPU &cpu, const AddressingModes &addr_mode);

        void BEQHandler(CPU &cpu, const AddressingModes &addr_mode);

        void BITHandler(CPU &cpu, const AddressingModes &addr_mode);

        void BMIHandler(CPU &cpu, const AddressingModes &addr_mode);

        void BNEHandler(CPU &cpu, const AddressingModes &addr_mode);

        void BPLHandler(CPU &cpu, const AddressingModes &addr_mode);

        void BRKHandler(CPU &cpu, const AddressingModes &addr_mode);

        void BVCHandler(CPU &cpu, const AddressingModes &addr_mode);

        void BVSHandler(CPU &cpu, const AddressingModes &addr_mode);

        void CLCHandler(CPU &cpu, const AddressingModes &addr_mode);

        void CLDHandler(CPU &cpu, const AddressingModes &addr_mode);

        void CLIHandler(CPU &cpu, const AddressingModes &addr_mode);

        void CLVHandler(CPU &cpu, const AddressingModes &addr_mode);

        void CMPHandler(CPU &cpu, const AddressingModes &addr_mode);

        void CPXHandler(CPU &cpu, const AddressingModes &addr_mode);

        void CPYHandler(CPU &cpu, const AddressingModes &addr_mode);

        void DECHandler(CPU &cpu, const AddressingModes &addr_mode);

        void DEXHandler(CPU &cpu, const AddressingModes &addr_mode);

        void DEYHandler(CPU &cpu, const AddressingModes &addr_mode);

        void EORHandler(CPU &cpu, const AddressingModes &addr_mode);

        void INCHandler(CPU &cpu, const AddressingModes &addr_mode);

        void INXHandler(CPU &cpu, const AddressingModes &addr_mode);

        void INYHandler(CPU &cpu, const AddressingModes &addr_mode);

        void JMPHandler(CPU &cpu, const AddressingModes &addr_mode);

        void JSRHandler(CPU &cpu, const AddressingModes &addr_mode);

        void LDAHandler(CPU &cpu, const AddressingModes &addr_mode);

        void LDXHandler(CPU &cpu, const AddressingModes &addr_mode);

        void LDYHandler(CPU &cpu, const AddressingModes &addr_mode);

        void LSRHandler(CPU &cpu, const AddressingModes &addr_mode);

        void NOPHandler(CPU &cpu, const AddressingModes &addr_mode);

        void ORAHandler(CPU &cpu, const AddressingModes &addr_mode);

        void PHAHandler(CPU &cpu, const AddressingModes &addr_mode);

        void PHPHandler(CPU &cpu, const AddressingModes &addr_mode);

        void PLAHandler(CPU &cpu, const AddressingModes &addr_mode);

        void PLPHandler(CPU &cpu, const AddressingModes &addr_mode);

        void ROLHandler(CPU &cpu, const AddressingModes &addr_mode);

        void RORHandler(CPU &cpu, const AddressingModes &addr_mode);

        void RTIHandler(CPU &cpu, const AddressingModes &addr_mode);

        void RTSHandler(CPU &cpu, const AddressingModes &addr_mode);

        void SBCHandler(CPU &cpu, const AddressingModes &addr_mode);

        void SECHandler(CPU &cpu, const AddressingModes &addr_mode);

        void SEDHandler(CPU &cpu, const AddressingModes &addr_mode);

        void SEIHandler(CPU &cpu, const AddressingModes &addr_mode);

        void STAHandler(CPU &cpu, const AddressingModes &addr_mode);

        void STXHandler(CPU &cpu, const AddressingModes &addr_mode);

        void STYHandler(CPU &cpu, const AddressingModes &addr_mode);

        void TAXHandler(CPU &cpu, const AddressingModes &addr_mode);

        void TAYHandler(CPU &cpu, const AddressingModes &addr_mode);

        void TSXHandler(CPU &cpu, const AddressingModes &addr_mode);

        void TXAHandler(CPU &cpu, const AddressingModes &addr_mode);

        void TXSHandler(CPU &cpu, const AddressingModes &addr_mode);

        void TYAHandler(CPU &cpu, const AddressingModes &addr_mode);

        /* GENERIC HANDLERS ======================================================================= */

        const OperandPair getOperand(CPU &cpu, const AddressingModes &addr_mode);

        const OperandPair getOperandWithoutPageCrossingCycle(CPU &cpu, const AddressingModes &addr_mode);

        const Word getEffectiveAddress(CPU &cpu, const AddressingModes &addr_mode);

        void branchHandler(CPU &cpu, const AddressingModes &addr_mode);
    };

    static std::unordered_map<Instructions, InstructionHandler> handlersTable = {
        {ADC, InstructionHandler(&InstructionHandlers::ADCHandler)},
        {AND, InstructionHandler(&InstructionHandlers::ANDHandler)},
        {ASL, InstructionHandler(&InstructionHandlers::ASLHandler)},
        {BCC, InstructionHandler(&InstructionHandlers::BCCHandler)},
        {BCS, InstructionHandler(&InstructionHandlers::BCSHandler)},
        {BEQ, InstructionHandler(&InstructionHandlers::BEQHandler)},
        {BIT, InstructionHandler(&InstructionHandlers::BITHandler)},
        {BMI, InstructionHandler(&InstructionHandlers::BMIHandler)},
        {BNE, InstructionHandler(&InstructionHandlers::BNEHandler)},
        {BPL, InstructionHandler(&InstructionHandlers::BPLHandler)},
        {BRK, InstructionHandler(&InstructionHandlers::BRKHandler)},
        {BVC, InstructionHandler(&InstructionHandlers::BVCHandler)},
        {BVS, InstructionHandler(&InstructionHandlers::BVSHandler)},
        {CLC, InstructionHandler(&InstructionHandlers::CLCHandler)},
        {CLD, InstructionHandler(&InstructionHandlers::CLDHandler)},
        {CLI, InstructionHandler(&InstructionHandlers::CLIHandler)},
        {CLV, InstructionHandler(&InstructionHandlers::CLVHandler)},
        {CMP, InstructionHandler(&InstructionHandlers::CMPHandler)},
        {CPX, InstructionHandler(&InstructionHandlers::CPXHandler)},
        {CPY, InstructionHandler(&InstructionHandlers::CPYHandler)},
        {DEC, InstructionHandler(&InstructionHandlers::DECHandler)},
        {DEX, InstructionHandler(&InstructionHandlers::DEXHandler)},
        {DEY, InstructionHandler(&InstructionHandlers::DEYHandler)},
        {EOR, InstructionHandler(&InstructionHandlers::EORHandler)},
        {INC, InstructionHandler(&InstructionHandlers::INCHandler)},
        {INX, InstructionHandler(&InstructionHandlers::INXHandler)},
        {INY, InstructionHandler(&InstructionHandlers::INYHandler)},
        {JMP, InstructionHandler(&InstructionHandlers::JMPHandler)},
        {JSR, InstructionHandler(&InstructionHandlers::JSRHandler)},
        {LDA, InstructionHandler(&InstructionHandlers::LDAHandler)},
        {LDX, InstructionHandler(&InstructionHandlers::LDXHandler)},
        {LDY, InstructionHandler(&InstructionHandlers::LDYHandler)},
        {LSR, InstructionHandler(&InstructionHandlers::LSRHandler)},
        {NOP, InstructionHandler(&InstructionHandlers::NOPHandler)},
        {ORA, InstructionHandler(&InstructionHandlers::ORAHandler)},
        {PHA, InstructionHandler(&InstructionHandlers::PHAHandler)},
        {PHP, InstructionHandler(&InstructionHandlers::PHPHandler)},
        {PLP, InstructionHandler(&InstructionHandlers::PLPHandler)},
        {PLA, InstructionHandler(&InstructionHandlers::PLAHandler)},
        {ROL, InstructionHandler(&InstructionHandlers::ROLHandler)},
        {ROR, InstructionHandler(&InstructionHandlers::RORHandler)},
        {RTI, InstructionHandler(&InstructionHandlers::RTIHandler)},
        {RTS, InstructionHandler(&InstructionHandlers::RTSHandler)},
        {SBC, InstructionHandler(&InstructionHandlers::SBCHandler)},
        {SEC, InstructionHandler(&InstructionHandlers::SECHandler)},
        {SED, InstructionHandler(&InstructionHandlers::SEDHandler)},
        {SEI, InstructionHandler(&InstructionHandlers::SEIHandler)},
        {STA, InstructionHandler(&InstructionHandlers::STAHandler)},
        {STX, InstructionHandler(&InstructionHandlers::STXHandler)},
        {STY, InstructionHandler(&InstructionHandlers::STYHandler)},
        {TAX, InstructionHandler(&InstructionHandlers::TAXHandler)},
        {TAY, InstructionHandler(&InstructionHandlers::TAYHandler)},
        {TSX, InstructionHandler(&InstructionHandlers::TSXHandler)},
        {TXA, InstructionHandler(&InstructionHandlers::TXAHandler)},
        {TXS, InstructionHandler(&InstructionHandlers::TXSHandler)},
        {TYA, InstructionHandler(&InstructionHandlers::TYAHandler)},        
    };

};