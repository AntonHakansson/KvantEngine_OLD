set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)

# Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.8)
# Name your project here
set(PNAME KvantEngine)
project(${PNAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors")

include_directories(include)
include_directories(src)
include_directories(third-party)
include_directories(third-party/cpp-filewatcher/include/)

add_library(${PROJECT_NAME}
  src/Core/Engine.cpp
  src/Core/Window.cpp
  src/Core/StateManager.cpp
  src/CoreComponents/CNode.cpp
  src/CoreComponents/CMeshRenderer.cpp
  src/CoreComponents/CControllable.cpp
  src/CoreSystems/NodeSystem.cpp
  src/CoreSystems/RenderSystem.cpp
  src/CoreSystems/InputSystem.cpp
  src/States/State.cpp
  src/util/Error.cpp
  src/imgui/imgui_impl_sdl_gl3.cpp

  third-party/imgui/imgui_demo.cpp
  third-party/imgui/imgui.cpp
  third-party/imgui/imgui_draw.cpp
)

# Cotire PCH
cotire(${PROJECT_NAME})

# Set location for library installation
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/KvantEngine DESTINATION /usr/include)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/third-party/spdlog DESTINATION /usr/include)

INCLUDE(FindPkgConfig)

# Link to SDL2 libraries
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

# OPENGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
  MESSAGE(Found OPENGL)
endif()
find_package(GLUT REQUIRED)
if (GLUT_FOUND)
  MESSAGE(Found GLUT)
endif()
include_directories(library ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(
    ${PROJECT_NAME}
    ${OPENGL_gl_LIBRARY}
    ${GLUT_LIBRARIES} )

# GLEW libraries
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
  MESSAGE(Found glew)
  include_directories($(GLEW_INCLUDE_DIRS))
  target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
endif()

# Link to boost libraries
find_package(Boost REQUIRED COMPONENTS system filesystem)
target_link_libraries(${PROJECT_NAME} ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})
add_definitions(-DBOOST_LOG_DYN_LINK)

# Link to entityx
link_directories(/usr/lib)
target_link_libraries(${PROJECT_NAME} entityx)

# Link to yaml
target_link_libraries(${PROJECT_NAME} yaml-cpp)

# Link to file watcher
target_link_libraries(${PROJECT_NAME} cpp-filewatcher)

# Link to freeimage
target_link_libraries(${PROJECT_NAME} freeimage)
