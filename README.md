# Quadratic sieve in C++

## Introduction
The Quadratic Sieve is an integer factorization algorithm that is used to factorize large integers. It was invented by *Carl Pomerance* in 1981 as an improvement to Schroeppel’s linear sieve. 

In practice, it is the second fastest algorithm for factorizing integers of more than 100 digits, after the General Number Field Sieve. It is however, the fastest for integers of less than 100 digits. Given our ressources, we will focus on the factorization of integers of less than 100 digits and therefore, the Quadratic Sieve algorithm is relevant.



## Aim

Factorizing large number as been a well-studied problem because many cryptographic systems, like
RSA, rely on the difficulty of factorizing large numbers. To decipher a message encrypted with RSA, one must factorize a large number $N$. However, the RSA algorithm is designed so that N is the product of two large prime numbers $p$ and $q$:

$$N=p \times q$$



## Steps summary

1. Choose a smoothness bound $B$.
2. Use sieving to locate $π(B)+1$ numbers a such that $a^2≡ x \mod N$ is B-smooth.
3. Decompose the numbers into their prime factors and place the powers in a matrix
4. Reduce the matrix modulo 2.
5. Find the kernel of the transposed matrix modulo 2.
6. Combine the prime factors of the numbers in the kernel.
7. Compute the greatest common divisor of the combinaison and N. Check if it is a non-trivial factor.

## Quadratic Sieve by Carl Pomerance (1981)

### 1. Presentation
The Quadratic Sieve is an integer factorization algorithm that is used to factorize large integers. It was invented by Carl Pomerance in 1981 as an improvement to Schroeppel’s linear sieve. In practice, it is the second fastest algorithm for factorizing integers of more than 100 digits, after the General
Number Field Sieve. It is however, the fastest for integers of less than 100 digits. Given our ressources, we will focus on the factorization of integers of less than 100 digits and therefore, the Quadratic Sieve algorithm is relevant.

<!-- ### 2. Aim

Factorizing large number as been a well-studied problem because many cryptographic systems, like RSA, rely on the difficulty of factorizing large numbers.
To decipher a message encrypted with RSA, one must factorize a large number N . However, the RSA algorithm is designed so that N is the product of two large prime numbers p and q:

$N =p×q$ -->

Carl Pomerance, inspired by Dixon’s idea based on Kraitchik’s work, proposed a technique in two phases:

### Data collection phase

The collection phase consists in finding a set of numbers $a_i$ such that $a_i² ≡ x_i \mod N$, which will then be combined in the subsequent phase to yield a square on the right side.


Pomerance greatly improved this phase with three ideas:
- Collect only couple ${a, x}$ such that $a^2 ≡ x \mod N$ is B-smooth.
- Use the Legendre symbol in a sieve to find such numbers.
- Start the sieve near $\sqrt{N}$, to get small $x$.

A number is B-smooth if all its prime factors are less than $B$. Pomerance propose, relying on the prime distribution, for a large number $N$, to choose $B$ as:
$
B = e^{\frac{1}{2}  \sqrt{\log N \log \log N}}
$