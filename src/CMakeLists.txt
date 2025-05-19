# Gather all source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS *.cpp *.hpp)


add_library(qs_lib ${SRC_FILES})

# Optional: if you want to build a main binary
add_executable(qs_main main.cpp)
target_link_libraries(qs_main PRIVATE qs_lib)

# add_library(eratosthene_lib Eratosthene/eratosthene.cpp)
# target_include_directories(eratosthene_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Eratosthene) # Specify include directories for the library

# target_link_libraries(quadratic_sieve_lib eratosthene_lib m)