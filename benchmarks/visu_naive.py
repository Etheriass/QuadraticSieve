import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

records = []

with open(os.path.join(os.path.dirname(__file__), "naive_timings.txt"), 'r') as file:
    for line in file:
        split_line = line.split(" ")
        N, duration = int(split_line[2]), float(split_line[-1].split('s')[0])
        records.append((N, duration))

df = pd.DataFrame(records, columns=["N", "Duration"])
plt.figure(figsize=(8, 6))
sns.scatterplot(data=df, x="N", y="Duration")

plt.xscale("log")
plt.yscale("log")
plt.xlabel("Integer N")
plt.ylabel("Time to Factor (s)")
plt.title("Factorization Time vs. N ")
plt.tight_layout()
plt.savefig(os.path.join(os.path.dirname(__file__), "naive_factorization_time.png"))
plt.show()