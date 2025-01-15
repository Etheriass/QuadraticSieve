add_library(quadratic_sieve_lib quadratic_sieve.cpp)


add_library(eratosthene_lib Eratosthene/eratosthene.cpp)
target_include_directories(eratosthene_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Eratosthene) # Specify include directories for the library

target_link_libraries(quadratic_sieve_lib eratosthene_lib m)