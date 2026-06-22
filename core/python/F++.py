from collections import *
from itertools import *
from functools import *
from bisect import *
from heapq import *
import io
import os
import math
import sys
import struct
IN = lambda: sys.stdin.readline().rstrip("\r\n")
PN = lambda x: sys.stdout.write(x)
I = lambda: int(IN())
S = lambda: IN().split()
M = lambda: map(int, IN().split())
L = lambda: list(map(int, IN().split()))
G = lambda: map(lambda x: int(x) - 1, IN().split())


n = I()
a = [0] * n
mp = dict()
for i in range(n):
    a[i] = I()
    if a[i] in mp:
        mp[a[i]] += 1
    else:
        mp[a[i]] = 1

ans = 0
for i in range(n):
    for j in range(i, n):
        x = a[i] * a[j]
        if x in mp:
            if i == j:
                ans += mp[x]
            else:
                ans += 2 * mp[x]
print(ans)
