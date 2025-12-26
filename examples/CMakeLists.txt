cmake_minimum_required(VERSION 3.30)

include(../pico_sdk_init.cmake)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)

project(examples C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

pico_sdk_init()

if (DEFINED PICO_COMPILER_SYSROOT)
    set(LIBCXX_STD_MODULE_DIR "${PICO_COMPILER_SYSROOT}/share/libc++/v1")
    set(LIBCXX_STD_MODULE "${LIBCXX_STD_MODULE_DIR}/std.cppm")
else()
    message(FATAL_ERROR "PICO_COMPILER_SYSROOT is not set; cannot locate libc++ std module")
endif()

if (NOT CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS)
    find_program(CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS
            NAMES clang-scan-deps clang-scan-deps-21 clang-scan-deps-20
            PATHS ${PICO_TOOLCHAIN_PATH}/bin /usr/bin)
endif()

add_executable(led_blink
        led_blink_raw.cpp
)
target_compile_features(led_blink PRIVATE cxx_std_26)
target_compile_options(led_blink PRIVATE
  $<$<COMPILE_LANG_AND_ID:C,Clang,AppleClang>:-Weverything -Wno-c++98-compat>
  $<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:-Weverything -Wno-c++98-compat>
)
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

if (EXISTS "${LIBCXX_STD_MODULE}")
    target_sources(led_blink PRIVATE
            FILE_SET libcxx_modules TYPE CXX_MODULES
            BASE_DIRS "${LIBCXX_STD_MODULE_DIR}"
            FILES "${LIBCXX_STD_MODULE}"
    )
else()
    message(FATAL_ERROR "libc++ std module not found at ${LIBCXX_STD_MODULE}; import std will fail")
endif()

pico_add_extra_outputs(led_blink)
