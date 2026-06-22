import sys

input = lambda: sys.stdin.buffer.readline().decode().rstrip()

n = int(input())
a = []

for _ in range(n):
    val = int(input())
    a.append(val)

a.sort()

for val in a:
    print(val)
