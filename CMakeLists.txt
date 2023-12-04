cmake_minimum_required(VERSION 3.20)
project(spblas-miniapps VERSION 1.0)

# Include the subdirectory containing the header-only library
add_subdirectory(miniapps)
add_subdirectory(test)
add_subdirectory(spblas)

# Add the main executable
add_executable(spblas-miniapps main.cpp)

# find dependencies
find_package(lapackpp REQUIRED)
if(NOT lapackpp_FOUND)
    message(FATAL_ERROR "LAPACK++ not found. Please install it.")
endif()

# Link the main executable with the library
target_link_libraries(spblas-miniapps PRIVATE miniapps)
target_link_libraries(spblas-miniapps PRIVATE spblas)

include_directories(${lapackpp_INCLUDE_DIRS})
target_link_libraries(spblas-miniapps PRIVATE ${lapackpp_LIBRARIES})
