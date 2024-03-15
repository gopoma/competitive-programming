import sys
import random

# from colorama import Fore, Back, Style

input = sys.stdin.readline

def inp():
    return(int(input()))

def inlt():
    return(list(map(int, input().split())))

# https://atcoder.jp/contests/abc339/tasks/abc339_f
if __name__ == '__main__':
    N = inp()

    A = []
    for _ in range(N):
        A.append(inp())

    """
    print(Fore.CYAN)
    print(N)
    print(A)

    print(Fore.WHITE)
    """

    Mod = random.randint(10 ** 30, 10 ** 31 + 1)

    d = dict()
    for i in range(N):
        k = A[i] % Mod
        if k not in d:
            d[k] = 1
        else:
            d[k] += 1
        A[i] = k

    ans = 0

    # print(A)

    for i in range(N):
        for j in range(N):
            val = d.get((A[i] * A[j]) % Mod)
            if val is None:
                val = 0

            ans += val

    print(ans)
