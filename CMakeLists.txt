cmake_minimum_required(VERSION 3.23)
project(IAL C)

set(CMAKE_C_STANDARD 11)

include_directories(c201)

add_executable(IAL
        c201/c201-test-utils.c
        c201/c201-test-utils.h
        c201/c201-test.c
        c201/c201.c
        c201/c201.h)
