cmake_minimum_required(VERSION 3.2)

project(miniapps)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

# configure the build
enable_testing()

include(rl_build_options)
include(rl_version)

# find dependencies
find_package(lapackpp REQUIRED)

# find dependencies
find_package(blaspp REQUIRED)

# configure spblas subproject
#add_subdirectory(spblas)

# compile sources
add_subdirectory(miniapps)
add_subdirectory(test)

# export the configuration
include(rl_config)
