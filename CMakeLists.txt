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
        include(cmake/CreateInstaller.cmake)
    endif ()
endif ()

if (ENABLE_BROWSER_LIBRARY)
    add_subdirectory("./modules/gbemu-bindings")
endif ()


