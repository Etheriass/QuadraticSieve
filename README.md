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

If OpenMP is found, you will see it in the output of `cmake ..`.

## Run Instructions

To run the main program:

```bash
./build/src/qs_main <input_number>
```

**Example:**

```bash
./build/src/qs_main 340282366920938463463374607431768211439
```

Output:
```bash
=== Quadratic Sieve Factorization ===
 N = 340282366920938463463374607431768211439
 B = 21473

Collection phase:
pi(B) = 2407
Factor base reduced from 2407 to 1216 elements
Number of relations to find: 1216
 Sieve 1: interval size = 428367093
Found 1713 relations

Processing phase:
 WIEDEMANN: found a kernel vector with 785 non-zero element in 1 iterations
 Tentative solution:
  a = 99669503353599935594445096719843763585
  b = 339487779049157348578088401868280434633
  gcd(b-a, N) = 3272519596853078450649244729
  gcd(a+b, N) = 1

SUCCESS: 3272519596853078450649244729 is a non-trivial factor of 340282366920938463463374607431768211439

--- Timings (s) ------------- s -------- % --
Collection phase         10.6336 98.4627 %
  Eratosthenes sieve     0.0001  0.0010  %
  Sieving                10.6215 98.3505 %
  Matrix filling         0.0115  0.1067  %
Processing phase         0.1660  1.5370  %
  Matrix construction    0.0606  0.5613  %
  Kernel search          0.1035  0.9586  %
  Solution computation   0.0015  0.0142  %
Total                    10.7996 
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
