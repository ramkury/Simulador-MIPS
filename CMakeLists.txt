cmake_minimum_required(VERSION 3.2)
project(Simulador_MIPS)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp include/isa.h src/isa.cpp src/control.cpp include/control.h)
set(TESTS tests/catch.h tests/memory_access_tests.cpp tests/fdx_tests.cpp)
add_executable(Simulador_MIPS ${SOURCE_FILES})