cmake_minimum_required(VERSION 3.22)
project(tinydb)

set(CMAKE_CXX_STANDARD 23)


add_executable(tinydb main.cpp db.h student.h query.h parsing.h utils.h db.cpp parsing.cpp query.cpp student.cpp utils.cpp)



