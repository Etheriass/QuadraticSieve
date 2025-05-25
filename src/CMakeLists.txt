# Gather all source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS *.cpp *.hpp)

# Exclude main.cpp from the library
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(qs_lib ${SRC_FILES})

# Now build the actual executable with main.cpp
add_executable(qs_main main.cpp)
target_link_libraries(qs_main PRIVATE qs_lib)
# This ensures that main.cpp is only compiled into the qs_main binary, not into the test binaries.