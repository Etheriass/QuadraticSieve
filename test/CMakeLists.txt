find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Define the test executable
add_executable(test_eratosthene eratosthene.cpp)

# Link the test executable with BOOST libraries
target_link_libraries(test_eratosthene PRIVATE eratosthene_lib  Boost::unit_test_framework)

# Add the test to the CTest suite
add_test(NAME EratostheneTests COMMAND test_eratosthene)