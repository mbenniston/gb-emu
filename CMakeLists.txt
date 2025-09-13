cmake_minimum_required(VERSION 3.10)

project(gb-emu)

set(CMAKE_CXX_CLANG_TIDY clang-tidy)
set(CMAKE_C_CLANG_TIDY clang-tidy)

add_library(gbemu
        gbemu/cpu.c
        gbemu/instructions/instructions.c
        gbemu/bus.c
        gbemu/registers.c
        gbemu/emulator.c
        gbemu/interrupt_controller.c
        gbemu/timer_controller.c
        gbemu/lcd.c
        gbemu/ppu.c
        gbemu/joypad.c
        gbemu/cartridge.c
        gbemu/mbc.c
        gbemu/mbcs/rom_only.c
        gbemu/mbcs/mbc3.c
        gbemu/mbcs/mbc3_ram_battery.c)

add_library(gbemu-web
        gbemuweb/bindings.cpp
        gbemuweb/bindings_glue.cpp
)

set_property(TARGET gbemu PROPERTY C_STANDARD 11)
set_property(TARGET gbemu-web PROPERTY C_STANDARD 11)
set_property(TARGET gbemu-web PROPERTY CXX_STANDARD 20)

target_link_libraries(gbemu-web PRIVATE gbemu)
