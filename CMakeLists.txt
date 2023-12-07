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
include(FetchContent)
FetchContent_Declare(
  spblas
  GIT_REPOSITORY https://github.com/SparseBLAS/spblas-reference.git
  GIT_TAG main)
FetchContent_MakeAvailable(spblas)
# Fetch and populate the content of the external project
FetchContent_GetProperties(spblas)
if(NOT spblas_POPULATED)
    FetchContent_Populate(spblas)
    # Now you can use the content of the external project
    add_subdirectory(${spblas_SOURCE_DIR} ${spblas_BINARY_DIR})
endif()

# compile sources
add_subdirectory(miniapps)
add_subdirectory(test)

# export the configuration
include(rl_config)
