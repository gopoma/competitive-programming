# PersistentSegmentTree

Segment tree persistente: **cada `set` devuelve la raíz de una versión NUEVA** y deja la vieja intacta. Las raíces son tuyas: podés leer o ramificar desde cualquiera en cualquier momento.

Una raíz es simplemente un `int`.

Convenciones, contrato del `Node`, el pool y el monoide de ejemplo: [README.md](README.md).

## API

Todas las operaciones toman la raíz de forma **explícita**. No hay estado implícito de "versión actual": vos manejás el historial.

```cpp
PersistentSegmentTree<T> st(n, q)        // reserva el pool, los dos argumentos obligatorios
vector<int> roots = {st.build(a)};       // el patron de uso
```

| método | costo | nodos nuevos | qué hace |
|---|---|---|---|
| `st.build(a)` | O(n) | `2n − 1` | raíz de la versión inicial |
| `st.build()` | **O(1)** | **0** | raíz de la versión todo-`T()` |
| `st.set(root, p, x)` | O(log n) | `C + 1` | raíz nueva; la vieja sigue válida |
| `st.copy(root)` | **O(1)** | **1** | duplica una versión |
| `st.get(root, p)` | O(log n) | 0 | la `T` en `p` de esa versión |
| `st.prod(root, l, r)` | O(log n) | 0 | pliega `a[l..r]` de esa versión |
| `st.all_prod(root)` | **O(1)** | 0 | pliega todo de esa versión |
| `st.nodes_used()` | O(1) | — | cuánto del pool se consumió |

con `C = ceil(log2 n)`. **Las consultas no crean nodos**, solo `set`, `build` y `copy`.

## Por qué `build()` sin argumentos es gratis

El **nodo 0 es el nodo nulo**: representa un subárbol enteramente `T()`. `build()` devuelve `0` y no aloca nada, y un `set` desde ahí materializa solo el camino que toca.

Eso tiene una consecuencia que conviene tener presente: si tu problema necesita *ceros de verdad* y `T()` no es tu cero, arrancá de `build(vector<T>(n, T(0)))`, no de `build()`.

## Memoria

```
max_nodes(n, q) = 2n + (ceil(log2 n) + 1) * q + 1
```

Pesimista: asume que **cada** consulta es un `set`, que es lo más caro, y cubre **un** `build`. Si vas a hacer más de un `build`, sumalos aparte.

Medido con un `T` de 40 bytes (el `Node` de 5 campos del ejemplo), o sea 48 bytes por nodo interno:

| n | q | nodos usados | estructura | pico | build | `q` sets | `q` prods |
|---|---|---|---|---|---|---|---|
| 200 000 | 200 000 | 4 137 847 | 189.4 MB | 208.1 MB | 0.006 s | 0.228 s | 0.362 s |
| 1 000 000 | 1 000 000 | 22 951 213 | 1050.6 MB | 1121.0 MB | 0.050 s | 1.836 s | 3.443 s |

**El cuello de botella es la memoria, nunca el tiempo.** A 256 MB el techo práctico es `q ≈ 2.7·10⁵` con `n = 2·10⁵` (unos 21 nodos por `set`). Con un `T` de 8 bytes el techo sube proporcionalmente.

## Ejemplo

Una lista de arreglos con máxima suma de subarreglo por rango: set en un punto del arreglo `k`, consulta sobre el arreglo `k`, y clonar el arreglo `k` (el `Node` está en el [README](README.md#a-máxima-suma-de-un-subarreglo-con-el-vacío-permitido)):

```cpp
int n, q; cin >> n >> q;
vector<Node> a(n);
for (Node& x : a) { ll t; cin >> t; x = Node(t); }
PersistentSegmentTree<Node> st(n, q);
vector<int> roots = {st.build(a)};
while (q--) {
    int type, k; cin >> type >> k; k--;
    if (type == 1) { int p; ll x; cin >> p >> x; p--;
                     roots[k] = st.set(roots[k], p, Node(x)); }
    else if (type == 2) { int l, r; cin >> l >> r; l--, r--;
                          cout << st.prod(roots[k], l, r).best << "\n"; }
    else roots.push_back(st.copy(roots[k]));
}
```

Fijate que `roots[k] = st.set(roots[k], ...)` **reemplaza** la versión `k` en tu vector, mientras que `roots.push_back(st.copy(...))` **agrega** una. Esa diferencia es todo el control de historial que necesitás: el template no decide nada por vos.

## Por qué `reserve` y no `assign` con un contador

La alternativa habitual es predimensionar el arreglo de nodos y llevar un `timer` que avanza con cada creación. Medí las dos:

- **Tiempo**: inconsistente, 1.17×/1.39×/0.78× según la corrida. No hay ganador.
- **Memoria**: `reserve` usa **41–42% menos**, porque solo las páginas tocadas entran en el working set.

La ganancia del `reserve` es memoria, no velocidad — y en esta estructura la memoria es justo el recurso escaso.

## Si `p` se va de rango

El assert lo caza. Un `set` con `p = 10⁸` sobre un árbol construido con `n = 2` dispara `assert(0 <= p && p < n)` antes de tocar nada. Esta estructura **no** es sparse: `n` es un `int` y el pool se dimensionó para él. Si necesitás coordenadas gigantes, es [`SparseSegmentTree`](SparseSegmentTree.md).

## Verificación

- Contra Kadane de fuerza bruta: **107 100 rangos** sobre `n = 1..34`, junto con `SegmentTree` y `SparseSegmentTree` usando el mismo `Node`.
- **212 940 rangos** leídos desde **todas** las versiones del historial, ramificando desde raíces arbitrarias (no solo desde la última).

Ese segundo test es el que importa acá: una implementación que comparte nodos mal puede dar bien sobre la versión actual y mal sobre las viejas.

**Sin link de juez todavía.** Hay una solución escrita para CSES *Range Queries and Copies* usando este template, verificada localmente pero no enviada.
