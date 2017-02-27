# Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.6)
#Name your project here
set(PNAME KvantEngine)
project(${PNAME})

# Set compiler to gcc-4.9 version
SET(CMAKE_C_COMPILER /usr/bin/gcc-4.9)
SET(CMAKE_CXX_COMPILER /usr/bin/g++-4.9)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors")

include_directories(src)
add_executable(${PROJECT_NAME}
  src/window.cpp
  src/main.cpp
)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

# OPENGL
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(library ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(
    ${PROJECT_NAME}
    ${OPENGL_gl_LIBRARY}
    ${GLUT_LIBRARIES} )

#GLEW libraries
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
  MESSAGE(Found glew)
  include_directories($(GLEW_INCLUDE_DIRS))
  target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
endif()

target_link_libraries(${PROJECT_NAME} -lboost_log)
