cmake_minimum_required(VERSION 3.21)
project(QuadraticSieve CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Check packages
# find_package(benchmark REQUIRED)

# Add source folder first (defines the qs_lib)
add_subdirectory(src)

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
