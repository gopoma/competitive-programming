# SparseSegmentTree

Igual que [`SegmentTree`](SegmentTree.md) — monoide $(S, \cdot, e)$, `T()` es $e$ y `operator+` es
$\cdot$ — pero **los nodos se crean recién cuando se los toca**, así que el largo puede ser
$10^{18}$ sin comprimir coordenadas.

Dado un largo $n$ (que puede no entrar en un `int`), procesa en $O(\log n)$: asignar, calcular el
producto de un intervalo, y buscar un borde por descenso. Los índices son `long long`.

**Todos los rangos son cerrados, `[l, r]`, y no pueden ser vacíos**: `assert(0 <= l && l <= r && r < n)`.
Catálogo de nodos en [README.md](README.md).

**Pool**: hay que declarar de antemano cuántas operaciones vas a hacer.

$$\texttt{max\_nodes}(n, q) = (\lceil \log_2 n \rceil + 1)\,q + 1$$

No hay costo de construcción: un árbol de $10^{18}$ recién instanciado tiene **un** nodo.

## Constructor

```cpp
SparseSegmentTree<T> st(long long len, long long max_ops);
```

Reserva el pool para un árbol de largo `len` y `max_ops` operaciones que creen nodos.

**Restricciones**: $len \ge 1$, $max\_ops \ge 0$. · **Complejidad**: $O(1)$ — solo reserva.

## max_nodes

```cpp
static long long SparseSegmentTree<T>::max_nodes(long long len, long long max_ops)
```

Devuelve cuántos nodos va a reservar el constructor con esos parámetros, para presupuestar memoria
antes de instanciar.

**Complejidad**: $O(1)$.

## set

```cpp
void st.set(long long pos, T val)
```

`a[pos] = val`, materializando el camino hasta `pos` si hacía falta.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(\log n)$, y crea hasta
$\lceil \log_2 n \rceil + 1$ nodos.

## get

```cpp
T st.get(long long pos) const
```

Devuelve `a[pos]`, o `T()` si esa posición nunca se tocó.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## prod

```cpp
T st.prod(long long l, long long r) const
```

Devuelve `a[l] + ... + a[r]`.

**Restricciones**: $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## all_prod

```cpp
T st.all_prod() const
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
vector<T> st.dump() const
```

Devuelve los `n` elementos en orden, incluyendo los que nunca se tocaron (que valen `T()`), para
depurar. Hace `assert(n <= DUMP_MAX)` con `DUMP_MAX = 10'000'000`, porque con el `n` real de un
sparse el vector no cabría.

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

### Suma de rango sobre coordenadas gigantes

Sin comprimir, sin ordenar las consultas, y sin saber de antemano qué índices van a aparecer:

```cpp
SparseSegmentTree<NodeSum> st(1'000'000'000'000'000'000LL, q);

st.set(123456789012345LL, NodeSum(7));
st.set(999999999999999LL, NodeSum(3));
cout << st.prod(0, 1'000'000'000'000'000LL).sum << "\n";   // 10
```

### Conteo de puntos en un rango (compresión implícita)

```cpp
SparseSegmentTree<NodeSum> st(LIM, q);
vector<long long> cuantos;                      // o un unordered_map si se repiten

for(auto x : puntos) {
    st.set(x, NodeSum(1));                      // o acumular si hay repetidos
}

cout << st.prod(lo, hi).sum << "\n";
```

### $k$-ésimo punto, sin comprimir

```cpp
long long p = st.max_right(0, n - 1, [&](const NodeSum& v) { return v.sum < k; });
cout << p + 1 << "\n";                          // la coordenada del k-esimo
```

### Primer índice $\ge l$ con $a_j \ge x$ sobre un dominio enorme

```cpp
long long p = st.max_right(l, n - 1, [&](const NodeMx& v) { return v.mx < x; });
cout << (p == n - 1 ? -1 : p + 1) << "\n";
```

Entre dos posiciones materializadas el predicado es **constante**, así que el descenso salta los
tramos vacíos de una: el costo es $O(\log n)$ aunque el rango barra $10^{18}$ índices.

### Prefijo más largo de $[l, r]$ con suma $\le S$

```cpp
long long p = st.max_right(l, r, [&](const NodeSum& v) { return v.sum <= S; });
cout << p - l + 1 << "\n";                      // el largo, sin if
```
