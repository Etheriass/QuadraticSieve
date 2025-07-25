import numpy as np
from math import gcd, isqrt

def primes_up_to(n):
    """Return list of primes ≤ n."""
    sieve = [True] * (n + 1)
    sieve[0:2] = [False, False]
    for i in range(2, int(n**0.5) + 1):
        if sieve[i]:
            for j in range(i*i, n + 1, i):
                sieve[j] = False
    return [p for p, is_prime in enumerate(sieve) if is_prime]

def simple_sieve(N, B_bound, A_len):
    """
    Perform a basic trial-division sieve for Q(x) = (r + x)^2 - N
    over x = 0..A_len-1, collecting those Q(x) that are B-smooth.
    """
    factor_base = primes_up_to(B_bound)
    r = int(np.sqrt(N)) + 1
    relations = []
    for x in range(A_len):
        Q = (r + x)**2 - N
        val = Q
        for p in factor_base:
            while val % p == 0:
                val //= p
        if abs(val) == 1:
            relations.append((r + x, Q))
    return factor_base, relations

def berlekamp_massey_gf2(s):
    """Berlekamp-Massey over GF(2)."""
    n = len(s)
    C = [1] + [0]*n
    B = [1] + [0]*n
    L, m = 0, 1
    for i in range(n):
        d = s[i]
        for j in range(1, L+1):
            d ^= C[j] & s[i-j]
        if d:
            T = C.copy()
            for j in range(n - m + 1):
                C[j + m] ^= B[j]
            if 2*L <= i:
                B, L, m = T, i + 1 - L, 1
            else:
                m += 1
        else:
            m += 1
    return C[:L+1]

def find_kernel_vector(A_mat, B_mat, u, v, num_powers=10):
    """Wiedemann: find x with M x = 0 over GF(2)."""
    M = (A_mat @ B_mat) % 2
    # generate M^i
    M_pows = [np.eye(M.shape[0], dtype=int)]
    for _ in range(1, num_powers):
        M_pows.append((M_pows[-1] @ M) % 2)
    # sequence s_i = u^T M^i v
    s = [int((u @ Mp @ v) % 2 )for Mp in M_pows]
    print("Sequence s:", s)
    coeffs = berlekamp_massey_gf2(s)
    print("Berlekamp-Massey coefficients:", coeffs)
    x = np.zeros_like(v)
    for i, c in enumerate(coeffs):
        if c:
            x ^= (M_pows[i] @ v) % 2
    return M, x

def factor_demo(N, a, b):
    """Extract a factor of N via gcd(a±b, N)."""
    a_mod, b_mod = a % N, b % N
    print(f"Computing gcd for a = {a_mod}, b = {b_mod}, N = {N}")
    g1 = gcd(a_mod - b_mod, N)
    g2 = gcd(a_mod + b_mod, N)
    print(f"gcd(a - b, N) = {g1}")
    print(f"gcd(a + b, N) = {g2}")

def main():
    # Quadratic Sieve: simple sieve stage
    N = 2041
    B_bound = 7
    A_len = 20
    fb, rels = simple_sieve(N, B_bound, A_len)
    print("Factor base:", fb)
    print("Smooth relations (x, Q):", rels)

    # Matrix kernel via Wiedemann
    A_mat = np.array([
        [0,1,0,0],
        [1,1,0,1],
        [1,0,1,0],
        [0,0,1,1],
        [0,1,0,0]
    ])
    B_mat = np.array([
        [0,1,1,0,0],
        [1,1,0,0,1],
        [0,0,1,1,0],
        [0,1,0,1,0]
    ])

    # u = np.random.randint(0, 2, size=A_mat.shape[0])
    # v = np.random.randint(0, 2, size=B_mat.shape[1])
    u = np.array([1, 1, 1, 0, 1])
    v = np.array([0, 1, 0, 1, 1])
    print("Random u:", u)
    print("Random v:", v)

    M, x = find_kernel_vector(A_mat, B_mat, u, v)
    print("Kernel vector x:", x)
    print("M @ x % 2 =", (M @ x) % 2)

    # Solution computation
    print("a *= ", [rels[i][0] for i in range(len(x)) if x[i] == 1])
    print("b² *= ", [rels[i][1] for i in range(len(x)) if x[i] == 1])
    a = 1
    b = 1
    for i in range(len(x)):
        if x[i] == 1:
            a *= rels[i][0]
            b *= rels[i][1]
    
    b = isqrt(b)
    print("Tentative solution (a, b):", a, b)
    factor_demo(N, a, b)

if __name__ == "__main__":
    main()

