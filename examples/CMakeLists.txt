cmake_minimum_required(VERSION 3.13)

include(../pico_sdk_init.cmake)

project(examples C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

pico_sdk_init()

add_executable(led_blink_raw
        led_blink_raw.cpp
)

target_link_libraries(led_blink_raw pico_runtime)

pico_add_extra_outputs(led_blink_raw)
