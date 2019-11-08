# cmake_minimum_required(VERSION <specify CMake version here>)
project(cmsc403a4 C)

set(CMAKE_C_STANDARD 99)

add_executable(cmsc403a4 Parser.c Analyzer.c Givens.c Tokenizer.c Parser.h Tokenizer.h)