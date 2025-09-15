cmake_minimum_required(VERSION 3.10)
find_package(SDL3 REQUIRED)

add_executable(gbemu-native main.c)
target_link_libraries(gbemu-native PRIVATE ${SDL3_LIBRARIES} gbemu)
