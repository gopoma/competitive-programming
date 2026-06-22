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
b = math.pi / 4
N = 1000000
def f(x):
    if x == 0:
        return 1
    return math.sin(x) / x
vr = 0.7589

MonteCarlo(a, b, N, f, vr)
