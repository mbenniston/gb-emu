cmake_minimum_required(VERSION 3.10)

add_library(gbemu
        cpu.c
        instructions/instructions.c
        bus.c
        registers.c
        emulator.c
        interrupt_controller.c
        timer_controller.c
        lcd.c
        ppu.c
        joypad.c
        cartridge.c
        mbc.c
        mbcs/rom_only.c
        mbcs/mbc3.c
        mbcs/mbc3_ram_battery.c)

target_include_directories(gbemu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET gbemu PROPERTY C_STANDARD 11)

if (ENABLE_TESTS)
    add_subdirectory(tests)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_sanitizers(gbemu)
endif ()