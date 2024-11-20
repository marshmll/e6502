#pragma once

#include "e6502/cpu.h"
#include "e6502/decode.h"
#include "e6502/handlers.h"

namespace E6502
{
    class CPU;
    void handleInstruction(const E6502::Byte &opcode, E6502::CPU &cpu);
}