cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_BOARD pico2_w CACHE STRING "Pico board")
set(PICO_PLATFORM rp2350-arm-s CACHE STRING "Pico platform")
set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/pico-sdk")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(pico_sdk_import.cmake)

project(aion-zero-fmw C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# ─────────────────────────────────────────────
# Waveshare LCD library
# ─────────────────────────────────────────────

add_library(waveshare_config
        lib/waveshare-lcd/Config/DEV_Config.c
)

target_include_directories(waveshare_config PUBLIC
        lib/waveshare-lcd/Config
)

target_link_libraries(waveshare_config PUBLIC
        pico_stdlib
        hardware_spi
        hardware_i2c
        hardware_pwm
)


add_library(waveshare_lcd
        lib/waveshare-lcd/LCD/LCD_1in44.c
)

target_include_directories(waveshare_lcd PUBLIC
        lib/waveshare-lcd/LCD
        lib/waveshare-lcd/Config
)

target_link_libraries(waveshare_lcd PUBLIC
        waveshare_config
)


add_library(waveshare_gui
        lib/waveshare-lcd/GUI/GUI_Paint.c
)

target_include_directories(waveshare_gui PUBLIC
        lib/waveshare-lcd/GUI
        lib/waveshare-lcd/Fonts
        lib/waveshare-lcd/Config
        lib/waveshare-lcd/LCD
)

target_link_libraries(waveshare_gui PUBLIC
        waveshare_config
        waveshare_lcd
)


add_library(waveshare_fonts
        lib/waveshare-lcd/Fonts/font8.c
        lib/waveshare-lcd/Fonts/font12.c
        lib/waveshare-lcd/Fonts/font16.c
        lib/waveshare-lcd/Fonts/font20.c
        lib/waveshare-lcd/Fonts/font24.c
        lib/waveshare-lcd/Fonts/font12CN.c
        lib/waveshare-lcd/Fonts/font24CN.c
)

target_include_directories(waveshare_fonts PUBLIC
        lib/waveshare-lcd/Fonts
)


# ─────────────────────────────────────────────
# App
# ─────────────────────────────────────────────

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        src/*.hpp
)

add_executable(aion-zero-fmw
        ${SOURCES}
        src/application/application.hpp
        src/application/application.cpp
        src/application/main_menu/main_menu.hpp
        src/application/main_menu/main_menu.cpp
        src/engine/input.hpp
        src/engine/input.cpp
)

target_link_libraries(aion-zero-fmw
        pico_stdlib
        pico_cyw43_arch_none
        hardware_spi

        waveshare_config
        waveshare_lcd
        waveshare_gui
        waveshare_fonts
)

target_include_directories(aion-zero-fmw PRIVATE
        lib/waveshare-lcd/Config
        lib/waveshare-lcd/LCD
        lib/waveshare-lcd/GUI
        lib/waveshare-lcd/Fonts
)


# ─────────────────────────────────────────────
# Pico output
# ─────────────────────────────────────────────

pico_enable_stdio_usb(aion-zero-fmw 1)
pico_enable_stdio_uart(aion-zero-fmw 0)

pico_add_extra_outputs(aion-zero-fmw)
