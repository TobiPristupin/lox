# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/pristu/.local/lib/python3.6/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/pristu/.local/lib/python3.6/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pristu/Documents/lox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pristu/Documents/lox/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/jlox.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jlox.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jlox.dir/flags.make

CMakeFiles/jlox.dir/main.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/lox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jlox.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/main.cpp.o -c /home/pristu/Documents/lox/main.cpp

CMakeFiles/jlox.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/lox/main.cpp > CMakeFiles/jlox.dir/main.cpp.i

CMakeFiles/jlox.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/lox/main.cpp -o CMakeFiles/jlox.dir/main.cpp.s

CMakeFiles/jlox.dir/Runner.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/Runner.cpp.o: ../Runner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/lox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/jlox.dir/Runner.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/Runner.cpp.o -c /home/pristu/Documents/lox/Runner.cpp

CMakeFiles/jlox.dir/Runner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/Runner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/lox/Runner.cpp > CMakeFiles/jlox.dir/Runner.cpp.i

CMakeFiles/jlox.dir/Runner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/Runner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/lox/Runner.cpp -o CMakeFiles/jlox.dir/Runner.cpp.s

CMakeFiles/jlox.dir/Scanner.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/Scanner.cpp.o: ../Scanner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/lox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/jlox.dir/Scanner.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/Scanner.cpp.o -c /home/pristu/Documents/lox/Scanner.cpp

CMakeFiles/jlox.dir/Scanner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/Scanner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/lox/Scanner.cpp > CMakeFiles/jlox.dir/Scanner.cpp.i

CMakeFiles/jlox.dir/Scanner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/Scanner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/lox/Scanner.cpp -o CMakeFiles/jlox.dir/Scanner.cpp.s

CMakeFiles/jlox.dir/TokenType.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/TokenType.cpp.o: ../TokenType.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/lox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/jlox.dir/TokenType.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/TokenType.cpp.o -c /home/pristu/Documents/lox/TokenType.cpp

CMakeFiles/jlox.dir/TokenType.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/TokenType.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/lox/TokenType.cpp > CMakeFiles/jlox.dir/TokenType.cpp.i

CMakeFiles/jlox.dir/TokenType.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/TokenType.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/lox/TokenType.cpp -o CMakeFiles/jlox.dir/TokenType.cpp.s

CMakeFiles/jlox.dir/LoxException.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/LoxException.cpp.o: ../LoxException.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/lox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/jlox.dir/LoxException.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/LoxException.cpp.o -c /home/pristu/Documents/lox/LoxException.cpp

CMakeFiles/jlox.dir/LoxException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/LoxException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/lox/LoxException.cpp > CMakeFiles/jlox.dir/LoxException.cpp.i

CMakeFiles/jlox.dir/LoxException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/LoxException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/lox/LoxException.cpp -o CMakeFiles/jlox.dir/LoxException.cpp.s

CMakeFiles/jlox.dir/Parser.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/Parser.cpp.o: ../Parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/lox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/jlox.dir/Parser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/Parser.cpp.o -c /home/pristu/Documents/lox/Parser.cpp

CMakeFiles/jlox.dir/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/Parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/lox/Parser.cpp > CMakeFiles/jlox.dir/Parser.cpp.i

CMakeFiles/jlox.dir/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/Parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/lox/Parser.cpp -o CMakeFiles/jlox.dir/Parser.cpp.s

CMakeFiles/jlox.dir/tools/AstPrinter.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/tools/AstPrinter.cpp.o: ../tools/AstPrinter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/lox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/jlox.dir/tools/AstPrinter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/tools/AstPrinter.cpp.o -c /home/pristu/Documents/lox/tools/AstPrinter.cpp

CMakeFiles/jlox.dir/tools/AstPrinter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/tools/AstPrinter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/lox/tools/AstPrinter.cpp > CMakeFiles/jlox.dir/tools/AstPrinter.cpp.i

CMakeFiles/jlox.dir/tools/AstPrinter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/tools/AstPrinter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/lox/tools/AstPrinter.cpp -o CMakeFiles/jlox.dir/tools/AstPrinter.cpp.s

CMakeFiles/jlox.dir/FileReader.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/FileReader.cpp.o: ../FileReader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/lox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/jlox.dir/FileReader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/FileReader.cpp.o -c /home/pristu/Documents/lox/FileReader.cpp

CMakeFiles/jlox.dir/FileReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/FileReader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/lox/FileReader.cpp > CMakeFiles/jlox.dir/FileReader.cpp.i

CMakeFiles/jlox.dir/FileReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/FileReader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/lox/FileReader.cpp -o CMakeFiles/jlox.dir/FileReader.cpp.s

CMakeFiles/jlox.dir/tests/ScannerTest.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/tests/ScannerTest.cpp.o: ../tests/ScannerTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/lox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/jlox.dir/tests/ScannerTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/tests/ScannerTest.cpp.o -c /home/pristu/Documents/lox/tests/ScannerTest.cpp

CMakeFiles/jlox.dir/tests/ScannerTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/tests/ScannerTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/lox/tests/ScannerTest.cpp > CMakeFiles/jlox.dir/tests/ScannerTest.cpp.i

CMakeFiles/jlox.dir/tests/ScannerTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/tests/ScannerTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/lox/tests/ScannerTest.cpp -o CMakeFiles/jlox.dir/tests/ScannerTest.cpp.s

# Object files for target jlox
jlox_OBJECTS = \
"CMakeFiles/jlox.dir/main.cpp.o" \
"CMakeFiles/jlox.dir/Runner.cpp.o" \
"CMakeFiles/jlox.dir/Scanner.cpp.o" \
"CMakeFiles/jlox.dir/TokenType.cpp.o" \
"CMakeFiles/jlox.dir/LoxException.cpp.o" \
"CMakeFiles/jlox.dir/Parser.cpp.o" \
"CMakeFiles/jlox.dir/tools/AstPrinter.cpp.o" \
"CMakeFiles/jlox.dir/FileReader.cpp.o" \
"CMakeFiles/jlox.dir/tests/ScannerTest.cpp.o"

# External object files for target jlox
jlox_EXTERNAL_OBJECTS =

jlox: CMakeFiles/jlox.dir/main.cpp.o
jlox: CMakeFiles/jlox.dir/Runner.cpp.o
jlox: CMakeFiles/jlox.dir/Scanner.cpp.o
jlox: CMakeFiles/jlox.dir/TokenType.cpp.o
jlox: CMakeFiles/jlox.dir/LoxException.cpp.o
jlox: CMakeFiles/jlox.dir/Parser.cpp.o
jlox: CMakeFiles/jlox.dir/tools/AstPrinter.cpp.o
jlox: CMakeFiles/jlox.dir/FileReader.cpp.o
jlox: CMakeFiles/jlox.dir/tests/ScannerTest.cpp.o
jlox: CMakeFiles/jlox.dir/build.make
jlox: lib/libgtestd.a
jlox: lib/libgtest_maind.a
jlox: lib/libgtestd.a
jlox: CMakeFiles/jlox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pristu/Documents/lox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable jlox"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jlox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jlox.dir/build: jlox

.PHONY : CMakeFiles/jlox.dir/build

CMakeFiles/jlox.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jlox.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jlox.dir/clean

CMakeFiles/jlox.dir/depend:
	cd /home/pristu/Documents/lox/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pristu/Documents/lox /home/pristu/Documents/lox /home/pristu/Documents/lox/cmake-build-debug /home/pristu/Documents/lox/cmake-build-debug /home/pristu/Documents/lox/cmake-build-debug/CMakeFiles/jlox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jlox.dir/depend

