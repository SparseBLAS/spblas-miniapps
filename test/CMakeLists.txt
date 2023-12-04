# Create an executable for tests
add_executable(test_rbki test_rbki.cpp)
add_executable(test_rsvd test_rsvd.cpp)

# Link the test executables with the library
target_link_libraries(test_rbki PRIVATE miniapps)
target_link_libraries(test_rsvd PRIVATE miniapps)

# Include the testing framework (e.g., Google Test)
# This assumes you have Google Test installed or added to your project
# Add appropriate commands depending on your testing framework

target_include_directories(test_rbki PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(test_rbki PRIVATE ${GTEST_LIBRARIES})

target_include_directories(test_rsvd PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(test_rsvd PRIVATE ${GTEST_LIBRARIES})