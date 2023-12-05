message(STATUS "\n\n-- miniapps checking for spblas ... ")
find_package(spblas REQUIRED)
message(STATUS "miniapps found spblas ${spblas_VERSION}\n")

# interface library for use elsewhere in the project
add_library(miniapps_spblas INTERFACE)

target_link_libraries(miniapps_spblas INTERFACE spblas)

install(TARGETS miniapps_spblas EXPORT miniapps_spblas)

install(EXPORT miniapps_spblas
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
    EXPORT_LINK_INTERFACE_LIBRARIES)