cmake_minimum_required(VERSION 3.10)

project(gb-emu)

option(ENABLE_NATIVE_BUILD "Build the native version of gbemu" OFF)
option(ENABLE_INSTALLER "Build the installer for the native version of gbemu" OFF)
option(ENABLE_BROWSER_LIBRARY "Build the browser version of gbemu" ON)

set(CMAKE_CXX_CLANG_TIDY clang-tidy)
set(CMAKE_C_CLANG_TIDY clang-tidy)

add_subdirectory("./modules/gbemu")

if (ENABLE_NATIVE_BUILD)
add_subdirectory("./applications/gbemu-native")
    if (ENABLE_INSTALLER)
        # include(cmake/CreateInstaller.cmake)
    endif ()
endif ()

if (ENABLE_BROWSER_LIBRARY)
        add_library(gbemu-web
                gbemuweb/bindings.cpp
                gbemuweb/bindings_glue.cpp
        )

        set_property(TARGET gbemu-web PROPERTY C_STANDARD 11)
        set_property(TARGET gbemu-web PROPERTY CXX_STANDARD 20)

        target_link_libraries(gbemu-web PRIVATE gbemu)
endif ()


