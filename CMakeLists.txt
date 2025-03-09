# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (ai_example_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

set(OPTION_BUILD_SHARED_LIBS OFF CACHE BOOL "Disable shared libraries" FORCE)
set(FLTK_BUILD_TEST OFF CACHE BOOL "Build FLTK tests" FORCE)
set(FLTK_BUILD_EXAMPLES OFF CACHE BOOL "Build FLTK examples" FORCE)

include_directories(${CMAKE_BINARY_DIR}/external/fltk)
add_subdirectory(external/fltk)
add_subdirectory(external/philslib)
add_subdirectory(external/expected)
add_subdirectory(external/fmtlib)

add_library(
  genann
  STATIC
  external/genann/genann.h
  external/genann/genann.c)

# Include sub-projects.
add_subdirectory ("ai_example")
