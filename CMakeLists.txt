cmake_minimum_required(VERSION 3.25)
project(AgenC C)

set(CMAKE_C_STANDARD 11)

add_executable(AgenC
        Main.c "cell.c" "cell.h" "cell.h" "cell.h" list.c list.h cell.h cell.h cell.h)
