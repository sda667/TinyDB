cmake_minimum_required(VERSION 3.22)
project(tinydb)

set(CMAKE_CXX_STANDARD 23)

add_executable(tinydb main.cpp db.c db.h student.c student.h query.c query.h parsing.c parsing.h utils.c utils.h)



