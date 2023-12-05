message(STATUS "Checking for regression tests ...")
find_package(GTest)
set(tmp FALSE)
if (GTest_FOUND)
    set(tmp TRUE)

    add_executable(miniapps_tests src/randnla/test_cqrrpt.cc)
    target_link_libraries(miniapps_tests miniapps GTest::GTest GTest::Main)
    gtest_discover_tests(miniapps_tests)

endif()
message(STATUS "Checking for regression tests ... ${tmp}")
