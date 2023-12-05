# interface library for RBLAS

message(
    STATUS "miniapps checking for spblas ... "
)
find_package(
    spblas REQUIRED
)
message(
    STATUS "miniapps found spblas ${spblas_VERSION}\n"
)
add_library(
    miniapps_spblas INTERFACE
)
target_link_libraries(
    miniapps_spblas INTERFACE spblas
)
install(
    TARGETS miniapps_spblas EXPORT miniapps_spblas
)
install(
    EXPORT miniapps_spblas
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
    EXPORT_LINK_INTERFACE_LIBRARIES
)

# interface library for BLAS++, inherited from RBLAS.

message(
    STATUS "miniapps checking for BLAS++, inherited from RBLAS ..."
)
find_package(
    blaspp REQUIRED
)
message(
    STATUS "miniapps found BLAS++ ${blaspp_VERSION}.\n"
)
add_library(
    miniapps_blaspp INTERFACE
)
target_link_libraries(
    miniapps_blaspp INTERFACE blaspp
)
install(
    TARGETS miniapps_blaspp EXPORT miniapps_blaspp
)
install(
    EXPORT miniapps_blaspp
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
    EXPORT_LINK_INTERFACE_LIBRARIES
)

# interface library for Random123, inherited from RBLAS.

message(
    STATUS "miniapps checking for Random123, inherited from RBLAS ... "
)
find_package(
    Random123 REQUIRED
)
message(
    STATUS "miniapps found Random123 ${Random123_VERSION}.\n"
)
add_library(
    miniapps_Random123 INTERFACE
)
target_include_directories(
    miniapps_Random123
    SYSTEM INTERFACE "${Random123_INCLUDE_DIR}"
)
install(
    TARGETS miniapps_Random123 EXPORT miniapps_Random123
)
install(
    EXPORT miniapps_Random123
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
    EXPORT_LINK_INTERFACE_LIBRARIES
)