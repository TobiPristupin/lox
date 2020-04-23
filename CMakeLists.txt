cmake_minimum_required(VERSION 3.15)
project(jlox)

set(CMAKE_CXX_STANDARD 17)

add_executable(jlox main.cpp Runner.cpp Runner.h TokenType.h Token.h Scanner.cpp Scanner.h TokenType.cpp LoxException.cpp LoxException.h)