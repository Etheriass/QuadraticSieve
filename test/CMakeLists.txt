enable_testing()

# Recursively collect all of your .cpp tests
file(GLOB_RECURSE TEST_SRC CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/test/*.cpp)

# Print the entire list at configure time:
message(STATUS "Found test sources:")
foreach(f IN LISTS TEST_SRC)
  message(STATUS "  ${f}")
endforeach()

foreach(test_file IN LISTS TEST_SRC)
  # Extract filename without extension
  get_filename_component(test_name ${test_file} NAME_WE)  

  # Create one executable per test file
  add_executable(${test_name} ${test_file})

  # Link our library and GTest
  target_link_libraries(${test_name} PRIVATE qs_lib GTest::gtest GTest::gtest_main)

  # Register with CTest
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
