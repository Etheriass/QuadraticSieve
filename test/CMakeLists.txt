cmake_policy(SET CMP0167 NEW)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Collect test files
file(GLOB_RECURSE TEST_SRC CONFIGURE_DEPENDS *.cpp)

foreach(test_file ${TEST_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE qs_lib Boost::unit_test_framework)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()