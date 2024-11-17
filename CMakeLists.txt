cmake_minimum_required(VERSION 3.16)
project(e6502 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(e6502 src/main.cpp)
add_subdirectory(src)

target_compile_features(e6502 PRIVATE cxx_std_17)

target_include_directories(e6502 PRIVATE include)

target_precompile_headers(e6502 PRIVATE include/stdafx.h)

install(TARGETS e6502)