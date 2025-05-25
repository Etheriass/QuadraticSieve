file(GLOB TEST_SRC CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/test/*.cpp)

foreach(test_file ${TEST_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(test_${test_name} ${test_file})
    target_link_libraries(test_${test_name} PRIVATE qs_lib gtest gtest_main)
    add_test(NAME ${test_name} COMMAND test_${test_name})
endforeach()