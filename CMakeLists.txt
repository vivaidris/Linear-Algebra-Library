cmake_minimum_required(VERSION 3.10)

project(LinearAlgebra_Lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES main.cpp)

add_executable(LinearAlgebra_Lib ${SOURCES})

target_include_directories(LinearAlgebra_Lib PRIVATE dependencies)