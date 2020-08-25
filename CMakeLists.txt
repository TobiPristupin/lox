cmake_minimum_required(VERSION 3.15)
project(jlox)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-E")

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_subdirectory(lib/GSL-master)
include_directories(lib/GSL-master/include)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(jlox main.cpp Runner.cpp Runner.h TokenType.h Token.h Scanner.cpp Scanner.h TokenType.cpp LoxError.cpp LoxError.h Expr.cpp Expr.h Parser.cpp Parser.h FileReader.cpp FileReader.h tests/ScannerTest.cpp tests/ParserTest.cpp Token.cpp Interpreter.h Interpreter.cpp tests/InterpreterTest.cpp Stmt.cpp Stmt.h Environment.cpp Environment.h LoxObject.cpp LoxObject.h tools/Utils.cpp tools/Utils.h LoxCallable.h standardlib/StandardFunctions.h standardlib/StandardFunctions.cpp LoxFunctionWrapper.cpp LoxFunctionWrapper.h typedefs.h Resolver.cpp Resolver.h LoxClass.cpp LoxClass.h)
target_link_libraries(jlox gtest gtest_main)
add_executable(test test.cpp)

find_program(iwyu_path NAMES include-what-you-use iwyu)
if(NOT iwyu_path)
    message(FATAL_ERROR "Could not find the program include-what-you-use")
endif()

set_property(TARGET jlox PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})