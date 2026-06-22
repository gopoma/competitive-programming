import math
import random

def MonteCarlo(a, b, N, f, vr):
    arr = [0 for _ in range(N)]
    for i in range(len(arr)):
        arr[i] = random.uniform(a, b)
    I = 0
    for x in arr:
        I += f(x)
    I *= (b - a)
    I /= N

    print("Integral:")
    print(f"Valor Calculado: {I}")
    print(f"Valor Real: {vr}")

a = 0
b = 1
N = 10000000
def f(x):
    return math.exp(x + x ** 2) * 4

MonteCarlo(a, b, N, f, 10.9652)
