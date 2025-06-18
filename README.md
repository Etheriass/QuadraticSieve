# Quadratic sieve in C++

## Introduction
The Quadratic Sieve is an integer factorization algorithm that is used to factorize large integers. It was invented by *Carl Pomerance* in 1981 as an improvement to Schroeppel’s linear sieve. 

In practice, it is the second fastest algorithm for factorizing integers of more than 100 digits, after the General Number Field Sieve. It is however, the fastest for integers of less than 100 digits. Given our ressources, we will focus on the factorization of integers of less than 100 digits and therefore, the Quadratic Sieve algorithm is relevant.

Factorizing large number as been a well-studied problem because many cryptographic systems, like RSA, rely on the difficulty of factorizing large numbers. 

<!-- To decipher a message encrypted with RSA, one must factorize a large number $N$. However, the RSA algorithm is designed so that $N$ is the product of two large prime numbers $p$ and $q$:

$$N=p \times q$$ -->

## RSA

RSA is an asymmetric encryption algorithm *(public key for encryption and private key for decryption)*. It was published in 1977 by Ron Rivest, Adi Shamir and Leonard Adleman, which first name initials give "RSA".

### Principle
The aim of RSA is to build a **one-way** function, meaning it is easy to compute in one direction but computationally hard to reverse.

First, let's posit two required lemmas:

**Bézout's Identity:** for any two integers $p$ and $q$, there exist integers $x$ and $y$ such that: 
$$px+qy= \gcd⁡(p,q)$$ 

Then if $p$ and $q$ are distinct prime numbers:
$$px+qy= 1 $$

<!-- **Fermat's Little Theorem:** if $p$ is a prime number and $a$ is any integer not divisible by $p$, then:
$$a^{p−1} \equiv 1 \mod p \iff a^p \equiv  a \mod p$$ -->

**Euler's theorem (generalization of Fermat's Little Theorem)**: if $n$ is a positive integer and $a$ is an integer coprime with $n$, and $\varphi(n)$ is Euler's totient function, then:
$$a^{\varphi(n)} \equiv 1 \mod n$$

The Euler's totient function can be computed using the Euler's product formula:

$$\varphi(n) = n \prod_{p|n}\left(1-\frac{1}{p}\right)$$

where $p$ are the distinct prime factors of $n$.


Given:
- $n = p \times q$ with $p$ and $q$ distinct prime numbers
- $a$ an integer coprime with $n$
- The Euler's totient $\varphi(n)=\varphi(pq) = pq \times \left(1-\frac{1}{p}\right) \times \left(1-\frac{1}{q}\right) = pq - q - p =(p-1)(q-1)$
- $e$, an integer coprime with $\varphi(n)$ 

Then, according to Bézout's identity, there exist two integers $d$ and $m$ such as:
$$ed - m\varphi(n) = 1 \iff ed = 1 + m\varphi(n)$$

Giving:

$$a^{ed} = a^{1 + m\varphi(n)} = a \times (a^{\varphi(n)})^m$$

Using Euler's theorem:
$$a^{ed} \equiv a \times \left( (1)^m \mod n \right)$$


Resulting in the **RSA theorem:**
$$a^{ed} \equiv a$$

Hence using $e$ and $d$ it is possible to encrypt and decrypt a message.


### Keys generation


1. Choose two distinct large prime numbers: $p$ and $q$
2. Compute the product named the **modulus**: $n = p \times q$
3. Compute the *Euler's totient function* in $n$: $\varphi(n)=\varphi(pq)=(p-1)(q-1)$ (while the original version of RSA use Euler's totient, modern implementation use Carmichael's function for efficiency but the process is the same because $\lambda(n)$ divide $\varphi(n)$)
4. Choose an integer $e$ smaller and coprime to $\varphi(n)$, $e$ is called **encryption exponent** or **public key exponent**.
5. Compute $d$ the **decryption exponent** or **private key exponent** which is the *modular multiplicative inverse* of $e$ modulo $\varphi(n)$: $d \equiv e^{-1} \mod \varphi(n)$. This is solved in the form $de \equiv 1 \mod \varphi(n)$ using the *extended Euclidean algorithm*.

Then we have both keys:
- **Public key: $(n,e)$**
- **Private key: $d$**

The size of the modulus $n$ in bits is the key length. Nowadays, RSA system use 2048 or 4096 bits keys.

We can use the logarithm to estimate the number of decimal digits in function of the key length $k$:

$$2^k = 10^n$$
$$k \log(2) = n \log(10)$$
$$n = k \log(2)$$

| Key Size (bits) | Approximate Number of Decimal Digits |
|-----------------|--------------------------------------|
| 1024            | 308                                  |
| 2048            | 617                                  |
| 4096            | 1233                                 |

### Encryption and decryption of a message
Let the message $M$ be an natural integer smaller than $n$.

The ciphertext is then: $C \equiv M^e \mod n$

To recover the initial message we need the private key: $C^d \equiv M^{ed} \equiv M \mod n$

### Reverse operation
We saw that having the decryption exponent $d$ and the modulus $n$ able use to decode the cyphertext. 

$d$ is found by solving $de \equiv 1 \mod \varphi(n)$, the problem is that if $n$ is large and we don't know its factorisation the computation of $\varphi(n)$ is too long.

Thus finding the factorisation of $n$ is the key to the key...

## Aim

Given a large RSA number $n$ the aim is to find its prime factors such as:

$$n = p \times q$$



## Quadratic Sieve by Carl Pomerance (1981)

Carl Pomerance, inspired by Dixon’s idea based on Kraitchik’s work, proposed a technique in two phases:

### Data collection phase

The collection phase consists in finding a set of numbers $a_i$ such that $a_i² ≡ x_i \mod N$, which will then be combined in the subsequent phase to yield a square on the right side.


Pomerance greatly improved this phase with three ideas:
- Collect only couple ${a, x}$ such that $a^2 ≡ x \mod N$ is B-smooth.
- Use the Legendre symbol in a sieve to find such numbers.
- Start the sieve near $\sqrt{N}$, to get small $x$.

A number is B-smooth if all its prime factors are less than $B$. Pomerance propose, relying on the prime distribution, for a large number $N$, to choose $B$ as:
$$ B = e^{\frac{1}{2}  \sqrt{\log N \log \log N}}$$

### Data processing phase
First, the collected $x_i$ are decomposed into their prime factors. Then we build a
matrix $M$ where each row corresponds to the power of the prime factors of $x_i$.
The matrix has $B$ columns and $\pi(B)$ rows.

Remember that a square number is a number that all its prime factors have an
even power. Therefore, if we find a set of numbers $x$ such that their product has
only even powers for each prime factor, we have a square number. In other words, we
have to find a combinaison of the rows of the matrix that gives an even vector.

In order to find such a combinaison, we have to find the kernel in $GF_2$ of the
transposed matrix modulo 2.

For a standard matrix, we use the Gauss elimination method to find the kernel
(time complexity of $O(n^3$ )).
However, in this case, the matrix $M$ is large and sparse, and better methods
exist to find the kernel.

At the creation of the quadratic sieve algorithm, the kernel was found by the
Lanczos' algorithm. But now we use Wiedemann's algorithm, which is a linear
algebra algorithm of time complexity $O(n\omega)$, with $\omega$ the number of
nonzero coefficients.



## Steps summary

1. Choose a smoothness bound $B$.
2. Use sieving to locate $π(B)+1$ numbers $a$ such that $a^2≡ x \mod N$ is B-smooth.
3. Decompose the numbers into their prime factors and place the powers in a matrix
4. Reduce the matrix modulo 2.
5. Find the kernel of the transposed matrix modulo 2.
6. Combine the prime factors of the numbers in the kernel.
7. Compute the greatest common divisor of the combinaison and N. Check if it is a non-trivial factor.


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