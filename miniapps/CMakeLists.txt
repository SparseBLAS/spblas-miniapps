
set(miniapps_cxx_sources
    util.hh
    cqrrpt.hh
)

set(miniapps_libs
    lapackpp
    blaspp
    spblas
)
if (miniapps_HAS_OpenMP)
    list(APPEND miniapps_libs OpenMP::OpenMP_CXX)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/rl_config.hh.in rl_config.hh)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/rl_config.hh
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/miniapps)

add_library(miniapps INTERFACE)

set(miniapps_cxx_opts -Wall -Wextra)
if (SANITIZE_ADDRESS)
    list(APPEND miniapps_cxx_opts -fsanitize=address)
    target_link_options(miniapps INTERFACE -fsanitize=address)
endif()
target_compile_options(miniapps INTERFACE ${miniapps_cxx_opts})

#set_source_files_properties(${miniapps_cxx_sources}
#    PROPERTIES COMPILE_OPTIONS "${miniapps_cxx_opts}"
#)

target_include_directories(
    miniapps INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/..>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/comps>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/drivers>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/misc>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/miniapps>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/miniapps/comps>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/miniapps/drivers>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/miniapps/misc>
)

target_link_libraries(miniapps INTERFACE ${miniapps_libs})

install(
    FILES "${CMAKE_CURRENT_SOURCE_DIR}/../miniapps.hh"
    DESTINATION include
)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DESTINATION include FILES_MATCHING PATTERN "*.hh"
)

install(
    TARGETS miniapps
    EXPORT miniapps
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/miniapps
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# install(
#     EXPORT miniapps
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
#     EXPORT_LINK_INTERFACE_LIBRARIES
# )
