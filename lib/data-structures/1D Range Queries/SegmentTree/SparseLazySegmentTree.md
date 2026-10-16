# SparseLazySegmentTree

[`SparseSegmentTree`](SparseSegmentTree.md) más updates de rango: nodos creados al tocarlos, largo
hasta $10^{18}$, y `apply(l, r, upd)` en $O(\log n)$.

El contrato del `Node` es el único distinto de la familia: **no** es `operator*=`, es

```cpp
void apply(const LazyUpdate& f, long long len)
```

porque el árbol **le pasa el largo**. Un nodo sparse puede representar un tramo gigante que nunca
se materializó, así que no puede llevar su propio `size`. El `LazyUpdate` sí es igual al de
[`LazySegmentTree`](LazySegmentTree.md): `LazyUpdate()` es $\mathrm{id}$ y `operator*=` es $\circ$.
Catálogo en [README.md](README.md).

**Todos los rangos son cerrados, `[l, r]`, y no pueden ser vacíos**: `assert(0 <= l && l <= r && r < n)`.
Los índices son `long long`.

**Pool**: el factor 4 sale de que un `apply` de rango toca hasta cuatro caminos.

$$\texttt{max\_nodes}(n, q) = 4(\lceil \log_2 n \rceil + 1)\,q + 1$$

> El lazy **no se baja con `push`**: eso materializaría nodos durante una lectura. Lo pendiente
> viaja como parámetro en el descenso, así que todas las lecturas son `const`.

## Constructor

```cpp
SparseLazySegmentTree<Node, LazyUpdate> st(long long len, long long max_ops);
```

Reserva el pool para un árbol de largo `len` y `max_ops` operaciones que creen nodos.

**Restricciones**: $len \ge 1$, $max\_ops \ge 0$. · **Complejidad**: $O(1)$ — solo reserva.

## max_nodes

```cpp
static long long SparseLazySegmentTree<Node, LazyUpdate>::max_nodes(long long len, long long max_ops)
```

Devuelve cuántos nodos va a reservar el constructor con esos parámetros, para presupuestar memoria
antes de instanciar.

**Complejidad**: $O(1)$.

## set

```cpp
void st.set(long long pos, Node val)
```

`a[pos] = val`, materializando el camino hasta `pos` si hacía falta.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## apply

```cpp
(1) void st.apply(long long pos, LazyUpdate upd)
(2) void st.apply(long long l, long long r, LazyUpdate upd)
```

- (1): `a[pos] = upd(a[pos])`.
- (2): `a[i] = upd(a[i])` para todo `i` en `[l, r]`.

**Restricciones**: (1) $0 \le pos < n$; (2) $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## get

```cpp
Node st.get(long long pos) const
```

Devuelve `a[pos]`, con los `apply` pendientes ya resueltos.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## prod

```cpp
Node st.prod(long long l, long long r) const
```

Devuelve `a[l] + ... + a[r]`.

**Restricciones**: $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## all_prod

```cpp
Node st.all_prod() const
```

Devuelve `a[0] + ... + a[n-1]`.

**Complejidad**: $O(1)$.

## max_right

```cpp
template <class F> long long st.max_right(long long l, long long r, F pred) const
```

Devuelve el **mayor** $p \in [l, r]$ tal que `pred(prod(l, p))` es cierto, o `l - 1` si ninguno lo
cumple.

**Restricciones**: $0 \le l \le r < n$, `pred` monótono sobre el rango y sin efectos de lado. ·
**Complejidad**: $O(\log n)$.

## min_left

```cpp
template <class F> long long st.min_left(long long l, long long r, F pred) const
```

Devuelve el **menor** $p \in [l, r]$ tal que `pred(prod(p, r))` es cierto, o `r + 1` si ninguno lo
cumple.

**Restricciones**: las mismas, con `pred` monótono al **decrecer** $p$. ·
**Complejidad**: $O(\log n)$.

## dump

```cpp
vector<Node> st.dump() const
```

Devuelve los `n` elementos en orden, incluyendo los tramos que nunca se materializaron (con los
`apply` pendientes ya aplicados), para depurar. Hace `assert(n <= DUMP_MAX)` con
`DUMP_MAX = 10'000'000`.

**Complejidad**: $O(n)$.

## size / nodes_used

```cpp
long long st.size() const
long long st.nodes_used() const
```

El largo del árbol, y cuántos nodos del pool se materializaron — para depurar el presupuesto.

**Complejidad**: $O(1)$.

---

### Los centinelas

`l - 1` y `r + 1` están elegidos para que el largo del tramo salga **sin un `if`**:
`p - l + 1` y `r - p + 1`. Con el centinela los dos dan $0$, y como el rango es cerrado y no
vacío, el centinela nunca es un índice válido.

## Examples

### Add y suma de rango sobre coordenadas gigantes

El `Node` recibe el largo, así que no necesita `size`:

```cpp
struct LazyAdd {
    long long a = 0;
    LazyAdd() {}
    LazyAdd(long long x) : a(x) {}
    LazyAdd& operator*=(const LazyAdd& f) { a += f.a; return *this; }
};

struct NodeSum {
    long long sum = 0;
    NodeSum() {}
    NodeSum(long long x) : sum(x) {}
    friend NodeSum operator+(const NodeSum& a, const NodeSum& b) { return NodeSum(a.sum + b.sum); }
    void apply(const LazyAdd& f, long long len) { sum += f.a * len; }   // el largo lo da el arbol
};

SparseLazySegmentTree<NodeSum, LazyAdd> st(1'000'000'000'000'000'000LL, q);
st.apply(1'000'000, 2'000'000'000'000LL, LazyAdd(3));
cout << st.prod(0, 5'000'000'000'000LL).sum << "\n";
```

### Pintar intervalos y contar

Con un `LazyUpdate` de assign, `apply(l, r, assign(1))` pinta y `prod` cuenta lo pintado:

```cpp
st.apply(l, r, LazyUpdate::assign(1));
cout << st.prod(0, n - 1).sum << "\n";          // cuantas posiciones quedaron pintadas
```

### Primer índice $\ge l$ con $a_j \ge x$ tras varios add de rango

```cpp
long long p = st.max_right(l, n - 1, [&](const NodeMx& v) { return v.mx < x; });
cout << (p == n - 1 ? -1 : p + 1) << "\n";
```

Entre dos posiciones materializadas el predicado es **constante**, así que el descenso salta los
tramos vacíos de una: el costo es $O(\log n)$ aunque el rango barra $10^{18}$ índices. Eso vale
también cuando el tramo vacío tiene un `apply` pendiente — el `Node` lo resuelve con el largo que
le pasa el árbol.

### Prefijo más largo de $[l, r]$ con suma $\le S$

```cpp
long long p = st.max_right(l, r, [&](const NodeSum& v) { return v.sum <= S; });
cout << p - l + 1 << "\n";                      // el largo, sin if
```

### Sufijo más largo de $[l, r]$ con suma $\le S$

```cpp
long long p = st.min_left(l, r, [&](const NodeSum& v) { return v.sum <= S; });
cout << r - p + 1 << "\n";
```
