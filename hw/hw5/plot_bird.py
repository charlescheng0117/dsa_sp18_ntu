import sys
import os
import numpy as np
import matplotlib.pyplot as plt

if len(sys.argv) != 2:
    print("Usage: python3 plot_bird.py bird.in")
    sys.exit()

in_file = open(sys.argv[1], "r")

T = int(in_file.readline())

n_list = []

for i in range(T):
    n = int(in_file.readline())
    bird_list = []
    for j in range(n):
        x, y = [ int(ele) for ele in in_file.readline().strip().split(" ") ]
        bird_list.append((x, y))
    fig = plt.figure()
    plt.ylim(ymin=0, ymax=10)
    plt.xlim(xmin=0, xmax=10)
    plt.scatter(*zip(*bird_list))

plt.show()


