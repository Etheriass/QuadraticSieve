cmake_minimum_required(VERSION 3.21)
project(QuadraticSieve CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source folder first (defines qs_lib and qs_main)
add_subdirectory(src)


# OMP option
option(ENABLE_OPENMP "Build with OpenMP support" ON)

if(ENABLE_OPENMP)
  find_package(OpenMP REQUIRED)

  if(OpenMP_CXX_FOUND)
    # link your executable (or library) against the OpenMP target:
    target_link_libraries(qs_lib PRIVATE OpenMP::OpenMP_CXX)
    # Define a compile-time macro so you can #ifdef your code
    target_compile_definitions(qs_lib PRIVATE USE_OPENMP)
  endif()
endif()

# --------------------------
# Dependency management
# --------------------------
include(FetchContent)

# GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Google Benchmark
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main
)

# Disable Google Benchmark's self-tests
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)


# Make available
FetchContent_MakeAvailable(
  googletest
  googlebenchmark
)

enable_testing()

# Add test and benchmark code
add_subdirectory(test)
add_subdirectory(benchmark)
