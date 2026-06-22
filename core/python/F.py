import sys
from collections import Counter

input = lambda: sys.stdin.buffer.readline().decode().rstrip()
n = int(input())
a = []
for i in range(n):
    a.append(int(input()))
a.sort()

d = Counter(a)

ans = 0

for x in a:
    for y in a:
        z = x * y
        if z > a[-1]:
            break
        if z in d:
            ans += d[z]

print(ans)
