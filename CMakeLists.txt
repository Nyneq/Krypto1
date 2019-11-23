cmake_minimum_required(VERSION 3.14)

project(krypto1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp functions.h functions.cpp tests.cpp)

add_executable(krypto1 ${SOURCE_FILES})