cmake_minimum_required(VERSION 3.10)

add_executable(gbemu-native main.c)
target_link_libraries(gbemu-native PRIVATE gbemu)
