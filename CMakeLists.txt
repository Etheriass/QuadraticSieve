cmake_minimum_required(VERSION 3.21)
project(QuadraticSieve CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------
# Dependency management
# --------------------------
include(FetchContent)

# GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)

FetchContent_MakeAvailable(googletest)


# Add source folder first (defines qs_lib and qs_main)
add_subdirectory(src)
# Add test code
add_subdirectory(test)
enable_testing()

# OMP option
option(ENABLE_OPENMP "Build with OpenMP support" ON)

if(ENABLE_OPENMP)
  find_package(OpenMP REQUIRED)

  if(OpenMP_CXX_FOUND)
    # link executable against the OpenMP target:
    target_link_libraries(qs_lib PRIVATE OpenMP::OpenMP_CXX)
    # Define a compile-time macro so #ifdef
    target_compile_definitions(qs_lib PRIVATE USE_OPENMP)
  else()
    message(WARNING "OpenMP not found")
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