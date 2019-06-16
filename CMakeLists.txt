cmake_minimum_required(VERSION 3.14)

project(meet)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDES ${PROJECT_SOURCE_DIR}/src/*.h*)

add_executable(meet ${INCLUDES} ${SOURCES})
