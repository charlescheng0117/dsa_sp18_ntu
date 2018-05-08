import numpy as np
import string
import sys

DEBUG = False

all_char = list(string.ascii_lowercase)

char_to_int = {}
int_to_char = {}

for i, c in enumerate(all_char):
    char_to_int[c] = i
    int_to_char[i] = c


def generate_str(low=1, high=6, c_start=0, c_end=26):
    length_S = np.random.randint(low = low, high=high)
    S = [0] * length_S
    rand_array = np.random.randint(low=c_start, high=c_end, size = length_S)

    if DEBUG:
        print("length_S = {}\nrand_array = {}".format(length_S, rand_array))

    for i in range(length_S):
        S[i] = int_to_char[rand_array[i]]

    S = ''.join(S)
    
    return S

print("insert: low, high, c_start, c_end, Q\nOr just Q:", file=sys.stderr)
_input = input()

_input = [int(i) for i in _input.split(" ")]

if len(_input) == 1:
    low = 1
    high = 5
    c_start = 0
    c_end = 6
    Q = _input[0]
else:
    low, high, c_start, c_end, Q = _input


# generate S
S = generate_str(low, high, c_start, c_end)
print(S)

# generate Q
#Q = np.random.randint(low=low, high=high)
print(Q)

# generate subtasks
for i in range(Q):
    task_id = np.random.randint(low = 1, high = 4)
    
    if task_id == 1 or task_id == 2:
        char_id = np.random.randint(low = c_start, high = c_end)
        next_char = int_to_char[char_id]
        print("{} {}".format(task_id, next_char))

    else: # == 3
        Ti = generate_str(low, high, c_start, c_end)
        print("{} {}".format(task_id, Ti))


