# Quadratic Sieve in C++

## Introduction

The Quadratic Sieve is an integer factorization algorithm that is used to factorize large integers. It was invented by *Carl Pomerance* in 1981 as an improvement to Schroeppel’s linear sieve. 

In practice, it is the second fastest algorithm for factorizing integers of more than 100 digits, after the General Number Field Sieve. It is, however, the fastest for integers of less than 100 digits. Given our resources, we will focus on the factorization of integers of less than 100 digits and therefore, the Quadratic Sieve algorithm is relevant.

Factorizing large numbers has been a well-studied problem because many cryptographic systems, like RSA, rely on the difficulty of factorizing large numbers. 

The principle of the Quadratic Sieve is explained in the `maths/Proof.pdf` document.

## Project Purpose

This project implements the Quadratic Sieve algorithm, a complex integer factorization method that bridges the fields of Mathematics and High-Performance Computing (HPC). It serves as a practical application of the discoveries made in my other repository, `hpc-playground`, where I experiment with various HPC algorithms and their optimizations (e.g., cache usage, AVX instructions).

## Steps Summary

1. Choose a smoothness bound $B$.
2. Use sieving to locate $π(B)+1$ numbers $a$ such that $a^2≡ x \mod N$ is B-smooth.
3. Decompose the numbers into their prime factors and place the powers in a matrix.
4. Reduce the matrix modulo 2.
5. Find the kernel of the transposed matrix modulo 2.
6. Combine the prime factors of the numbers in the kernel.
7. Compute the greatest common divisor of the combination and $N$. Check if it is a non-trivial factor.

## Dependencies

To build and run this project, ensure you have the following installed:

- **CMake** (minimum version 3.21)
- **C++ compiler** with support for C++17 (e.g., g++ or clang++)
- **OpenMP** (optional, for parallelization)

**GoogleTest** will be downloaded automatically during the build process.

## Build Instructions

Follow these steps to build the project:

```bash
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

### Enabling OpenMP

To activate OpenMP features, switch ON in the `CMakeLists.txt`:

```cmake
option(ENABLE_OPENMP "Build with OpenMP support" ON)
```

If OpenMP is found, you will see "Using OpenMP" in the output of `cmake ..`.

## Run Instructions

To run the main program:

```bash
./build/src/qs_main
```

## Testing

To run all tests:

```bash
cd build
ctest -V
```

To run a specific test (using a regex):

```bash
ctest -V -R wiedemann
```

## Contact

If you encounter any errors or have suggestions for improvement, feel free to contact me. Contributions and feedback are always welcome!
