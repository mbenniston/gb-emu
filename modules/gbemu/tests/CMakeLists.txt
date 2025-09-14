cmake_minimum_required(VERSION 3.10)

add_executable(blarggs
        integration/blarggs.c
)

target_link_libraries(blarggs PRIVATE
        gbemu
        unity
)

add_test(blarggs_test blarggs)
