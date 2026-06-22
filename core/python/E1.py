import math
import sys
from random import randint as rn
import random
import functools
from heapq import heappop, heappush
import decimal
from decimal import Decimal

decimal.getcontext().prec = 100

pi = Decimal('3.141592653589793238462643383279502884197169399')


def dec_sin(x):
    res = Decimal(x)
    it = -1
    for i in range(3, 29 + 1, 2):
        res += Decimal(x) ** i / Decimal(math.factorial(i)) * it
        it *= -1

    return res


def dec_acos(x):
    return Decimal(math.atan2((1 - x ** 2).sqrt(), x))


def solve():
    x1, y1, r1 = map(int, input().split())
    x2, y2, r2 = map(int, input().split())

    if (x1 - x2) ** 2 + (y1 - y2) ** 2 >= (r1 + r2) ** 2:
        print('0.00000000000000000')
        return

    d = math.dist([x1, y1], [x2, y2])

    if max(r1, r2) >= min(r1, r2) + d:
        print('%.18f' % (math.pi * min(r1, r2) ** 2))
        return

    res = Decimal(0)
    d = Decimal((x1 - x2) ** 2 + (y1 - y2) ** 2)
    d = d.sqrt()

    for rr1, rr2 in [[r1, r2], [r2, r1]]:
        rr1 = Decimal(rr1)
        rr2 = Decimal(rr2)

        angle = dec_acos((rr2 ** 2 + d ** 2 - rr1 ** 2) / Decimal(2 * rr2 * d))
        seg = angle * rr2 ** 2 - rr2 ** 2 * (dec_sin(2 * angle) / 2)

        res += seg

    print('%.18f' % res)
    return


if __name__ == '__main__':

    multitest = 0

    if multitest:
        t = int(sys.stdin.readline())
        for _ in range(t):
            solve()
    else:
        solve()
    # gen()
