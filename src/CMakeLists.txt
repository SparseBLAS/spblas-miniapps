set(miniapps_cxx_srcs
    randnla/cqrrpt.cc
    misc/util.cc
)

set(miniapps_libs
    miniapps_spblas
    miniapps_lapackpp
    miniapps_blaspp
) 

add_library(miniapps ${miniapps_cxx_srcs})

target_include_directories(
    miniapps PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/miniapps>
    $<INSTALL_INTERFACE:include>
    $<INSTALL_INTERFACE:include/miniapps>
)

target_link_libraries(miniapps PUBLIC ${miniapps_libs})

install(
    DIRECTORY "${CMAKE_SOURCE_DIR}/include/"
    DESTINATION include FILES_MATCHING PATTERN "*.hh"
)

install(
    TARGETS miniapps
    EXPORT miniapps
    INCLUDES DESTINATION include/miniapps
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)