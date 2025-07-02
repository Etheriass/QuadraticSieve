# Quadratic sieve in C++

## Introduction
The Quadratic Sieve is an integer factorization algorithm that is used to factorize large integers. It was invented by *Carl Pomerance* in 1981 as an improvement to Schroeppel’s linear sieve. 

In practice, it is the second fastest algorithm for factorizing integers of more than 100 digits, after the General Number Field Sieve. It is however, the fastest for integers of less than 100 digits. Given our ressources, we will focus on the factorization of integers of less than 100 digits and therefore, the Quadratic Sieve algorithm is relevant.

Factorizing large number as been a well-studied problem because many cryptographic systems, like RSA, rely on the difficulty of factorizing large numbers. 




## Steps summary

1. Choose a smoothness bound $B$.
2. Use sieving to locate $π(B)+1$ numbers $a$ such that $a^2≡ x \mod N$ is B-smooth.
3. Decompose the numbers into their prime factors and place the powers in a matrix
4. Reduce the matrix modulo 2.
5. Find the kernel of the transposed matrix modulo 2.
6. Combine the prime factors of the numbers in the kernel.
7. Compute the greatest common divisor of the combinaison and N. Check if it is a non-trivial factor.


## OMP
To activate OMP features, switch ON in the `CMakeLists.txt`:
```bash
option(ENABLE_OPENMP "Build with OpenMP support" ON)
```

## Build

```bash
mkdir -p build
cd build
cmake ..
make
```

## Tests

```bash
cd build
ctest -V
```

## Benchmark
```bash
cmake --build . --target run_all_benchmarks
```