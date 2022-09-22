cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_overclock C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_COPY_TO_RAM 1)
pico_sdk_init()

add_executable(pico_overclock
  pico_overclock.c
)

target_link_libraries(pico_overclock pico_stdlib pico_mem_ops)

pico_add_extra_outputs(pico_overclock)
