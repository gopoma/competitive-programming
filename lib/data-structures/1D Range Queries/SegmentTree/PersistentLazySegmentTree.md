# PersistentLazySegmentTree

[`PersistentSegmentTree`](PersistentSegmentTree.md) más updates de rango: **cada `apply` también
devuelve la raíz de una versión nueva**. Mismo contrato de `Node` y `LazyUpdate` que
[`LazySegmentTree`](LazySegmentTree.md) — `Node()` es $e$, `operator+` es $\cdot$, `LazyUpdate()`
es $\mathrm{id}$, `LazyUpdate::operator*=` es $\circ$, y `Node::operator*=(const LazyUpdate&)` es
la aplicación. El `Node` tiene que llevar su propio largo si el mapeo lo necesita.

Dado un largo $n$, procesa en $O(\log n)$: asignar, aplicar un mapeo a un intervalo, consultar el
producto de un intervalo de cualquier versión, y buscar un borde por descenso.

**Todos los rangos son cerrados, `[l, r]`, y no pueden ser vacíos**: `assert(0 <= l && l <= r && r < n)`.
Catálogo de nodos en [README.md](README.md).

**Pool**: el factor 4 sale de que un `apply` de rango toca hasta cuatro caminos.

$$\texttt{max\_nodes}(n, q) = 2n + 4(\lceil \log_2 n \rceil + 1)\,q + 1$$

> El lazy **no se baja con `push`**: eso escribiría en nodos compartidos y corrompería las
> versiones viejas. Lo pendiente viaja como parámetro en el descenso, así que todas las lecturas
> son `const`.

## Constructor

```cpp
PersistentLazySegmentTree<Node, LazyUpdate> st(int len, long long max_ops);
```

Reserva el pool para un árbol de largo `len` y `max_ops` operaciones que creen versiones.

**Restricciones**: $len \ge 1$, $max\_ops \ge 0$. · **Complejidad**: $O(1)$ — solo reserva.

## max_nodes

```cpp
static long long PersistentLazySegmentTree<Node, LazyUpdate>::max_nodes(int len, long long max_ops)
```

Devuelve cuántos nodos va a reservar el constructor con esos parámetros, para presupuestar memoria
antes de instanciar.

**Complejidad**: $O(1)$.

## build

```cpp
(1) int st.build()
(2) int st.build(const vector<Node>& init)
```

- (1): la versión "todo en `Node()`", que **no gasta un solo nodo** del pool.
- (2): la versión inicializada con `init`, que cuesta $2n$ nodos.

Las dos devuelven la raíz.

**Restricciones**: (2) `init.size() == n`. · **Complejidad**: (1) $O(1)$, (2) $O(n)$.

## set

```cpp
int st.set(int root, int pos, Node val)
```

Devuelve la raíz de una versión nueva, idéntica a `root` salvo que `a[pos] = val`.

**Restricciones**: `root` válido, $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## apply

```cpp
(1) int st.apply(int root, int pos, LazyUpdate upd)
(2) int st.apply(int root, int l, int r, LazyUpdate upd)
```

Devuelve la raíz de una versión nueva con `upd` aplicado a `a[pos]` (1) o a todo `a[l..r]` (2).

**Restricciones**: (1) $0 \le pos < n$; (2) $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## get

```cpp
Node st.get(int root, int pos) const
```

Devuelve el `a[pos]` de la versión `root`.

**Restricciones**: `root` válido, $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## prod

```cpp
Node st.prod(int root, int l, int r) const
```

Devuelve `a[l] + ... + a[r]` en la versión `root`.

**Restricciones**: `root` válido, $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## all_prod

```cpp
Node st.all_prod(int root) const
```

Devuelve `a[0] + ... + a[n-1]` en la versión `root`.

**Complejidad**: $O(1)$.

## max_right

```cpp
template <class F> int st.max_right(int root, int l, int r, F pred) const
```

Devuelve el **mayor** $p \in [l, r]$ tal que `pred(prod(root, l, p))` es cierto, o `l - 1` si
ninguno lo cumple.

**Restricciones**: $0 \le l \le r < n$, `pred` monótono sobre el rango y sin efectos de lado. ·
**Complejidad**: $O(\log n)$.

## min_left

```cpp
template <class F> int st.min_left(int root, int l, int r, F pred) const
```

Devuelve el **menor** $p \in [l, r]$ tal que `pred(prod(root, p, r))` es cierto, o `r + 1` si
ninguno lo cumple.

**Restricciones**: las mismas, con `pred` monótono al **decrecer** $p$. ·
**Complejidad**: $O(\log n)$.

## dump

```cpp
vector<Node> st.dump(int root) const
```

Devuelve los `n` elementos de la versión `root` en orden, con el lazy ya resuelto, para depurar.

**Complejidad**: $O(n)$.

## copy

```cpp
int st.copy(int root)
```

Devuelve otra raíz que apunta al mismo contenido, sin copiar nada.

**Complejidad**: $O(1)$.

## size / nodes_used

```cpp
int st.size() const
long long st.nodes_used() const
```

El largo del árbol, y cuántos nodos del pool se consumieron — para depurar el presupuesto.

**Complejidad**: $O(1)$.

---

### Los centinelas

`l - 1` y `r + 1` están elegidos para que el largo del tramo salga **sin un `if`**:
`p - l + 1` y `r - p + 1`. Con el centinela los dos dan $0$, y como el rango es cerrado y no
vacío, el centinela nunca es un índice válido.

## Examples

### Historial de updates de rango

```cpp
PersistentLazySegmentTree<NodeSumLazy, LazyAdd> st(n, q);
vector<int> ver;
ver.push_back(st.build(a));

for(int i = 0; i < q; i++) {
    ver.push_back(st.apply(ver.back(), l, r, LazyAdd(v)));
}

cout << st.prod(ver[t], l, r).sum << "\n";      // la suma como estaba en el tiempo t
```

### Deshacer: volver a una versión anterior

No hace falta nada especial, porque ninguna versión se destruye:

```cpp
int actual = ver.back();
actual = ver[ver.size() - 3];                   // tres pasos atras, en O(1)
```

### Ramificar: dos futuros desde el mismo pasado

```cpp
int base = st.build(a);
int ramaA = st.apply(base, 0, n / 2, LazyAdd(5));
int ramaB = st.apply(base, n / 2, n - 1, LazyAdd(-5));
// base sigue intacto, y las dos ramas son independientes
```

### Primer $j \ge l$ con $a_j \ge x$ en una versión vieja

```cpp
int p = st.max_right(ver[t], l, n - 1, [&](const NodeMxLazy& v) { return v.mx < x; });
cout << (p == n - 1 ? -1 : p + 1) << "\n";
```

### Prefijo más largo de $[l, r]$ con suma $\le S$, en la versión `t`

```cpp
int p = st.max_right(ver[t], l, r, [&](const NodeSumLazy& v) { return v.sum <= S; });
cout << p - l + 1 << "\n";                      // el largo, sin if
```

---

## Hasta dónde llega

Intel Core Ultra 7 155U, g++ 13.2.0 `-O2 -DNDEBUG`, proceso fijado a un core con prioridad alta,
**un proceso por corrida**. Las celdas que entran en 8 s son el mínimo de 3 corridas; las que se
pasan son una sola, porque afinar un número que ya no sirve es tiempo tirado.

> **Las celdas pesadas son órdenes de magnitud, no valores precisos.** La grilla entera tardó
> ~1.5 h y la máquina deriva térmicamente: una celda del treap que la grilla midió en 5.7 s dio
> 9.3–12.3 s al re-medirla después. Lo que **sí** es robusto es el veredicto (entra / no entra) y
> la forma de la matriz; el número exacto de una celda de más de 5 s no lo es.

Marcas, con las referencias **5 s** y **1024 MiB**:

| | en tiempo | en memoria |
|---|---|---|
| sin marca | entra | entra |
| `~` | 4–6.5 s: en el borde, medí tu caso | más de 820 MiB, o sea 80% del límite |
| `!` | se pasa de 5 s | se pasa de 1024 MiB |
| `≫` | no se corrió: con una `q` menor ya se había ido muy lejos, y el tiempo crece con `q` | — |
| `✕` | no terminó o no pudo reservar el pool | — |

`Node` de 16 B, `LazyUpdate` de 8 B, `InternalNode` de 32 B. Carga: 25% `apply` de rango creando versión, 50% `prod` sobre una versión al azar, 25% `max_right`.

### Tiempo total (build + consultas)

| n \ q | 10⁵ | 2·10⁵ | 5·10⁵ | 10⁶ | 2·10⁶ | 5·10⁶ | 10⁷ |
|---|---|---|---|---|---|---|---|
| **10⁵** | 180 ms | 459 ms | 1.6 s | 3.2 s | 9.4 s `!` | 26.3 s `!` | 56.5 s `!` |
| **2·10⁵** | 280 ms | 540 ms | 1.5 s | 4.2 s `~` | 11.8 s `!` | 31.8 s `!` | `≫` |
| **5·10⁵** | 279 ms | 586 ms | 2.1 s | 4.7 s `~` | 12.1 s `!` | 36.2 s `!` | `≫` |
| **10⁶** | 312 ms | 715 ms | 2.2 s | 5.3 s `~` | 13.2 s `!` | 37.3 s `!` | `≫` |
| **2·10⁶** | 469 ms | 1.0 s | 2.2 s | 5.1 s `~` | 11.6 s `!` | 36.3 s `!` | `≫` |
| **5·10⁶** | 437 ms | 879 ms | 2.7 s | 5.8 s `~` | 14.3 s `!` | 36.3 s `!` | `≫` |
| **10⁷** | 666 ms | 1.1 s | 2.6 s | 6.1 s `~` | 15.8 s `!` | 42.3 s `!` | `≫` |

### Pico de memoria en MiB

`PeakWorkingSetSize` del proceso entero, así que **incluye el vector de entrada**, que es lo que de verdad vas a tener en memoria.

| n \ q | 10⁵ | 2·10⁵ | 5·10⁵ | 10⁶ | 2·10⁶ | 5·10⁶ | 10⁷ |
|---|---|---|---|---|---|---|---|
| **10⁵** | 58 | 104 | 241 | 469 | 926 `~` | 2297 `!` | 4580 `!` |
| **2·10⁵** | 69 | 117 | 264 | 507 | 995 `~` | 2457 `!` | — |
| **5·10⁵** | 95 | 148 | 306 | 569 | 1095 `!` | 2672 `!` | — |
| **10⁶** | 137 | 192 | 359 | 637 | 1194 `!` | 2863 `!` | — |
| **2·10⁶** | 216 | 275 | 451 | 744 | 1331 `!` | 3092 `!` | — |
| **5·10⁶** | 449 | 512 | 701 | 1015 `~` | 1644 `!` | 3530 `!` | — |
| **10⁷** | 834 `~` | 900 `~` | 1097 `!` | 1427 `!` | 2086 `!` | 4063 `!` | — |

**La más cara de las siete, por lejos, y la única donde la memoria se agota antes que el tiempo.** El techo de tiempo es $q = 5\cdot10^5$ (1.5–2.7 s), pero mirá la fila $n = 10^7$: con ese mismo $q = 5\cdot10^5$ ya son **1097 MiB**, o sea que se pasa de memoria en una celda que entra cómoda en tiempo. A $q = 5\cdot10^6$ el pico va de 2.2 a 4.0 GiB, y la columna $q = 10^7$ no se corrió más allá de la primera fila porque con `q` menor ya se había ido a 36 s.

Contra el `LazySegmentTree` no persistente, a $n = q = 10^6$: **5.3 s contra 390 ms y 637 MiB contra 60**, o sea 14x el tiempo y 11x la memoria. El factor 4 del pool (un `apply` de rango toca hasta cuatro caminos) se multiplica por el `InternalNode` de 32 B.

Si necesitás $q \ge 10^6$ con updates de rango **y** persistencia, mirá si el problema sale offline antes de pelear con esto.
