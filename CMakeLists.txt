cmake_minimum_required(VERSION 3.25)

project(AgenC C)

set(CMAKE_C_STANDARD 11)

add_executable(AgenC Main.c cell.c cell.h list.c list.h menu.c menu.h timer.c timer.h contact.c contact.h appointment.c appointment.h file.c file.h)

target_link_libraries(AgenC m)