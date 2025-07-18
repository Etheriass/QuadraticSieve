import time
from tqdm import tqdm

N = 5316911983139663487003542222693990401

start = time.time()
for i in tqdm(range(2, int(N**0.5))):
    if N % i == 0:
        print(f"\n{i} is a factor of {N}")


end = time.time()
print(f"\nTime elapsed: {end - start:.2f} seconds")
