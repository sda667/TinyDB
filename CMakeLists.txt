cmake_minimum_required(VERSION 3.22)
project(tinydb)

set(CMAKE_CXX_STANDARD 23)

add_executable(tinydb main.cpp db.cpp db.h student.cpp student.h query.cpp query.h parsing.cpp parsing.h utils.cpp utils.h)



