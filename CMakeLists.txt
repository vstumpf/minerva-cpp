cmake_minimum_required(VERSION 3.1)

project(minerva CXX)

# Processing third parties
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/3rdparty/cmake" ${CMAKE_MODULE_PATH})
set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)

# Tell CMake where to search for includes and libs on Windows
if (WIN32)
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
  )
endif ()

find_package(OpenGL REQUIRED)
find_package(DevIL)

# Setup clang-tidy if available
find_program(
  CLANG_TIDY_EXE
  NAMES "clang-tidy"
  DOC "Path to clang-tidy executable"
)
if(NOT CLANG_TIDY_EXE)
  message(STATUS "clang-tidy not found.")
else()
  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
  set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*")
endif()

add_subdirectory(3rdparty)
add_subdirectory(src)
