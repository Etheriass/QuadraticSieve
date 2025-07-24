import math
import os

def is_prime(n):
    """Deterministic Miller–Rabin for n up to 64 bits (and beyond)."""
    if n < 2:
        return False
    # quick checks for small divisors
    small = [2,3,5,7,11,13,17,19,23,29]
    for p in small:
        if n % p == 0:
            return n == p
    # write n-1 = d*2^r
    d, r = n-1, 0
    while d % 2 == 0:
        d //= 2
        r += 1
    # these bases suffice deterministically up to very large n
    bases = [2, 325, 9375, 28178, 450775, 9780504, 1795265022]
    for a in bases:
        if a % n == 0:
            continue
        x = pow(a, d, n)
        if x == 1 or x == n-1:
            continue
        for _ in range(r-1):
            x = pow(x, 2, n)
            if x == n-1:
                break
        else:
            return False
    return True

def prev_prime(x):
    """Largest prime ≤ x."""
    if x < 2:
        return None
    n = x if x % 2 else x-1
    while n >= 2:
        if is_prime(n):
            return n
        n -= 2
    return None

def next_prime(x):
    """Smallest prime ≥ x."""
    n = x if x % 2 else x+1
    while True:
        if is_prime(n):
            return n
        n += 2

def generate_rsa_numbers(bound):
    """Generate RSA numbers of the form N = p * q where p and q are consecutive primes."""
    with open(os.path.join(os.path.dirname(__file__), "rsa_numbers.txt"), "w") as file:
        for n in range(8, bound + 1):
            r = math.isqrt(10**n)
            p = prev_prime(r)
            q = next_prime(r)
            N = p * q
            file.write(f"{N} {p} {q}\n")



