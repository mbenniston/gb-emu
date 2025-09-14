cmake_minimum_required(VERSION 3.10)

add_library(gbemu-bindings
        bindings.cpp
        bindings_glue.cpp
)

set_property(TARGET gbemu-bindings PROPERTY C_STANDARD 11)
set_property(TARGET gbemu-bindings PROPERTY CXX_STANDARD 20)

target_link_libraries(gbemu-bindings PRIVATE gbemu)