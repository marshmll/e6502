#pragma once

#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN || \
    defined(__BIG_ENDIAN__) ||                               \
    defined(__ARMEB__) ||                                    \
    defined(__THUMBEB__) ||                                  \
    defined(__AARCH64EB__) ||                                \
    defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
#define LITTLE_ENDIAN_PLATFORM 0
#define BIG_ENDIAN_PLATFORM 1
#elif defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN || \
    defined(__LITTLE_ENDIAN__) ||                                 \
    defined(__ARMEL__) ||                                         \
    defined(__THUMBEL__) ||                                       \
    defined(__AARCH64EL__) ||                                     \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
#define LITTLE_ENDIAN_PLATFORM 1
#define BIG_ENDIAN_PLATFORM 0
#else
#error "I have no idea of what platform is this!"
#endif

#define IS_BIG_ENDIAN_PLATFORM BIG_ENDIAN_PLATFORM