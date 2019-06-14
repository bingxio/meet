cmake_minimum_required(VERSION 3.14)

project(Meet)

set(CMAKE_CXX_STANDARD 17)

add_executable(Meet src/Meet.cpp src/Token.cpp src/Lexer.cpp)
