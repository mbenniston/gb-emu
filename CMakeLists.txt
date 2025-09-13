cmake_minimum_required(VERSION 3.10)

project(gb-emu)

set(CMAKE_CXX_CLANG_TIDY clang-tidy)
set(CMAKE_C_CLANG_TIDY clang-tidy)

add_subdirectory("./modules/gbemu")

add_library(gbemu-web
        gbemuweb/bindings.cpp
        gbemuweb/bindings_glue.cpp
)

set_property(TARGET gbemu-web PROPERTY C_STANDARD 11)
set_property(TARGET gbemu-web PROPERTY CXX_STANDARD 20)

target_link_libraries(gbemu-web PRIVATE gbemu)
