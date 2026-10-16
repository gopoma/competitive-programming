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

Medido, no estimado: Intel Core Ultra 7 155U, g++ 13.2.0 `-O2 -DNDEBUG`, proceso fijado a un
core con prioridad alta, **un proceso por corrida** y el mínimo de 3. El pico de memoria es
`PeakWorkingSetSize` del proceso entero, así que **incluye el vector de entrada**, que es lo que
de verdad vas a tener en memoria. La fila del techo también está medida: es la `q` más grande que
entró en 1 s, buscada a mano, no extrapolada de las otras filas.

`Node` de 16 B, `LazyUpdate` de 8 B, `InternalNode` de 32 B. Carga: 25% `apply` de rango creando versión, 50% `prod` sobre una versión al azar, 25% `max_right`.

| n | q | build | consultas | **total** | **pico** | ¿entra en 1 s / 1024 MiB? |
|---|---|---|---|---|---|---|
| 10⁴ | 10⁵ | 0.3 ms | 213.7 ms | **214 ms** | **41 MiB** · 6.0M nodos | sí |
| 10⁴ | 5·10⁵ | 0.3 ms | 1278.6 ms | **1279 ms** | **183 MiB** · 30.0M nodos | **no**, se pasa de 1 s |
| 10⁵ | 10⁵ | 3.3 ms | 296.2 ms | **300 ms** | **58 MiB** · 7.4M nodos | sí |
| 10⁵ | 5·10⁵ | 3.5 ms | 1770.7 ms | **1774 ms** | **241 MiB** · 36.2M nodos | **no**, se pasa de 1 s |
| 10⁶ | 10⁵ | 29.4 ms | 397.9 ms | **427 ms** | **136 MiB** · 10.4M nodos | sí |
| 10⁶ | 5·10⁵ | 32.2 ms | 2425.6 ms | **2458 ms** | **359 MiB** · 44.0M nodos | **no**, se pasa de 1 s |
| 10⁶ | 10⁶ | 30.4 ms | 5918.7 ms | **5949 ms** | **636 MiB** · 86.0M nodos | **no**, se pasa de 1 s |
| 10⁶ | **2·10⁵** | 30.0 ms | 874.0 ms | **904 ms** | **192 MiB** · 18.8M nodos | **el techo medido** |

Las referencias son los límites típicos de un problema: **1 s** y **1024 MiB**. Si tu problema da
2 s o 256 MiB, escalá.

**La más cara de las siete, por lejos.** El factor 4 del pool se paga en todo: a $n = q = 10^6$ son 86 M de nodos, 637 MiB y **5.9 s**. El techo medido a $n = 10^6$ es $q = 2\cdot10^5$ — siete veces menos que el `LazySegmentTree` no persistente. Si necesitás $q = 10^6$ con updates de rango **y** persistencia, esta estructura no te sirve: buscá si el problema se puede resolver offline.
