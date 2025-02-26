find_package(GTest REQUIRED)

set(miniapps_test_srcs
  randnla/test_cqrrpt.cc
  solvers/test_cg.cpp
  solvers/test_bicgstab.cpp
)

add_executable(miniapps_tests ${miniapps_test_srcs})
target_link_libraries(miniapps_tests miniapps GTest::GTest GTest::Main)

gtest_discover_tests(miniapps_tests)
