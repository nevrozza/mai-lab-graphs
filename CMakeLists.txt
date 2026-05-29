cmake_minimum_required(VERSION 4.1)
project(graphs C)

set(CMAKE_C_STANDARD 17)

add_executable(graphs main.c
        utils/utils.c
        utils/utils.h
        solve/solve.c
        solve/solve.h
        cli/cli.c
        cli/cli.h)
