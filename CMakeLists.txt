cmake_minimum_required(VERSION 3.15)
project(jlox)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_subdirectory(lib/GSL-master)
include_directories(lib/GSL-master/include)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(jlox main.cpp Runner.cpp Runner.h TokenType.h Token.h Scanner.cpp Scanner.h TokenType.cpp LoxError.cpp LoxError.h Expr.cpp Expr.h Parser.cpp Parser.h tools/AstPrinter.cpp tools/AstPrinter.h FileReader.cpp FileReader.h tests/ScannerTest.cpp tests/ParserTest.cpp Token.cpp Interpreter.h Interpreter.cpp tests/InterpreterTest.cpp Stmt.cpp Stmt.h Environment.cpp Environment.h LoxObject.cpp LoxObject.h)
target_link_libraries(jlox gtest gtest_main)
add_executable(test test.cpp)

#find_package(Microsoft.GSL CONFIG)
#target_link_libraries(jlox Microsoft.GSL::GSL)
