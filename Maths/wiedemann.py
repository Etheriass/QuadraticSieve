import numpy as np
import time

def random_sparse_f2(n: int, density=0.1):
    """Generate a random sparse n x n matrix over F2 with given density."""
    A = np.random.rand(n, n) < density
    A = A.astype(int)
    return A

def gf2_rank(A: np.ndarray) -> int:
    """Compute the rank of a binary matrix A over GF(2) using Gaussian elimination."""
    M = A.copy() % 2
    m, n = M.shape
    rank = 0
    for col in range(n):
        # Find a pivot in column `col` at or below row `rank`
        pivot = None
        for r in range(rank, m):
            if M[r, col] == 1:
                pivot = r
                break
        if pivot is None:
            continue
        # Swap the pivot row into position `rank`
        if pivot != rank:
            M[[pivot, rank]] = M[[rank, pivot]]
        # Eliminate all 1s below the pivot
        for r in range(rank + 1, m):
            if M[r, col] == 1:
                M[r, :] ^= M[rank, :]
        rank += 1
        if rank == m:
            break
    return rank


def get_u_v(n: int) -> tuple[np.ndarray, np.ndarray]:   
    """Generate random vectors u and v in F2^n such that u.v = 0."""
    v = np.random.randint(0, 2, size=n)
    u = np.random.randint(0, 2, size=n)
    while (u @ v) % 2 != 0:  # ensure that f(0) = 0
        u = np.random.randint(0, 2, size=n)
    return u, v

def berlekamp_massey(s: np.ndarray) -> list[int]:
    """Berlekamp-Massey algorithm to find the minimal polynomial of sequence s over F2."""
    n = len(s)
    C = [1] + [0] * n  # current polynomial
    B = [1] + [0] * n  # previous polynomial
    L = 0
    m = 1
    for i in range(n):
        d = s[i] # discrepancy
        for j in range(1, L + 1):
            d ^= C[j] & s[i - j] # XOR operation for addition in F_2
        if d == 0:
            m += 1
        else:
            T = C[:]
            for j in range(i + 1):
                if j >= m:
                    C[j] ^= B[j - m]
            if 2 * L <= i:
                L = i + 1 - L
                B = T
                m = 1
            else:
                m += 1
    return C[:L + 1]

def wiedemann(A: np.ndarray, max_iterations=1000) -> np.ndarray:
    """Wiedemann algorithm to find a non-trivial kernel vector of A over F2."""
    n = A.shape[0]
    rank = gf2_rank(A)
    if rank < n:
        print(f"Rank of A is {rank}, so the matrix is singular, kernel is not trivial.")
    else:
        print("Matrix A is non-singular, kernel is trivial.")
        return np.zeros(n, dtype=int)

    iteration = 0
    found = False
    while not found:
        if iteration >= max_iterations:
            raise RuntimeError(f"Exceeded maximum iterations ({max_iterations}) without finding a kernel vector.")
        # Get random vectors u and v
        u, v = get_u_v(n)

        # Krylov subspace
        Kv = [v.copy()]
        for i in range(1, 2*n):
            Kv.append(A @ Kv[-1] % 2)

        # Scalar sequence
        s = np.zeros(2*n, dtype=int)
        for i in range(2*n):
            s[i] = np.dot(u.T, Kv[i]) % 2

        C = berlekamp_massey(s) # {c_0, c_1, ..., c_L} with c_0 = 1
        d = len(C)-1  
        if C[-1] != 0:
            continue # Get new (u,v) because f(0) != 0

        # Polynomial g(x) = c_0 + c_1 x + ... + c_{d-1} x^{d-1}
        q = [ C[d-1-j] for j in range(d) ] 

        # Kernel candidate
        w = np.zeros(n, dtype=int)
        for j, c in enumerate(q):
            if c:
                w = (w + Kv[j]) % 2

        if np.sum(w) == 0:
            continue # Get new (u,v) because w = 0

        # Check kernel candidate
        r = (A @ w) % 2
        if np.sum(r) == 0:
            if np.sum(w) > 1:
                print(f"Found a non-trivial kernel vector in {iteration} iterations.")
                return w
            elif rank == n - 1:
                print(f"Found the only kernel vector in {iteration} iterations.")
                return w
        else:
            iteration += 1

if __name__ == "__main__":
    A = random_sparse_f2(1000, density=0.1)
    start = time.time()
    w = wiedemann(A)
    end = time.time()
    # print("Kernel vector w:", w)
    print(f"Time taken: {end - start:.3f}s")