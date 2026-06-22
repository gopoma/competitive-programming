from math import acos, pi, sin, cos, sqrt
I = lambda: [Decimal(int(x)) for x in input().split()]
from decimal import *

getcontext().prec = 100
eps = 2e-7

def _acos(x):
    if 1 - eps > abs(x) > eps:
        return Decimal(acos(x))
    if x < 0:
        return pi - _acos(-x)
    if abs(x) < eps:
        return Decimal(pi) / 2 - x - x ** 3 / 6 - x ** 5 * 3 / 40 - x ** 7 * 5 / 112
    else:
        t = Decimal(1) - x
        return (2 * t).sqrt() * (
                1 + t / 12 + t ** 2 * 3 / 160 + t ** 3 * 5 / 896 + t ** 4 * 35 / 18432 + t ** 5 * 63 / 90112)

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
    print(r2 * r2 * (_acos(c1) - c1*(1-c1*c1).sqrt()) + r1 * r1 * (_acos(c2) - c2*(1-c2*c2).sqrt()))
