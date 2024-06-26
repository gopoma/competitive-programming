import math
import random

# a: límite inferior
# b: límite superior
# N: cantidad de puntos a generar
# f: función a integrar
# vt: valor teórico
def MonteCarlo(a, b, N, f, vt):
    arr = [0 for _ in range(N)]
    for i in range(len(arr)):
        arr[i] = random.uniform(a, b)
    I = 0
    for x in arr:
        I += f(x)
    I *= (b - a)
    I /= N
    print("Integral:")
    print(f"Valor Calculado por Monte Carlo: {I}")
    print(f"Valor Teórico: {vt}")

    E = abs(vt - I)
    print(f"Error: {E}")

a = 0
b = 1
N = 10000
def f(x):
    return math.exp(-x)
vt = 0.632
MonteCarlo(a, b, N, f, vt)
