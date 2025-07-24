import os
import subprocess
from miller_rabin import generate_rsa_numbers

power_of_ten = 20

# Generate RSA numbers
generate_rsa_numbers(power_of_ten)

with open(os.path.join(os.path.dirname(__file__), "rsa_numbers.txt"), 'r') as infile, open(os.path.join(os.path.dirname(__file__), "naive_timings.txt"), 'w') as outfile:
    for line in infile:
        N, p, q = line.strip().split()
        try:
            # run your factorizer and capture its stdout
            result = subprocess.run(
                ["../build/src/naive_factorization", N],
                check=True,
                capture_output=True,
                text=True
            )
            outfile.write(f"{result.stdout.strip()}\n")
        except subprocess.CalledProcessError as e:
            print(f"Error on {N}: {e}")
            outfile.write(f"ERROR: {e}\n")
            exit(1)

# with open(os.path.join(os.path.dirname(__file__), "rsa_numbers.txt"), 'r') as infile, open(os.path.join(os.path.dirname(__file__), "qs_timings.txt"), 'w') as outfile:
#     for line in infile:
#         N, p, q = line.strip().split()
#         try:
#             # run your factorizer and capture its stdout
#             result = subprocess.run(
#                 ["../build/src/qs_main", N],
#                 check=True,
#                 capture_output=True,
#                 text=True
#             )
#             outfile.write(f"{result.stdout.strip()}\n")
#         except subprocess.CalledProcessError as e:
#             print(f"Error on {N}: {e}")
#             outfile.write(f"ERROR: {e}\n")
#             exit(1)
