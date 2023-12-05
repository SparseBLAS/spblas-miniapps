cmake_minimum_required(VERSION 3.2)

project(miniapps)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

# configure the build
enable_testing()
include(build_options)
include(version)

# find dependencies
#include(spblas)
include(lapackpp)
include(blaspp)

# compile sources
add_subdirectory(src)  # loads src/CMakeLists.txt
add_subdirectory(test)

# export the configuration
include(config)

