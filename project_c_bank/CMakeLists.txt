cmake_minimum_required(VERSION 3.30)
project(project_c_bank C)

set(CMAKE_C_STANDARD 11)

add_executable(project_c_bank main.c
        include/function.h
        src/funtion.c
        include/datatype.h)
