import math
import random

# a: límite inferior de la integral definida
# b: límite superior de la integral definida
# N: número de puntos aleatorios a generar
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
    print(f"Valor Calculado por Método Monte Carlo: {I}")
    print(f"Valot Teórico: {vt}")

a = 0
b = 1
N = 10000
def f(x):
    return (1 + math.exp(-x) * math.sin(4 * x))
vt = 1.30825
MonteCarlo(a, b, N, f, vt)
