cmake_minimum_required(VERSION 3.13)

include(../pico_sdk_init.cmake)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
project(examples C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

pico_sdk_init()

if (NOT CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS)
    find_program(CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS
            NAMES clang-scan-deps clang-scan-deps-21 clang-scan-deps-20
            PATHS ${PICO_TOOLCHAIN_PATH}/bin /usr/bin)
endif()

add_executable(led_blink
        led_blink_raw.cpp
)

target_compile_features(led_blink PRIVATE cxx_std_20)
target_link_libraries(led_blink pico_runtime)
pico_set_printf_implementation(led_blink none)
if (PICO_CLIB STREQUAL "llvm_libc")
    # libdummyhost provides stdio symbols for llvm-libc runtimes.
    target_link_options(led_blink PRIVATE -ldummyhost)
endif()

target_sources(led_blink PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}/sdk
        FILES sdk/hw/hw.cppm
)

pico_add_extra_outputs(led_blink)
