# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/batman/git/KvantEngine/engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/batman/git/KvantEngine/engine/build

# Include any dependencies generated for this target.
include CMakeFiles/KvantEngine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/KvantEngine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/KvantEngine.dir/flags.make

CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o: CMakeFiles/KvantEngine.dir/flags.make
CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o: ../src/Core/Engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o -c /home/batman/git/KvantEngine/engine/src/Core/Engine.cpp

CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/batman/git/KvantEngine/engine/src/Core/Engine.cpp > CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.i

CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/batman/git/KvantEngine/engine/src/Core/Engine.cpp -o CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.s

CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o.requires:

.PHONY : CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o.requires

CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o.provides: CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o.requires
	$(MAKE) -f CMakeFiles/KvantEngine.dir/build.make CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o.provides.build
.PHONY : CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o.provides

CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o.provides.build: CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o


CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o: CMakeFiles/KvantEngine.dir/flags.make
CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o: ../src/Core/Window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o -c /home/batman/git/KvantEngine/engine/src/Core/Window.cpp

CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/batman/git/KvantEngine/engine/src/Core/Window.cpp > CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.i

CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/batman/git/KvantEngine/engine/src/Core/Window.cpp -o CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.s

CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o.requires:

.PHONY : CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o.requires

CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o.provides: CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o.requires
	$(MAKE) -f CMakeFiles/KvantEngine.dir/build.make CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o.provides.build
.PHONY : CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o.provides

CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o.provides.build: CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o


CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o: CMakeFiles/KvantEngine.dir/flags.make
CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o: ../src/Core/StateManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o -c /home/batman/git/KvantEngine/engine/src/Core/StateManager.cpp

CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/batman/git/KvantEngine/engine/src/Core/StateManager.cpp > CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.i

CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/batman/git/KvantEngine/engine/src/Core/StateManager.cpp -o CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.s

CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o.requires:

.PHONY : CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o.requires

CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o.provides: CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/KvantEngine.dir/build.make CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o.provides.build
.PHONY : CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o.provides

CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o.provides.build: CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o


CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o: CMakeFiles/KvantEngine.dir/flags.make
CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o: ../src/CoreComponents/CNode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o -c /home/batman/git/KvantEngine/engine/src/CoreComponents/CNode.cpp

CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/batman/git/KvantEngine/engine/src/CoreComponents/CNode.cpp > CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.i

CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/batman/git/KvantEngine/engine/src/CoreComponents/CNode.cpp -o CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.s

CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o.requires:

.PHONY : CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o.requires

CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o.provides: CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o.requires
	$(MAKE) -f CMakeFiles/KvantEngine.dir/build.make CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o.provides.build
.PHONY : CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o.provides

CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o.provides.build: CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o


CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o: CMakeFiles/KvantEngine.dir/flags.make
CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o: ../src/CoreComponents/CMeshRenderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o -c /home/batman/git/KvantEngine/engine/src/CoreComponents/CMeshRenderer.cpp

CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/batman/git/KvantEngine/engine/src/CoreComponents/CMeshRenderer.cpp > CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.i

CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/batman/git/KvantEngine/engine/src/CoreComponents/CMeshRenderer.cpp -o CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.s

CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o.requires:

.PHONY : CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o.requires

CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o.provides: CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o.requires
	$(MAKE) -f CMakeFiles/KvantEngine.dir/build.make CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o.provides.build
.PHONY : CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o.provides

CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o.provides.build: CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o


CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o: CMakeFiles/KvantEngine.dir/flags.make
CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o: ../src/CoreComponents/CControllable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o -c /home/batman/git/KvantEngine/engine/src/CoreComponents/CControllable.cpp

CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/batman/git/KvantEngine/engine/src/CoreComponents/CControllable.cpp > CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.i

CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/batman/git/KvantEngine/engine/src/CoreComponents/CControllable.cpp -o CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.s

CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o.requires:

.PHONY : CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o.requires

CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o.provides: CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o.requires
	$(MAKE) -f CMakeFiles/KvantEngine.dir/build.make CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o.provides.build
.PHONY : CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o.provides

CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o.provides.build: CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o


CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o: CMakeFiles/KvantEngine.dir/flags.make
CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o: ../src/CoreSystems/NodeSystem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o -c /home/batman/git/KvantEngine/engine/src/CoreSystems/NodeSystem.cpp

CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/batman/git/KvantEngine/engine/src/CoreSystems/NodeSystem.cpp > CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.i

CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/batman/git/KvantEngine/engine/src/CoreSystems/NodeSystem.cpp -o CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.s

CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o.requires:

.PHONY : CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o.requires

CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o.provides: CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o.requires
	$(MAKE) -f CMakeFiles/KvantEngine.dir/build.make CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o.provides.build
.PHONY : CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o.provides

CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o.provides.build: CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o


CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o: CMakeFiles/KvantEngine.dir/flags.make
CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o: ../src/CoreSystems/RenderSystem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o -c /home/batman/git/KvantEngine/engine/src/CoreSystems/RenderSystem.cpp

CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/batman/git/KvantEngine/engine/src/CoreSystems/RenderSystem.cpp > CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.i

CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/batman/git/KvantEngine/engine/src/CoreSystems/RenderSystem.cpp -o CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.s

CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o.requires:

.PHONY : CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o.requires

CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o.provides: CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o.requires
	$(MAKE) -f CMakeFiles/KvantEngine.dir/build.make CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o.provides.build
.PHONY : CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o.provides

CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o.provides.build: CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o


CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o: CMakeFiles/KvantEngine.dir/flags.make
CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o: ../src/CoreSystems/InputSystem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o -c /home/batman/git/KvantEngine/engine/src/CoreSystems/InputSystem.cpp

CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/batman/git/KvantEngine/engine/src/CoreSystems/InputSystem.cpp > CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.i

CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/batman/git/KvantEngine/engine/src/CoreSystems/InputSystem.cpp -o CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.s

CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o.requires:

.PHONY : CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o.requires

CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o.provides: CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o.requires
	$(MAKE) -f CMakeFiles/KvantEngine.dir/build.make CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o.provides.build
.PHONY : CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o.provides

CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o.provides.build: CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o


CMakeFiles/KvantEngine.dir/src/States/State.cpp.o: CMakeFiles/KvantEngine.dir/flags.make
CMakeFiles/KvantEngine.dir/src/States/State.cpp.o: ../src/States/State.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/KvantEngine.dir/src/States/State.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KvantEngine.dir/src/States/State.cpp.o -c /home/batman/git/KvantEngine/engine/src/States/State.cpp

CMakeFiles/KvantEngine.dir/src/States/State.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KvantEngine.dir/src/States/State.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/batman/git/KvantEngine/engine/src/States/State.cpp > CMakeFiles/KvantEngine.dir/src/States/State.cpp.i

CMakeFiles/KvantEngine.dir/src/States/State.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KvantEngine.dir/src/States/State.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/batman/git/KvantEngine/engine/src/States/State.cpp -o CMakeFiles/KvantEngine.dir/src/States/State.cpp.s

CMakeFiles/KvantEngine.dir/src/States/State.cpp.o.requires:

.PHONY : CMakeFiles/KvantEngine.dir/src/States/State.cpp.o.requires

CMakeFiles/KvantEngine.dir/src/States/State.cpp.o.provides: CMakeFiles/KvantEngine.dir/src/States/State.cpp.o.requires
	$(MAKE) -f CMakeFiles/KvantEngine.dir/build.make CMakeFiles/KvantEngine.dir/src/States/State.cpp.o.provides.build
.PHONY : CMakeFiles/KvantEngine.dir/src/States/State.cpp.o.provides

CMakeFiles/KvantEngine.dir/src/States/State.cpp.o.provides.build: CMakeFiles/KvantEngine.dir/src/States/State.cpp.o


CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o: CMakeFiles/KvantEngine.dir/flags.make
CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o: ../src/util/Error.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o -c /home/batman/git/KvantEngine/engine/src/util/Error.cpp

CMakeFiles/KvantEngine.dir/src/util/Error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KvantEngine.dir/src/util/Error.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/batman/git/KvantEngine/engine/src/util/Error.cpp > CMakeFiles/KvantEngine.dir/src/util/Error.cpp.i

CMakeFiles/KvantEngine.dir/src/util/Error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KvantEngine.dir/src/util/Error.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/batman/git/KvantEngine/engine/src/util/Error.cpp -o CMakeFiles/KvantEngine.dir/src/util/Error.cpp.s

CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o.requires:

.PHONY : CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o.requires

CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o.provides: CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o.requires
	$(MAKE) -f CMakeFiles/KvantEngine.dir/build.make CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o.provides.build
.PHONY : CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o.provides

CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o.provides.build: CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o


# Object files for target KvantEngine
KvantEngine_OBJECTS = \
"CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o" \
"CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o" \
"CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o" \
"CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o" \
"CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o" \
"CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o" \
"CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o" \
"CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o" \
"CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o" \
"CMakeFiles/KvantEngine.dir/src/States/State.cpp.o" \
"CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o"

# External object files for target KvantEngine
KvantEngine_EXTERNAL_OBJECTS =

libKvantEngine.a: CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o
libKvantEngine.a: CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o
libKvantEngine.a: CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o
libKvantEngine.a: CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o
libKvantEngine.a: CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o
libKvantEngine.a: CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o
libKvantEngine.a: CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o
libKvantEngine.a: CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o
libKvantEngine.a: CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o
libKvantEngine.a: CMakeFiles/KvantEngine.dir/src/States/State.cpp.o
libKvantEngine.a: CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o
libKvantEngine.a: CMakeFiles/KvantEngine.dir/build.make
libKvantEngine.a: CMakeFiles/KvantEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/batman/git/KvantEngine/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX static library libKvantEngine.a"
	$(CMAKE_COMMAND) -P CMakeFiles/KvantEngine.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KvantEngine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/KvantEngine.dir/build: libKvantEngine.a

.PHONY : CMakeFiles/KvantEngine.dir/build

CMakeFiles/KvantEngine.dir/requires: CMakeFiles/KvantEngine.dir/src/Core/Engine.cpp.o.requires
CMakeFiles/KvantEngine.dir/requires: CMakeFiles/KvantEngine.dir/src/Core/Window.cpp.o.requires
CMakeFiles/KvantEngine.dir/requires: CMakeFiles/KvantEngine.dir/src/Core/StateManager.cpp.o.requires
CMakeFiles/KvantEngine.dir/requires: CMakeFiles/KvantEngine.dir/src/CoreComponents/CNode.cpp.o.requires
CMakeFiles/KvantEngine.dir/requires: CMakeFiles/KvantEngine.dir/src/CoreComponents/CMeshRenderer.cpp.o.requires
CMakeFiles/KvantEngine.dir/requires: CMakeFiles/KvantEngine.dir/src/CoreComponents/CControllable.cpp.o.requires
CMakeFiles/KvantEngine.dir/requires: CMakeFiles/KvantEngine.dir/src/CoreSystems/NodeSystem.cpp.o.requires
CMakeFiles/KvantEngine.dir/requires: CMakeFiles/KvantEngine.dir/src/CoreSystems/RenderSystem.cpp.o.requires
CMakeFiles/KvantEngine.dir/requires: CMakeFiles/KvantEngine.dir/src/CoreSystems/InputSystem.cpp.o.requires
CMakeFiles/KvantEngine.dir/requires: CMakeFiles/KvantEngine.dir/src/States/State.cpp.o.requires
CMakeFiles/KvantEngine.dir/requires: CMakeFiles/KvantEngine.dir/src/util/Error.cpp.o.requires

.PHONY : CMakeFiles/KvantEngine.dir/requires

CMakeFiles/KvantEngine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/KvantEngine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/KvantEngine.dir/clean

CMakeFiles/KvantEngine.dir/depend:
	cd /home/batman/git/KvantEngine/engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/batman/git/KvantEngine/engine /home/batman/git/KvantEngine/engine /home/batman/git/KvantEngine/engine/build /home/batman/git/KvantEngine/engine/build /home/batman/git/KvantEngine/engine/build/CMakeFiles/KvantEngine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/KvantEngine.dir/depend
