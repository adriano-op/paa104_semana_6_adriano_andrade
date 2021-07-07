cmake_minimum_required(VERSION 3.19)
project(semana6)

set(CMAKE_CXX_STANDARD 14)

add_executable(semana6 main.cpp)

add_subdirectory (matplotplusplus)

target_link_libraries (semana6 PUBLIC matplot)
