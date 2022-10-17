cmake_minimum_required(VERSION 3.23)
project(IAL C)

set(CMAKE_C_STANDARD 11)

include_directories(c206)

add_executable(IAL
        c206/c206-test-utils.c
        c206/c206-test-utils.h
        c206/c206-test.c
        c206/c206.c
        c206/c206.h
        )
