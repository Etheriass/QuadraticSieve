cmake_minimum_required(VERSION 3.21)
project(QuadraticSieve CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source folder first (defines qs_lib and qs_main)
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


# OMP option
option(ENABLE_OPENMP "Build with OpenMP support" ON)

if(ENABLE_OPENMP)
  find_package(OpenMP REQUIRED)

  if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found")
    # link executable against the OpenMP target:
    target_link_libraries(qs_lib PUBLIC OpenMP::OpenMP_CXX)
    # Define a compile-time macro so #ifdef
    target_compile_definitions(qs_lib PUBLIC USE_OPENMP)
    target_compile_definitions(benchmark PUBLIC USE_OPENMP)
  else()
    message(WARNING "OpenMP not found")
  endif()
endif()
    
# Pthread option
option(ENABLE_PTHREAD "Build with Pthread support" ON)
    
if(ENABLE_PTHREAD)
  find_package(Threads REQUIRED)
  if(Threads_FOUND)
    message(STATUS "PThread found")
    target_link_libraries(qs_lib PUBLIC Threads::Threads)
    target_compile_definitions(qs_lib PUBLIC USE_PTHREAD)
    target_compile_definitions(benchmark PUBLIC USE_PTHREAD)
  else()
    message(WARNING "PThread not found")
  endif()
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(
    -march=native        # Use the native architecture (current CPU)
    -funroll-loops       # Unroll loops
    -O3                  # Optimize for speed
    -Ofast -ffast-math   # Aggressive optimizations
    -flto                # Link Time Optimization
    -fstrict-aliasing    # Enable strict aliasing (assumes pointers of different types do not alias)
    -fomit-frame-pointer # Omit frame pointers
    -falign-functions=32 # Align functions to 32-byte boundaries
    -fno-exceptions      # Disable exceptions
    -fno-rtti            # Disable RTTI
  )

  include(CheckIPOSupported)
  check_ipo_supported(RESULT IPO_OK OUTPUT IPO_ERR)
  if (IPO_OK)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()

  # for linking with LTO
  add_link_options(-flto)
endif()