#pragma once

#include <cstdint>

namespace E6502
{
    using Byte = u_int8_t;   // 0 - 255
    using Word = u_int16_t;  // 0 - 65.535
    using DWord = u_int32_t; // 0 - 4.294.967.295

    static constexpr DWord MAX_MEM_SIZE = 1024 * 64;
}
