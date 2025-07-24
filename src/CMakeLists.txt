# Gather all source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# Exclude main.cpp from the library
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Exclude naive.cpp from the library
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/naive.cpp)

add_library(qs_lib ${SRC_FILES})

# Now build the actual executable with main.cpp
add_executable(qs_main main.cpp)
target_link_libraries(qs_main PRIVATE qs_lib)

# Add the naive executable
add_executable(naive_factorization naive.cpp)
target_link_libraries(naive_factorization PRIVATE qs_lib)