import numpy as np
import sys

if len(sys.argv) != 2:
    print("Usage: python3 gen_fries.py <n fries>")
    sys.exit()

n = int(sys.argv[1])

print(n)
fries = np.random.randint(1, 21, size=n)
for ele in fries:
    print(ele, end=" ")
print("")
