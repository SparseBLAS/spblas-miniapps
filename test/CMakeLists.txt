message(STATUS "Checking for regression tests ...")
find_package(GTest)

set(tmp FALSE)
if (GTest_FOUND)
    set(tmp TRUE)

    set(miniapps_test_srcs
        randnla/test_cqrrpt.cc
    )

    add_executable(miniapps_tests ${miniapps_test_srcs})

    target_link_libraries(miniapps_tests miniapps GTest::GTest GTest::Main)

    gtest_discover_tests(miniapps_tests)
endif()
message(STATUS "Checking for regression tests ... ${tmp}")

