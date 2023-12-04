# Create an interface library for the header-only library
add_library(miniapps INTERFACE)

# Add the include directory to the interface library
target_include_directories(miniapps INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/randnla
    ${CMAKE_CURRENT_SOURCE_DIR}/misc
)
