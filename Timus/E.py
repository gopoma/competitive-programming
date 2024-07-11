import matplotlib.pyplot as plt
import random

cols = int(input("Cantidad de Columnas: "))
steps = int(input("Cantidad de Generaciones: "))

# cols = 101 # Cantidad de Columnas
# steps = 50 # Cantidad de Generaciones

mtx = []

frow = []
if cols & 1:
    # Configuración Inicitial (Cantidad de Columnas Impar)
    for _ in range(cols // 2):
        frow.append(0)
    frow.append(1)
    for _ in range(cols // 2):
        frow.append(0)
else:
    # Configuración Inicial (Generada Aleatoriamente)
    frow = []
    for _ in range(cols):
        frow.append(int(random.randint(0, 1)))

mtx.append(frow)


nxt = {
    (0, 0, 0): 0,
    (0, 0, 1): 1,
    (0, 1, 0): 1,
    (0, 1, 1): 1,
    (1, 0, 0): 1,
    (1, 0, 1): 0,
    (1, 1, 0): 0,
    (1, 1, 1): 0,
}
assert nxt[(0, 0, 0)] == 0
assert nxt[(0, 0, 1)] == 1
assert nxt[(1, 1, 0)] == 0



# Producción de las siguientes Generaciones
for _ in range(steps - 1):
    last = mtx[-1]
    current = []
    for center in range(cols):
        L = ((center - 1) + cols) % cols
        R = (center + 1) % cols

        assert 0 <= L and L < cols
        assert 0 <= center and center < cols
        assert 0 <= R and R < cols
        assert last[L] in [0, 1]
        assert last[center] in [0, 1]
        assert last[R] in [0, 1]

        current.append(nxt[(last[L], last[center], last[R])])
    mtx.append(current)



# Transformación a Imagen
WHITE = [255, 255, 255]
BLACK = [0, 0, 0]

colors = [BLACK, WHITE]
img = []

for row in mtx:
    current = []
    for x in row:
        current.append(colors[x])
    img.append(current)



# Graficamos
plt.imshow(img)
plt.axis('off')
plt.show()
