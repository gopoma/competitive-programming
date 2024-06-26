import math
import random

# a: límite inferior de la integral
# b: límite superior de la integral
# N: cantidad de puntos aleatorios a generar para la integración
# f: función a integrar
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

a = 0
b = 1
N = 1000000
def f(x):
    return (x ** 2) * (math.sin(x ** 3))
vt = 0.153

MonteCarlo(a, b, N, f, vt)
