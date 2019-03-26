cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Sortowanie)

if(MSVC)
    add_compile_options(/W4 /O2 /MT)
endif()
if(GNU)
    add_compile_options(-Wall -Wextra -O3)
endif()
add_executable(test main.cpp)