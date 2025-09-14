cmake_minimum_required(VERSION 3.10)
add_library(unity src/unity.c)
target_include_directories(unity PUBLIC src)
