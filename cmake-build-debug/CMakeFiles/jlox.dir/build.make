# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /snap/clion/111/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/111/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pristu/Documents/jlox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pristu/Documents/jlox/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/jlox.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jlox.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jlox.dir/flags.make

CMakeFiles/jlox.dir/main.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/jlox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jlox.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/main.cpp.o -c /home/pristu/Documents/jlox/main.cpp

CMakeFiles/jlox.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/jlox/main.cpp > CMakeFiles/jlox.dir/main.cpp.i

CMakeFiles/jlox.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/jlox/main.cpp -o CMakeFiles/jlox.dir/main.cpp.s

CMakeFiles/jlox.dir/Runner.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/Runner.cpp.o: ../Runner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/jlox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/jlox.dir/Runner.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/Runner.cpp.o -c /home/pristu/Documents/jlox/Runner.cpp

CMakeFiles/jlox.dir/Runner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/Runner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/jlox/Runner.cpp > CMakeFiles/jlox.dir/Runner.cpp.i

CMakeFiles/jlox.dir/Runner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/Runner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/jlox/Runner.cpp -o CMakeFiles/jlox.dir/Runner.cpp.s

CMakeFiles/jlox.dir/Scanner.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/Scanner.cpp.o: ../Scanner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/jlox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/jlox.dir/Scanner.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/Scanner.cpp.o -c /home/pristu/Documents/jlox/Scanner.cpp

CMakeFiles/jlox.dir/Scanner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/Scanner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/jlox/Scanner.cpp > CMakeFiles/jlox.dir/Scanner.cpp.i

CMakeFiles/jlox.dir/Scanner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/Scanner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/jlox/Scanner.cpp -o CMakeFiles/jlox.dir/Scanner.cpp.s

CMakeFiles/jlox.dir/TokenType.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/TokenType.cpp.o: ../TokenType.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/jlox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/jlox.dir/TokenType.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/TokenType.cpp.o -c /home/pristu/Documents/jlox/TokenType.cpp

CMakeFiles/jlox.dir/TokenType.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/TokenType.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/jlox/TokenType.cpp > CMakeFiles/jlox.dir/TokenType.cpp.i

CMakeFiles/jlox.dir/TokenType.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/TokenType.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/jlox/TokenType.cpp -o CMakeFiles/jlox.dir/TokenType.cpp.s

CMakeFiles/jlox.dir/LoxException.cpp.o: CMakeFiles/jlox.dir/flags.make
CMakeFiles/jlox.dir/LoxException.cpp.o: ../LoxException.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pristu/Documents/jlox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/jlox.dir/LoxException.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jlox.dir/LoxException.cpp.o -c /home/pristu/Documents/jlox/LoxException.cpp

CMakeFiles/jlox.dir/LoxException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlox.dir/LoxException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pristu/Documents/jlox/LoxException.cpp > CMakeFiles/jlox.dir/LoxException.cpp.i

CMakeFiles/jlox.dir/LoxException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlox.dir/LoxException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pristu/Documents/jlox/LoxException.cpp -o CMakeFiles/jlox.dir/LoxException.cpp.s

# Object files for target jlox
jlox_OBJECTS = \
"CMakeFiles/jlox.dir/main.cpp.o" \
"CMakeFiles/jlox.dir/Runner.cpp.o" \
"CMakeFiles/jlox.dir/Scanner.cpp.o" \
"CMakeFiles/jlox.dir/TokenType.cpp.o" \
"CMakeFiles/jlox.dir/LoxException.cpp.o"

# External object files for target jlox
jlox_EXTERNAL_OBJECTS =

jlox: CMakeFiles/jlox.dir/main.cpp.o
jlox: CMakeFiles/jlox.dir/Runner.cpp.o
jlox: CMakeFiles/jlox.dir/Scanner.cpp.o
jlox: CMakeFiles/jlox.dir/TokenType.cpp.o
jlox: CMakeFiles/jlox.dir/LoxException.cpp.o
jlox: CMakeFiles/jlox.dir/build.make
jlox: CMakeFiles/jlox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pristu/Documents/jlox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable jlox"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jlox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jlox.dir/build: jlox

.PHONY : CMakeFiles/jlox.dir/build

CMakeFiles/jlox.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jlox.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jlox.dir/clean

CMakeFiles/jlox.dir/depend:
	cd /home/pristu/Documents/jlox/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pristu/Documents/jlox /home/pristu/Documents/jlox /home/pristu/Documents/jlox/cmake-build-debug /home/pristu/Documents/jlox/cmake-build-debug /home/pristu/Documents/jlox/cmake-build-debug/CMakeFiles/jlox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jlox.dir/depend

