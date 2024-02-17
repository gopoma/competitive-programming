from math import acos, pi, sin, cos, sqrt
I = lambda: [Decimal(int(x)) for x in input().split()]
from decimal import *

getcontext().prec = 100

def cos(x):
    i, lasts, s, fact, num, sign = 0, 0, 1, 1, 1, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i - 1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    return +s


def acos(x):
    mn, mx = Decimal(0), Decimal(pi)
    for i in range(100):
        md = (mn + mx) / 2
        if cos(md) <= x:
            mx = md
        else:
            mn = md
    return mx;


x1, y1, r1 = I()
x2, y2, r2 = I()
x = ((x1 - x2)*(x1-x2) + (y1 - y2)*(y1-y2)).sqrt()

if r1 + r2 <= x:
    print(0)
elif r1 + x <= r2:
    print(r1 * r1 * Decimal(pi))
elif r2 + x <= r1:
    print(r2 * r2 * Decimal(pi))
else:
    c1 = (r2 * r2 + x * x - r1 * r1) / (2 * x * r2)
    c2 = (r1 * r1 + x * x - r2 * r2) / (2 * x * r1)
    print(r2 * r2 * (acos(c1) - c1*(1-c1*c1).sqrt()) + r1 * r1 * (acos(c2) - c2*(1-c2*c2).sqrt()))
