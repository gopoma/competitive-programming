# SparseSegmentTree

Segment tree sobre un universo **demasiado grande para alocar**, hasta 10¹⁸. Los nodos se crean solo cuando un `set` los toca, así que la memoria sigue a la cantidad de consultas y no a `n`.

`n` y los índices son `long long` — eso es todo el punto: un árbol denso necesitaría `2n` nodos.

Convenciones, contrato del `Node`, el pool y el monoide de ejemplo: [README.md](README.md).

## Antes de usarlo: probablemente no lo necesitás

Si las coordenadas que vas a tocar son a lo sumo `q`, **comprimirlas y usar [`SegmentTree`](SegmentTree.md) es mejor en todo**: más rápido y con menos memoria. El sparse sirve cuando no podés comprimir — típicamente porque las consultas llegan online y no conocés las coordenadas de antemano.

Medido a `n = 10¹⁸`, `q = 2·10⁵`: el sparse usa 8.7 millones de nodos y ~400 MB. El denso con coordenadas comprimidas resolvería lo mismo en 20 MB.

## API

```cpp
SparseSegmentTree<T> st(n, q)   // reserva el pool, los dos argumentos obligatorios
```

No hay `build`: el árbol **arranca vacío**, con todas las posiciones en `T()`.

| método | costo | qué hace |
|---|---|---|
| `st.set(p, x)` | O(log n) | `a[p] = x` |
| `st.get(p)` | O(log n) | la `T` en `p` |
| `st.prod(l, r)` | O(log n) | pliega `a[l..r]` |
| `st.all_prod()` | **O(1)** | pliega todo el universo |
| `st.size()` | O(1) | `n` |
| `st.nodes_used()` | O(1) | cuánto del pool se consumió |

A diferencia de los persistentes, acá **no hay raíces explícitas**: el `set` muta en el lugar. Un camino que ya existe no cuesta nodos nuevos.

## Las posiciones intactas valen `T()`

Nunca materializadas, las posiciones no tocadas se comportan como `T()`. Para un monoide basado en sumas eso sale gratis: un cero no cambia ni una suma ni el mejor subarreglo, así que dejarlas afuera del árbol da la misma respuesta que guardarlas.

Pero si tu `T()` no es el valor por defecto que tu problema quiere, el sparse **no tiene** cómo expresarlo: no hay un `fill` inicial que no cueste O(n) nodos. Esa es la limitación real de la estructura.

## Memoria

```
max_nodes(n, q) = (ceil(log2 n) + 1) * q + 1
```

Asume que cada consulta es un `set`, que materializa un nodo por nivel. Es pesimista **dos veces**: un `set` que recorre un camino que ya existe no cuesta nada, y los nodos cerca de la raíz los comparten todos los caminos.

Medido con un `T` de 40 bytes (48 por nodo interno):

| n | q | nodos usados | estructura | pico | `q` sets | `q` prods |
|---|---|---|---|---|---|---|
| 200 000 | 200 000 | 314 240 | 14.4 MB | 23.6 MB | 0.096 s | 0.157 s |
| 1 000 000 | 1 000 000 | 1 561 880 | 71.5 MB | 99.0 MB | 0.990 s | 2.104 s |
| 10⁹ | 200 000 | 2 684 739 | 122.9 MB | 132.1 MB | 0.220 s | 0.376 s |
| **10¹⁸** | 200 000 | 8 668 775 | 396.8 MB | 406.0 MB | 0.518 s | 0.458 s |
| 10¹⁸ | 10⁶ | 41 026 645 | 1878.1 MB | 1905.6 MB | 3.196 s | 4.208 s |

A 256 MB el techo es `q ≈ 1.3·10⁵` con `n = 10¹⁸` (unos 43 nodos por `set`). Fijate cómo el costo por `set` crece con `log n`: 43 nodos a 10¹⁸ contra 21 a 2·10⁵.

## El detalle del punto medio

El cálculo del medio es `mx = lx + (rx - lx) / 2`, **no** `(lx + rx) / 2`. Con `n` cerca de 2⁶³ la segunda forma desborda. Es la clase de error que no aparece en los tests chicos y revienta exactamente en el caso para el que existe la estructura.

## Ejemplo

Máxima suma de un subarreglo de `a[l..r]` con coordenadas hasta 10¹⁸ (el `Node` está en el [README](README.md#a-máxima-suma-de-un-subarreglo-con-el-vacío-permitido)):

```cpp
const ll N = 1000000000000000000LL;
int q; cin >> q;
SparseSegmentTree<Node> st(N, q);
while (q--) {
    int type; cin >> type;
    if (type == 1) { ll p, x; cin >> p >> x; st.set(p, Node(x)); }
    else { ll l, r; cin >> l >> r; cout << st.prod(l, r).best << "\n"; }
}
```

## Alternativa: usar el persistente como sparse

`PersistentSegmentTree` también materializa solo los caminos que toca, así que con `long long` en los índices haría de sparse. Lo contrasté y **no conviene**: el persistente clona en cada `set` en vez de mutar en el lugar, así que gasta muchos más nodos para el mismo trabajo. Dos templates separados es la decisión correcta, y la API de cada uno queda más intuitiva (uno con raíces explícitas, el otro sin).

## Verificación

- Contra Kadane de fuerza bruta: **107 100 rangos** sobre `n = 1..34`, junto con `SegmentTree` y `PersistentSegmentTree` usando el mismo `Node`.
- A `n = 10¹⁸`: **20 000 sets y 400 consultas de rango** contrastadas contra un `map`, con 933 284 nodos usados. Cero errores.

Ese segundo test es el que importa: verifica la aritmética de índices en el rango donde el `(lx + rx) / 2` desbordaría.

**Sin link de juez todavía.**
