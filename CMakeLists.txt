cmake_minimum_required(VERSION 3.23)
project(Cpp_Matrix)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
file(GLOB_RECURSE SOURCES "src/*.*")

add_executable(Cpp_Matrix main.cpp ${SOURCES})
