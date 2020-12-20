project(dwm C)
set(CMAKE_C_STANDARD 99)

cmake_minimum_required(VERSION 3.19)

add_executable(dwm config.h drw.h util.h drw.c dwm.c transient.c util.c)