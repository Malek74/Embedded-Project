# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Malek\blink\build\_deps\picotool-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Malek\blink\build\_deps\picotool-build

# Include any dependencies generated for this target.
include bintool/CMakeFiles/bintool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include bintool/CMakeFiles/bintool.dir/compiler_depend.make

# Include the compile flags for this target's objects.
include bintool/CMakeFiles/bintool.dir/flags.make

bintool/CMakeFiles/bintool.dir/bintool.cpp.obj: bintool/CMakeFiles/bintool.dir/flags.make
bintool/CMakeFiles/bintool.dir/bintool.cpp.obj: bintool/CMakeFiles/bintool.dir/includes_CXX.rsp
bintool/CMakeFiles/bintool.dir/bintool.cpp.obj: C:/Malek/blink/build/_deps/picotool-src/bintool/bintool.cpp
bintool/CMakeFiles/bintool.dir/bintool.cpp.obj: bintool/CMakeFiles/bintool.dir/compiler_depend.ts
	cd /d C:\Malek\blink\build\_deps\picotool-build\bintool && C:\VSARM\mingw\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT bintool/CMakeFiles/bintool.dir/bintool.cpp.obj -MF CMakeFiles\bintool.dir\bintool.cpp.obj.d -o CMakeFiles\bintool.dir\bintool.cpp.obj -c C:\Malek\blink\build\_deps\picotool-src\bintool\bintool.cpp

bintool/CMakeFiles/bintool.dir/bintool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bintool.dir/bintool.cpp.i"
	cd /d C:\Malek\blink\build\_deps\picotool-build\bintool && C:\VSARM\mingw\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Malek\blink\build\_deps\picotool-src\bintool\bintool.cpp > CMakeFiles\bintool.dir\bintool.cpp.i

bintool/CMakeFiles/bintool.dir/bintool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bintool.dir/bintool.cpp.s"
	cd /d C:\Malek\blink\build\_deps\picotool-build\bintool && C:\VSARM\mingw\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Malek\blink\build\_deps\picotool-src\bintool\bintool.cpp -o CMakeFiles\bintool.dir\bintool.cpp.s

bintool/CMakeFiles/bintool.dir/mbedtls_wrapper.c.obj: bintool/CMakeFiles/bintool.dir/flags.make
bintool/CMakeFiles/bintool.dir/mbedtls_wrapper.c.obj: bintool/CMakeFiles/bintool.dir/includes_C.rsp
bintool/CMakeFiles/bintool.dir/mbedtls_wrapper.c.obj: C:/Malek/blink/build/_deps/picotool-src/bintool/mbedtls_wrapper.c
bintool/CMakeFiles/bintool.dir/mbedtls_wrapper.c.obj: bintool/CMakeFiles/bintool.dir/compiler_depend.ts
	cd /d C:\Malek\blink\build\_deps\picotool-build\bintool && C:\VSARM\mingw\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT bintool/CMakeFiles/bintool.dir/mbedtls_wrapper.c.obj -MF CMakeFiles\bintool.dir\mbedtls_wrapper.c.obj.d -o CMakeFiles\bintool.dir\mbedtls_wrapper.c.obj -c C:\Malek\blink\build\_deps\picotool-src\bintool\mbedtls_wrapper.c

bintool/CMakeFiles/bintool.dir/mbedtls_wrapper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bintool.dir/mbedtls_wrapper.c.i"
	cd /d C:\Malek\blink\build\_deps\picotool-build\bintool && C:\VSARM\mingw\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Malek\blink\build\_deps\picotool-src\bintool\mbedtls_wrapper.c > CMakeFiles\bintool.dir\mbedtls_wrapper.c.i

bintool/CMakeFiles/bintool.dir/mbedtls_wrapper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bintool.dir/mbedtls_wrapper.c.s"
	cd /d C:\Malek\blink\build\_deps\picotool-build\bintool && C:\VSARM\mingw\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Malek\blink\build\_deps\picotool-src\bintool\mbedtls_wrapper.c -o CMakeFiles\bintool.dir\mbedtls_wrapper.c.s

# Object files for target bintool
bintool_OBJECTS = \
"CMakeFiles/bintool.dir/bintool.cpp.obj" \
"CMakeFiles/bintool.dir/mbedtls_wrapper.c.obj"

# External object files for target bintool
bintool_EXTERNAL_OBJECTS =

bintool/libbintool.a: bintool/CMakeFiles/bintool.dir/bintool.cpp.obj
bintool/libbintool.a: bintool/CMakeFiles/bintool.dir/mbedtls_wrapper.c.obj
bintool/libbintool.a: bintool/CMakeFiles/bintool.dir/build.make
bintool/libbintool.a: bintool/CMakeFiles/bintool.dir/link.txt
	cd /d C:\Malek\blink\build\_deps\picotool-build\bintool && $(CMAKE_COMMAND) -P CMakeFiles\bintool.dir\cmake_clean_target.cmake
	cd /d C:\Malek\blink\build\_deps\picotool-build\bintool && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bintool.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bintool/CMakeFiles/bintool.dir/build: bintool/libbintool.a
.PHONY : bintool/CMakeFiles/bintool.dir/build

bintool/CMakeFiles/bintool.dir/clean:
	cd /d C:\Malek\blink\build\_deps\picotool-build\bintool && $(CMAKE_COMMAND) -P CMakeFiles\bintool.dir\cmake_clean.cmake
.PHONY : bintool/CMakeFiles/bintool.dir/clean

bintool/CMakeFiles/bintool.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Malek\blink\build\_deps\picotool-src C:\Malek\blink\build\_deps\picotool-src\bintool C:\Malek\blink\build\_deps\picotool-build C:\Malek\blink\build\_deps\picotool-build\bintool C:\Malek\blink\build\_deps\picotool-build\bintool\CMakeFiles\bintool.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : bintool/CMakeFiles/bintool.dir/depend

